

#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_

#include "Fahrausnahme.h"
#include "Kreuzung.h"

class Streckenende : public Fahrausnahme {
public:
    // Konstruktor: Initialisiert die Ausnahme mit einem Fahrzeug und einem Weg
    Streckenende(Fahrzeug& fahrzeug, Weg& weg);

    // Destruktor
    virtual ~Streckenende();

    // Überschreibt die Methode vBearbeiten, um die Ausnahme zu verarbeiten, wenn ein Fahrzeug das Ende des Weges erreicht.
    void vBearbeiten() override;
};

#endif /* STRECKENENDE_H_ */
