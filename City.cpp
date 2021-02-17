#include "City.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

string ToLow(string str){
    for (unsigned int i = 0; i < strlen(str.c_str()); i++)
        if (str[i] >= 0x41 && str[i] <= 0x5A)
            str[i] = str[i] + 0x20;
    return str;
}

City::City() {//default constructor
	head = NULL;
	name = "";
}

City::~City()//destructor
{
	bus * p = head;
	bus * q = head;
	while (q){
		p = q;
		q = p->link;
		if(q){
            delete p->pasrs;
            delete p;
		}
	}
}

void City::delete_bus(int bus_no){
    bus *index = head;
    if(head == NULL){
        cout << "There is nothing to delete." << endl;
    }else if(head->link == NULL){
        if(head->bus_no == bus_no){
            delete head->pasrs;
            delete head;
            head = NULL;
            cout << "The bus deleted." << endl;
        }else{
            cout << "The bus not found." << endl;
        }
    }else{
        while(true){
            if(index->link->bus_no == bus_no){
                bus *temp;
                temp = index->link;
                index->link = index->link->link;
                delete temp->pasrs;
                delete temp;
                cout << "The bus deleted." << endl;
                break;
            }else{
                if(index->link->link == NULL){
                    cout << "The bus not found." << endl;
                    break;
                }
                index = index->link;
            }
        }
    }
}

void City::add_bus(int bus_no, int bus_size, string comp_name, string arr_time, string dep_time, int price){
	bus *index = head;

	if(index == NULL){

        bus *temp = new bus;
        temp->bus_no = bus_no;
        temp->bus_size = bus_size;
        temp->comp_name = comp_name;
        temp->to_city = name;
        temp->arr_time = arr_time;
        temp->dep_time = dep_time;
        temp->price = price;
        temp->pasrs = new Passenger[bus_size];

        head = temp;

	}else if(index->link == NULL){
        if(index->price >= price){

            bus *temp = new bus;
            temp->bus_no = bus_no;
            temp->bus_size = bus_size;
            temp->comp_name = comp_name;
            temp->to_city = name;
            temp->arr_time = arr_time;
            temp->dep_time = dep_time;
            temp->price = price;
            temp->pasrs = new Passenger[bus_size];
            index->link = temp;

        }else{
            bus *temp = new bus;
            temp->bus_no = bus_no;
            temp->bus_size = bus_size;
            temp->comp_name = comp_name;
            temp->to_city = name;
            temp->arr_time = arr_time;
            temp->dep_time = dep_time;
            temp->price = price;
            temp->pasrs = new Passenger[bus_size];

            temp->link = index;
            head = temp;
        }
	}else{
        while(true){
           if(index->link->price < price){
                bus *temp = new bus;
                temp->bus_no = bus_no;
                temp->bus_size = bus_size;
                temp->comp_name = comp_name;
                temp->to_city = name;
                temp->arr_time = arr_time;
                temp->dep_time = dep_time;
                temp->price = price;
                temp->pasrs = new Passenger[bus_size];

                temp->link = index->link;
                index->link = temp;
                break;
            }else if(index->link->price >= price){
                if(index->link->link == NULL){

                    bus *temp = new bus;
                    temp->bus_no = bus_no;
                    temp->bus_size = bus_size;
                    temp->comp_name = comp_name;
                    temp->to_city = name;
                    temp->arr_time = arr_time;
                    temp->dep_time = dep_time;
                    temp->price = price;
                    temp->pasrs = new Passenger[bus_size];

                    index->link->link = temp;
                    break;
                }
                index = index->link;
            }
        }

	}
}

/*Display the contents of the City to console.*/
void City::print(){
	bus *temp = head;

	if (temp == NULL){
		cout << "Empty list..." << endl;
	}
	else{
		while (temp != NULL){

		    cout << temp->comp_name << "\t\t" << temp->bus_no << "\t" << temp->bus_size << "\t\t" << temp->from_city << "\t" << temp->to_city << "\t" << temp->arr_time << "\t" << temp->dep_time << "\t\t" << temp->price << endl;

			temp = temp->link;
		}
	}
}

