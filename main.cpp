

#include <iostream>
#include <memory> // für smart pointers
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <exception>
#include <filesystem>
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Simulationsobjekt.h"
#include "Weg.h"
#include "SimuClient.h"
#include <random>
#include "vertagt_liste.h"
#include "vertagt_aktion.h"
#include "Kreuzung.h"
#include "Simulation.h"

using namespace std;
extern double dGlobaleZeit;

void vAufgabe_Probe() {
    Fahrzeug* pF1 = new PKW("Audi", 150, 8);
    dGlobaleZeit = 0.0;
    Fahrzeug::vKopf();
    dGlobaleZeit = 3.0;
    cout << endl << "Globalezeit = " << dGlobaleZeit << endl;
    pF1->vSimulieren();
    std::cout << *pF1 << endl;
    delete pF1;
    char c;
    std::cin >> c;
}

void vAufgabe_1(){

	dGlobaleZeit = 0.0;

	Fahrzeug s1("Auto"); // Deklaration der statischen Variable


	Fahrzeug s2("Bus"); // Deklaration der statischen Variable

	Fahrzeug *d1 = new Fahrzeug("Motorrad"); // Erste dynamische Variable

	Fahrzeug *d2 = new Fahrzeug("LKW"); // Zweite dynamische Variable

	delete d1; // Loeschen vom ersten dynamischen Objekt
	d1 = nullptr;

	delete d2; // Loeschen vom zweiten dynamischen Objekt
	d2 = nullptr;

	// Erstellen von smart pointers mit make_unique
	std::unique_ptr<Fahrzeug> uPtr1 = std::make_unique<Fahrzeug>("Scooter");
	std::unique_ptr<Fahrzeug> uPtr2 = std::make_unique<Fahrzeug>("Fahrrad");

	// Erstellen von smart pointers mit make_shared
	std::shared_ptr<Fahrzeug> sPtr1 = std::make_shared<Fahrzeug>("PKW");
	std::shared_ptr<Fahrzeug> sPtr2 = std::make_shared<Fahrzeug>("LKW");

	// Speichern von einem shared_ptr Objekt in einem weiteren
	std::cout << "Anzahl der Referenzen vor der Zuweisung: " << sPtr1.use_count()
			  << std::endl;
	std::shared_ptr<Fahrzeug> sPtr3 = sPtr1;
	std::cout << "Anzahl der Referenzen nach der Zuweisung: " << sPtr1.use_count()
			  << std::endl << std::endl;

	/* Speichern von einem unique_ptr Objekt in einem weiteren

	std::cout << "Anzahl der Referenzen vor der Zuweisung: " << uPtr1.use_count()
		  << std::endl;
	std::unique_ptr<Fahrzeug> uPtr3 = uPtr1;
	std::cout << "Anzahl der Referenzen nach der Zuweisung: " << uPtr1.use_count()
			  << std::endl << std::endl;

	error: 'class std::unique_ptr<Fahrzeug>' has no member named 'use_count'
	Bei unique_ptr dürfen mehrere Zeiger sich nicht den Besitz des Objekts teilen.
	Deshalb hat die Klasse für unique_ptr die Funktion "use_count" nicht.
	*/

	// Erzeugen von vector<unique_ptr<Fahrzeug>>
	std::vector<std::unique_ptr<Fahrzeug>> uniqueFahrzeugVektor;
	uniqueFahrzeugVektor.push_back(move(uPtr1));
	uniqueFahrzeugVektor.push_back(move(uPtr2));

	/* Welche Fahrzeuge koennen Sie dort speichern?
	 *
	 * In diesem Vektor koennen nur Fahrzeuge gespeichert werden, deren Besitz
	 * eindeutig ist (unique_ptr).
	 *
	 * Wie muessen Sie den Besitzwechsel anzeigen?
	 *
	 * Der Besitzwechsel muss mit der Funktion move() durchgefuehrt werden.
	 * Nach dem Aufruf von move() ist der urspruengliche unique_ptr auf nullptr gesetzt.
	 */

	uniqueFahrzeugVektor.clear();

    std::shared_ptr<Fahrzeug> sPtr4 = std::make_shared<Fahrzeug>("Fahrrad");
    std::shared_ptr<Fahrzeug> sPtr5 = std::make_shared<Fahrzeug>("Motorrad");

	// Erzeugen von vector<shared_ptr<Fahrzeug>>
	std::vector<std::shared_ptr<Fahrzeug>> sharedFahrzeugVektor;
	sharedFahrzeugVektor.push_back(move(sPtr4)); // Der Besitz des Objekts wird auf den anderen getragen.
	sharedFahrzeugVektor.push_back(sPtr5); // Eine zusaetzliche Referenz wird auf dasselbe Objekt erstellt.

	/* Welche Fahrzeuge koennen Sie dort speichern?
	 *
	 * In diesem Vektor koennen nur Fahrzeuge gespeichert werden, die von
	 * mehreren Zeigern referenziert werdern koennen (shared_ptr).
	 *
	 */

	std::cout << "Anzahl der Referenzen von sPtr4: " << sPtr4.use_count() << std::endl;
	std::cout << "Anzahl der Referenzen von sPtr5: " << sPtr5.use_count() << std::endl
			  << std::endl;

	sharedFahrzeugVektor.clear();

	/*
	 * Bitte notieren Sie beim Debuggen,
	 * in welchen Zeilen die jeweiligen Objekte geloescht werden.
	 *
	 * Ohne move(): Das Objekt wird geloescht, wenn der Vektor mit clear() geleert wird
	 * oder am Ende des Scopes. Der Destruktor wird aufgerufen, sobald alle Referenzen
	 * weg sind.
	 *
	 * Mit move(): Das urspruengliche Objekt wird nach dem move() auf nullptr gesetzt.
	 * Der Destruktor wird aufgerufen, sobald auch die letzte Referenz, die das Objekt
	 * nach dem move() besitzt, geloescht wird.
	 *
	 */

    Fahrzeug f1("PKW1", 40);
    Fahrzeug f2("AUTO3", 30);

    Fahrzeug::vKopf();
    f1.vAusgeben(std::cout);
    std::cout << std::endl << std::endl;
    f2.vAusgeben(std::cout);
    std::cout << std::endl
    		  << std::endl;
}

