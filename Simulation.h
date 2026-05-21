

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "Simulationsobjekt.h"
#include <iostream>
#include <list>
#include <memory>
#include <map>
#include "Kreuzung.h"

class Simulation {
public:
    Simulation();
    virtual ~Simulation();
    // Methode zum Einlesen der Simulationsdaten aus einem Eingabestrom
    // Optional kann die grafische Darstellung aktiviert werden
    void vEinlesen(std::istream& in, bool bMitGrafik = false);

    // Container für alle Kreuzungen in der Simulation
    std::map<std::string, std::shared_ptr<Kreuzung>> p_pKreuzung;

    // Methode zum Starten und Durchführen der Simulation über eine gegebene Dauer
    // Die Simulationsschritte erfolgen mit einem angegebenen Zeitschritt
    void vSimulieren(double dDauer, double dZeitschritt);
};

#endif /* SIMULATION_H_ */
