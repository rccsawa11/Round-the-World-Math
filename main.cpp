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
    "A NASA Dragonfly mission will explore a world with lakes made of methane.",
    "Beavers help prevent floods.",
    "Sheep eat grass around solar panels, preventing fires and fertilizing land.",
    "Prairie dogs build underground cities.",
    "Octopi can squeeze through openings the size of their eye.",
    "Whales store carbon in their bodies, helping ecosystems."
};

string spanFacts[numFacts] = {
    "En Bangladesh, las escuelas en barcos llevan educacion durante inundaciones.",
    "Los cientificos pueden convertir el dioxido de carbono en proteina en polvo.",
    "Algunos aviones usan combustible mas limpio hecho de aceite de cocina usado.",
    "Los satelites detectan pinguinos por manchas de guano en el hielo.",
    "La mision Dragonfly explorara un mundo con lagos de metano.",
    "Los castores ayudan a prevenir inundaciones.",
    "Las ovejas comen pasto alrededor de paneles solares, fertilizando naturalmente.",
    "Los perritos de las praderas construyen ciudades subterraneas.",
    "Los pulpos pueden pasar por aberturas del tamano de sus ojos.",
    "Las ballenas almacenan carbono, ayudando a los ecosistemas."
};

// --- FUNCTION PROTOTYPES ---
string selectLanguage();
string helloUser(string language);
bool askQues(string language, string power, int &score, bool &usedPower);

int main() {
    srand(time(0));

    // Initial language prompt
    cout << "Welcome to... \n++ MATH FOR FACTS ++" << endl;
    cout << "Choose your language:\n";
    cout << "1.) English\n";
    cout << "2.) Espanol\n";

    string language = selectLanguage();
    string userName = helloUser(language);

    string power;
    // Power Menu
    if (language == "Spanish") {
        cout << "Responde preguntas --> Gana puntos!\n";
        cout << "\nElige tu poder:\n";
        cout << "1. Multiplicador 2x\n";
        cout << "2. Saltar 1 pregunta\n";
        cout << "3. Ganar 10 puntos extra\n";
        cout << "Escribe tu eleccion (1, 2, o 3): \n";
    } else {
        cout << "| ANSWER QUESTIONS  --> EARN POINTS! | \n";
        cout << "Choose a power to boost your experience! :\n";
        cout << "1. Multiplier 2x\n";
        cout << "2. Skip 1 question\n";
        cout << "3. Earn 10 bonus points\n";
        cout << "Type your choice (1, 2, or 3): \n";
    }
    cin >> power;

    if (language == "Spanish") {
        cout << "\n--- COMIENZO DEL JUEGO ---\n";
        cout << "| 10 PREGUNTAS --> 5 PUNTOS CADA UNA |\n";
        cout << "Nota: Los poderes comienzan despues de 10 puntos y se activan cada OTROS 10 puntos!\n";
    } else {
        cout << "\n--- GAME START ---\n";
        cout << "| 10 QUESTIONS --> 5 POINTS EACH |\n";
        cout << "Note: Powers start after 10 points and activate every OTHER 10 points!\n";
    }

    int score = 0;
    bool usedPower = false;

    for (int i = 0; i < numQues; i++) {
        askQues(language, power, score, usedPower);
    }

    if (language == "Spanish") {
        cout << "\n + WOW! + \nPUNTUACION FINAL: " << score << "\nFELICIDADES, GRACIAS POR JUGAR :] *" << endl;
    } else {
        cout << "\n + WOW! + \nFINAL SCORE: " << score << "\nCONGRATULATIONS, THANK YOU FOR PLAYING :] *" << endl;
    }

    ofstream outFile("scores.txt");
    outFile << "Player: " << userName << endl;
    outFile << "Final Score: " << score << endl;
    outFile.close();

    return 0;
}

// --- FUNCTION DEFINITIONS ---

string selectLanguage() {
    string langChoice;
    cin >> langChoice;
    // Standardizing the logic: 2 is Spanish, anything else is English
    return (langChoice == "2") ? "Spanish" : "English";
}

string helloUser(string language) {
    string name;
    if (language == "Spanish") {
        cout << "Ingresa tu nombre: \n";
    } else {
        cout << "Enter your name: \n";
    }
    cin >> name;

    if (language == "Spanish") {
        cout << "Bienvenido, " << name << "!\n";
    } else {
        cout << "Welcome, " << name << "!\n";
    }
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
        if (operation == 0) { cout << "What is " << a << " + " << b << "? \n"; correct = a + b; }
        else if (operation == 1) { cout << "What is " << a << " - " << b << "? \n"; correct = a - b; }
        else if (operation == 2) { cout << "What is " << a << " x " << b << "? \n"; correct = a * b; }
        else { if (b == 0) b = 1; cout << "What is " << a << " / " << b << "? (Don't worry about decimal places...) \n"; correct = a / b; }
    } else {
        if (operation == 0) { cout << "Cuanto es " << a << " + " << b << "? \n"; correct = a + b; }
        else if (operation == 1) { cout << "Cuanto es " << a << " - " << b << "? \n"; correct = a - b; }
        else if (operation == 2) { cout << "Cuanto es " << a << " x " << b << "? \n"; correct = a * b; }
        else { if (b == 0) b = 1; cout << "Cuanto es " << a << " / " << b << "? (No te preocupes por puntos decimales) \n"; correct = a / b; }
    }

    while (!(cin >> answer)) {
        if (language == "Spanish") cout << "Por favor ingresa un numero valido: \n";
        else cout << "Please enter a valid number: \n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool powerActive = (score >= 10) && ((score / 10) % 2 != 0);

    // --- CORRECT ANSWER LOGIC ---
    if (answer == correct) {
        int gain = 5;
        if (powerActive) {
            if (power == "1") {
                gain = 10;
                cout << (language == "Spanish" ? ">> MULTIPLICADOR 2X ACTIVO! " : ">> 2X MULTIPLIER ACTIVE! ");
                cout << "(Points: " << gain << ")\n";
            }
            else if (power == "3") {
                gain = 15;
                cout << (language == "Spanish" ? ">> BONO +10 ACTIVO! " : ">> +10 BONUS ACTIVE! ");
                cout << "(Points: " << gain << ")\n";
            }
            else if (power == "2") {
                cout << (language == "Spanish" ? "Correcto! +5 puntos (Salto listo!)\n" : "Correct! +5 points (Skip ready!)\n");
            }
        } else {
            cout << (language == "Spanish" ? "Correcto! +5 puntos (Poder recargando...)\n" : "Correct! +5 points (Power recharging...)\n");
        }
        score += gain;

        int idx = rand() % numFacts;
        if (language == "English") cout << "\nFUN FACT: \n" << engFacts[idx] << endl;
        else cout << "\nDATO CURIOSO: \n" << spanFacts[idx] << endl;

        return true;
    }

    // --- SKIP LOGIC ---
    if (power == "2" && powerActive && !usedPower) {
        usedPower = true;
        if (language == "Spanish") cout << ">> INCORRECTO! Pero tu poder de SALTAR te salvo! (Poder agotado)\n";
        else cout << ">> WRONG! But your SKIP power saved you! (Power used up)\n";
        return true;
    }

    // --- WRONG ANSWER ---
    if (language == "Spanish") {
        cout << "Respuesta incorrecta! Sigue adelante!\n";
        if (power == "2" && !usedPower && !powerActive) cout << "(El poder de saltar se esta recargando...)\n";
    } else {
        cout << "Wrong answer! Keep going!\n";
        if (power == "2" && !usedPower && !powerActive) cout << "(Skip power currently recharging...)\n";
    }

    return false;