void vAufgabe_1a(){

	std::vector<std::unique_ptr<Fahrzeug>> fahrzeugVektor;

	for(int i=1; i<=3; ++i){
		std::string name;
		double maxGeschwindigkeit;

		std::cout << "Name des " << i << ". Fahrzeugs: ";
		std::cin >> name;

		std::cout << "Maximale Geschwindigkeit des " << i << ". Fahrzeugs: ";
		std::cin >> maxGeschwindigkeit;

		std::cout << std::endl;

		fahrzeugVektor.push_back(std::make_unique<Fahrzeug>(name, maxGeschwindigkeit));

	}

	double dZeittakt = 0.1; // z. Bsp. 6 Minuten
	double dSimulationsdauer = 2; // z. Bsp. 2 Stunden

	Fahrzeug::vKopf();
	for(dGlobaleZeit = 0; dGlobaleZeit < dSimulationsdauer; dGlobaleZeit += dZeittakt){
		for(auto& fahrzeug : fahrzeugVektor){
			fahrzeug->vSimulieren();
			fahrzeug->vAusgeben(std::cout);

			std::cout << std::endl;
	  	  	std::cout << std::string(120, '-') << std::endl;
		}
	}
}

void vAufgabe_2(){

	// Anzahl der zu erzeugenden PKWs und Fahrraeder aus der Konsole einlesen
	int anzahlPKW, anzahlFahrrad;
	std::cout << "Anzahl der PKWs: ";
	std::cin >> anzahlPKW;
	std::cout << "Anzahl der Fahrraeder: ";
	std::cin >> anzahlFahrrad;
	std::cout << std::endl;

	//Vektor für PKWs und Fahrrraeder
	std::vector<std::unique_ptr<Fahrzeug>> fahrzeugVektor;

	//PKWs erstellen und zum Vektor hinzufuegen
	for(int i = 0; i < anzahlPKW; ++i){
		std::string name;
		double maxGeschwindigkeit, verbrauch;
		std::cout << "Name des " << i+1 << ". PkWs: ";
		std::cin >> name;
		std::cout << "Maximale Geschwindigkeit des " << i+1 << ". PKWs: ";
		std::cin >> maxGeschwindigkeit;
		std::cout << "Verbrauch des " << i+1 << ". PKWs: ";
		std::cin >> verbrauch;

		fahrzeugVektor.push_back(std::make_unique<PKW>(name, maxGeschwindigkeit, verbrauch));
	}

	//Fahrraeder erstellen und zum Vektor hinzufuegen
	for(int i = 0; i < anzahlFahrrad; ++i){
		std::string name;
		double maxGeschwindigkeit;
		std::cout << "Name des " << i+1 << ". Fahrrads: ";
		std::cin >> name;
		std::cout << "Maximale Geschwindigkeit des " << i+1 << ". Fahrrads: ";
		std::cin >> maxGeschwindigkeit;

		fahrzeugVektor.push_back(std::make_unique<Fahrrad>(name, maxGeschwindigkeit));
	}

	double dZeittakt = 0.1;
	double dSimulationsdauer = 5; // 5 Stunden
	bool istVollgetankt = false;

	Fahrzeug::vKopf();
	for(dGlobaleZeit = 0; dGlobaleZeit < dSimulationsdauer; dGlobaleZeit += dZeittakt){
		for(auto& fahrzeug : fahrzeugVektor){
			fahrzeug->vSimulieren();
			// Nach 3 Stunden PKWs volltanken
		    if (fabs(dGlobaleZeit - 3.0) < 1e-9 && !istVollgetankt) { // Toleranz für Vergleich
		        for (auto& fahrzeug : fahrzeugVektor) {
		            PKW* pkw = dynamic_cast<PKW*>(fahrzeug.get());
		            if (pkw) {
		                pkw->dTanken(); // volltanken
						//fahrzeug->vAusgeben(std::cout);
		            }
		        }
		        istVollgetankt = true;
		    }
			fahrzeug->vAusgeben(std::cout);
			std::cout << std::endl;
		}
		std::cout << std::string(53, '-') << " Zeit: " << dGlobaleZeit << " h "
			  	  << std::string(53, '-') <<std::endl << std::endl;
	}
}

