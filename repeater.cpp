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
    string commandUsr;
    
    cout << "Welcome!" << '\n';
    cout << "To create a directory, type MKDIR " << '\n';
    cout << "To delete a directory, type DELDIR" << '\n';
    cout << "To edit a directory, type EDITDIR" << '\n';
    cout << "To show content of directory, type LISTDIR <directory>" << '\n';
    cout << "To show everything, type LISTALL" << '\n';
    cout << "To show hints, type HELP" << '\n';
    cout << "To exit the program, type EXIT" << '\n';

    while (cout << ">> ", getline(cin, commandUsr)) {

        commandUsr = upperCaseWord(commandUsr);
        
        // 1. Создание раздела
        if (commandUsr == "MKDIR") {
            cout << "To cancel, type EXIT" << '\n';
            cout << "Enter the name of the new directory: \n";
            getline(cin, commandUsr);
            commandUsr = upperCaseWord(commandUsr);
            if (commandUsr == "EXIT") { continue; }
            ofstream newdir; // <!>
            newdir.open("directories.txt", ofstream::app);
            newdir << "### " + commandUsr + " ###" + '\n' + "---###---" << '\n';
            newdir.close();
            cout << "Directory created" << '\n';
        }

        // 2. Удаление раздела
        if (commandUsr == "DELDIR") { 
            cout << "To cancel, type EXIT" << '\n';                  // Если файл пустой, то выводить сообщение:
            cout << "Enter the name of the directory to delete: \n"; // "Nothing to delete!"
            getline(cin, commandUsr);                                // (доработать)
            commandUsr = upperCaseWord(commandUsr);

            if (commandUsr == "EXIT") { break; }
            
            bool flagToFind = false;
            string finder;
            ifstream toCopyDir("directories.txt");
            ofstream fakeDir("directoriesTemp.txt");
            while (getline(toCopyDir, finder)) {
                if (finder == "### " + commandUsr + " ###") {
                    flagToFind = true;
                    finder = "";
                }
                else if (flagToFind == true) {
                    if (finder == "---###---") {
                        flagToFind = false;
                        finder = "";
                        continue;
                    }
                    else {
                        finder = "";
                        continue;
                    }
                }
                else {
                    fakeDir << finder << '\n';
                    finder = "";
                }
            }
            toCopyDir.close();
            fakeDir.close();
            ofstream trueDir("directories.txt");
            ifstream toTrueDir("directoriesTemp.txt");
            while (getline(toTrueDir, finder)) {
                trueDir << finder << '\n';
            }
            trueDir.close();
            toTrueDir.close();
            remove("directoriesTemp.txt");
        }

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
    
    return 0;
}
