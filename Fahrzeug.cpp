
#include <iomanip>
#include <iostream>
#include <cmath>

#include "Fahrzeug.h"
#include "PKW.h"
#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"

double dGlobaleZeit = 0;

// Default-Konstruktor: Initialisiert ein Fahrzeug ohne Name und Maximalgeschwindigkeit
Fahrzeug::Fahrzeug() : Simulationsobjekt(){
	std::cout << "Name vom Fahrzeug: " << p_sName << std::endl
			  << "ID vom Fahrzeug: " << p_iID << std::endl << std::endl;
}

// Konstruktor mit Namen für das Fahrzeug
Fahrzeug::Fahrzeug(const std::string& name) : Simulationsobjekt(name){
}

// Konstruktor mit Namen und Maximalgeschwindigkeit für das Fahrzeug
Fahrzeug::Fahrzeug(const std::string& name, double maxGeschwindigkeit)
    : Simulationsobjekt(name), // Konstruktor mit Namen und Maximalgeschwindigkeit
      p_dMaxGeschwindigkeit((maxGeschwindigkeit>0) ? maxGeschwindigkeit : 0)
{
}

// Destruktor gibt an, dass ein Fahrzeug gelöscht wurde
Fahrzeug::~Fahrzeug() {
}

// Gibt die Fahrzeugdaten aus
void Fahrzeug::vAusgeben(std::ostream& os) const {
	Simulationsobjekt::vAusgeben(os);
	os << std::fixed << std::setprecision(2)
	   << std::setw(20) << p_dMaxGeschwindigkeit
	   << std::setw(20) << p_dGesamtStrecke
	   << std::setw(25) << dGeschwindigkeit(); // Aktuelle Geschwindigkeit anzeigen
}

// Überschrift für die Ausgabe
void Fahrzeug::vKopf() {
	std::cout << std::resetiosflags(std::ios::right)
			  << std::setiosflags(std::ios::left)
			  << std::setw(5) << "ID"
			  << std::setw(10) << "Name"
			  << std::setw(22) << "MaxGeschwindigkeit"
			  << std::setw(18) << "Gesamtstrecke"
			  << std::setw(28) << "Aktuelle Geschwindigkeit"
			  << std::setw(20) << "Gesamtverbrauch"
			  << std::setw(30) << "Tankinhalt" << std::endl
			  << std::string(120, '-') << std::endl;
}

// Simuliert das Verhalten des Fahrzeugs und berechnet zurückgelegte Strecke
void Fahrzeug::vSimulieren() {
    double dZeitDifferenz = dGlobaleZeit - p_dZeit;

    if(fabs(dGlobaleZeit - p_dZeit) > 1e-6){
        // Berechne die zurückgelegte Strecke basierend auf dem Verhalten (Verhalten)
        if (p_pVerhalten != nullptr) {
            p_dZurueckgelegteStrecke = p_pVerhalten->dStrecke(*this, dZeitDifferenz);
        }

        else {
        	p_dZurueckgelegteStrecke = dGeschwindigkeit() * dZeitDifferenz;
        }

        // Aktualisiere die Gesamtstrecke und die Abschnittsstrecke
        p_dAbschnittStrecke += p_dZurueckgelegteStrecke;
        p_dGesamtStrecke += p_dZurueckgelegteStrecke;

        // Aktualisiere die Gesamtzeit
        p_dGesamtZeit += dZeitDifferenz;
        p_dZeit = dGlobaleZeit;
    }
}

// Gibt die aktuelle Geschwindigkeit des Fahrzeugs zurück
double Fahrzeug::dGeschwindigkeit() const {
	return p_dMaxGeschwindigkeit; // Aktuelle Geschwindigkeit des Fahrzeugs
}

// Simuliert das Tanken des Fahrzeugs
double Fahrzeug::dTanken(double dMenge) {
	// Fahrräder und Fahrzeuge ohne Tank tanken nicht.
	return 0;
}

// Überlädt den Operator '<' zum Vergleichen von Fahrzeugen basierend auf der Gesamtstrecke
bool Fahrzeug::operator<(const Fahrzeug& vergleich) const {
    return p_dGesamtStrecke < vergleich.p_dGesamtStrecke; // Vergleiche nach Gesamtstrecke
}

// Überlädt den Zuweisungsoperator '=' zum Kopieren eines Fahrzeuges
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& zuweisen) {
	if (this != &zuweisen) {
		// Stammdaten kopieren
		p_sName = zuweisen.p_sName;
		p_dMaxGeschwindigkeit = zuweisen.p_dMaxGeschwindigkeit;
		// p_iID wird nicht kopiert, da es einzigartig sein muss
	}
	return *this;
}

// Setzt das Fahrzeug auf eine neue Strecke für das Fahren
void Fahrzeug::vNeueStrecke(Weg& weg){
	// AbschnittStrecke auf 0 setzen
	p_dAbschnittStrecke = 0;
    p_dZeit = dGlobaleZeit;
	// neues Verhalten für den aktuellen Weg erzeugen
	p_pVerhalten = std::make_unique<Fahren>(weg);
}

// Setzt das Fahrzeug auf eine neue Strecke für das Parken oder Fahren
void Fahrzeug::vNeueStrecke(Weg& weg, double startZeit){
    p_dAbschnittStrecke = 0;
    p_dZeit = dGlobaleZeit;
	if(startZeit >= 0){
    	p_pVerhalten = std::make_unique<Parken>(weg, startZeit);
    }

    else{
    	p_pVerhalten = std::make_unique<Fahren>(weg);
    }
}

// Gibt die aktuelle Abschnittsstrecke des Fahrzeugs zurück
double Fahrzeug::getAbschnittStrecke() const
{
	return p_dAbschnittStrecke;
}

// Leere Funktion zum Zeichnen des Fahrzeugs auf einem Weg
void Fahrzeug::vZeichnen(const Weg&){
}

void Fahrzeug::vEinlesen(std::istream& i)
{
	Simulationsobjekt::vEinlesen(i);
	i >> this->p_dMaxGeschwindigkeit;
}