void vAufgabe_3(){
	// operator <<
	PKW* aPKW = new PKW("Auto", 220, 5);
	Fahrrad* aFahrrad = new Fahrrad("Fahrrad", 30);

	// Ausgabe der Fahrzeuge
	Fahrzeug::vKopf();
	std::cout << *aPKW << std::endl << *aFahrrad << std::endl;
	std::cout << std::endl;

	delete aPKW;
	delete aFahrrad;

	// operator <
    PKW* aPKW2 = new PKW("Motorrad", 220, 2);
    PKW* aPKW3 = new PKW("Scooter", 50, 2);

    dGlobaleZeit = 2;
    aPKW2->vSimulieren(); // Beispielhafte Simulation
    aPKW3->vSimulieren();

    // Vergleich der Gesamtstrecken
    if (*aPKW3 < *aPKW2) {
        std::cout << aPKW3->getName() << " hat eine kürzere Strecke als " << aPKW2->getName() << std::endl;
    }

    else {
        std::cout << aPKW3->getName() << " hat eine längere oder gleich lange Strecke als " << aPKW2->getName() << std::endl;
    }

    std::cout << std::endl;

    delete aPKW2;
    delete aPKW3;

    Fahrzeug original("Auto", 120);
    Fahrzeug anderesFahrzeug("Lastwagen", 80);

    std::cout << "Original Fahrzeug:" << std::endl;
    std::cout << original;
    std::cout << std::endl << std::endl;

    std::cout << "Anderes Fahrzeug vor der Zuweisung:" << std::endl;
    anderesFahrzeug.vAusgeben(std::cout);
    std::cout << std::endl << std::endl;

    anderesFahrzeug = original; // Zuweisungsoperator

    std::cout << "Anderes Fahrzeug nach der Zuweisung:" << std::endl;
    std::cout << anderesFahrzeug;
    std::cout << std::endl << std::endl;
}

void vAufgabe_4(){

	Weg weg("weg", 100.0, Tempolimit::Landstrasse);

	std::cout << "Ausgabe des Weges:" << std::endl;
	std::cout << weg << std::endl;  // <<-Operator wird verwendet
}

