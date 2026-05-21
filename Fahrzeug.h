

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include <string>
#include <iostream>
#include <iomanip>

#include "Simulationsobjekt.h"
#include "SimuClient.h"

// Forward-Deklarationen für die Klassen Verhalten, Fahren und Parken
class Verhalten;
class Fahren;
class Parken;
class Weg;

extern double dGlobaleZeit; // Globale Zeit, die in der Simulation verwendet wird

class Fahrzeug : public Simulationsobjekt{
public:
    // Default-Konstruktor: Initialisiert ein Fahrzeug ohne Name und Maximalgeschwindigkeit
    Fahrzeug();

    // Konstruktor mit Namen für das Fahrzeug
    Fahrzeug(const std::string& name);

    // Konstruktor mit Namen und Maximalgeschwindigkeit für das Fahrzeug
    Fahrzeug(const std::string& name, double maxGeschwindigkeit);

    // Destruktor: Bereinigt das Fahrzeug-Objekt
    virtual ~Fahrzeug();

    // Copy-Konstruktor verbieten
    Fahrzeug(const Fahrzeug&) = delete;

    // Zuweisungsoperator definieren
    Fahrzeug& operator=(const Fahrzeug& zuweisen);

    // Gibt die Fahrzeugdaten aus
    virtual void vAusgeben(std::ostream& os) const override;

    // Gibt die Kopfzeile für die Fahrzeugausgabe aus
    static void vKopf();

    // Simuliert das Verhalten des Fahrzeugs und berechnet zurückgelegte Strecke
    virtual void vSimulieren() override;

    // Simuliert das Tanken des Fahrzeugs
    virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());

    // Gibt die aktuelle Geschwindigkeit des Fahrzeugs zurück
    virtual double dGeschwindigkeit() const;

    // Überlädt den Operator '<' zum Vergleichen von Fahrzeugen basierend auf der Gesamtstrecke
    bool operator<(const Fahrzeug& vergleich) const;

    // Setzt das Fahrzeug auf eine neue Strecke zum Fahren
    void vNeueStrecke(Weg& weg);

    // Setzt das Fahrzeug auf eine neue Strecke zum Parken oder Fahren
    void vNeueStrecke(Weg& weg, double startZeit);

    // Gibt die aktuelle Abschnittsstrecke des Fahrzeugs zurück
    double getAbschnittStrecke() const;

    // Virtuelle Methode für das Zeichnen des Fahrzeugs auf einem Weg
    virtual void vZeichnen(const Weg&);

	virtual void vEinlesen(std::istream& i);

protected:
    double p_dMaxGeschwindigkeit = 0; // Maximale Geschwindigkeit des Fahrzeugs
    double p_dGesamtStrecke = 0; // Gesamte Strecke, die das Fahrzeug zurückgelegt hat
    double p_dGesamtZeit = 0; // Gesamte Zeit, die das Fahrzeug gefahren ist
    double p_dAbschnittStrecke = 0; // Zurückgelegte Strecke auf dem aktuellen Weg
    double p_dZurueckgelegteStrecke = 0; // Zurückgelegte Strecke im aktuellen Simulationszeitraum
    double p_dGeschwindigkeit = 0;


    // Verhalten des Fahrzeugs (z. B. Fahren oder Parken)
    std::unique_ptr<Verhalten> p_pVerhalten;
};

#endif /* FAHRZEUG_H_ */
