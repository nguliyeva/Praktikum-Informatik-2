

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug{
public:
	Fahrrad();
    Fahrrad(std::string name);

    // Konstruktor: Initialisiert ein Fahrrad mit einem Namen und einer maximalen Geschwindigkeit
    Fahrrad(const std::string& name, double maxGeschwindigkeit);

    // Destruktor: Bereinigt das Fahrrad-Objekt
    virtual ~Fahrrad();

    // Gibt die Fahrzeugdaten aus (überschreibt die Funktion der Basisklasse)
    void vAusgeben(std::ostream& os) const override;

    // Simuliert das Verhalten des Fahrrads (überschreibt die Funktion der Basisklasse)
    void vSimulieren() override;

    // Berechnet die aktuelle Geschwindigkeit des Fahrrads
    double dGeschwindigkeit() const override;

    // Zeichnet das Fahrrad auf dem Weg, basierend auf der relativen Position und Geschwindigkeit
    void vZeichnen(const Weg& weg) override;

    void vEinlesen(std::istream& i);
};

#endif /* FAHRRAD_H_ */