void vAufgabe_5(){
    // Erzeuge einen Weg
    Weg weg("Autobahn", 500);

    // Erzeuge Fahrzeuge
    std::unique_ptr<Fahrzeug> pkw1 = std::make_unique<PKW>("Auto", 100, 5);
    std::unique_ptr<Fahrzeug> pkw2 = std::make_unique<PKW>("Motorrad", 90, 4);
    std::unique_ptr<Fahrzeug> fahrrad = std::make_unique<Fahrrad>("Fahrrad", 50);

    // Setze die Fahrzeuge auf den Weg
    weg.vAnnahme(std::move(pkw1));
    weg.vAnnahme(std::move(pkw2), 2); // startet nach 2 Stunden
    weg.vAnnahme(std::move(fahrrad));

    // Simuliere den Weg
    for (dGlobaleZeit = 0; dGlobaleZeit <= 10; dGlobaleZeit++){
    	Fahrzeug::vKopf();
        weg.vSimulieren(); // Simuliert alle Fahrzeuge auf dem Weg
        std::cout << endl;
        std::cout << weg; // Ausgabe nach jedem Simulationsschritt
        std::cout << "Globalezeit = " << dGlobaleZeit << std::endl << std::endl;
    }
}

void vAufgabe_6()
{
    // Grafikfenster initialisieren
    bInitialisiereGrafik(800, 500);

    // Zwei Wege mit Länge 500 km und den entsprechenden Tempolimits
    Weg hin("Hin", 500, Tempolimit::Landstrasse); // Landstraße: 100 km/h
    Weg ruck("Rueck", 500, Tempolimit::Landstrasse); // Innerorts: 50 km/h

    // Koordinaten für eine gerade Straße definieren
    int koordinates[] = {700, 250, 100, 250}; // Einfache gerade Linie zur Demonstration
    bZeichneStrasse(hin.getName(), ruck.getName(), 500, 2, koordinates);

    // Fahrzeuge auf die Wege setzen
    hin.vAnnahme(std::make_unique<PKW>("Auto", 150, 20, 50));  // PKW fährt sofort los
    hin.vAnnahme(std::make_unique<Fahrrad>("f1", 45)); // Fahrrad fährt sofort los
    ruck.vAnnahme(std::make_unique<PKW>("Motorrad", 90, 4), 2);  // PKW startet nach 2 Stunden
    ruck.vAnnahme(std::make_unique<Fahrrad>("f2", 50), 3); // Fahrrad startet nach 3 Stunden
    std::cout << std::endl;

    // Simulationsschleife für 10 Zeiteinheiten, Inkrementierung um 0.25 Stunden
    for (dGlobaleZeit = 0; dGlobaleZeit <= 15; dGlobaleZeit += 0.5){
    	vSetzeZeit(dGlobaleZeit);
        Fahrzeug::vKopf();
    	if(fabs(dGlobaleZeit - 5) <= 1e-6){
    		hin.vAnnahme(make_unique<PKW>("Minivan", 100, 6), 6);
    	}
        // Simulation der Fahrzeuge auf den Wegen
        hin.vSimulieren();
        ruck.vSimulieren();

        // Aktualisierte Zustände der Wege und Fahrzeuge ausgeben
        std::cout << hin << std::endl
                  << ruck;
        std::cout << "Globale Zeit = " << dGlobaleZeit << std::endl << std::endl;

        vSleep(500);  // Pause von 0.5 Sekunden, um jede Zeiteinheit zu visualisieren
    }

    vBeendeGrafik();  // Grafiksession beenden
}

