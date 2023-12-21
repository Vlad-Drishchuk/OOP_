//
// Created by Vladyslav Drishchuk on 18.12.2023.
//

#include "Order.h"
#include "Publication.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "string"
#include "limits"

class Users;
using namespace std;

void Order::SetOrderId(std::string OID) {
    OrderId = OID;
}
void Order::SetUserId(std::string UID) {
    UserId = UID;
}
void Order::SetPublicationID(std::string PID) {
    PublicatonID = PID;
}
void Order::SetPublicationData(std::string PData) {
    PublicatioData = PData;
}
void Order::SetPublicationPrice(int Price) {
    PublicationPrice = Price;
}
void Order::SetPublicationAmount(int Amount) {
    totalAmount = Amount;
}
void Order::SetTotalPrice(int TotalPrice) {
    totalPrice = TotalPrice;
}

int FindMaxIdO() {

    std::ifstream Jornal("OrderJornal.txt");

    if (!Jornal.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return 0;
    }

    int maxId = std::numeric_limits<int>::min(); // Початкове значення для порівняння

    std::string line;
    while (getline(Jornal, line)) {
        std::istringstream iss(line);
        std::string token;

        // Пропускаємо першу комірку (ID)
        getline(iss, token, '|');

        // Читаємо значення ID
        getline(iss, token, '|');
        token.erase(token.begin(), std::find_if_not(token.begin(), token.end(), ::isspace));


        try {
            int currentId = std::stoi(token);
            if (currentId > maxId) {
                maxId = currentId;
            }
        } catch (const std::exception &e) {
            std::cout << "Error parsing ID: " << e.what() << std::endl;
        }
    }

    Jornal.close();

    if (maxId != std::numeric_limits<int>::min()) {
        //std::cout << "Max I D: " << maxId << std::endl;
        return maxId +1;
    } else {
        std::cout << "No valid IDs found." << std::endl;
        maxId = 0;
        return maxId+1;
    }
}

void Order::NewOrder(int UserID) {
    cout << UserID << endl;
    string OrderId;
    string PublicatonID;
    string PublicatioData;
    int PublicationPrice;
    int totalAmount;
    int totalPrice;
    Publication book;
    Order order;
    book.ShowAllBook();

    cout << endl << endl << "Введіть ID публікації яке хочете замовити: ";
    cin >> PublicatonID;
    book.getInfoBook(PublicatonID);
    cout<<"Обробка отриманої публікації..."<<endl;
    cout<<"Введіть кількість тиражу: ";
    cin>>totalAmount;
    PublicatioData = book.GetName() +" "+ book.GetAuthor()+" "+ to_string(book.GetPrice());
    cout<<"Ціна за штуку: " << book.GetPrice()<<endl;
    totalPrice = totalAmount * book.GetPrice();
    cout<<"Загальна ціна замовлення: "<<totalPrice<<endl;
    cout<<"Бажаєте підтведите замовлення?"<< endl<<"Y - так"<<endl;
    char Choice;
    cin>>Choice;
    if(Choice = 'Y'){
        order.SetPublicationData(PublicatioData);
        order.SetOrderId(to_string(FindMaxIdO()));
//    cout<<"IDS:"<<order.GetOrderId();
        order.SetPublicationID(PublicatonID);
        order.SetPublicationPrice(book.GetPrice());
        order.SetPublicationAmount(totalAmount);
        order.SetTotalPrice(totalPrice);

        ofstream Orders("OrderJornal.txt", ios::app);
        if (!Orders.is_open()){
            cout<<"Error opening file!"<<endl;
            return;
        }
        cout<<order.GetOrderId();
        Orders << "|" << order.GetOrderId() <<"|"<< UserID << "|" << order.GetPubicationID() << "|" << order.GetPublicationData() << "|" << order.GetPublicationPrice() << "|" << order.GetTotalAmoumt() << "|" << order.GetTotalPrice() << "|" << "\n";
        Orders.close();

        cout<<"Замовлення збережено"<<endl;
        Users user;
        user.LogIn();
    }
    else{
        Users user;
        user.LogIn();
    }
}

void Order::GetOrderByID(int UserID) {
    ifstream orderFile("OrderJornal.txt");
    if (!orderFile.is_open()) {
        cerr << "Error opening Order Journal file!" << endl;
        return;
    }

    string line;
    cout << "Orders for User with UserID " << UserID << ":" << endl;
    int numIterations = -1;  // Встановлено для виведення всіх записів
    int count = 0;  // Лічильник ітерацій

    while (getline(orderFile, line) && (numIterations == -1 || count < numIterations)) {
        istringstream iss(line);
        string orderId, orderUserId;

        // Читаємо значення OrderID та UserID
        getline(iss, orderId, '|');
        getline(iss, orderId, '|');
        getline(iss, orderUserId, '|');

        // Якщо UserID співпадає з вказаним значенням, виводимо рядок
        if (stoi(orderUserId) == UserID) {
            cout << line << endl;
            ++count;  // Збільшуємо лічильник ітерацій
        }
    }

    orderFile.close();
    Users user;
    user.LogIn();
}

void Order::ShowAllOrder() {
    ifstream inputFile("OrderJornal.txt");

    // Перевірте, чи файл вдалося відкрити
    if (!inputFile.is_open()) {
        std::cerr << "Не вдалося відкрити файл" << std::endl;
        return; // Поверніть код помилки
    }

    // Прочитайте та виведіть кожен рядок поспіль
    string line;
    while (getline(inputFile, line)) {
        cout << line << std::endl;
    }

    // Закрийте файл
    inputFile.close();
    return;
}

void Order::GetOrder(string ID) {
    ifstream Jornal("OrderJornal.txt");

    if (!Jornal.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    string line;
    vector<std::string> userData;

    while (getline(Jornal, line)) {
        std::istringstream iss(line);
        std::string userLine;

        // Читаємо всі сім комірок
        for (int i = 0; i < 8; ++i) {
            if (getline(iss, userLine, '|')) {
                // Видаляємо зайві пробіли з даних
                userLine.erase(userLine.begin(), std::find_if_not(userLine.begin(), userLine.end(), ::isspace));

                userData.push_back(userLine);
            } else {
                // Можливо, важливо обробити помилку, якщо не вдається прочитати сім комірок
                std::cout << "Error reading data!" << std::endl;
                return;
            }
        }

        if (ID == userData[1]) {
            // Отримано дані користувача, тепер записуємо їх в новий файл
            try {
                std::ofstream newUserFile("Order.txt", ios::app);

                if (!newUserFile.is_open()) {
                    std::cout << "Error opening file for writing!" << std::endl;
                    return;
                }
                // Розпаковуємо дані відповідно до змінних
                OrderId = userData[1];
                UserId = userData[2];
                PublicatonID = userData[3];
                PublicatioData = userData[4];
                PublicationPrice = stoi(userData[5]);
                totalAmount = stoi(userData[6]);
                totalPrice = stoi(userData[7]);


                Order::SetOrderId(OrderId);
                Order::SetUserId(UserId);
                Order::SetPublicationID(PublicatonID);
                Order::SetPublicationData(PublicatioData);
                Order::SetPublicationPrice(PublicationPrice);
                Order::SetPublicationAmount(totalAmount);
                Order::SetTotalPrice(totalPrice);
            } catch (const std::exception &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }

            break;  // Зупиняємо пошук, оскільки ми знайшли користувача
        }

        userData.clear();  // Очищаємо вектор для наступного рядка
    }

    Jornal.close();


}

void Order::DeleteOrder(string OrderID) {
    }
