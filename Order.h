//
// Created by Vladyslav Drishchuk on 18.12.2023.
//

#ifndef OOPV2_ORDER_H
#define OOPV2_ORDER_H
#include "iostream"
#include "string"
#include "Users.h"
#include "Administrator.h"

using namespace std;
class Users;
class Administrator;

class Order {
private:
    string OrderId;
    string UserId;
    string PublicatonID;
    string PublicatioData;
    int PublicationPrice;
    int totalAmount;
    int totalPrice;
public:
    //Setters
    void SetOrderId(string OID);
    void SetUserId(string UID);
    void SetPublicationID(string PID);
    void SetPublicationData(string PData);
    void SetPublicationPrice(int Price);
    void SetPublicationAmount(int Amount);
    void SetTotalPrice(int TotalPrice);

    //Getters
    string GetUserID(){
        return UserId;
    }
    string GetOrderId(){
        return OrderId;
    }
    string GetPubicationID(){
        return PublicatonID;
    }
    string GetPublicationData(){
        return PublicatioData;
    }
    int GetPublicationPrice(){
        return PublicationPrice;
    }
    int GetTotalAmoumt(){
        return totalAmount;
    }
    int GetTotalPrice(){
        return totalPrice;
    }

    //Metods

    void NewOrder(int UserID);
    void DeleteOrder(string OrderID);
    void GetOrderByID(int UserID);
    void GetPublicationInfo();
    void ShowAllOrder();
    void GetOrder(string ID);
    //Friend
    friend class Users;
    friend class Administrator;
};


#endif //OOPV2_ORDER_H
