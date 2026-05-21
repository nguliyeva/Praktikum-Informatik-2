
#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <list>
#include <memory>

class Simulationsobjekt {
public:
    // Konstruktoren
    Simulationsobjekt();  // Standard-Konstruktor
    Simulationsobjekt(const std::string& name);  // Konstruktor mit Name
    virtual ~Simulationsobjekt();  // Destruktor

    // Copy-Konstruktor verbieten (diese Klasse kann nicht kopiert werden)
    Simulationsobjekt(const Simulationsobjekt&) = delete;

    // Vergleichsoperator für ID
    bool operator==(const Simulationsobjekt& vergleichID);

    // Virtuelle Methoden, die von abgeleiteten Klassen überschrieben werden können
    virtual void vAusgeben(std::ostream& os) const;  // Gibt das Simulationsobjekt aus
    virtual void vSimulieren() = 0;  // Virtuelle Methode für die Simulation

	virtual void vEinlesen(std::istream& in = std::cin);

    // Getter-Methoden
    std::string getName() const;  // Gibt den Namen des Simulationsobjekts zurück
    int getID() const;  // Gibt die ID des Simulationsobjekts zurück
	virtual double getZeit();

    static void vKopf();  // Gibt die Kopfzeilen für die Ausgabe von Simulationsobjekten aus

private:
    static int p_iMaxID;  // Statische Klassenvariable, um die ID für jedes Simulationsobjekt hochzuzählen

protected:
    std::string p_sName;  // Name des Simulationsobjekts
    const int p_iID;  // Eindeutige ID des Simulationsobjekts
    double p_dZeit = 0;  // Die Zeit, zu der das Objekt zuletzt simuliert wurde
};

// Überladener Operator << zur Ausgabe von Simulationsobjekten
std::ostream& operator<<(std::ostream& os, const Simulationsobjekt& simulationsobjekt);

std::istream& operator>>(std::istream& in, Simulationsobjekt& simulationsobjekt);

#endif /* SIMULATIONSOBJEKT_H_ */
