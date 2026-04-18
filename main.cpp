#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <limits>

using namespace std;

const int numQues = 10;
const int numFacts = 10;

// Fun Facts Arrays
string engFacts[numFacts] = {
    "In Bangladesh, schools on boats bring education to kids during floods.",
    "Scientists can turn carbon dioxide into protein powder using microbes.",
    "Some planes use cleaner fuel made from leftover frying oil.",
    "Satellites detect penguin colonies by spotting large guano stains on the ice.",
    "NASA’s Dragonfly mission will explore a world with lakes made of methane.",
    "Beavers help prevent floods.",
    "Sheep eat grass around solar panels, preventing fires and fertilizing land.",
    "Prairie dogs build underground cities.",
    "Octopi can squeeze through openings the size of their eye.",
    "Whales store carbon in their bodies, helping ecosystems."
};

string spanFacts[numFacts] = {
    "En Bangladesh, las escuelas en barcos llevan educación durante inundaciones.",
    "Los científicos pueden convertir el dióxido de carbono en proteína en polvo.",
    "Algunos aviones usan combustible más limpio hecho de aceite de cocina usado.",
    "Los satélites detectan pingüinos por manchas de guano en el hielo.",
    "La misión Dragonfly explorará un mundo con lagos de metano.",
    "Los castores ayudan a prevenir inundaciones.",
    "Las ovejas comen pasto alrededor de paneles solares, fertilizando naturalmente.",
    "Los perritos de las praderas construyen ciudades subterráneas.",
    "Los pulpos pueden pasar por aberturas del tamaño de sus ojos.",
    "Las ballenas almacenan carbono, ayudando a los ecosistemas."
};

string selectLanguage();
string helloUser(string language);
bool askQues(string language, string power, int &score, bool &usedPower);

int main() {
    srand(time(0));

    cout << "Enter 1 for English\n";
    cout << "Presiona 2 for Espanol\n";
    string language = selectLanguage();
    string userName = helloUser(language);

    string power;
    cout << "\nChoose your power:\n";
    cout << "1. Multiplier 2x\n";
    cout << "2. Skip 1 question\n";
    cout << "3. Earn 10 bonus points\n";
    cout << "Type your choice (1, 2, or 3): ";
    cin >> power;

    cout << "\n--- GAME START ---\n";
    cout << "Note: Powers start after 10 points and activate every OTHER 10 points!\n\n";

    int score = 0;
    bool usedPower = false;

    for (int i = 0; i < numQues; i++) {
        askQues(language, power, score, usedPower);
    }

    cout << "\nFINAL SCORE: " << score << endl;

    ofstream outFile("scores.txt");
    outFile << "Player: " << userName << endl;
    outFile << "Final Score: " << score << endl;
    outFile.close();

    return 0;
}

string selectLanguage() {
    string langChoice;
    cout << "Select language:\n1. English\n2. Espanol\n";
    cout << "Type your choice (1 or 2): ";
    cin >> langChoice;
    return (langChoice == "1") ? "English" : "Spanish";
}

string helloUser(string language) {
    string name;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Welcome, " << name << "!\n";
    return name;
}

bool askQues(string language, string power, int &score, bool &usedPower) {
    int a = rand() % 20;
    int b = rand() % 20;
    int operation = rand() % 4;
    int correct = 0;
    int answer;

    // Displaying question
    if (language == "English") {
        if (operation == 0) { cout << "What is " << a << " + " << b << "? "; correct = a + b; }
        else if (operation == 1) { cout << "What is " << a << " - " << b << "? "; correct = a - b; }
        else if (operation == 2) { cout << "What is " << a << " x " << b << "? "; correct = a * b; }
        else { if (b == 0) b = 1; cout << "What is " << a << " / " << b << "? (without the decimal- just the whole number)"; correct = a / b; }
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

    // --- CORRECT ANSWER LOGIC ---
    if (answer == correct) {
        int gain = 5;
        if (powerActive) {
            if (power == "1") { gain = 10; cout << >> 2X MULTIPLIER ACTIVE! "(Points: " << gain << ")\n"; }
            else if (power == "3") { gain = 15; cout << ">> +10 BONUS ACTIVE! (Points: " << gain << ")\n"; }
            else if (power == "2") { cout << "Correct! +5 points (Skip ready!)\n"; }
        } else {
            cout << "Correct! +5 points (Power recharging...)\n";
        }
        score += gain;

        // --- NEW: DISPLAY FACT ---
        int idx = rand() % numFacts;
        if (language == "English") cout << "FUN FACT: " << engFacts[idx] << endl;
        else cout << "DATO CURIOSO: " << spanFacts[idx] << endl;

        return true;
    }

    // --- SKIP LOGIC ---
    if (power == "2" && powerActive && !usedPower) {
        usedPower = true;
        cout << ">> WRONG! But your SKIP power saved you! (Power used up)\n";
        return true;
    }

    // --- WRONG ANSWER ---
    cout << "Wrong answer! Keep going!\n";
    if (power == "2" && !usedPower && !powerActive) {
        cout << "(Skip power currently recharging...)\n";
    }

    return false;
}
