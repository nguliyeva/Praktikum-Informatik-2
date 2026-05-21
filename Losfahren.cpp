
#include "Losfahren.h"

Losfahren::Losfahren(Fahrzeug& fahrzeug, Weg& weg) : Fahrausnahme(fahrzeug, weg){
	// TODO Auto-generated constructor stub

}

Losfahren::~Losfahren() {
	// TODO Auto-generated destructor stub
}

void Losfahren::vBearbeiten() {
    // Erfolgreich Fahrzeug abgegeben, gebe Fahrzeug- und Weginformationen aus
    std::cout << "Fahrzeug: " << p_fahrzeug.getName() << std::endl;
    std::cout << "Weg: " << p_weg.getName() << std::endl;
    std::cout << "Art der Ausnahme: Losfahren " << std::endl;
    std::cout << "Startzeit: " << dGlobaleZeit << std::endl;

    // Das Fahrzeug abgeben
    std::unique_ptr<Fahrzeug> fahrzeug = p_weg.pAbgabe(p_fahrzeug);

    // Überprüfen, ob das Fahrzeug erfolgreich abgegeben wurde
    if (fahrzeug) {
        // Das Fahrzeug wieder annehmen, wenn nötig
        p_weg.vAnnahme(std::move(fahrzeug));
        std::cout << "Fahrzeug erfolgreich wieder angenommen!" << std::endl << std::endl;
    } else {
        std::cout << "Fahrzeug konnte nicht abgegeben werden." << std::endl;
    }
}



