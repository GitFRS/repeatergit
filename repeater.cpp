#include <bits/stdc++.h>
using namespace std;
string upperCaseWord(string str) {
    string newString = "";
    for (auto c : str) {
        if (isupper(c) == true) {
            newString += c;
        }
        else if (c == ' ') {
            continue;
        }
        else {
            c = toupper(c);
            newString += c;
        }
    }
    return newString;
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp1251>nul"); 
    string commandUsr;

    ifstream start("source.txt");
    while (getline(start, commandUsr)) { // Костыль, возможная ошибка: записывать всё в одну переменную
        cout << commandUsr << '\n';      // commandUsr <!!!>
    }
    start.close();

    while (cout << ">> ", getline(cin, commandUsr)) {

        commandUsr = upperCaseWord(commandUsr);
        
        // 1. Создание раздела
        if (commandUsr == "MKDIR") {
            cout << "Для отмены введите EXIT" << '\n';
            cout << "Введите название нового раздела: ";
            getline(cin, commandUsr);
            commandUsr = upperCaseWord(commandUsr);
            if (commandUsr == "EXIT") { continue; }
            ofstream newdir; // <!>
            newdir.open("directories.txt", ofstream::app);
            newdir << "### " + commandUsr + " ###" << '\n';
            newdir.close();
            cout << "Раздел создан" << '\n';
        }

        // 2. Удаление раздела
        //if (commandUsr == "DELDIR") { }

        // 3. Редактирование раздела
        //if (commandUsr == "EDITDIR") { }
        

        // 5. Вывод всего содержимого
        if (commandUsr == "LISTALL") {
            ifstream list; // <?>
            list.open("directories.txt");
            while (getline(list, commandUsr)) { // <!!!> 
                cout << commandUsr << '\n';
            }
            list.close();
            continue;
        }

        // 6. Вывод подсказок
        if (commandUsr == "HELP") {
            ifstream help; // <?>
            help.open("help.txt");
            while (getline(help, commandUsr)) {
                cout << commandUsr << '\n';
            }
            help.close();
            continue;
 
        }

        // 7. Выход из программы
        if (commandUsr == "EXIT") {
            cout << "See you next time!" << '\n';
            system("pause>nul");
            return 0;
        }


    }
    
    system("pause>nul");
    return 0;
}
