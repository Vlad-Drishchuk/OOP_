//
// Created by Vladyslav Drishchuk on 16.12.2023.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "string"
#include "limits"
#include "Publication.h"
#include "Administrator.h"

int FindMaxIdP();
void Publication::SetId(const string ValId){
    PublicationId = ValId;
}
void Publication::SetName(const string ValId){
    PublicationName =ValId;
}
void Publication::SetAuthor(const string ValId){
    Author = ValId;
}
void Publication::SetPrice(int ValId){
    Price = ValId;
}


void Publication::bookNew() {
    int id;
    string title;
    string author;
    int price;

    id = FindMaxIdP();
    id = id +1;
    cout<<"Введіть назву книги:"<<endl;
    cin>>title;
    cout<<"Введіть автора:"<<endl;
    cin>>author;
    cout<<"Введіть ціну:"<<endl;
    cin>>price;

    SetId(to_string(id));
    SetName(title);
    SetAuthor(author);
    SetPrice(price);
    // Запис у файл
    WriteToFile();
    cout << "Записано!" << endl;
    return;
}

void Publication::WriteToFile() {
    ofstream NewBook("Publication.txt", ios::app);
    if (!NewBook.is_open()){
        cout<<"Error opening file!"<<endl;
        return;
    }

    NewBook<<"|"<<GetId()<<"|"<<GetName()<<"|"<<GetAuthor()<<"|"<<GetPrice()<<"|"<<"\n";
    NewBook.close();
    return;
}

int FindMaxIdP() {

    std::ifstream PublicationJ("Publication.txt");

    if (!PublicationJ.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return 0;
    }

    int maxId = std::numeric_limits<int>::min(); // Початкове значення для порівняння

    std::string line;
    while (getline(PublicationJ, line)) {
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

    PublicationJ.close();

    if (maxId != std::numeric_limits<int>::min()) {
        std::cout << "Max ID: " << maxId << std::endl;
        return maxId;
    } else {
        std::cout << "No valid IDs found." << std::endl;
        return 0;
    }
}

void Publication::ShowAllBook() {
    cout<<"Показ всіх публікацій..."<<endl;
    cout<<"|ID|Назва|Автор|Ціна|"<<endl;
    ifstream inputFile("Publication.txt");

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
string Publication::getInfoBook(const string& id) {
    ifstream Jornal("Publication.txt");
    if (!Jornal.is_open()) {
        cerr << "Error opening file!" << endl;
        return "";
    }

    string line;
    vector<std::string> userData;

    while (getline(Jornal, line)) {
        istringstream iss(line);
        string token;
        string userLine;

        for (int i = 0; i < 5; ++i) {
            if (getline(iss, userLine, '|')) {
                // Видаляємо зайві пробіли з даних
                userLine.erase(userLine.begin(), std::find_if_not(userLine.begin(), userLine.end(), ::isspace));

                userData.push_back(userLine);
            } else {
                // Можливо, важливо обробити помилку, якщо не вдається прочитати сім комірок
                std::cout << "Error reading data!" << std::endl;
                return "v ";
            }
        }

        if (id == userData[1]) {
            cout << userData[1];
            // Отримано дані користувача, тепер записуємо їх в новий файл
            try {
                std::ofstream newUserFile("UserP.txt");

                if (!newUserFile.is_open()) {
                    std::cout << "Error opening file for writing!" << std::endl;
                    return "";
                }
                // Розпаковуємо дані відповідно до змінних
                PublicationId = userData[1];
                PublicationName = userData[2];
                Author = userData[3];
                Price = stoi(userData[4]);


                // Записуємо дані в новий файл
                newUserFile << "|" << PublicationId << "|" << PublicationName << "|" << Author << "|" << Price
                            << "|" << "\n";

                newUserFile.close();
                Publication::SetId(PublicationId);
                Publication::SetName(PublicationName);
                Publication::SetAuthor(Author);
                Publication::SetPrice(Price);
            } catch (const std::exception &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }

            break;  // Зупиняємо пошук, оскільки ми знайшли користувача
        }

        userData.clear();  // Очищаємо вектор для наступного рядка
    }

    Jornal.close();

        ifstream inputFile("UserP.txt");

        // Перевірте, чи файл вдалося відкрити
        if (!inputFile.is_open()) {
            std::cerr << "Не вдалося відкрити файл" << std::endl;
            return "s"; // Поверніть код помилки
        }

        // Прочитайте та виведіть кожен рядок поспіль
        string line2;
        while (getline(inputFile, line)) {
            cout << line2 << std::endl;
        }

        // Закрийте файл
        inputFile.close();
        return line2;

}
