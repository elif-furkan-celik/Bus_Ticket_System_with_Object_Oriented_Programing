#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <cstdlib>
#include <iostream>
#include "City.h"
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

using namespace std;

int next_bus_no = 1;
City cities[80];
int city_count = 0;

string UpToLow(string str){
    for (unsigned int i = 0; i < strlen(str.c_str()); i++)
        if (str[i] >= 0x41 && str[i] <= 0x5A)
            str[i] = str[i] + 0x20;
    return str;
}

void save(){
    fstream file;
    file.open("Dosya.txt", ios::out|ios::trunc);
    if(file.is_open()){
        for(int i=0; i<city_count; i++){
            bus *index = cities[i].head;
            if(index == NULL){
                continue;
            }else{
                while(true){
                    for(int j=0; j<index->bus_size; j++){
                        file << cities[i].name << ","
                             << index->bus_no << ","
                             << index->bus_size << ","
                             << index->comp_name << ","
                             << index->arr_time << ","
                             << index->dep_time << ","
                             << index->price << ","
                             << index->pasrs[j].name << ","
                             << index->pasrs[j].surname << ","
                             << index->pasrs[j].sex << ","
                             <<index->pasrs[j].id << ","
                             <<index->pasrs[j].age << ","
                             <<index->pasrs[j].pnr << ","
                             <<index->pasrs[j].seat << "\n";
                    }
                    if(index->link == NULL){
                        break;
                    }
                        index = index->link;
                }
            }
        }
    }
    file.close();
}

void load(){
    fstream file;
    file.open("Dosya.txt", ios::in);
    string str = "";

    while(!file.eof()){
        string to_city1;
        string bus_no1;
        int b_no1;
        string bus_size1;
        int b_s1;
        string comp_name1;
        string arr_time1;
        string dep_time1;
        string price1;
        int pr1;
        string name1;
        string surname1;
        string sex1;
        string id1;
        string age1;
        string pnr1;
        string seat1;
        int se1;

        getline(file, str);

        if(str.length() == 0){
            break;
        }
        to_city1 = str.substr(0, str.find(","));

        str.erase(0,str.find(",")+1);

        bus_no1 = str.substr(0, str.find(","));
        str.erase(0,str.find(",")+1);

        stringstream to_bn(bus_no1);
        to_bn >> b_no1;

        bus_size1 = str.substr(0, str.find(","));
        str.erase(0,str.find(",")+1);

        stringstream to_bs(bus_size1);
        to_bs >> b_s1;

        comp_name1 = str.substr(0, str.find(","));
        str.erase (0,str.find(",")+1);

        arr_time1 = str.substr(0, str.find(","));
        str.erase (0,str.find(",")+1);

        dep_time1 = str.substr(0, str.find(","));
        str.erase (0,str.find(",")+1);

        price1 = str.substr(0, str.find(","));
        str.erase (0,str.find(",")+1);

        stringstream to_pr(price1);
        to_pr >> pr1;

        name1 = str.substr(0, str.find(","));
        str.erase (0,str.find(",")+1);

        surname1 = str.substr(0, str.find(","));
        str.erase (0,str.find(",")+1);

        sex1 = str.substr(0, str.find(","));
        str.erase (0,str.find(",")+1);

        id1 = str.substr(0, str.find(","));
        str.erase (0,str.find(",")+1);

        age1 = str.substr(0, str.find(","));
        str.erase (0,str.find(",")+1);

        pnr1 = str.substr(0, str.find(","));
        str.erase (0,str.find(",")+1);

        seat1 = str.substr(0, str.find("\n"));

        stringstream to_se(seat1);
        to_se >> se1;

        int temp = -1;

        if(city_count == 0){
            cities[city_count].name = to_city1;
            temp = city_count;
            city_count++;

        }else{

            for(int i=0; i<city_count; i++){
                if(cities[i].name == to_city1){
                    temp = i;
                }
            }
            if(temp == -1){
                cities[city_count].name = to_city1;
                temp = city_count;
                city_count++;
            }
        }
        if(cities[temp].find(b_no1) == 0){
            cities[temp].add_bus(b_no1, b_s1, comp_name1, arr_time1, dep_time1, pr1);
            next_bus_no++;
        }
        if(se1 != -1){
            cities[temp].add_passanger_s(b_no1, name1, surname1, sex1, id1, age1, pnr1, se1);
        }
    }
    file.close();
}


