

#ifndef WEG_H_
#define WEG_H_

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include <list>
#include <limits>
#include <memory>
#include "vertagt_liste.h"

// Vorwärtsdeklaration der Klassen Fahrzeug und Fahrausnahme
class Fahrzeug;
class Fahrausnahme;
class Kreuzung;

// Klasse Weg erbt von Simulationsobjekt
class Weg : public Simulationsobjekt {
public:
    Weg();  // Standardkonstruktor
	Weg(const std::string& name, double laenge, Tempolimit tempolimit = Tempolimit::Autobahn, bool bUeberholverbot = true,
			  std::shared_ptr<Kreuzung> pZielKreuzung = nullptr);
    virtual ~Weg();  // Destruktor

    // Getter-Methoden
    double getTempolimit() const;  // Rückgabe des Tempolimits
    double getLaenge() const;  // Rückgabe der Länge des Weges

    // Virtuelle Methoden, die von der Basisklasse überschrieben werden
    void vSimulieren() override;  // Simulation der Fahrzeuge auf dem Weg
    void vAusgeben(std::ostream& os) const override;  // Ausgabe des Weges und der Fahrzeuge
    static void vKopf(std::ostream& os);  // Kopfzeile für die Ausgabe

    // Methoden zum Hinzufügen von Fahrzeugen
    void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug);  // Fahrzeug zum Weg hinzufügen
    void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startZeit); // Überladene Methode zum Hinzufügen mit Startzeit (z.B. Parken oder Fahren)

    // Methode zum Entfernen eines Fahrzeugs vom Weg und Rückgabe des Fahrzeugs
    std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fahrzeug);

    // Getter für die Fahrzeugliste auf dem Weg
    const vertagt::VListe<std::unique_ptr<Fahrzeug>>& getFahrzeuge() const;

    // Methode zum Zeichnen der Fahrzeuge auf dem Weg
    void vZeichnen();

    double getSchranke() const;
    void setSchranke(double dSchranke);

    // Getter für Zielkreuzung und Rückweg
    std::shared_ptr<Kreuzung> getZielkreuzung() const;
    std::shared_ptr<Weg> getRueckWeg() const;
    void setRueckweg(std::shared_ptr<Weg> rueckweg);

private:
	double p_dLaenge = 0.0;
	//std::list<std::unique_ptr<Fahrzeug>> p_pFahrzeug;
    vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeug; // Typ ändern
	Tempolimit p_eTempolimit = Tempolimit::Autobahn;
    bool p_bUeberholverbot = true;
    double p_dVirtuelleSchranke = 0.0;
    double p_dGeschwindigkeit;

    /* Die Variable für den Rückweg (p_pRueckWeg) in der Klasse Weg kann nicht als const deklariert werden,
     * weil der Rückweg erst nach der Initialisierung des Objekts festgelegt wird. */
    const std::weak_ptr<Kreuzung> p_pZielkreuzung; // weak_ptr für die Zielkreuzung
    std::weak_ptr<Weg> p_pRueckweg; // weak_ptr für den Rückweg
};

#endif /* WEG_H_ */
