#ifndef OOPV2_PUBLICATION_H
#define OOPV2_PUBLICATION_H

#include <iostream>
#include <string>
#include "Administrator.h"

using namespace std;


// Додайте це оголошення класу
class Administrator;

class Publication {
private:
    string PublicationId;
    string PublicationName;
    string Author;
    int Price;

public:
    void SetId(string ValId);
    void SetName(string ValId);
    void SetAuthor(string ValId);
    void SetPrice(int ValId);

    string GetId(){
        return PublicationId;
    }
    string GetName(){
        return PublicationName;
    }
    string GetAuthor(){
        return Author;
    }
    int GetPrice(){
        return Price;
    }

    friend class Administrator;
    friend class Order;

    void bookNew();
    string getInfoBook(const string& id);
    void WriteToFile();
    void ShowAllBook();

};

#endif //OOPV2_PUBLICATION_H
