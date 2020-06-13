#include <bits/stdc++.h>
using namespace std;

struct dirs {
	ifstream copy;
	ofstream paste;
};

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

bool isExist(string commandUsr) {
    ifstream dir("directories.txt");
    string str;
    while (getline(dir, str)) {
        if (str == "### " + commandUsr + " ###") {
            dir.close();
            return true;
        }
    }
    dir.close();
    return false;
}

string clearWord(string a) {
    string b = "";
    for (auto c : a) {
        if (c != ' ') {
            b += c;
        }
    }
    return b;
}

void returnToDefaultDir() {
	string finderCopy;
	dirs copyPaste;
	copyPaste.copy.open("directoriesTemp.txt");
	copyPaste.paste.open("directories.txt");
	while (getline(copyPaste.copy, finderCopy)) {
		copyPaste.paste << finderCopy << '\n';
	}
	cout << "Operation completed!\n\n";
	copyPaste.copy.close();
	copyPaste.paste.close();
	remove("directoriesTemp.txt");
}


int main() {
    
    string commandUsr;

    vector <pair <string, string>> DICT;

    char addedTime[40];
    char repTime[40];
    time_t dmy = time(NULL); 
    time_t dmy2 = time(NULL) + 604800;
    tm* timeinfo = localtime(&dmy);
    const char* format = "%d.%m.%Y";
    strftime(addedTime, 40, format, timeinfo);
    tm* timeinfo1 = localtime(&dmy2);
    strftime(repTime, 40, format, timeinfo1);
    
    cout << "Welcome!" << '\n';
    cout << "To enter training, type TRAIN" << '\n';              // X
    cout << "To create a directory, type MKDIR " << '\n';         // \/
    cout << "To delete a directory, type DELDIR" << '\n';         // \/
    cout << "To edit a directory, type EDITDIR" << '\n';          // X
    cout << "To show content of directory, type LISTDIR" << '\n'; // \/
    cout << "To show everything, type LISTALL" << '\n';           // \/
    cout << "To show hints, type HELP" << '\n';                   // \/
    cout << "To exit the program, type EXIT\n\n";           // \/

    while (getline(cin, commandUsr)) {

        commandUsr = upperCaseWord(commandUsr);
        
        // 1. Вход в режим тренировки
         if (commandUsr == "TRAIN") {
             cout << "\nTo cancel or exit, type EXIT\n";
             cout << "If you want train everything, type TRAINALL\n";
             cout << "If you want train the directory, type TRAINDIR\n";
             getline(cin, commandUsr);
             commandUsr = upperCaseWord(commandUsr);
             if (commandUsr == "EXIT") { cout << '\n'; continue; }
             string words, wordsFirst, wordsSecond;
             if (commandUsr == "TRAINALL") {
                 cout << "Enter the key to the word: \n";
                 ifstream toTrain1("directories.txt");
                 while (!toTrain1.eof()) {
                     getline(toTrain1, words);
                     if (words[0] == '#' && words[1] == '#' && words[2] == '#' ||
                         words[0] == '-' && words[1] == '-' && words[2] == '-' ||
                         words[8] == 'W' && words[9] == 'o' && words[10] == 'r' && words[11] == 'd') {
                         continue;
                     }
                     else { 
                         if (words != "") {
                             wordsFirst = clearWord(words.substr(0, 20));
                             wordsSecond = clearWord(words.substr(21, 20)); 
                             DICT.push_back({ wordsFirst, wordsSecond }); 
                         }
                    }
                 }
                 toTrain1.close();
                 int countOfRight = 0;
                 random_shuffle(DICT.begin(), DICT.end());
                 while (DICT.size() > 0) {
                     string usrKey;
                     cout << DICT[0].first << "\nKey is: ";
                     cin >> usrKey;
                     if (usrKey == "EXIT") { break; }
                     if (usrKey == DICT[0].second) {
                         countOfRight++;
                     }
                     DICT.erase(DICT.begin());
                 }
                 cout << "Training is finished!\nYour score is: " << countOfRight << "\n\n";
             }
			 else if (commandUsr == "TRAINDIR") {
				cout << "Enter the name of the directory to train: \n"; 
				getline(cin, commandUsr);                                
				commandUsr = upperCaseWord(commandUsr);
				if (isExist(commandUsr) == false) { cout << "This directory doesn't exist!\n\n"; continue; }
				// %команда в команде%
				else {

				}
			 } 
		 }

        // 2. Создание раздела
        if (commandUsr == "MKDIR") {
            cout << "\nTo cancel, type EXIT\n" << "Enter the name of the new directory: \n"; 
            getline(cin, commandUsr);
            commandUsr = upperCaseWord(commandUsr);

            if (isExist(commandUsr) == true) { cout << "This directory is already exist!\n\n"; continue; }
            if (commandUsr == "EXIT") { cout << '\n'; continue; }
            
			ofstream newdir;
            newdir.open("directories.txt", ofstream::app);
            newdir << "### " + commandUsr + " ###" + '\n';
            newdir << "        Word        #        Key        #" 
                   << "    Added    #    Next repeat\n\n";
            newdir << "---###---" << '\n';
            newdir.close();
            cout << "Directory created\n\n";
        }

        // 3. Удаление раздела
        if (commandUsr == "DELDIR") { 
            bool flagToFind1 = false;
            string finderCopy;
			dirs copyPaste1;


			copyPaste1.copy.open("directories.txt");
            copyPaste1.paste.open("directoriesTemp.txt");
			getline(copyPaste1.copy, finderCopy);
			if (finderCopy == "") { cout << "Nothing to delete!\n\n"; continue; }
			copyPaste1.copy.close();

            copyPaste1.copy.open("directories.txt");
            cout << "\nTo cancel, type EXIT" << '\n'; 
            cout << "Enter the name of the directory to delete: \n"; 
            getline(cin, commandUsr);                                
            commandUsr = upperCaseWord(commandUsr);
            if (commandUsr == "EXIT") { cout << '\n'; continue; }
			else if (commandUsr == "TRAIN" || commandUsr == "MKDIR" || commandUsr == "DELDIR" ||
					 commandUsr == "EDITDIR" || commandUsr == "LISTDIR" || commandUsr == "LISTALL" ||
					 commandUsr == "HELP") { cout << "Incorrect input\n\n"; continue; }			
            while (getline(copyPaste1.copy, finderCopy)) {
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
                    copyPaste1.paste << finderCopy << '\n';
                    finderCopy = "";
                }
            }
            copyPaste1.copy.close();
            copyPaste1.paste.close();
			returnToDefaultDir();
        }

        // 4. Редактирование раздела
        if (commandUsr == "EDITDIR") {    
            cout << "To cancel, type EXIT\n" << "Enter the name of the directory to edit: \n";
            getline(cin, commandUsr);
            cout << '\n';
            commandUsr = upperCaseWord(commandUsr);

            if (isExist(commandUsr) == false) { cout << "Nothing to edit!\n\n"; continue; }
            if (commandUsr == "EXIT") { cout << '\n'; continue; }
            
			cout << "To stop edit, type EXIT twice\n" << "Enter words and keys after it: \n";
            bool flagToFind2 = false, exitFlag = false;
            string finderEditor;
			dirs copyPaste2;
			copyPaste2.copy.open("directories.txt");
			copyPaste2.paste.open("directoriesTemp.txt");
            while (getline(copyPaste2.copy, finderEditor)) {
                if (finderEditor == "### " + commandUsr + " ###") {
                    copyPaste2.paste << finderEditor << '\n';
                    copyPaste2.paste << "        Word        #        Key         #" 
                             << "    Added    #    Next repeat\n";
                    flagToFind2 = true;
                    finderEditor = "";
                }
                else if (flagToFind2 == true) {
                    if (finderEditor == "---###---") {
                        copyPaste2.paste << finderEditor;
                        finderEditor = "";
                    }
                    else {
                        string infWK;
                        while (cin >> infWK) {
                            char fullInf[] = "                                                                           ";
                            if (infWK[0] == 'E' && infWK[1] == 'X' && infWK[2] == 'I' && infWK[3] == 'T') { flagToFind2 = false; break; }
                            for (int i = 0; infWK[i] != '\0'; i++) { fullInf[i+1] = infWK[i]; } 
                            cin >> infWK;
                            for (int i = 0; infWK[i] != '\0'; i++) { fullInf[i+22] = infWK[i]; }
                            for (int i = 0; addedTime[i] != '\0'; i++) { fullInf[i+43] = addedTime[i]; }
                            for (int i = 0; repTime[i] != '\0'; i++) { fullInf[i+60] = repTime[i]; }
                            copyPaste2.paste << fullInf << '\n';
                        }
                    }
                }
                else {
                    copyPaste2.paste << finderEditor << '\n';
                    finderEditor = "";
                }
            }
            copyPaste2.paste.close();
            copyPaste2.copy.close();
			returnToDefaultDir();
        }

        // 5. Вывод содержимого раздела
        if (commandUsr == "LISTDIR") {
            cout << "\nTo cancel, type EXIT" << '\n';
            cout << "Enter the name of the directory to list: \n";
            getline(cin, commandUsr);
            cout << '\n';
            commandUsr = upperCaseWord(commandUsr);
			if (isExist(commandUsr) == false) { cout << "Nothing to list!\n\n"; continue; }
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
                    else { cout << finderLister << '\n'; }
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
            while (getline(help, commandUsr)) { cout << commandUsr << '\n'; }
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
