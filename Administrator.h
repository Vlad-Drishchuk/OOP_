//
// Created by Vladyslav Drishchuk on 16.12.2023.
//

#ifndef OOPV2_ADMINISTRATOR_H
#define OOPV2_ADMINISTRATOR_H
#include "iostream"
#include "string"
#include "Users.h"
#include "Publication.h"
using namespace std;
class Publication;


class Administrator {
private:
    string name;
    int administratorId;
protected:
    string password;

public:
    void setPassword();
    void LoginForAdmin();
    string getPassword(){
        return password;
    };
    void AdministratorMenu();
    void SelectOrder(string OrderId);
};


#endif //OOPV2_ADMINISTRATOR_H
