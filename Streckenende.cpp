
#include "Streckenende.h"

Streckenende::Streckenende(Fahrzeug& fahrzeug, Weg& weg) : Fahrausnahme(fahrzeug, weg){
	// TODO Auto-generated constructor stub

}

Streckenende::~Streckenende() {
	// TODO Auto-generated destructor stub
}

void Streckenende::vBearbeiten() {
    std::cout << "Fahrzeug: " << p_fahrzeug.getName() << std::endl;
    std::cout << "Weg: " << p_weg.getName() << std::endl;
    std::cout << "Art der Ausnahme: Streckenende " << std::endl;
    std::cout << "Startzeit: " << dGlobaleZeit << std::endl;

    auto pZielKreuzung = p_weg.getZielkreuzung();

    if(pZielKreuzung != nullptr){
        if (auto zielKreuzung = pZielKreuzung){
            zielKreuzung->vTanken(p_fahrzeug);
            auto pNeuerWeg = zielKreuzung->pZufaelligerWeg(p_weg); // pZufaelligerWeg Methode wird mit shared_ptr aufgerufen

            pNeuerWeg->vAnnahme(p_weg.pAbgabe(p_fahrzeug));

            std::cout << "ZEIT     : " << p_fahrzeug.getZeit() << std::endl;
            std::cout << "KREUZUNG : " << zielKreuzung->getName() << "[" << zielKreuzung->getTankstelle() <<"]"<< std::endl;
            std::cout << "WECHSEL  : " << p_weg.getName() << " -> " << pNeuerWeg->getName() << std::endl;
            std::cout << "FAHRZEUG : " << std::endl;
            p_fahrzeug.vKopf();
            std::cout << p_fahrzeug << std::endl << std::endl;
        }

        else{
            std::cout << "Zielkreuzung ist nicht vorhanden. Fahrzeug bleibt stehen." << std::endl;
            p_weg.pAbgabe(p_fahrzeug);

    }
}
}
