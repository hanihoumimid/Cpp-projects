#include <iostream>
#include <random>
#include <string>
#include <limits>
#include <vector>
#include <cstdlib>

bool checkLong(int& longueur) {
    if (longueur >= 8 && longueur <= 32) {
        return true;
    }
    std::cout << "La longueur doit être d'au moins 8 caractères et maximum 32 caractères" << std::endl;
    std::cin.clear();
    return false;
}



int generateNumber(){
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(48,57);

    char c = dis(gen);

    return c;
}


char generateUpperCase(){
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(65,90);

    char c = dis(gen);

    return c;
}


char generateLowerCase(){
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(97,122);

    char c = dis(gen);

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
    char c;
    std::string mdp;

    std::cout << "Bienvenue dans le générateur de mot de passe" << std::endl;
    std::cout << "Tout d'abord, veuillez indiquer la longueur du mot de passe" << std::endl;
    while (!(std::cin >> longueur) || !checkLong(longueur)) {
        std::cout << "Veuillez entrer un nombre valide entre 8 et 32 : ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,3);

    for (int i = 0; i < longueur; i++){
        switch(dis(gen)){
            case 0 : {
                mdp.push_back(generateSpecialOne());
                break;
            }
            case 1 : {
                mdp.push_back(generateLowerCase());
                break;
            }
            case 2 : {
                mdp.push_back(generateUpperCase());
                break;
            }
            case 3 : {
                mdp.push_back(generateNumber());
                break;
            }

            default : std::cout << "azer" << std::endl;
        }
    }
    std::cout << "Voici votre mot de passe : " << mdp << std::endl;

    system("pause");
}


