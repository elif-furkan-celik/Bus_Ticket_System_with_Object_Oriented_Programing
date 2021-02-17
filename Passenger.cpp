#include "Passenger.h"


void Passenger::print(){

    cout << "Passenger Name:\t" << "Passenger Surname:\t" << "Sex:\t" <<"Age:\t" << "Id:\t" << "Booking Id:\t" << endl;

    cout << name << "\t" << surname << "\t" << sex << "\t" << age << "\t" << id << "\t" << pnr << endl;

}

Passenger::Passenger() {//default constructor
	name = "";
	surname = "";
	sex = "";
	age = "";
	id = "";
	pnr = "-1";
	seat = -1;
}
