

#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme{
public:
    // Überschreibt die Methode vBearbeiten aus der Basisklasse Fahrausnahme
    void vBearbeiten() override;

    // Konstruktor der Klasse Losfahren, der ein Fahrzeug und einen Weg als Parameter erwartet
    Losfahren(Fahrzeug& fahrzeug, Weg& weg);

    // Destruktor der Klasse Losfahren
    virtual ~Losfahren();
};

#endif /* LOSFAHREN_H_ */
