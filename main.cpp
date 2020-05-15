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

unsigned long toRepeat1(unsigned long intDMY) {
    unsigned long repDay = intDMY / 60 % 60 % 10; // минуты mM
    repDay = intDMY / 60 % 60 / 10;
    return repDay;
}

int main() {
    
    string commandUsr;

    vector <pair <string, string>> DICT;

    char addedTime[40];
    char repTime[40];
    time_t dmy = time(NULL); 
    time_t dmy2 = time(NULL) + 604800;
    tm* timeinfo = localtime(&dmy);
    const char* format = "%d|%m|%Y";
    strftime(addedTime, 40, format, timeinfo);
    cout << addedTime << '\n';
    tm* timeinfo1 = localtime(&dmy2);
    strftime(repTime, 40, format, timeinfo1);
    cout << repTime << '\n';


    
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
            newdir << "### " + commandUsr + " ###" + '\n'/* + "---###---" << '\n'*/;
            newdir << "        Word        #        Key        #" 
                   << "    Added    #    Next repeat\n\n";
            newdir << "---###---" << '\n';
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
            ifstream toCopyDir1("directories.txt");
            ofstream fakeDir1("directoriesTemp.txt");
            while (getline(toCopyDir1, finderCopy)) {
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
                    fakeDir1 << finderCopy << '\n';
                    finderCopy = "";
                }
            }
            toCopyDir1.close();
            fakeDir1.close();
            ofstream trueDir1("directories.txt");
            ifstream toTrueDir1("directoriesTemp.txt");
            while (getline(toTrueDir1, finderCopy)) {
                trueDir1 << finderCopy << '\n';
            }
            cout << "Directory deleted\n\n";
            trueDir1.close();
            toTrueDir1.close();
            remove("directoriesTemp.txt");
        }



        // 4. Редактирование раздела
        if (commandUsr == "EDITDIR") {                // ПРЕДУПРЕЖДЕНИЕ!!!
            cout << "To cancel, type EXIT\n" << "Enter the name of the directory to edit: \n";
            getline(cin, commandUsr);
            cout << '\n';
            commandUsr = upperCaseWord(commandUsr);
            if (commandUsr == "EXIT") { cout << '\n'; continue; }
            cout << "To stop edit, type EXIT twice\n" << "Enter words and keys after it: \n";
            bool flagToFind2 = false, exitFlag = false;
            string finderEditor;
            ifstream toCopyDir2("directories.txt");
            ofstream fakeDir2("directoriesTemp.txt");
            while (getline(toCopyDir2, finderEditor)) {
                if (finderEditor == "### " + commandUsr + " ###") {
                    fakeDir2 << finderEditor << '\n';
                    fakeDir2 << "        Word        #        Key         #" 
                             << "    Added    #    Next repeat\n";
                    flagToFind2 = true;
                    finderEditor = "";
                }
                else if (flagToFind2 == true) {
                    if (finderEditor == "---###---") {
                        fakeDir2 << finderEditor;
                        flagToFind2 = false;
                        finderEditor = "";
                    }
                    else {
                        string infWK;
                        while (cin >> infWK) {
                            char fullInf[] = "                                                                           ";
                            /*for (int j = 0; j < 75; j++) { // Создание специальной строки
                                fullInf[j] = ' ';          // Для правильной записи в файл
                            }*/                             
                                                         
                            if (infWK[0] == 'E' && infWK[1] == 'X' && infWK[2] == 'I' && infWK[3] == 'T') { flagToFind2 = false; break; }
                            for (int i = 0; infWK[i] != '\0'; i++) { 
                                fullInf[i + 1] = infWK[i];
                            }
                            cin >> infWK;
                            for (int i = 0; infWK[i] != '\0'; i++) {
                                fullInf[i+22] = infWK[i];
                            }
                            for (int i = 0; addedTime[i] != '\0'; i++) {
                                fullInf[i+43] = addedTime[i];
                            }
                            for (int i = 0; repTime[i] != '\0'; i++) {
                                fullInf[i+60] = repTime[i];
                            }
                            fakeDir2 << fullInf << '\n';
                        }
                    }
                }
                else {
                    fakeDir2 << finderEditor << '\n';
                    finderEditor = "";
                }
            }
            cout << "Editing complete\n";
            fakeDir2.close();
            toCopyDir2.close();
            ofstream trueDir2("directories.txt");
            ifstream toTrueDir2("directoriesTemp.txt");
            while (getline(toTrueDir2, finderEditor)) {
                trueDir2 << finderEditor << '\n';
            }
            trueDir2.close();
            toTrueDir2.close();
            remove("directoriesTemp.txt");
        }



        // 5. Вывод содержимого раздела
        if (commandUsr == "LISTDIR") {
            cout << "\nTo cancel, type EXIT" << '\n';
            cout << "Enter the name of the directory to list: \n";
            cout << ">> ";
            getline(cin, commandUsr);
            cout << '\n';
            commandUsr = upperCaseWord(commandUsr);
            if (commandUsr == "EXIT") { cout << '\n'; continue; }
            cout << "========================================================\n\n";
            bool flagToFind3 = false;
            string finderLister;
            ifstream listdir("directories.txt");
            while (getline(listdir, finderLister)) {
                if (finderLister == "### " + commandUsr + " ###") {
                    flagToFind3 = true;
                    cout << finderLister << '\n';
                }
                else if (flagToFind3 == true) {
                    if (finderLister == "---###---") {
                        cout << finderLister << '\n';
                        break;
                    }
                    else {
                        cout << finderLister << '\n';
                    }
                }
            }
            cout << "\n========================================================\n\n";
            listdir.close();
        }

        // 6. Вывод всего содержимого
        if (commandUsr == "LISTALL") {
            cout << "\n========================================================\n\n";
            string listall;
            ifstream list;
            list.open("directories.txt");
            while (getline(list, listall)) { cout << listall << '\n'; }
            cout << "\n========================================================\n\n";
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
