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
    //time_t tm = time(NULL); // УДАЛИТЬ !!!
    //cout << ctime(&tm) << '\n';
    string commandUsr;
    
    cout << "Welcome!" << '\n';
    cout << "To enter training, type TRAIN" << '\n';              // X
    cout << "To create a directory, type MKDIR " << '\n';         // \/
    cout << "To delete a directory, type DELDIR" << '\n';         // \/
    cout << "To edit a directory, type EDITDIR" << '\n';          // X
    cout << "To show content of directory, type LISTDIR" << '\n'; // \/
    cout << "To show everything, type LISTALL" << '\n';           // \/
    cout << "To show hints, type HELP" << '\n';                   // \/
    cout << "To exit the program, type EXIT\n\n";           // \/

    while (cout << ">> ", getline(cin, commandUsr)) {

        commandUsr = upperCaseWord(commandUsr);
        

        // 1. Вход в режим тренировки
        // if (commandUsr == "TRAIN") {}


        // 2. Создание раздела
        if (commandUsr == "MKDIR") {
            cout << "\nTo cancel, type EXIT" << '\n';
            cout << "Enter the name of the new directory: \n"; // Ввести ограничение
            cout << ">> ";                                     // Если два раздела
            getline(cin, commandUsr);                          // Называются одинаково
            commandUsr = upperCaseWord(commandUsr);
            if (commandUsr == "EXIT") { cout << '\n'; continue; }
            ofstream newdir; // <!>
            newdir.open("directories.txt", ofstream::app);
            newdir << "### " + commandUsr + " ###" + '\n' + "---###---" << '\n';
            newdir.close();
            cout << "Directory created\n\n";
        }
        // 3. Удаление раздела
        if (commandUsr == "DELDIR") { 
            cout << "\nTo cancel, type EXIT" << '\n';                  // Если файл пустой, то выводить сообщение:
            cout << "Enter the name of the directory to delete: \n"; // "Nothing to delete!" 
            cout << ">> ";
            getline(cin, commandUsr);                                
            commandUsr = upperCaseWord(commandUsr);
            if (commandUsr == "EXIT") { cout << '\n'; continue; }            
            bool flagToFind1 = false;
            string finderCopy;
            ifstream toCopyDir("directories.txt");
            ofstream fakeDir("directoriesTemp.txt");
            while (getline(toCopyDir, finderCopy)) {
                if (finderCopy == "### " + commandUsr + " ###") {
                    flagToFind1 = true;
                    finderCopy = "";
                }
                else if (flagToFind1 == true) {
                    if (finderCopy == "---###---") {
                        flagToFind1 = false;
                        finderCopy = "";
                        continue;
                    }
                    else {
                        finderCopy = "";
                        continue;
                    }
                }
                else {
                    fakeDir << finderCopy << '\n';
                    finderCopy = "";
                }
            }
            toCopyDir.close();
            fakeDir.close();
            ofstream trueDir("directories.txt");
            ifstream toTrueDir("directoriesTemp.txt");
            while (getline(toTrueDir, finderCopy)) {
                trueDir << finderCopy << '\n';
            }
            cout << "Directory deleted\n\n";
            trueDir.close();
            toTrueDir.close();
            remove("directoriesTemp.txt");
        }
        // 4. Редактирование раздела
        /*if (commandUsr == "EDITDIR") {
            cout << "To cancel, type EXIT" << '\n';
            cout << "Enter the name of the directory to edit: \n";
            getline(cin, commandUsr);
            cout << '\n';
        */ 
        // 5. Вывод содержимого раздела
        if (commandUsr == "LISTDIR") {
            cout << "\nTo cancel, type EXIT" << '\n';
            cout << "Enter the name of the directory to list: \n";
            cout << ">> ";
            getline(cin, commandUsr);
            cout << '\n';
            commandUsr = upperCaseWord(commandUsr);
            if (commandUsr == "EXIT") { cout << '\n'; continue; }
            cout << "==========\n\n";
            bool flagToFind2 = false;
            string finderLister;
            ifstream listdir("directories.txt");
            while (getline(listdir, finderLister)) {
                if (finderLister == "### " + commandUsr + " ###") {
                    flagToFind2 = true;
                    cout << "==========\n\n";
                    cout << finderLister << '\n';
                }
                else if (flagToFind2 == true) {
                    if (finderLister == "---###---") {
                        cout << finderLister << '\n';
                        break;
                    }
                    else {
                        cout << finderLister << '\n';
                    }
                }
            }
            cout << "\n==========\n\n";
            listdir.close();
        }
    



        // 6. Вывод всего содержимого
        if (commandUsr == "LISTALL") {
            cout << "\n==========\n\n";
            string listall;
            ifstream list;
            list.open("directories.txt");
            while (getline(list, listall)) { cout << listall << '\n'; }
            cout << "\n==========\n\n";
            list.close();
            continue;
        }
        // 7. Вывод подсказок
        if (commandUsr == "HELP") {
            cout << "==========\n\n";
            ifstream help;
            help.open("help.txt");
            while (getline(help, commandUsr)) {
                cout << commandUsr << '\n';
            }
            cout << "\n==========\n";
            help.close();
            continue;
        }
        // 8. Выход из программы
        if (commandUsr == "EXIT") {
            cout << "See you next time!" << '\n';
            system("pause>nul");
            return 0;
        }
    }
    return 0;
}
