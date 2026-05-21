

#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include "Streckenende.h"
#include "Losfahren.h"
#include "Kreuzung.h"


Weg::Weg() : Simulationsobjekt(){
	// TODO Auto-generated constructor stub
}

Weg::Weg(const std::string& name, double laenge, Tempolimit tempolimit,
		 bool ueberholverbot, std::shared_ptr<Kreuzung> pZielKreuzung)
		 : Simulationsobjekt(name), p_dLaenge(laenge), p_eTempolimit(tempolimit),
		   p_bUeberholverbot(ueberholverbot), p_pZielkreuzung(pZielKreuzung){
}

Weg::~Weg() {
	// TODO Auto-generated destructor stub
}

double Weg::getTempolimit() const {
    return static_cast<double>(p_eTempolimit);
}

double Weg::getLaenge() const{
	return p_dLaenge;
}

void Weg::vSimulieren() {
   	p_pFahrzeug.vAktualisieren();
   	p_dVirtuelleSchranke = p_dLaenge;

    for (auto fahrzeug = p_pFahrzeug.begin(); fahrzeug != p_pFahrzeug.end(); ++fahrzeug){
    	try{
            // Zuerst wird überprüft, ob das Fahrzeug das Ende des Weges erreicht hat
			(*fahrzeug)->vSimulieren();
			std::cout << *(*fahrzeug) << std::endl;
        }

        catch (Fahrausnahme& ausnahme){
            ausnahme.vBearbeiten();  // Bearbeitung der Ausnahme

        }
    }
	p_pFahrzeug.vAktualisieren();
	vZeichnen();
}

void Weg::vAusgeben(std::ostream& os) const{

	Weg::vKopf(std::cout);
	Simulationsobjekt::vAusgeben(os);
	os << std::setw(7) << " : "  << std::setw(5) << p_dLaenge << " ( ";

	for(const auto& fahrzeug : p_pFahrzeug){
			os << fahrzeug->getName() << " ";
	}

	os << ")" << std::endl;
}

void Weg::vKopf(std::ostream& os){
    os << std::resetiosflags(std::ios::right)
       << std::setiosflags(std::ios::left)
	   << "ID " << std::setw(15)
	   << "| Name" << std::setw(10)
	   << "| Laenge" << std::setw(10)
	   << "| Fahrzeuge" << std::endl
	   << std::string(90, '-') << std::endl;
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug){
	if(fahrzeug != nullptr){
	    fahrzeug->vNeueStrecke(*this);
	    p_pFahrzeug.push_back(std::move(fahrzeug));
	}
    }

// neue überladene Funktion
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startZeit) {
	if(fahrzeug != nullptr){
	    fahrzeug->vNeueStrecke(*this, startZeit);
	    p_pFahrzeug.push_front(std::move(fahrzeug));
	}
}


const vertagt::VListe<std::unique_ptr<Fahrzeug>>& Weg::getFahrzeuge() const{
    return p_pFahrzeug;
}

// Funktion zum Entfernen und Zurückgeben des Fahrzeugs
std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug) {
    for (auto it = p_pFahrzeug.begin(); it != p_pFahrzeug.end(); ++it) {
    	if (*it != nullptr)
    	{
    		if (**it == fahrzeug) { // Vergleiche das Fahrzeug
            std::unique_ptr<Fahrzeug> ptr = std::move(*it); // Move den unique_ptr
            p_pFahrzeug.erase(it); // Lösche das Fahrzeug aus der Liste
            return ptr; // Rückgabe des Zeigers
        }
    	}
    }
    std::cout<<"Fahrzeug nicht gefunden"<<std::endl;
    return nullptr; // Fahrzeug nicht gefunden
}

void Weg::vZeichnen(){
    if (!p_pFahrzeug.empty())
    {
        for (auto& it : p_pFahrzeug)
        {
            it->vZeichnen(*this);
        }
    }
}

double Weg::getSchranke() const {
    // Wenn ein Überholverbot besteht, wird die virtuelle Schranke zurückgegeben,
    // die die maximal erlaubte Position für Fahrzeuge auf dem Weg angibt
    if (p_bUeberholverbot == true) {
        return p_dVirtuelleSchranke;
    }
    // Andernfalls wird die volle Länge des Wegs zurückgegeben
    else {
        return p_dLaenge;
    }
}

void Weg::setSchranke(double dSchranke) {
    // Setzt die Position der virtuellen Schranke, die anzeigt, bis wohin Fahrzeuge fahren dürfen
    p_dVirtuelleSchranke = dSchranke;
}

/* Bei weak_ptr erfolgt der Zugriff auf das Objekt durch Aufruf der Funktion
   lock(), um zu testen, ob der zugehörige shared_ptr noch gültig ist. */
std::shared_ptr<Kreuzung> Weg::getZielkreuzung() const {
    // Gibt einen shared_ptr zur Zielkreuzung zurück, falls dieser noch gültig ist
    return p_pZielkreuzung.lock();
}

std::shared_ptr<Weg> Weg::getRueckWeg() const {
    // Gibt einen shared_ptr zum Rückweg zurück, falls dieser noch gültig ist
    return p_pRueckweg.lock();
}

void Weg::setRueckweg(std::shared_ptr<Weg> rueckweg) {
    // Setzt den Rückweg
    p_pRueckweg = rueckweg;
}
