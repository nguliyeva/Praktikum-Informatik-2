

#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include <exception>
#include "Fahrzeug.h"
#include "Weg.h"

class Fahrausnahme : public std::exception {
public:
    // Konstruktor: Initialisiert die Fahrausnahme mit einem Fahrzeug und einem Weg
    Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg);

    // Reine virtuelle Funktion zur Bearbeitung der Ausnahme
    virtual void vBearbeiten() = 0;

    // Destruktor: Bereinigt das Fahrausnahme-Objekt
    virtual ~Fahrausnahme();

protected:
    // Referenz auf das betroffene Fahrzeug
    Fahrzeug& p_fahrzeug;

    // Referenz auf den betroffenen Weg
    Weg& p_weg;
};

#endif /* FAHRAUSNAHME_H_ */