int City::pass_delete(string pnr){
    bus *index = head;
    int choice;
    char cho = '0';

    if(head == NULL){
        cout << "The booking id did not found." << endl;
        return 0;
	}else{
        do{
            for(int i=0; i<index->bus_size; i++){
                if(index->pasrs[i].pnr == pnr){
                    cout << "Company Name:\t" << "Bus No:\t" << "Bus Size:\t" <<"From:\t" << "To:\t" << "Arrival Time:\t" << "Departure Time:\t" << "Price:" << endl;

                    cout << "Company " << index->comp_name << "\t" << index->bus_no << "\t" << index->bus_size << "\t" << index->from_city << "\t" << index->to_city << "\t" << index->arr_time << "\t" << index->dep_time << "\t" << index->price << endl;

                    index->pasrs[i].print();
                    do{
                        choice = 0;
                        cho = '0';
                        cout << "What do you want to do now:"<< endl;
                        cout << "1: Delete ticket" << endl;
                        cout << "2: Exit" << endl;

                        cin >> cho;
                        if(cho == '1'){
                        choice = 1;
                        }
                        if(cho == '2'){
                            choice = 2;
                        }
                        if(choice != 1 && choice != 2){
                            cout << "Incorrect choice, please try again:" << endl;
                        }

                    }while(choice != 1 && choice != 2);

                    switch(choice){
                        case 1:
                            cout << "The ticket for, " << index->pasrs[i].name << " " << index->pasrs[i].surname << ", is deleting.." << endl;
                            index->pasrs[i].name = "";
                            index->pasrs[i].surname = "";
                            index->pasrs[i].sex = "";
                            index->pasrs[i].age = "";
                            index->pasrs[i].id = "";
                            index->pasrs[i].seat = -1;
                            index->pasrs[i].pnr = "-1";
                            cout << "The ticket successfully deleted." << endl;
                        case 2:
                            cout << "Returning to the previous page..." << endl;
                    }
                    return 1;
                }
            }
            index = index->link;
        }while(index->link != NULL);
    }
    cout << "The booking id did not found." << endl;
    return 0;
}

void City::print_pass(int bus_no){
    bus *index = head;
    int temp;
    int choice = 0;
    char ad_exit;
    char cho ='0';
    string passenger_name;
    string passenger_surname;
    string passenger_sex;
    int passenger_age;
    int passenger_id;
    int passenger_pnr;

	if(head == NULL){
        cout << "The bus did not found." << endl;
	}else{
	    do{
            ad_exit = '1';
            while(true){
                if(index->bus_no == bus_no){
                    for(int i=0; i<index->bus_size; i++){
                        if(index->pasrs[i].pnr == "-1"){
                            cout << "Seat " << i+1 << ":" << "Empty" << endl;
                        }else{
                            cout << "Seat " << i+1 << ":" << index->pasrs[i].name << " " << index->pasrs[i].surname << endl;
                        }
                    }

                    while(true){
                        cout << "Choose a passenger and enter its seat number, please!" << endl;
                        cout << "Seat Number( It must be a numeric number. ): " << endl;
                        cin >> temp;
                        if(index->pasrs[temp-1].pnr == "-1"){
                        cout << "The chosen seat is empty, please choose another one.";
                        }else{
                            break;
                        }
                    }
                    cout << "Company Name:\t" << "Bus No:\t" << "Bus Size:\t" <<"From:\t" << "To:\t" << "Arrival Time:\t" << "Departure Time:\t" << "Price:" << endl;

                    cout << "Company " << index->comp_name << "\t" << index->bus_no << "\t" << index->bus_size << "\t" << index->from_city << "\t" << index->to_city << "\t" << index->arr_time << "\t" << index->dep_time << "\t" << index->price << endl;

                    index->pasrs[temp-1].print();

                    do{
                        choice = 0;
                        cho = '0';
                        cout << "What do you want to do now:"<< endl;
                        cout << "1: Delete ticket" << endl;
                        cout << "2: Exit" << endl;

                        cin >> cho;
                        if(cho == '1'){
                        choice = 1;
                        }
                        if(cho == '2'){
                            choice = 2;
                        }
                        if(choice != 1 && choice != 2){
                            cout << "Incorrect choice, please try again:" << endl;
                        }

                    }while(choice != 1 && choice != 2);

                    switch(choice){
                        case 1:
                            cout << "The passenger, " << index->pasrs[temp-1].name << " " << index->pasrs[temp-1].surname << ", is deleting.." << endl;
                            index->pasrs[temp-1].name = "";
                            index->pasrs[temp-1].surname = "";
                            index->pasrs[temp-1].sex = "";
                            index->pasrs[temp-1].age = -1;
                            index->pasrs[temp-1].id = -1;
                            index->pasrs[temp-1].seat = -1;
                            index->pasrs[temp-1].pnr = "-1";
                            cout << "The passenger successfully deleted." << endl;
                        case 2:
                            cout << "Returning to the previous page..." << endl;
                    }
                    break;
                }else if(index->link == NULL){
                    cout << "The bus did not found." << endl;
                    break;
                }
                index = index->link;
            }

            cout << "\n\nFor previous page please click 0. Otherwise you will continue." << endl;
            cin >> ad_exit;

	    }while(ad_exit != '0');
	}

}

