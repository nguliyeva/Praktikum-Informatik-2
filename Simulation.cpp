

#include "Simulation.h"
#include "Kreuzung.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Fahrzeug.h"
#include "Simulationsobjekt.h"
#include <map>
#include <iostream>
#include <iomanip>
#include <memory>
#include <cstdlib>


Simulation::Simulation() {
    // TODO Automatisch generierter Konstruktor
}

Simulation::~Simulation() {
    // TODO Automatisch generierter Destruktor
}

// Funktion zum Einlesen von Simulationsdaten
#include <sstream>
#include <iostream>
#include <memory>
#include <string>

void Simulation::vEinlesen(std::istream& in, bool bMitGrafik)
{
    if (bMitGrafik) {
        bInitialisiereGrafik(1200, 1200);
    }

    in.exceptions(std::ios_base::failbit | std::ios_base::badbit);

    std::string line;
    int zeile = 0;

    try {
        while (true) {
            try {
                if (!std::getline(in, line)) break;
            } catch (const std::ios_base::failure&) {
                if (in.eof()) break;
                throw;
            }

            ++zeile;

            if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos)
                continue;

            std::istringstream ls(line);
            std::string schluesselWort;
            ls >> schluesselWort;

            if (schluesselWort == "KREUZUNG") {
                auto neueKreuzung = std::make_shared<Kreuzung>();
                ls >> *neueKreuzung;

                if (p_pKreuzung.find(neueKreuzung->getName()) != p_pKreuzung.end())
                    throw std::runtime_error("Kreuzung existiert schon.");

                p_pKreuzung[neueKreuzung->getName()] = neueKreuzung;

                if (bMitGrafik) {
                    int x, y;
                    ls >> x >> y;
                    bZeichneKreuzung(x, y);
                }
            }
            else if (schluesselWort == "STRASSE") {
                std::string nameQ, nameZ, nameW1, nameW2;
                int laenge, limit, ueberhol;
                ls >> nameQ >> nameZ >> nameW1 >> nameW2 >> laenge >> limit >> ueberhol;

                auto itQ = p_pKreuzung.find(nameQ);
                auto itZ = p_pKreuzung.find(nameZ);
                if (itQ == p_pKreuzung.end() || itZ == p_pKreuzung.end())
                    throw std::runtime_error("Kreuzung nicht gefunden.");

                if (limit < 1 || limit > 3)
                    throw std::runtime_error("Ungueltiges Tempolimit.");

                Tempolimit t = (limit == 1) ? Tempolimit::Innerorts
                              : (limit == 2) ? Tempolimit::Landstrasse
                                             : Tempolimit::Autobahn;

                bool bUeberholverbot;
                switch (ueberhol) {
                    case 0: bUeberholverbot = false; break;
                    case 1: bUeberholverbot = true;  break;
                    default:
                        throw std::runtime_error("Ungueltiges Ueberholverbot (nur 0 oder 1 erlaubt).");
                }

                Kreuzung::vVerbinde(nameW1, nameW2, laenge, itQ->second, itZ->second, t, bUeberholverbot);

                if (bMitGrafik) {
                    int anzahl;
                    ls >> anzahl;
                    std::vector<int> coords(2 * anzahl);
                    for (int i = 0; i < 2 * anzahl; i++) ls >> coords[i];
                    bZeichneStrasse(nameW1, nameW2, laenge, anzahl, coords.data());
                }
            }
            else if (schluesselWort == "PKW") {
                std::string sName, nameS;
                double dGeschwindigkeit = 0, dVerbrauch = 0, dTankvolumen = 0, startZeit = 0;

                // WICHTIG: ls benutzen, nicht in
                ls >> sName >> dGeschwindigkeit >> dVerbrauch >> dTankvolumen >> nameS >> startZeit;

                auto it = p_pKreuzung.find(nameS);
                if (it == p_pKreuzung.end())
                    throw std::runtime_error("Die Startkreuzung existiert nicht.");

                auto pkw = std::make_unique<PKW>(sName, dGeschwindigkeit, dVerbrauch, dTankvolumen);
                it->second->vAnnahme(std::move(pkw), startZeit);
            }
            else if (schluesselWort == "FAHRRAD") {
                std::string sName, nameS;
                double dGeschwindigkeit = 0, startZeit = 0;

                // WICHTIG: ls benutzen, nicht in
                ls >> sName >> dGeschwindigkeit >> nameS >> startZeit;

                auto it = p_pKreuzung.find(nameS);
                if (it == p_pKreuzung.end())
                    throw std::runtime_error("Kreuzung existiert nicht.");

                auto fahrrad = std::make_unique<Fahrrad>(sName, dGeschwindigkeit);
                it->second->vAnnahme(std::move(fahrrad), startZeit);
            }
            else {
                throw std::runtime_error("Ungueltiges Schluesselwort: " + schluesselWort);
            }
        } // while
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << " in Zeilennummer: " << zeile << std::endl;
        throw;
    }
}





// Simulationsschleife mit gegebener Dauer und Zeitschritt
void Simulation::vSimulieren(double dDauer, double dZeitschritt) {
    for (dGlobaleZeit = 0; dGlobaleZeit <= dDauer; dGlobaleZeit += dZeitschritt) {

        vSetzeZeit(dGlobaleZeit);

        Fahrzeug::vKopf();
        for (auto& kreuzung : p_pKreuzung) {
            kreuzung.second->vSimulieren(); // Simulation für jede Kreuzung
        }

        std::cout << "Globalezeit :" << dGlobaleZeit << std::endl << std::endl;

        vSleep(500);
    }
}
