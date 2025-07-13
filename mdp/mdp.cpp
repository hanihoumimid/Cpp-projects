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
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(48,57);

    char c = dis(gen);

    std::cout << "Ascii : " << c << ",int : " << int(c) << std::endl;

    return c;
    
}


char generateUpperCase(){
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(65,90);

    char c = dis(gen);

    std::cout << "Ascii : " << c << ",int : " << int(c) << std::endl;

    return c;
    
}


char generateLowerCase(){
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(97,122);

    char c = dis(gen);

    std::cout << "Ascii : " << c << ",int : " << int(c) << std::endl;

    return c;
    
}

char generateSpecialOne(){
    std::random_device rd;
    std::mt19937 gen(rd()); 

    std::uniform_int_distribution<> intervalle_dis(0, 3);
    int intervalle = intervalle_dis(gen);

    char c; 

    switch(intervalle){
        case 0: { 
            std::uniform_int_distribution<> char_dis(33, 47);
            c = char_dis(gen); 
            break;
        }
        case 1: {
            std::uniform_int_distribution<> char_dis(58, 64);
            c = char_dis(gen);
            break;
        }
        case 2: {
            std::uniform_int_distribution<> char_dis(91, 96);
            c = char_dis(gen);
            break;
        }
        case 3: {
            std::uniform_int_distribution<> char_dis(123, 126);
            c = char_dis(gen);
            break;
        }
        default:
            std::cout << "Error" << std::endl;
            break;
    }


    return c;
}







int main(){
    int longueur;
    int longe = generateNumber();
    char c = generateSpecialOne();
    std::cout << "Test caracteres spe in ascii : " << c << int(c) << std::endl;
    std::cout << "Bienvenue dans le générateur de mot de passe" << std::endl;
    std::cout << "Tout d'abord, veuillez indiquer la longueur du mot de passe" << std::endl;
    while (!(std::cin >> longueur)) {
        std::cout << "Entrée invalide. Veuillez entrer un nombre pour la longueur du mot de passe (minimum 8, max 32) : ";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


