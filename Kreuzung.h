

#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#include <list>
#include <iostream>
#include <vector>
#include <memory>
#include "Simulationsobjekt.h"
#include "Tempolimit.h"

class Weg;
class Fahrzeug;

class Kreuzung : public Simulationsobjekt {
public:

    Kreuzung();
    Kreuzung(std::string name, double tankstelle = 0);
    virtual ~Kreuzung();

    // Verbindet zwei Kreuzungen mit einem Hin- und Rückweg
    static void vVerbinde(
        std::string hinweg,
        std::string rueckweg,
        double wegLaenge,
        std::shared_ptr<Kreuzung> start,
        std::shared_ptr<Kreuzung> ziel,
        Tempolimit tempolimit,
        bool ueberholverbot
    );

    // Tanken des Fahrzeugs an der Kreuzung
    void vTanken(Fahrzeug& fahrzeug);

    // Nimmt ein Fahrzeug ohne Startzeit an der Kreuzung an
    void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug);

    // Nimmt ein Fahrzeug mit einer Startzeit an der Kreuzung an
    void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double zeit);

    // Simuliert die Aktivitäten auf den Wegen, die von der Kreuzung ausgehen
    void vSimulieren() override;

    // Gibt das verbleibende Tankvolumen der Kreuzung zurück
    double getTankstelle() const;

    // Wählt einen zufälligen Weg (nicht den Rückweg) von der Kreuzung
    std::shared_ptr<Weg> pZufaelligerWeg(const Weg& pWeg) const;

    // Ausgabe der Kreuzungsdaten
    void vAusgeben(std::ostream& os) const override;

    // Einlesen der Kreuzungsdaten aus einem Eingabestrom
    void vEinlesen(std::istream& i);

    static void vKopf();

private:
    std::vector<std::shared_ptr<Weg>> p_pWege; // Liste der Wege, die von der Kreuzung ausgehen
    //da ein Weg nicht eindeutig einer einzelnen Kreuzung gehört, sondern von mehreren Objekten
    //(z. B. Kreuzungen, Fahrzeugen, Simulation) gemeinsam genutzt wird.
    double p_dTankstelle = 0; // Tankvolumen der Kreuzung
};

#endif /* KREUZUNG_H_ */
