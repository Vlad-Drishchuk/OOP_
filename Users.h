//
// Created by Vladyslav Drishchuk on 16.12.2023.
//

#ifndef OOPV2_USERS_H
#define OOPV2_USERS_H

#include "iostream"
#include "string"
#include "Order.h"
#include "Administrator.h"

using namespace std;
class Order;
class Administrator;

class Users{

private:
    string UserId;
    string Name;
    string LastName;
    string Addres;
    string Email;

public:

    //friend void Order::NewOrder(int UserID);
    void NewOrder(int UserID);
    friend class Order;
    friend class Administrator;
//Setters
    void SetId(string ValId);
    void SetName(string ValName);
    void SetlastName(string ValName);
    void SetAddres(string ValName);
    void SetEmail(string ValName);

    //Getters
    string getID(){
        return UserId;
    };
    string getName(){
        return Name;
    };
    string getLastName(){
        return LastName;
    };
    string getAddres(){
        return Addres;
    };
    string getEmals(){
        return Email;
    };

    //Metodos
    void RgisterNewUser();

    bool IdentificationUser(string ID);
    void GetUser(string ID);
    void CleanFile();
    void LogIn();
};

#endif //OOPV2_USERS_H
