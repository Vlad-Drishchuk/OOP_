#include <iostream>
#include <vector>
#include <string>
#include "Users.h"
#include "Administrator.h"
#include "Publication.h"

using namespace std;



int main()
{
    Administrator administrator;
    Users user;
    cout << "Привіт!\n1. Увійти як користувач\n2. Увійти як адмін\nКим ви являєтесь: ";
    int a;
    cin >> a;
    if (a == 1){

        user.LogIn();
    }
    if (a==2){
        administrator.setPassword();
        administrator.LoginForAdmin();
        main();
    }
    else{
        return 0;
    }

    user.CleanFile();
    return 0;

}