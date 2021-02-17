#include <iostream>
#include "Passenger.h"
#include <stdlib.h>
#include <chrono>
#include <string.h>

using namespace std;

struct bus{
	int bus_no;
	int bus_size;
	Passenger *pasrs;
	string comp_name;
	string from_city = "Ankara";
	string to_city;
	string arr_time;
	string dep_time;
	int price;
	bus *link = NULL;
};

class City{
public:
    string name;
    bus *head;
    void add_bus(int bus_no, int bus_size, string comp_name, string arr_time, string dep_time, int price);
	// Display the contents of the linkedlist to console.
	void print();
	void print_pass(int bus_no);
    void delete_bus(int bus_no);
    int pass_delete(string pnr);
    int find(int bus_no);

	// If the item isn't found, a null pointer is returned.
	void add_passanger(int bus_no);
	void add_passanger_s(int bus_no, string name, string surname, string sex, string id, string age, string pnr, int seat);
    City();
	City(string);

	~City();

};
