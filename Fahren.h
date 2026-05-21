

#ifndef FAHREN_H_
#define FAHREN_H_

#include "Verhalten.h"

class Fahren : public Verhalten {
public:
    // Konstruktor: Initialisiert das Fahren-Verhalten mit einem gegebenen Weg
    Fahren(Weg& weg);

    // Destruktor: Bereinigt das Fahren-Objekt
    virtual ~Fahren();

    // Berechnet die Strecke, die ein Fahrzeug innerhalb eines bestimmten Zeitintervalls zurücklegt
    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};

#endif /* FAHREN_H_ */
