#include <iostream>
#include <random>

using namespace std;

int main() {

cout << "Bienvenue dans le jeu du juste chiffre" << endl;

int chiffre, guess, a, b;

cout << "entrez les bornes a et b, le chiffre sera compris entre elles" << endl;
cin >> a;
cin >> b;

srand(time(NULL));
chiffre = rand() % b + a;

cout << "Le chiffre est compris entre " << a << " et" << b << ", à vous de jouer";
cin >> guess;

while (guess != chiffre) {

    if (guess > chiffre) {
        cout << "Plus petit";
        cin >> guess;
    }

    else {
        cout << "Plus grand";
        cin >> guess;
    }
}

cout << "Bravo";
cin >> guess;

return 0;

}