void City::add_passanger(int bus_no){
    bus *index = head;
    int temp;
    char user_exit;
    string passenger_name;
    string passenger_surname;
    string passenger_sex;
    string passenger_age;
    string passenger_id;

	if(head == NULL){
        cout << "The bus did not found." << endl;
	}else {
        while(true){
            if(index->bus_no == bus_no){
                do{
                    user_exit = '1';
                    for(int i=0; i<index->bus_size; i++){
                        if(index->pasrs[i].pnr == "-1"){
                            cout << "Seat " << i+1 << ":" << "Empty" << endl;
                        }else{
                            cout << "Seat " << i+1 << ":" << "Not Empty" << endl;
                        }
                    }

                    while(true){
                        cout << "Choose a seat and enter its number, please!!" << endl;
                        cout << "Seat Number( It must be a numeric number. ): " << endl;
                        cin >> temp;
                        if(index->pasrs[temp-1].pnr == "-1"){
                            break;
                        }else{
                            cout << "The chosen seat is not available, please choose another one.";
                        }
                    }

                    cout << "Write your name, please!" << endl;
                    cin >> passenger_name;
                    passenger_name = ToLow(passenger_name);

                    cout << "Write your surname, please!" << endl;
                    cin >> passenger_surname;
                    passenger_surname = ToLow(passenger_surname);

                    cout << "Write your sex, please!" << endl;
                    cin >> passenger_sex;
                    passenger_sex = ToLow(passenger_sex);

                    cout << "Write your age, please!" << endl;
                    cin >> passenger_age;
                    passenger_age = ToLow(passenger_age);

                    cout << "Write your id, please!" << endl;
                    cin >> passenger_id;
                    passenger_id = ToLow(passenger_id);

                    cout << "Great! Nearly done." << endl;
                    cout << "Now, please do it your PAYMENT." << endl;
                    cout << "After PAYMENT, your booking will be done." << endl;
                    cout << ".................." << endl;
                    cout << "Thank you"  << endl;

                    srand (time(NULL));

                    index->pasrs[temp-1].name = passenger_name;
                    index->pasrs[temp-1].surname = passenger_surname;
                    index->pasrs[temp-1].sex = passenger_sex;
                    index->pasrs[temp-1].age = passenger_age;
                    index->pasrs[temp-1].id = passenger_id;
                    index->pasrs[temp-1].seat = temp;
                    index->pasrs[temp-1].pnr = alphanum[rand() % 5];

                    cout << "Your booking is done."  << endl;

                    cout << "Company Name:\t" << "Bus No:\t" << "Bus Size:\t" <<"From:\t" << "To:\t" << "Arrival Time:\t" << "Departure Time:\t" << "Price:" << endl;

                    cout << "Company " << index->comp_name << "\t" << index->bus_no << "\t" << index->bus_size << "\t" << index->from_city << "\t" << index->to_city << "\t" << index->arr_time << "\t" << index->dep_time << "\t" << index->price << endl;

                    index->pasrs[temp-1].print();

                    cout << "\n\nFor previous page please click 0. Otherwise you will continue." << endl;
                    cin >> user_exit;

                }while(user_exit != '0');
                break;
            }else if(index->link == NULL){
                cout << "The bus did not found." << endl;
                break;
            }
                index = index->link;
        }
	}
}

int City::find(int bus_no){
    bus *index = head;

	if(head == NULL){
        return 0;
	}else{
        while(true){
            if(index->bus_no == bus_no){
                return 1;
                }else if(index->link == NULL){
                    return 0;
                }
            index = index->link;
        }
	}
}


void City::add_passanger_s(int bus_no, string name, string surname, string sex, string id, string age, string pnr, int seat){
    bus *index = head;
    int temp;

	if(head == NULL){
        cout << "The bus did not found." << endl;
	}else{
        while(true){
            if(index->bus_no == bus_no){

                index->pasrs[seat].name = name;
                index->pasrs[seat].surname = surname;
                index->pasrs[seat].sex = sex;
                index->pasrs[seat].age = age;
                index->pasrs[seat].id = id;
                index->pasrs[seat].seat = seat;
                index->pasrs[seat].pnr = pnr;

                break;
                }else if(index->link == NULL){
                    cout << "The bus did not found." << endl;
                    break;
                }
                    index = index->link;
        }
	}
}