void vAufgabe_6a()
{
    // Erstelle eine Liste von Ganzzahlen
    vertagt::VListe<int> Liste;

    // Füge 10 Zufallszahlen zur Liste hinzu
    for (int i = 0; i <= 10; i++)
    {
        int seed = 0, a = 0, b = 10; // Definiere den Bereich der Zufallszahlen
        static std::mt19937 device(seed); // Erzeuge einen Zufallszahlengenerator
        std::uniform_int_distribution<int> dist(a, b); // Definiere die Verteilung
        int zuf = dist(device); // Generiere eine Zufallszahl
        Liste.push_back(zuf); // Füge die Zufallszahl zur Liste hinzu
        Liste.vAktualisieren(); // Aktualisiere die Liste
    }

    std::cout << "Alle Elemente in der Liste:" << std::endl;
    // Gebe alle Elemente in der Liste aus
    for (auto& it : Liste)
    {
        std::cout << it;
    }

    std::cout << std::endl << std::endl;

    // Entferne alle Elemente größer als 5 aus der Liste
    for (auto it = Liste.begin(); it != Liste.end(); it++)
    {
        if (*it > 5)
        {
        	Liste.erase(it); // Lösche das Element
        }
    }

    std::cout << "Ausgabe der Liste ohne vAktualisieren, nachdem alle Elemente groesser als 5 entfernt wurden"
    		  << std::endl;
    // Gebe die verbleibenden Elemente in der Liste aus
    for (auto& it : Liste)
    {
        std::cout << it;
    }

    std::cout << std::endl;

    std::cout << std::endl << "Liste nach vAktualisieren():" << std::endl;
    Liste.vAktualisieren(); // Aktualisiere die Liste erneut

    // Gebe die aktualisierte Liste aus
    for (auto& it : Liste)
    {
        std::cout << it;
    }

    std::cout << std::endl;

    // Füge eine zufällige Zahl am Ende der Liste hinzu
    int k = 1 + (rand() % 10);
    Liste.push_back(k);

    // Füge eine zufällige Zahl am Anfang der Liste hinzu
    int l = 1 + (rand() % 10);
    Liste.push_front(l);

    Liste.vAktualisieren(); // Aktualisiere die Liste erneut

    std::cout << std::endl
    		  << "Am Anfang und am Ende der Liste noch zwei beliebige Zahlen:"
    		  << std::endl;

    // Gebe die endgültige Liste aus
    for (auto& it : Liste)
    {
        std::cout << it;
    }
}

void vAufgabe_7() {
    // Initialisiert die Grafik mit einer Größe von 1000 x 600 Pixel
    bInitialisiereGrafik(1000, 600);

    // Erstellen von Kreuzungsobjekten mit Namen und optionalem Tankstellenvolumen
    shared_ptr<Kreuzung> kr1 = make_shared<Kreuzung>("K1");
    shared_ptr<Kreuzung> kr2 = make_shared<Kreuzung>("K2", 1000);
    shared_ptr<Kreuzung> kr3 = make_shared<Kreuzung>("K3");
    shared_ptr<Kreuzung> kr4 = make_shared<Kreuzung>("K4");

    // Zeichnen der Kreuzungen an spezifischen Positionen auf dem Bildschirm
    bZeichneKreuzung(680, 40); // Position von Kreuzung K1
    bZeichneKreuzung(680, 300); // Position von Kreuzung K2
    bZeichneKreuzung(680, 570); // Position von Kreuzung K3
    bZeichneKreuzung(320, 300); // Position von Kreuzung K4

    // Verbinden der Kreuzungen durch Straßen mit spezifischen Eigenschaften
    Kreuzung::vVerbinde("W12", "W21", 40, kr1, kr2, Tempolimit::Landstrasse, true); // Straße 1
    Kreuzung::vVerbinde("W23a", "W32a", 115, kr2, kr3, Tempolimit::Autobahn, false); // Straße 2
    Kreuzung::vVerbinde("W23b", "W32b", 40, kr2, kr3, Tempolimit::Innerorts, true); // Straße 3
    Kreuzung::vVerbinde("W24", "W42", 55, kr2, kr4, Tempolimit::Innerorts, true); // Straße 4
    Kreuzung::vVerbinde("W34", "W43", 85, kr3, kr4, Tempolimit::Autobahn, false); // Straße 5
    Kreuzung::vVerbinde("W44a", "W44b", 130, kr4, kr4, Tempolimit::Landstrasse, false); // Straße 6

    // Definition der Straßenverläufe als Koordinaten
    int str1[] = {680, 40, 680, 300};
    int str2[] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
    int str3[] = {680, 300, 680, 570};
    int str4[] = {680, 300, 320, 300};
    int str5[] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
    int str6[] = {320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300};

    // Zeichnen der Straßen auf der Karte basierend auf den definierten Koordinaten
    bZeichneStrasse("W12", "W21", 40, 2, str1);
    bZeichneStrasse("W23a", "W32a", 115, 6, str2);
    bZeichneStrasse("W23b", "W32b", 40, 2, str3);
    bZeichneStrasse("W24", "W42", 55, 2, str4);
    bZeichneStrasse("W34", "W43", 85, 5, str5);
    bZeichneStrasse("W44a", "W44b", 130, 7, str6);

    // Fahrzeuge an der Kreuzung kr1 annehmen (Startpunkt der Simulation)
    kr1->vAnnahme(make_unique<PKW>("Auto1", 120, 10, 200), 2);
    kr1->vAnnahme(make_unique<PKW>("Auto2", 100, 10, 200), 5);
    kr1->vAnnahme(make_unique<Fahrrad>("Fahrrad1", 20), 1);

    // Schleife zur Simulation der Fahrzeugbewegung und Zeitaktualisierung
    std::cout << endl;
    for (dGlobaleZeit = 0; dGlobaleZeit <= 20; dGlobaleZeit += 0.25) {
        vSetzeZeit(dGlobaleZeit);
        Fahrzeug::vKopf();
        kr1->vSimulieren();
        kr2->vSimulieren();
        kr3->vSimulieren();
        kr4->vSimulieren();

        std::cout << "Globale Zeit = " << dGlobaleZeit << std::endl << std::endl;

        vSleep(200); // Kurze Pause für visuelles Feedback
    }
    vBeendeGrafik(); // Grafik beenden
}

