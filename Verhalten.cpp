
#include "Verhalten.h"

Verhalten::Verhalten(Weg& weg) : p_pWeg(weg){
	// TODO Auto-generated constructor stub

}

Verhalten::~Verhalten() {
	// TODO Auto-generated destructor stub
}

Weg& Verhalten::getWeg() const {
	return p_pWeg;
}

