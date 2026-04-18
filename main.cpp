#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

const int numQues = 10;

string selectLanguage();
string helloUser(string language);
bool askQues(string language, string power, int &score);

int main() {
    srand(time(0));

    cout << "Enter 1 for English\n";
    cout << "Presiona 2 for Espanol\n";
    string language = selectLanguage();
    helloUser(language);

    string power;
    cout << "\nChoose your power:\n";
    cout << "1. Multiplier 2x\n";
    cout << "2. Skip 1 question\n";
    cout << "3. Earn 10 bonus points\n";
    cout << "Type your choice (1, 2, or 3): ";
    cin >> power;

    cout << "\n--- GAME START ---\n";
    cout << "Note: Powers activate every OTHER 10 points (10-19, 30-39, etc.)!\n\n";

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

    // Question Display
    if (language == "English") {
        if (operation == 0) { cout << "What is " << a << " + " << b << "? "; correct = a + b; }
        else if (operation == 1) { cout << "What is " << a << " - " << b << "? "; correct = a - b; }
        else if (operation == 2) { cout << "What is " << a << " x " << b << "? "; correct = a * b; }
        else { if (b == 0) b = 1; cout << "What is " << a << " / " << b << "? (ignore decimals) "; correct = a / b; }
    } else {
        if (operation == 0) { cout << "Cuanto es " << a << " + " << b << "? "; correct = a + b; }
        else if (operation == 1) { cout << "Cuanto es " << a << " - " << b << "? "; correct = a - b; }
        else if (operation == 2) { cout << "Cuanto es " << a << " x " << b << "? "; correct = a * b; }
        else { if (b == 0) b = 1; cout << "Cuanto es " << a << " / " << b << "? "; correct = a / b; }
    }

    cin >> answer;

    if (answer == correct) {
        int gain = 5;

        // "EVERY OTHER 10 POINTS" LOGIC:
        bool powerActive = (score / 10) % 2 != 0;

        if (powerActive) {
            if (power == "1") {
                gain = 5 * 2;
                cout << ">> 2X MULTIPLIER ACTIVE! (Points: " << gain << ")\n";
            }
            else if (power == "3") {
                gain = 5 + 10;
                cout << ">> +10 BONUS ACTIVE! (Points: " << gain << ")\n";
            }
            else {
                cout << "Correct! +5 points\n";
            }
        } else {
            cout << "Correct! +5 points (Power recharging...)\n";
        }

        score += gain;
        return true;
    }

    // Encouraging message block
    cout << "Wrong answer! ";
    int msg = rand() % 3;
    if (language == "English") {
        if (msg == 0) cout << "Don't give up, keep trying!\n";
        else if (msg == 1) cout << "Nice effort, you'll get it next time!\n";
        else cout << "Keep going, you've got this!\n";
    } else {
        if (msg == 0) cout << "¡No te rindas, sigue intentándolo!\n";
        else if (msg == 1) cout << "¡Buen esfuerzo, lo lograrás la próxima vez!\n";
        else cout << "¡Sigue adelante, tú puedes!\n";
    }

    // Skip power logic
    if (power == "2" && ((score / 10) % 2 != 0)) {
        cout << ">> Skip used! No penalty.\n";
        return true;
    }

    return false;
}  