int main(){
    char id_ = '0';
    int id = 0;
    int busNo, choice;
    string pnr;
    string pw = "11";
    char ad_exit = '1';
    char us_exit = '1';
    char admin_exit = '1';
    char user_exit = '1';
    string city_name="";
    char cho = '0';
    load();

    while(true){
        do{
            id_ = '0';
            id = 0;
            cout << "                       Main Page                 \n\n\n" << endl;
            cout << "1: user" << endl;
            cout << "2: admin" << endl;
            cout << "Are you admin or user: ";
            cin >> id_;
            if(id_ == '1'){
                id = 1;
            }
            if(id_ == '2'){
                id = 2;
            }
            if(id != 1 && id != 2){
                system ("CLS");
                cout << "Incorrect choice, please try again:" << endl;
            }

        }while(id != 1 && id != 2);

        switch(id){
            case 1:
                do{
                    user_exit = '1';
                    system ("CLS");
                    cout << "                       USER                 \n\n\n" << endl;

                    do{
                        choice = 0;
                        cho = '0';
                        system ("CLS");
                        cout << "                       USER                 \n\n\n" << endl;
                        cout << "\n\n1: Buy a ticket" << endl;
                        cout << "2: Display your ticket" <<endl;
                        cout << "\nChose your action: ";

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
                        do{
                            us_exit = '1';
                            if(city_count == 0){
                                cout << "There is no scheduled Bus Service." << endl;
                            }else{
                                system ("CLS");
                                cout << "                       USER                 \n\n\n" << endl;

                                cout << "Company Name:\t" << "Bus No:\t" << "Bus Size:\t" <<"From:\t" << "To:\t" << "Arrival Time:\t" << "Departure Time:\t" << "Price:" << endl;
                                for(int i=0; i<city_count; i++){
                                    cities[i].print();
                                }
                                cout << "Choose a destination city and write it as shown on the screen, please: " << endl;
                                cin >> city_name;
                                city_name = UpToLow(city_name);
                                int temp = -1;
                                for(int i=0; i<city_count; i++){
                                    if(cities[i].name == city_name){
                                        temp = i;
                                    }
                                }
                                if(temp == -1){
                                    cout << "\nThere is no scheduled Bus Service to go to the " << city_name << "." << endl;
                                }else{

                                    system ("CLS");
                                    cout << "                       USER                 \n\n\n" << endl;
                                    cout << "The Bus Service to go to the " << city_name << ".\n\n" << endl;
                                    cout << "Company Name:\t" << "Bus No:\t" << "Bus Size:\t" <<"From:\t" << "To:\t" << "Arrival Time:\t" << "Departure Time:\t" << "Price:" << endl;
                                    cities[temp].print();
                                    cout << "\n\nChoose a Bus Service that appropriate for you and enter the Bus No, please." << endl;
                                    cout << "\nBus No( It must be a numeric number. ): " << endl;

                                    cin >> busNo;

                                    cities[temp].add_passanger(busNo);
                                }
                            }

                            cout << "\n\nFor previous page please click 0. Otherwise you will continue." << endl;
                            cin >> us_exit;

                        }while(us_exit != '0');
                        break;
                    case 2:
                        do{
                            us_exit = '1';
                            if(city_count == 0){
                                cout << "There is no scheduled Bus Service." << endl;
                            }else{
                                system ("CLS");
                                cout << "                       USER                 \n\n\n" << endl;
                                cout << "Company Name:\t" << "Bus No:\t" << "Bus Size:\t" <<"From:\t" << "To:\t" << "Arrival Time:\t" << "Departure Time:\t" << "Price:" << endl;
                                for(int i=0; i<city_count; i++){
                                    cities[i].print();
                                }
                                cout << "Choose a destination city and write it as shown on the screen, please: " << endl;
                                cin >> city_name;
                                city_name = UpToLow(city_name);
                                int temp = -1;
                                for(int i=0; i<city_count; i++){
                                    if(cities[i].name == city_name){
                                        temp = i;
                                    }
                                }
                                if(temp == -1){
                                    cout << "\nThere is no scheduled Bus Service to go to the " << city_name << "." << endl;
                                }else{

                                    int returned = 0;
                                    do{
                                        system ("CLS");
                                        cout << "                       USER                 \n\n\n" << endl;
                                        cout << "The Bus Service to go to the " << city_name << ".\n\n" << endl;
                                        cout << "Company Name:\t" << "Bus No:\t" << "Bus Size:\t" <<"From:\t" << "To:\t" << "Arrival Time:\t" << "Departure Time:\t" << "Price:" << endl;
                                        cities[temp].print();

                                        cout << "\n\nWrite your booking id, please." << endl;
                                        cout << "\nBooking Id: " << endl;

                                        cin >> pnr;

                                        returned = cities[temp].pass_delete(pnr);

                                        if(returned == 0){
                                            cout << "Incorrect choice, please try again:" << endl;
                                        }
                                    }while(returned == 0);
                                }
                            }
                            cout << "\n\nFor previous page please click 0. Otherwise you will continue." << endl;
                            cin >> us_exit;

                        }while(us_exit != '0');
                        break;
                    }


                    cout << "\n\nFor main page please click 0. Otherwise you will continue." << endl;
                    cin >> user_exit;

                }while(user_exit != '0');
                save();
                system ("CLS");
                break;
            case 2:

            do{
                    cout << "\npassword: ";
                    cin >> pw;
                    if(pw!="123"){
                        system ("CLS");
                        cout << "Incorrect password, please try again (For exit enter 0):\n" << endl;
                        cout << "1: user" << endl;
                        cout << "2: admin" << endl;
                        cout << "Are you admin or user: 2";
                    }

                    if(pw == "0"){
                        break;
                    }
                }while(pw!="123");

                if(pw == "0"){
                    break;
                }
                do{
                    admin_exit = '1';

                    do{
                        choice = 0;
                        cho = '0';
                        system ("CLS");
                        cout << "                       ADMIN                 \n\n\n" << endl;
                        cout << "\n\n1: Add Bus" << endl;
                        cout << "2: Display Passengers" <<endl;
                        cout << "\nChose your action: ";

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
                        do{
                            ad_exit = '1';
                            system ("CLS");
                            cout << "                       ADMIN                 \n\n\n" << endl;
                            cout << "\n\nGreat! Now we will ask you some information about bus." << endl;
                            cout << "\nDeparture City:";
                            cin >> city_name;
                            city_name = UpToLow(city_name);

                            int temp = -1;
                            for(int i=0; i<city_count; i++){
                                if(cities[i].name == city_name){
                                    temp = i;
                                }
                            }
                            if(temp == -1){
                                cities[city_count].name = city_name;
                                temp = city_count;
                                city_count++;
                            }

                            int bus_size = 10;
                            int price = 10;
                            string comp_name;
                            string arr_time;
                            string dep_time;

                            cout << "\nWhat is your company name: ";
                            cin >> comp_name;
                            comp_name = UpToLow(comp_name);


                            system ("CLS");
                            cout << "                       ADMIN                 \n\n\n" << endl;
                            cout << "\nDeparture City:" << city_name;
                            cout << "\nCompany name: " << comp_name;
                            cout << "\nWhat is your bus size( It must be a numeric number. ): ";
                            cin >> bus_size;


                            cout << "\nWhat is your arrival time: ";
                            cin >> arr_time;
                            arr_time = UpToLow(arr_time);

                            cout << "\nWhat is your departure time: ";
                            cin >> dep_time;
                            dep_time = UpToLow(dep_time);

                            cout << "\nWhat is your ticket price( It must be a numeric number. ): ";
                            cin >> price;


                            cout << "\n\nGreat! Now we are creating your bus..." << endl;
                            cities[temp].add_bus(next_bus_no, bus_size, comp_name, arr_time, dep_time, price);
                            next_bus_no++;
                            cout << "\nYour bus successfully created." << endl;

                            cout << "\n\nFor previous page please click 0. Otherwise you will continue." << endl;
                            cin >> ad_exit;

                        }while(ad_exit != '0');
                        break;
                    case 2:
                        do{
                            ad_exit = '1';
                            system ("CLS");
                            cout << "                       ADMIN                 \n\n\n" << endl;

                            if(city_count == 0){
                                cout << "\nThere is no scheduled Bus Service." << endl;
                            }else{
                                system ("CLS");
                                cout << "                       ADMIN                 \n\n\n" << endl;
                                cout << "Company Name:\t" << "Bus No:\t" << "Bus Size:\t" <<"From:\t" << "To:\t" << "Arrival Time:\t" << "Departure Time:\t" << "Price:" << endl;
                                for(int i=0; i<city_count; i++){
                                    cities[i].print();
                                }
                                cout << "\nDeparture City of Passenger:" << endl;
                                cin >> city_name;
                                city_name = UpToLow(city_name);
                                int temp = -1;
                                for(int i=0; i<city_count; i++){
                                    if(cities[i].name == city_name){
                                        temp = i;
                                    }
                                }
                                if(temp == -1){
                                    cout << "\nThere is no scheduled Bus Service to go to the " << city_name << "." << endl;
                                }else{

                                    system ("CLS");
                                    cout << "                       ADMIN                 \n\n\n" << endl;
                                    cout << "\nDeparture City:" << city_name;
                                    cout << "Company Name:\t\t" << "Bus No:\t" << "Bus Size:\t" <<"From:\t" << "To:\t" << "Arrival Time:\t" << "Departure Time:\t" << "Price:" << endl;
                                    cities[temp].print();
                                    cout << "\nBus No( It must be a numeric number. ):" << endl;
                                    cin >> busNo;

                                    cities[temp].print_pass(busNo);
                                }
                            }

                            cout << "\n\nFor previous page please click 0. Otherwise you will continue." << endl;
                            cin >> ad_exit;

                        }while(ad_exit != '0');
                        break;
                    }

                    cout << "\n\nFor main page please click 0. Otherwise you will continue." << endl;
                    cin >> admin_exit;

                }while(admin_exit != '0');
                save();
                system ("CLS");
                break;
        }
    }
    return 0;
}
