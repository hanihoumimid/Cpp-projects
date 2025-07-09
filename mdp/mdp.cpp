#include <iostream>
#include <random>
#include <string>
#include <limits>


int main(){
    int longueur;
    
    std::cout << "Bienvenue dans le générateur de mot de passe" << std::endl;
    std::cout << "Tout d'abord, veuillez indiquer la longueur du mot de passe" << std::endl;

    while (!(std::cin >> longueur)) {
        std::cout << "Entrée invalide. Veuillez entrer un nombre pour la longueur du mot de passe : ";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
}