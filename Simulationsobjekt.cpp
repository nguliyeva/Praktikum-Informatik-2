

#include "Simulationsobjekt.h"

// Statische Variable zur Verwaltung der IDs aller Simulationsobjekte
int Simulationsobjekt::p_iMaxID = 0; // Initialisierung der statischen ID-Variable

// Standard-Konstruktor
Simulationsobjekt::Simulationsobjekt()
    : p_iID(p_iMaxID++) { // ID wird automatisch hochgezählt
    // Kein Name gesetzt, ID wird erzeugt
}

// Konstruktor mit Name
Simulationsobjekt::Simulationsobjekt(const std::string& name)
	: p_sName(name), p_iID(p_iMaxID++) { // ID wird automatisch hochgezählt
	// Wenn der Name übergeben wird, wird das Simulationsobjekt mit Name erstellt
	std::cout << "Neues Simulationsobjekt erstellt: " << p_sName
			  << " mit ID " << p_iID << std::endl << std::endl;
}

// Destruktor
Simulationsobjekt::~Simulationsobjekt() {
	// Gibt aus, dass ein Simulationsobjekt gelöscht wurde
	std::cout << "Simulationsobjekt gelöscht: " << p_sName
			  << " mit ID " << p_iID << std::endl << std::endl;
}

// Ausgabe von Kopfzeilen (Überschriften)
void Simulationsobjekt::vKopf() {
	// Ausgabe von Spaltenüberschriften
	std::cout << std::resetiosflags(std::ios::right)
			  << std::setiosflags(std::ios::left)
			  << std::setw(5) << "ID"
			  << std::setw(10) << "Name"
			  << std::setw(22) << "MaxGeschwindigkeit"
			  << std::setw(18) << "Gesamtstrecke"
			  << std::setw(28) << "Aktuelle Geschwindigkeit"
			  << std::setw(20) << "Gesamtverbrauch"
			  << std::setw(30) << "Tankinhalt" << std::endl
			  << std::string(120, '-') << std::endl;
}

// Ausgabe der grundlegenden Informationen über das Simulationsobjekt
void Simulationsobjekt::vAusgeben(std::ostream& os) const {
	os << std::setiosflags(std::ios::left)
	   << std::setw(4) << p_iID
	   << std::setw(18) << p_sName;
}

void Simulationsobjekt::vEinlesen(std::istream& in)
{
	if (p_sName != "")
	{
		throw std::runtime_error("Es wurde versucht, in ein vorhandenes Objekt einzulesen. Der Vorgang wird abgebrochen!");
	}

	in >> p_sName;
}

// Simulationsmethode
void Simulationsobjekt::vSimulieren() {
	// Gibt eine Nachricht aus, dass das Objekt simuliert wird
	std::cout << "Simuliere das Objekt: " << p_sName << std::endl;
}

// Überladen des << Operators zur Ausgabe des Simulationsobjekts
std::ostream& operator<<(std::ostream& os, const Simulationsobjekt& simulationsobjekt) {
	simulationsobjekt.vAusgeben(os);
	return os;
}

std::istream& operator>>(std::istream& in, Simulationsobjekt& simulationsobjekt){
	simulationsobjekt.vEinlesen(in);
	return in;
}

// Vergleichsoperator zur Überprüfung der ID
bool Simulationsobjekt::operator==(const Simulationsobjekt& simulationsobjekt) {
	// Wenn die IDs übereinstimmen, gibt true zurück
	return (this->p_iID == simulationsobjekt.p_iID);
}

// Getter für den Namen des Objekts
std::string Simulationsobjekt::getName() const {
	// Rückgabe des Namens des Objekts
	return p_sName;
}

// Getter für die ID des Objekts
int Simulationsobjekt::getID() const {
	// Rückgabe der eindeutigen ID des Objekts
	return p_iID;
}

double Simulationsobjekt::getZeit()
{
	return p_dZeit;
}
