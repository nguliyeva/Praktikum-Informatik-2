

#ifndef PKW_H_
#define PKW_H_

#include "Fahrzeug.h"
#include <limits>
#include <iomanip>

class PKW : public Fahrzeug{
public:

    PKW(){
    }
    PKW(std::string name);
    // Konstruktor für PKW mit optionalem Tankvolumen (Standardwert 55)
    PKW(const std::string& name, double maxGeschwindigkeit, double verbrauch, double tankvolumen = 55);

    // Virtueller Destruktor
    virtual ~PKW();

    // Gibt die Fahrzeuginformationen aus
    void vAusgeben(std::ostream& os) const override;

    // Simuliert die Bewegung des Fahrzeugs
    void vSimulieren() override;

    // Tanken des Fahrzeugs, wenn Menge übergeben wird oder volltanken
    double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;

    // Berechnet die Geschwindigkeit unter Berücksichtigung des Tempolimits
    double dGeschwindigkeit() const override;

    // Gibt den aktuellen Tankinhalt zurück
    double getTankinhalt() const;

    // Zeichnet das Fahrzeug auf dem angegebenen Weg
    void vZeichnen(const Weg& weg) override;

    void vEinlesen(std::istream& i);

protected:
    double p_dVerbrauch = 0; // Verbrauch in Litern pro 100 km
    double p_dTankvolumen = 0; // Maximales Tankvolumen in Litern
    double p_dTankinhalt = 0; // Aktueller Tankinhalt in Litern
    double p_dGesamtverbrauch = 0; // Gesamtverbrauch in Litern
};

#endif /* PKW_H_ */
