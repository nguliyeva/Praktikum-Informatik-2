

#include "PKW.h"
#include "Verhalten.h"

PKW::PKW(std::string name) : Fahrzeug(name){
}

PKW::PKW(const std::string& name, double maxGeschwindigkeit, double verbrauch, double tankvolumen)
    : Fahrzeug(name, maxGeschwindigkeit), p_dVerbrauch(verbrauch),
	  p_dTankvolumen(tankvolumen), p_dTankinhalt(tankvolumen/2){
	// TODO Auto-generated constructor stub
}

PKW::~PKW() {
	// TODO Auto-generated destructor stub
}

double PKW::dTanken(double dMenge)
{
	double dAlteTankinhalt = p_dTankinhalt;
	if (dMenge < p_dTankvolumen)
		p_dTankinhalt = dMenge;
	else
		p_dTankinhalt = p_dTankvolumen;

	return p_dTankinhalt - dAlteTankinhalt;
}

void PKW::vAusgeben(std::ostream& os) const {
    // Aufruf der Basisklasse vAusgeben
    Fahrzeug::vAusgeben(os);
    // PKW-spezifische Daten ausgeben
    os << std::resetiosflags(std::ios::right)
       << std::setiosflags(std::ios::left)
       << std::setw(20) << p_dGesamtverbrauch
       << std::setw(20) << p_dTankinhalt;
}

void PKW::vSimulieren(){
    if (p_dTankinhalt > 1e-6){
        // Berechnen des Verbrauchs
    	// PKWs fahren nur, wenn Kraftstoff vorhanden ist
		// Strecken-Zähler zwischenspeichern
		double dGesamtStreckeTemp = p_dGesamtStrecke;

		// Fahrzeug fahren lassen
		Fahrzeug::vSimulieren();

		// Verbrauch nachrechnen
		p_dGesamtverbrauch += (p_dGesamtStrecke - dGesamtStreckeTemp) * p_dVerbrauch / 100;
		p_dTankinhalt -= (p_dGesamtStrecke - dGesamtStreckeTemp) * p_dVerbrauch / 100;

        // Überprüfen, ob der Tank leer ist
        if(p_dTankinhalt < 0){
        	p_dTankinhalt = 0;
        }
    }

    else{
    	// Wenn der Tank leer ist
    	std::cout << "PKW " << p_sName << " steht, weil der Tank leer ist. Bitte nachtanken." << std::endl;
  	  	std::cout << std::string(120, '-') << std::endl;
        p_dZeit = dGlobaleZeit;
    }
}

double PKW::dGeschwindigkeit() const{

	if(p_pVerhalten == nullptr){
		return Fahrzeug::dGeschwindigkeit();
	}

	Weg& weg = p_pVerhalten->getWeg();
	double grenze = weg.getTempolimit();

	// Überprüfen, ob die Geschwindigkeit des Fahrzeugs das Tempolimit überschreitet
	if (p_dMaxGeschwindigkeit > grenze){
		return grenze;
	}

	else{
		return p_dMaxGeschwindigkeit;
	}

	if (p_dTankinhalt <= 0.0) {
	        return 0.0;
	    }
	    return Fahrzeug::dGeschwindigkeit();  // veya sende hız nasıl hesaplanıyorsa
	}


double PKW::getTankinhalt() const{
	return p_dTankinhalt;
}

void PKW::vZeichnen(const Weg& weg){
    double relPos = p_dAbschnittStrecke / weg.getLaenge();
    bZeichnePKW(p_sName, weg.getName(), relPos, dGeschwindigkeit(), p_dTankinhalt);
}

void PKW::vEinlesen(std::istream& i){
	Fahrzeug::vEinlesen(i);
	i >> p_dGesamtverbrauch >> p_dTankinhalt;
}
