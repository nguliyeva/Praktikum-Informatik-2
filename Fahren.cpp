

#include "Fahren.h"
#include "Fahrzeug.h"
#include "Streckenende.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "PKW.h"


Fahren::Fahren(Weg& weg) : Verhalten(weg) {
}

Fahren::~Fahren() {
}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) {
    // Berechnet die zurückgelegte Strecke basierend auf der Geschwindigkeit und dem Zeitintervall
    double dStrecke = aFzg.dGeschwindigkeit() * dZeitIntervall;

    // Prüfen, ob das Fahrzeug noch Platz auf dem Weg hat
    if ((p_pWeg.getLaenge() - aFzg.getAbschnittStrecke()) > 0) {

        // Überprüfen, ob das Fahrzeug die Schranke (z.B. Überholverbot oder Hindernis) erreicht oder überschreitet
        if ((aFzg.getAbschnittStrecke() + dStrecke) > p_pWeg.getSchranke()) {

            // Wenn die Schranke erreicht wird, wird die Strecke entsprechend gekürzt
            dStrecke = p_pWeg.getSchranke() - aFzg.getAbschnittStrecke();
            return dStrecke;
        }
        else {
            // Wenn die Schranke nicht erreicht wird, wird sie auf die neue Position des Fahrzeugs gesetzt
            p_pWeg.setSchranke(aFzg.getAbschnittStrecke() + dStrecke);
            return dStrecke;
        }
    }
    else {
        // Wenn das Ende des Weges erreicht ist, wird eine Ausnahme (Streckenende) geworfen
        throw Streckenende(aFzg, p_pWeg);
    }
}
