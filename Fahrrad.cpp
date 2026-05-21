

#include "Fahrrad.h"
#include "Verhalten.h"

Fahrrad::Fahrrad() : Fahrzeug() {}

Fahrrad::Fahrrad(std::string name): Fahrzeug(name){
}

// Konstruktor: Initialisiert ein Fahrrad mit einem Namen und einer maximalen Geschwindigkeit
Fahrrad::Fahrrad(const std::string& name, double maxGeschwindigkeit)
    : Fahrzeug(name, maxGeschwindigkeit) {
	// TODO Automatisch generierter Konstruktor
}

// Destruktor: Bereinigt das Fahrrad-Objekt
Fahrrad::~Fahrrad() {
	// TODO Automatisch generierter Destruktor
}

// Gibt die Fahrzeugdaten aus (überschreibt die Funktion der Basisklasse)
void Fahrrad::vAusgeben(std::ostream& os) const {
	// Aufruf der Basisklasse vAusgeben
    Fahrzeug::vAusgeben(os);
}

// Simuliert das Verhalten des Fahrzeugs
void Fahrrad::vSimulieren(){
    Fahrzeug::vSimulieren();
}

// Berechnet die aktuelle Geschwindigkeit des Fahrrads unter Berücksichtigung einer Abnahme
double Fahrrad::dGeschwindigkeit() const{
    double geschwindigkeit = p_dMaxGeschwindigkeit;
    int anzahlAbnahme = p_dGesamtStrecke / 20;

    // Geschwindigkeit um 10% pro 20 km verringern
    for (int i = 0; i < anzahlAbnahme; ++i) {
        geschwindigkeit *= 0.9; // 10% verringern
        if (geschwindigkeit < 12.0) {
            return 12.0; // minimale Geschwindigkeit
        }
    }
    return geschwindigkeit;
}

// Zeichnet das Fahrrad auf dem Weg, basierend auf der relativen Position und Geschwindigkeit
void Fahrrad::vZeichnen(const Weg& weg){
    double relPos = getAbschnittStrecke() / weg.getLaenge();
    bZeichneFahrrad(getName(), weg.getName(), relPos, dGeschwindigkeit());
}

void Fahrrad::vEinlesen(std::istream& i){
	Fahrzeug::vEinlesen(i);
}
