#include "Administrator.h"
#include "Publication.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "string"

using namespace std;

void Administrator::setPassword() {
    password = "VladD";
}

void Administrator::LoginForAdmin() {
    cout << "Введіть пароль: ";
    string PasswordCheck = getPassword();
    string passwordInput;
    cin >> passwordInput;
    if (PasswordCheck == passwordInput) {
        AdministratorMenu();
    } else {
        cout << "Неправильний пароль" << std::endl;
        return;
    }
}

void Administrator::AdministratorMenu() {
    cout << "Вітаю в меню для адмінів" << std::endl;
    cout << "1. Додати публікацю" << "\n" << "2. Переглянути замовлення" <<"\n"<<"3. Вийти"<<endl;
    int choice;
    cin >> choice;

    if (choice == 1) {
        Publication book1;
        book1.bookNew();
        AdministratorMenu();
        // ваш код для додавання публікації
    } else if (choice == 2) {
        Order order;
        order.ShowAllOrder();
        string OrderId;
        cout<<"Виберіть замовлення: ";
        cin>>OrderId;
        SelectOrder(OrderId);


    } else if(choice == 3){
        return;
    }
    else if(choice == 4){
        Publication book;
        book.ShowAllBook();
    }
    else {
        cout << "Неправильний вибір." << std::endl;
    }
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void deleteOrder(string OrderID) {
    ifstream inputFile("OrderJornal.txt");
    ofstream tempFile("tempOrderJornal.txt", ios::out);  // Change ios::app to ios::out

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Error opening files!" << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string orderId="NOT";

        if (getline(iss, orderId, '|')) {
            getline(iss, orderId, '|');

            orderId.erase(remove(orderId.begin(), orderId.end(), ' '), orderId.end());
            cout<< orderId <<"="<<OrderID<<endl;

            if (orderId != OrderID) {
                tempFile << line << endl;
            }
        } else {
            cerr << "Error reading orderId from line: " << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    // Delete the old file
    remove("OrderJornal.txt");

    // Rename the new file to the desired name
    rename("tempOrderJornal.txt", "OrderJornal.txt");
}


void Administrator::SelectOrder(string OrderId) {
    Users user;
    Order order;
    char Choice;

    order.GetOrder(OrderId);
    string ID;
    ID = order.GetUserID();
    cout<<ID<<endl;
    user.GetUser(ID);

    cout<<"Інформація про замовлення:"<<endl<<"Отримувач:"<<endl<<"Імʼя:"<<user.getName()<<" "<<user.getLastName()<<endl<<"Індекс: "<<user.getAddres()<<endl<<"Пошта: "<<user.getEmals()<<endl<<endl;

    cout<<"Публікація: "<<endl<<"Дані:"<<order.GetPublicationData()<<endl<<"Кількість: "<< order.GetTotalAmoumt()<<endl<<"Загальна ціна: "<< order.GetTotalPrice()<<endl;

    cout<<"Замовлення виконано?"<<endl;
    cout<<"Y-Так"<<endl;
    cin>> Choice;

    if(Choice == 'Y'){
        cout<<"Видалення замовлення з файлу"<<endl;
        deleteOrder(order.GetOrderId());
    }
    AdministratorMenu();
}