void vAufgabe_8() {
    // Initialisiert Fahrzeuge und eine Kreuzung für die Ein-/Ausgabe aus einer Datei
    std::unique_ptr<PKW> auto1 = std::make_unique<PKW>("");
    std::unique_ptr<Fahrrad> fahrrad1 = std::make_unique<Fahrrad>("");
    std::shared_ptr<Kreuzung> kreuzung1 = std::make_shared<Kreuzung>("");

    // Öffnen der Datei zum Einlesen
    std::ifstream fin("VO.dat");
    fin.exceptions(std::ios_base::eofbit | std::ios_base::failbit | std::ios_base::badbit);

    // Fehlerbehandlung beim Dateizugriff und Einlesen
    try {
        fin >> *auto1 >> *fahrrad1 >> *kreuzung1;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        throw;
    }

    // Ausgabe der eingelesenen Daten auf die Konsole
    auto1->vKopf();
    auto1->vAusgeben(std::cout);
    std::cout << "" << std::endl;
    fahrrad1->vAusgeben(std::cout);
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

    kreuzung1->vKopf();
    kreuzung1->vAusgeben(std::cout);
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
}

void vAufgabe_9() {

    // Öffnen der Datei für die Simulationseinstellungen
    std::ifstream fin("Simu2.dat");

    // Prüfen, ob die Datei geöffnet werden kann
    if (!fin.good()) {
        std::cout << "Die Datei kann nicht geöffnet werden." << std::endl;
        return;
    }

    // Initialisieren des Simulation-Objekts und Einlesen der Daten
    Simulation simulation;

    simulation.vEinlesen(fin);
    simulation.vSimulieren(10, 0.1); // Simulation für 10 Sekunden mit einem Zeitschritt von 0.1
    vBeendeGrafik(); // Beenden der Grafik nach der Simulation
}

void vAufgabe_9a() {
    // Öffnen der Datei für die Simulation mit grafischer Ausgabe
    ifstream fin("SimuDisplay.dat");
    if (!fin.good()) {
        cout << "Die Datei konnte nicht geöffnet werden!" << endl;
        return;
    }

    // Initialisieren des Simulation-Objekts und Einlesen der Daten mit Grafikaktivierung
    Simulation simulation;

    simulation.vEinlesen(fin, true); // true aktiviert die grafische Darstellung
    simulation.vSimulieren(10, 0.1); // Simulation für 10 Sekunden mit einem Zeitschritt von 0.1
    vBeendeGrafik(); // Beenden der Grafik nach der Simulation
}

int main()
{
	//vAufgabe_Probe();
	//vAufgabe_1();
	//vAufgabe_1a();
	//vAufgabe_2();
	//vAufgabe_3();
	//vAufgabe_4();
	//vAufgabe_5();
	vAufgabe_6();
    //vAufgabe_6a();
	//vAufgabe_7();
	//vAufgabe_8();
	//vAufgabe_9();
	//vAufgabe_9a();

	return 0;
}
