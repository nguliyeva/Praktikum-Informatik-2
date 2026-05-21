
#include <cmath>

#include "Parken.h"
#include "Fahren.h"
#include "Losfahren.h"

Parken::Parken(Weg& weg, double startZeit)
    : Verhalten(weg), p_startZeit(startZeit) {
}

Parken::~Parken() {
}

// Berechnet die zurückgelegte Strecke eines Fahrzeugs im Parkmodus
double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
    // Falls die globale Zeit noch kleiner oder gleich der Startzeit minus eine kleine Toleranz ist, bleibt das Fahrzeug geparkt (keine Strecke zurückgelegt)
    if(dGlobaleZeit <= p_startZeit - 1e-6){
        return 0;
    }

    // Andernfalls wird eine Losfahren-Ausnahme ausgelöst
    else{
        throw Losfahren(aFzg, p_pWeg); // Losfahren wird als Ausnahme geworfen
    }
}
