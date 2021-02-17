#include <iostream>
#include <stdlib.h>
#include <chrono>

using namespace std;

class Passenger{
public:
    string name;
    string surname;
    string sex;
    string id;
    string age;
    string pnr;
    int seat;

	void print();

    Passenger();
};
