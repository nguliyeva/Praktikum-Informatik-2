

#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include <random>
#include <iomanip>
#include <memory>
#include <iostream>

Kreuzung::Kreuzung(): Simulationsobjekt() {
}

Kreuzung::Kreuzung(std::string name, double tankstelle)
    : Simulationsobjekt(name), p_dTankstelle(tankstelle) {
    // TODO Automatisch generierter Konstruktor
}

Kreuzung::~Kreuzung() {
    // TODO Automatisch generierter Destruktor
}

// Verbindet zwei Kreuzungen über Hin- und Rückwege
void Kreuzung::vVerbinde(std::string hinweg, std::string rueckweg, double wegLaenge,
                         std::shared_ptr<Kreuzung> start, std::shared_ptr<Kreuzung> ziel,
                         Tempolimit tempolimit, bool ueberholverbot) {

    // Erzeugt Hinweg und Rückweg und verbindet Start- und Zielkreuzungen
    std::shared_ptr<Weg> Hinweg = std::make_shared<Weg>(hinweg, wegLaenge, tempolimit, ueberholverbot, ziel);
    std::shared_ptr<Weg> Rueckweg = std::make_shared<Weg>(rueckweg, wegLaenge, tempolimit, ueberholverbot, start);

    // Setzt den Rückweg für beide Richtungen //yönünü belirler
    Hinweg->setRueckweg(Rueckweg);
    Rueckweg->setRueckweg(Hinweg);

    // Fügt den Hinweg zur Wege-Liste der Startkreuzung hinzu
    start->p_pWege.push_back(std::move(Hinweg));

    // Fügt den Rückweg zur Wege-Liste der Zielkreuzung hinzu
    ziel->p_pWege.push_back(std::move(Rueckweg));
}

// Tankt ein Fahrzeug an der Kreuzung, falls eine Tankstelle verfügbar ist
void Kreuzung::vTanken(Fahrzeug& fahrzeug) {
    if (p_dTankstelle > 0) {
        double dMenge = fahrzeug.dTanken();
        p_dTankstelle -= dMenge;

        if (p_dTankstelle < 0) {
            p_dTankstelle = 0;
        }
        std::cout << "Getankte Menge: " << dMenge << std::endl;
    }
}

// Annahme eines Fahrzeugs zur Weitergabe an den ersten abgehenden Weg
void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dZeit) {
    if (pFahrzeug != nullptr) {
        vTanken(*pFahrzeug);
        auto it = p_pWege.begin();
        (*it)->vAnnahme(move(pFahrzeug), dZeit);
    }
}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug) {
    if (pFahrzeug != nullptr) {
    	vTanken(*pFahrzeug);
        auto it = p_pWege.begin();
        (*it)->vAnnahme(move(pFahrzeug));
    }
}

// Führt die Simulation für alle abgehenden Wege der Kreuzung aus
void Kreuzung::vSimulieren() {
    for (auto& weg : p_pWege) {
        weg->vSimulieren();
    }
}

// Gibt einen zufälligen Weg zurück, der nicht der Rückweg des übergebenen Wegs ist
std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(const Weg& pWeg) const {
    // Wenn nur ein Weg existiert, wird dieser sofort zurückgegeben
    if (p_pWege.size() == 1) {
        return p_pWege.front();
    }

    // Zeiger auf einen zufällig ausgewählten Weg, der später bestimmt wird
    std::shared_ptr<Weg> pZufaelligerWeg;

    // Initialisierung der Zufallszahlen mit einer festen Seed (zur Reproduzierbarkeit)
    int seed = 0;
    int a = 0, b = p_pWege.size() - 1; // Intervall für die Zufallszahlen
    static std::mt19937 device(seed);  // Zufallsgenerator
    std::uniform_int_distribution<int> dist(a, b); // Verteilung über das Intervall

    // Schleife zur Auswahl eines zufälligen Wegs, der nicht der Rückweg ist
    do {
        int iZaehler = 0; // Zähler zur Auswahl des n-ten Elements
        int iZufallszahl = dist(device); // Generiere eine zufällige Zahl im Intervall [a, b]

        // Durchlaufe die Wege-Liste und wähle den Weg aus, der dem Zufallsindex entspricht
        for (auto it = p_pWege.begin(); it != p_pWege.end(); it++) {
            if (iZaehler == iZufallszahl) {
                pZufaelligerWeg = *it; // Weist den ausgewählten Weg zu
            }
            iZaehler++;
        }
    } while (pZufaelligerWeg == pWeg.getRueckWeg()); // Wiederholen, falls der Rückweg gewählt wurde

    return pZufaelligerWeg; // Gibt den zufällig gewählten, gültigen Weg zurück
}

// Gibt die aktuelle Tankfüllung der Tankstelle an der Kreuzung zurück
double Kreuzung::getTankstelle() const {
    return p_dTankstelle;
}

// Ausgabe der Kreuzungsinformationen
void Kreuzung::vAusgeben(std::ostream& os) const {
    Simulationsobjekt::vAusgeben(os);
    os << std::resetiosflags(std::ios::right)
       << std::setiosflags(std::ios::left)
       << std::setw(50) << p_dTankstelle << std::setw(25);
}

// Ausgabe der Überschriften für die Kreuzungsdaten
void Kreuzung::vKopf() {
    std::cout << std::resetiosflags(std::ios::right)
              << std::setiosflags(std::ios::left)
              << std::setw(5) << "ID"
              << std::setw(15) << "Name"
              << std::setw(30) << "Tankstelle" << std::endl
              << std::string(30, '-') << std::endl;
}

// Einlesen der Kreuzungsdaten
void Kreuzung::vEinlesen(std::istream& i) {
    Simulationsobjekt::vEinlesen(i);
    i >> p_dTankstelle;
}
