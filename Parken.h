

#ifndef PARKEN_H_
#define PARKEN_H_

#include "Verhalten.h"

class Parken : public Verhalten {
public:
    // Konstruktor der Klasse Parken, der einen Weg und eine Startzeit erwartet
    Parken(Weg& weg, double startZeit);

    // Destruktor der Klasse Parken
    virtual ~Parken();

    // Überschreibt die Methode dStrecke aus der Basisklasse Verhalten
    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;

private:
    double p_startZeit; // Startzeit des Parkens
};

#endif /* PARKEN_H_ */
