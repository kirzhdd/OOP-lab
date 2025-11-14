#pragma once
#include "Saving.h"
#include <fstream>
#include <string>
#include <iostream>

class SaveManager {
private:
    std::string save_filename = "savings/savegame.dat";
    
public:
    bool save_game(const Saving& game_data);
    bool load_game(Saving& game_data);
    
private:
    void save_saving_data(std::ofstream& file, const Saving& data) ;
    bool load_saving_data(std::ifstream& file, Saving& data) ;


    void save_manager_data(std::ofstream& file, const Saving::ManagerData& data) ;
    void save_gfield_data(std::ofstream& file, const Saving::GFieldData& data) ;
    bool load_manager_data(std::ifstream& file, Saving::ManagerData& data) ;
    bool load_gfield_data(std::ifstream& file, Saving::GFieldData& data) ;


    void save_string_vector(std::ofstream& file, const std::vector<std::string>& vec); 
    std::vector<std::string> load_string_vector(std::ifstream& file) ;
};
