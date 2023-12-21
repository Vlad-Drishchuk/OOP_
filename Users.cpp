
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "string"
#include "limits"
#include "Users.h"
#include "Order.h"

using namespace std;


void Users::SetName(const std::string ValName) {
    Name = ValName;
}
void Users::SetId(string ValId) {
    UserId = ValId;
}

void Users::SetlastName(std::string ValName) {
    LastName = ValName;
}
void Users::SetAddres(string ValName){
    Addres = ValName;
}
void Users::SetEmail(string ValName){
    Email = ValName;
}

void Users::LogIn(){
    cout<< "Привіт, введи свій ID: ";
    string ID;
    cin>>ID;
    bool result = IdentificationUser(ID);

    if (result) {
        GetUser(ID);
        int Choice = 0;
        cout << "Привіт! " << Users::getName() << endl;
        cout << "Меню користувача: " << endl ;
        cout << "1. Додати замовлення\n" <<"2. Мої замовлення\n";
        cin >> Choice;
        Order MyOrder;
        int id = stoi(ID);
        if(Choice == 1) {
            MyOrder.NewOrder(id);
        }
        if(Choice == 2){
            MyOrder.GetOrderByID(id);
        }
        if(Choice == 0){
            return;
        }


    } else {
        char Choice = 'x';
        std::cout << "User not found!!!" << std::endl << result;
        cout << "Бажаєте зареєструватись?" << endl;
        cout << "Y-так, N-ні" <<endl;
        cin >> Choice;
        if (Choice == 'Y'){
            RgisterNewUser();
        } else{
            cout << "Завершення програми...";
            return;
        }

    }
}

bool Users::IdentificationUser(string ID){
    std::ifstream Jornal("Jornal.txt");

    if (!Jornal.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return false;
    }

    std::string line;
    std::string token = "NOT";

    while (getline(Jornal, line)) {
        std::istringstream iss(line);

        // Пропускаємо першу ячейку
        getline(iss, token, '|');

        // Витягаємо дані з другої ячейки
        getline(iss, token, '|');

        // Видаляємо зайві пробіли з даних
        token.erase(token.begin(), std::find_if_not(token.begin(), token.end(), ::isspace));


        if (ID == token) {
            Jornal.close();
            return true;
        }
    }

    Jornal.close();

    // Якщо ID не знайдено, повертаємо false
    return false;
}

void Users::GetUser(const string ID) {
    ifstream Jornal("Jornal.txt");

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
        for (int i = 0; i < 6; ++i) {
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
                std::ofstream newUserFile("UserFile.txt");

                if (!newUserFile.is_open()) {
                    std::cout << "Error opening file for writing!" << std::endl;
                    return;
                }
                bool userData7;
                // Розпаковуємо дані відповідно до змінних
                UserId = std::stoi(userData[1]);
                Name = userData[2];
                LastName = userData[3];
                Addres = userData[4];
                Email = userData[5];


                // Записуємо дані в новий файл
                newUserFile << UserId << "|" << Name << "|" << LastName << "|" << Addres << "|"
                            << Email << "|" << "\n";

                newUserFile.close();
                Users::SetId(UserId);
                Users::SetName(Name);
                Users::SetlastName(LastName);
                Users::SetAddres(Addres);
                Users::SetEmail(Email);
            } catch (const std::exception &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }

            break;  // Зупиняємо пошук, оскільки ми знайшли користувача
        }

        userData.clear();  // Очищаємо вектор для наступного рядка
    }

    Jornal.close();

}
int FindMaxId() {

    std::ifstream Jornal("Jornal.txt");

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
        std::cout << "Max ID: " << maxId << std::endl;
        return maxId;
    } else {
        std::cout << "No valid IDs found." << std::endl;
    }
}

void Users::RgisterNewUser() {
    cout << "Створення нового користувача..." << endl;
    int UserID;
    string RName, RLastName, RAddres, REmail;
    UserID = FindMaxId();
    UserID = UserID+1;
    string UserIDS = to_string(UserID);
    cout <<"Ваш userId визначно: " << UserIDS << endl;
    cout<< "Введіть ваше імʼя: ";
    cin >> RName;
    cout << endl << "Введіть ваше прізвище: ";
    cin >> RLastName;
    cout << endl << "Введіть свій індекс: ";
    cin >> RAddres ;
    cout << endl << "Введіть свій email:";
    cin >> REmail;


    cout << endl << "Запис...";


    cout << ".";

    ofstream Jornal("Jornal.txt", ios::app);

    if (!Jornal.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    Jornal <<"|"<< UserIDS << "|"<<RName<<"|"<<RLastName<<"|"<<RAddres<<"|"<< REmail<<"|"<<"\n";



    Jornal.close();
    LogIn();
}

void Users::CleanFile(){
    ofstream UserFile("UserFile.txt");
    if (!UserFile.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return;
    }
    UserFile<<" ";
    UserFile.close();
}
