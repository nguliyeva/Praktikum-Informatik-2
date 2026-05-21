

#ifndef VERHALTEN_H_
#define VERHALTEN_H_

#include "Weg.h"
#include "Fahrzeug.h"

// Die abstrakte Basisklasse Verhalten beschreibt das allgemeine Verhalten eines Fahrzeugs auf einem Weg.
// Sie dient als Grundlage für spezifische Verhaltensweisen wie Fahren und Parken.
class Verhalten {
public:
    // Konstruktor: Initialisiert das Verhalten mit einem bestimmten Weg
    Verhalten(Weg& weg);

    // Destruktor
    virtual ~Verhalten();

    // Rein virtuelle Methode dStrecke: Berechnet die zurückgelegte Strecke des Fahrzeugs
    // und ist von den abgeleiteten Klassen zu implementieren
    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;

    // Getter-Methode, die den Weg zurückgibt, auf dem sich das Fahrzeug befindet
    Weg& getWeg() const;

protected:
    // Referenz auf den Weg, auf dem das Fahrzeug sich befindet
    Weg& p_pWeg;
};

#endif /* VERHALTEN_H_ */
