#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <limits>

using namespace std;

const int numQues = 10;

string selectLanguage();
string helloUser(string language);
// Updated: Added bool &usedPower to track if power was already used
bool askQues(string language, string power, int &score, bool &usedPower);

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
    
    int score = 0;
    bool usedPower = false; // Tracks if the power has been used yet

    for (int i = 0; i < numQues; i++) {
        askQues(language, power, score, usedPower);
    }

    cout << "\nFINAL SCORE: " << score << endl;

    ofstream outFile("scores.txt");
    outFile << "Final Score: " << score << endl;
    outFile.close();

    return 0;
}

// ... (selectLanguage and helloUser functions remain the same) ...
string selectLanguage() {
    string langChoice;
    cout << "Select language:\n";
    cout << "1. English\n2. Espanol\n";
    cin >> langChoice;
    if (langChoice == "1") { return "English"; } else { return "Spanish"; }
}

string helloUser(string language) {
    string name;
    cout << "Enter your name: ";
    cin >> name;
    // Add this line back in:
    cout << "Welcome, " << name << "!\n";
    return name;
}

bool askQues(string language, string power, int &score, bool &usedPower) {
    int a = rand() % 20;
    int b = rand() % 20;
    int operation = rand() % 4;
    int correct = 0;
    int answer;

    // Displaying question (Omitted for brevity, keep your original)
    if (language == "English") {
        if (operation == 0) { cout << "What is " << a << " + " << b << "? "; correct = a + b; }
        else if (operation == 1) { cout << "What is " << a << " - " << b << "? "; correct = a - b; }
        else if (operation == 2) { cout << "What is " << a << " x " << b << "? "; correct = a * b; }
        else {
            if (b == 0) b = 1;
            cout << "What is " << a << " / " << b << "? (ignore decimals) ";
            correct = a / b;
        }
    } else {
        if (operation == 0) { cout << "Cuanto es " << a << " + " << b << "? "; correct = a + b; }
        else if (operation == 1) { cout << "Cuanto es " << a << " - " << b << "? "; correct = a - b; }
        else if (operation == 2) { cout << "Cuanto es " << a << " x " << b << "? "; correct = a * b; }
        else { if (b == 0) b = 1; cout << "Cuanto es " << a << " / " << b << "? "; correct = a / b; }
    }

    while (!(cin >> answer)) {
        cout << "Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool powerActive = (score >= 10) && ((score / 10) % 2 != 0);

    // --- CORRECT ANSWER ---
    if (answer == correct) {
        int gain = 5;
        if (powerActive) {
            if (power == "1") { gain = 10; cout << ">> 2X MULTIPLIER ACTIVE! (Points: " << gain << ")\n"; }
            else if (power == "3") { gain = 15; cout << ">> +10 BONUS ACTIVE! (Points: " << gain << ")\n"; }
            else if (power == "2") { cout << "Correct! +5 points\n"; }
        } else {
            cout << "Correct! +5 points (Power recharging...)\n";
        }
        score += gain;
        return true;
    }

    // --- SKIP LOGIC (Updated to check usedPower) ---
    if (power == "2" && powerActive && !usedPower) {
        usedPower = true; // Mark it as used!
        cout << ">> WRONG! But your SKIP power saved you! (Power used up)\n";
        return true; 
    }

    // --- WRONG ANSWER ---
    cout << "Wrong answer! ";
    if (power == "2" && !usedPower && !powerActive) {
        cout << "(Skip power currently recharging...)\n";
    }
    
    // ... (Your encouragement message code remains here) ...
    return false;
}
