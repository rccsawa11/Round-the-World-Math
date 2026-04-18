#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
const int numQues = 7;
string selectLanguage();
string helloUser(string language);
bool askQues(string language, string power, int &score);
int main() {
    srand(time(0));
    string language = selectLanguage();
    helloUser(language);
    string power;
    cout << "\nChoose your power:\n";
    cout << "1. Multiplier 2x\n";
    cout << "2. Skip 1 question\n";
    cout << "3. Earn 10 bonus points\n";
    cout << "4. Reveal answer\n";
    cout << "Type your choice: ";
    cin >> power;
    cout << "\nEASY THERE!\n";
    cout << "You earn powers every 10 points.\n";
    int score = 0;
    for (int i = 0; i < numQues; i++) {
        askQues(language, power, score);
    }
    cout << "\nFINAL SCORE: " << score << endl;
    ofstream outFile("scores.txt");
    outFile << "Final Score: " << score << endl;
    outFile.close();
    return 0;
}
string selectLanguage() {
    string langChoice;
    cout << "Select language:\n";
    cout << "1. English\n2. Espanol\n";
    cin >> langChoice;
    if (langChoice == "1") {
        cout << "English selected.\n";
        return "English";
    } else {
        cout << "Espanol seleccionado.\n";
        return "Spanish";
    }
}
string helloUser(string language) {
    string name;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Welcome, " << name << "!\n";
    return name;
}
bool askQues(string language, string power, int &score) {
    int a = rand() % 20;
    int b = rand() % 20;
    int operation = rand() % 4;
    int correct = 0;
    int answer;
    if (language == "English") {

        if (operation == 0) {
            cout << "What is " << a << " + " << b << "? ";
            correct = a + b;
        }
        else if (operation == 1) {
            cout << "What is " << a << " - " << b << "? ";
            correct = a - b;
        }
        else if (operation == 2) {
            cout << "What is " << a << " x " << b << "? ";
            correct = a * b;
        }
        else {
            if (b == 0) b = 1;
            cout << "What is " << a << " / " << b << "? (ignore decimals) ";
            correct = a / b;
        }
    }
    else {

        if (operation == 0) {
            cout << "Cuanto es " << a << " + " << b << "? ";
            correct = a + b;
        }
        else if (operation == 1) {
            cout << "Cuanto es " << a << " - " << b << "? ";
            correct = a - b;
        }
        else if (operation == 2) {
            cout << "Cuanto es " << a << " x " << b << "? ";
            correct = a * b;
        }
        else {
            if (b == 0) b = 1;
            cout << "Cuanto es " << a << " / " << b << "? ";
            correct = a / b;
        }
    }
    cin >> answer;
    if (answer == correct) {
        int gain = 5;
        if (power == "1") {
            gain *= 2;
            cout << "2X MULTIPLIER ACTIVE!\n";
        }
        if (power == "3") {
            gain += 10;
            cout << "+10 BONUS POINTS!\n";
        }
        score += gain;
        cout << "Correct! +" << gain << " points\n";
        return true;
    }
    cout << "Wrong answer!\n";
    if (power == "2") {
        cout << "Skip used! No penalty.\n";
        return true;
    }
    if (power == "4") {
        cout << "Correct answer was: " << correct << endl;
    }
    return false;
}