#include <iostream>
#include <random>
#include <string>
#include <limits>
#include <vector>
#include <cstdlib>
#include <map>
#include <fstream>
#include <sstream>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>


bool checkLong(int& longueur) {
    if (longueur >= 8 && longueur <= 64) {
        return true;
    }
    std::cout << "La longueur doit être d'au moins 8 caractères et maximum 64 caractères" << std::endl;
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


std::map<std::string, std::string> loadEnv(const std::string& filename){
    std::ifstream file(filename);
    std::map<std::string, std::string> env;
    std::string line;

    while(std::getline(file,line)){
        std::istringstream is_line(line);
        std::string key;
        if(std::getline(is_line, key, '=')){
            std::string value;
            if(std::getline(is_line, value)){
                env[key] = value;
            }
        }
    }

    return env;
}

void createTableIfNotExists(sql::Connection* conn) {
    try {
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());

        stmt->execute(
            "CREATE TABLE IF NOT EXISTS mdp ("
            "id INT AUTO_INCREMENT PRIMARY KEY, "
            "nom VARCHAR(50) NOT NULL, "
            "pass VARCHAR(64)"
            ")"
        );

        std::cout << "Table 'mdp' créée (ou déjà existante)." << std::endl;
    } catch (const sql::SQLException& e) {
        std::cerr << "Erreur lors de la création de la table : " << e.what() << std::endl;
    }
}



int main(){
    int longueur;
    char c;
    std::string mdp, mdp_name;

    auto env = loadEnv("../.env");

    std::string host = "tcp://" + env["DB_HOST"] + ":" + env["DB_PORT"];
    std::string user = env["DB_USER"];
    std::string pass = env["DB_PASSWORD"];
    std::string db = env["DB_NAME"];
        
    sql::Driver* driver = get_driver_instance();
    std::unique_ptr<sql::Connection> conn(driver->connect(host, user, pass));
    conn->setSchema(db);

    std::cout << "Bienvenue dans le générateur de mot de passe" << std::endl;
    std::cout << "Tout d'abord, veuillez indiquer la longueur du mot de passe" << std::endl;
    while (!(std::cin >> longueur) || !checkLong(longueur)) {
        std::cout << "Veuillez entrer un nombre valide entre 8 et 64 : ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    std::cout << "Veuillez maintenant indiquer l\'identification du mot de passe" << std::endl;
    std::getline(std::cin, mdp_name);

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

            default : std::cout << "Bug" << std::endl;
        }
    }
try
{
    std::unique_ptr<sql::PreparedStatement> prep_stmt(
    conn->prepareStatement("INSERT INTO mdp(nom, pass) VALUES (?, ?)")
);
    prep_stmt->setString(1, mdp_name);
    prep_stmt->setString(2, mdp);
    prep_stmt->execute();

}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}

    return 0;
}


