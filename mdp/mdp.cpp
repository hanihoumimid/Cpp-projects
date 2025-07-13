#include <iostream>
#include <random>
#include <string>
#include <limits>

void checkLong(int longueur){
    if (longueur < 8){
        std::cout << "La longueur doit être d'au moins 8 caractères" << std::endl;
        std::cin >> longueur;
    }
    else if (longueur > 32){
        std::cout << "La longueur doit être inférieur à 32 caractères" << std::endl;
        std::cin >> longueur;
    }
}


int generateNumber(){
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> dis(48,57);

    char c = dis(gen);

    std::cout << "Ascii : " << c << ",int : " << int(c) << std::endl;

    return c;
    
}

int main(){
    int longueur;
    int longe = generateNumber();
    std::cout << "Bienvenue dans le générateur de mot de passe" << std::endl;
    std::cout << "Tout d'abord, veuillez indiquer la longueur du mot de passe" << std::endl;
    while (!(std::cin >> longueur)) {
        std::cout << "Entrée invalide. Veuillez entrer un nombre pour la longueur du mot de passe (minimum 8, max 32) : ";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


