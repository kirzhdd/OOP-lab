#include "SaveManager.h"

/*
работаем с ,бинарным файлом .dat
представляем все данные как char* (так как это универсальный
указатель на байты) с помощью reinterpret_cast<const char*>
*/

//итоговое сохранение и загрузка
bool SaveManager::save_game(const Saving& game_data) {
    std::ofstream file(save_filename, std::ios::binary);
    if (!file) {
        return false;
    }
        
    try {
        save_saving_data(file, game_data);
    } catch (const std::exception& e) {
        return false;
    }

    return !file.fail();
}

bool SaveManager::load_game(Saving& game_data) {
    std::ifstream file(save_filename, std::ios::binary);
    if (!file) {
        return false;
    }
        
    try {
        if (!load_saving_data(file, game_data)) return false;
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}
    

//сохранение и загрузка полей GManager = Saving - Manager и GField
void SaveManager::save_saving_data(std::ofstream& file, const Saving& data) {
    save_manager_data(file, data.manager);
    save_gfield_data(file, data.gfield);
}
    
bool SaveManager::load_saving_data(std::ifstream& file, Saving& data) {
    if (!load_manager_data(file, data.manager)) return false;
    if (!load_gfield_data(file, data.gfield)) return false;
    return true;
}
    

//сохранение ManagerData
//нам нужно записать ВСЕ поля ВСЕХ полей
void SaveManager::save_manager_data(std::ofstream& file, const Saving::ManagerData& data) {
    // уровень
file.write(reinterpret_cast<const char*>(&data.level), sizeof(data.level));
        
    // PlayerData
    file.write(reinterpret_cast<const char*>(&data.player.lifes), sizeof(data.player.lifes));
    file.write(reinterpret_cast<const char*>(&data.player.damage), sizeof(data.player.damage));
    file.write(reinterpret_cast<const char*>(&data.player.x), sizeof(data.player.x));
    file.write(reinterpret_cast<const char*>(&data.player.y), sizeof(data.player.y));
    file.write(reinterpret_cast<const char*>(&data.player.close_combat), sizeof(data.player.close_combat));
        
    // FieldData
    file.write(reinterpret_cast<const char*>(&data.field.height), sizeof(data.field.height));
    file.write(reinterpret_cast<const char*>(&data.field.width), sizeof(data.field.width));
        
    // cохраняем каждую из клеток поля
    for (int i = 0; i < data.field.height; ++i) {
        for (int j = 0; j < data.field.width; ++j) {
            const auto& cell = data.field.cells[i][j];
            file.write(reinterpret_cast<const char*>(&cell.impassible), sizeof(cell.impassible));
            file.write(reinterpret_cast<const char*>(&cell.is_there_player), sizeof(cell.is_there_player));
            file.write(reinterpret_cast<const char*>(&cell.is_there_enemy), sizeof(cell.is_there_enemy));
            file.write(reinterpret_cast<const char*>(&cell.trap), sizeof(cell.trap));
            file.write(reinterpret_cast<const char*>(&cell.enemy_tower), sizeof(cell.enemy_tower));
        }
    }
        
    // враги
    int enemy_count = data.enemies.size();
    file.write(reinterpret_cast<const char*>(&enemy_count), sizeof(enemy_count));
    for (const auto& enemy : data.enemies) {
        file.write(reinterpret_cast<const char*>(&enemy.x), sizeof(enemy.x));
        file.write(reinterpret_cast<const char*>(&enemy.y), sizeof(enemy.y));
        file.write(reinterpret_cast<const char*>(&enemy.lifes), sizeof(enemy.lifes));
        file.write(reinterpret_cast<const char*>(&enemy.damage), sizeof(enemy.damage));
    }
        
    // killed
    int kill_count = data.killed.size();
    file.write(reinterpret_cast<const char*>(&kill_count), sizeof(kill_count));
    for (const auto& [enemy_type, count] : data.killed) {
        file.write(reinterpret_cast<const char*>(&enemy_type), sizeof(enemy_type));
        file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    }
        
    // HandData
    save_string_vector(file, data.hand.acceptable);
    save_string_vector(file, data.hand.spells);
    file.write(reinterpret_cast<const char*>(&data.hand.last_spell), sizeof(data.hand.last_spell));
    file.write(reinterpret_cast<const char*>(&data.hand.max_count), sizeof(data.hand.max_count));
}



//сохраням gfield - нам также нужно записать ВСЁ
void SaveManager::save_gfield_data(std::ofstream& file, const Saving::GFieldData& data) {
    file.write(reinterpret_cast<const char*>(&data.height), sizeof(data.height));
    file.write(reinterpret_cast<const char*>(&data.width), sizeof(data.width));
        
    //все клетки поля gfield
    for (int i = 0; i < data.height; ++i) {
        for (int j = 0; j < data.width; ++j) {
            const auto& cell = data.gcells[i][j];
            file.write(reinterpret_cast<const char*>(&cell.impassible), sizeof(cell.impassible));
            file.write(reinterpret_cast<const char*>(&cell.is_there_player), sizeof(cell.is_there_player));
            file.write(reinterpret_cast<const char*>(&cell.is_there_enemy), sizeof(cell.is_there_enemy));
            file.write(reinterpret_cast<const char*>(&cell.trap), sizeof(cell.trap));
            file.write(reinterpret_cast<const char*>(&cell.enemy_tower), sizeof(cell.enemy_tower));
            file.write(reinterpret_cast<const char*>(&cell.x0), sizeof(cell.x0));
            file.write(reinterpret_cast<const char*>(&cell.y0), sizeof(cell.y0));
        }
    }
}


//загружаем ВСЕ поля ВСЕХ полей Manager
bool SaveManager::load_manager_data(std::ifstream& file, Saving::ManagerData& data) {
    // уровень
    file.read(reinterpret_cast<char*>(&data.level), sizeof(data.level));
        
    // PlayerData
    file.read(reinterpret_cast<char*>(&data.player.lifes), sizeof(data.player.lifes));
    file.read(reinterpret_cast<char*>(&data.player.damage), sizeof(data.player.damage));
    file.read(reinterpret_cast<char*>(&data.player.x), sizeof(data.player.x));
    file.read(reinterpret_cast<char*>(&data.player.y), sizeof(data.player.y));
    file.read(reinterpret_cast<char*>(&data.player.close_combat), sizeof(data.player.close_combat));
        
    // FieldData
    file.read(reinterpret_cast<char*>(&data.field.height), sizeof(data.field.height));
    file.read(reinterpret_cast<char*>(&data.field.width), sizeof(data.field.width));
        
    // загружаем все клетки поля
    data.field.cells.resize(data.field.height, std::vector<Saving::CellData>(data.field.width));
    for (int i = 0; i < data.field.height; ++i) {
        for (int j = 0; j < data.field.width; ++j) {
            auto& cell = data.field.cells[i][j];
            file.read(reinterpret_cast<char*>(&cell.impassible), sizeof(cell.impassible));
            file.read(reinterpret_cast<char*>(&cell.is_there_player), sizeof(cell.is_there_player));
            file.read(reinterpret_cast<char*>(&cell.is_there_enemy), sizeof(cell.is_there_enemy));
            file.read(reinterpret_cast<char*>(&cell.trap), sizeof(cell.trap));
            file.read(reinterpret_cast<char*>(&cell.enemy_tower), sizeof(cell.enemy_tower));
        }
    }
        
    // враги
    int enemy_count;
    file.read(reinterpret_cast<char*>(&enemy_count), sizeof(enemy_count));
    data.enemies.resize(enemy_count);
    for (int i = 0; i < enemy_count; ++i) {
        auto& enemy = data.enemies[i];
        file.read(reinterpret_cast<char*>(&enemy.x), sizeof(enemy.x));
        file.read(reinterpret_cast<char*>(&enemy.y), sizeof(enemy.y));
        file.read(reinterpret_cast<char*>(&enemy.lifes), sizeof(enemy.lifes));
        file.read(reinterpret_cast<char*>(&enemy.damage), sizeof(enemy.damage));
    }
        
    // killed
    int kill_count;
    file.read(reinterpret_cast<char*>(&kill_count), sizeof(kill_count));
    for (int i = 0; i < kill_count; ++i) {
        char enemy_type;
        int count;
        file.read(reinterpret_cast<char*>(&enemy_type), sizeof(enemy_type));
        file.read(reinterpret_cast<char*>(&count), sizeof(count));
        data.killed[enemy_type] = count;
    }
        
    // HandData
    data.hand.acceptable = load_string_vector(file);
    data.hand.spells = load_string_vector(file);
    file.read(reinterpret_cast<char*>(&data.hand.last_spell), sizeof(data.hand.last_spell));
    file.read(reinterpret_cast<char*>(&data.hand.max_count), sizeof(data.hand.max_count));
        
    return !file.fail();
}
    


//загружаем всё про gfield
bool SaveManager::load_gfield_data(std::ifstream& file, Saving::GFieldData& data) {
    file.read(reinterpret_cast<char*>(&data.height), sizeof(data.height));
    file.read(reinterpret_cast<char*>(&data.width), sizeof(data.width));
        
    //все клетки gfield
    data.gcells.resize(data.height, std::vector<Saving::GCellData>(data.width));
    for (int i = 0; i < data.height; ++i) {
        for (int j = 0; j < data.width; ++j) {
            auto& cell = data.gcells[i][j];
            file.read(reinterpret_cast<char*>(&cell.impassible), sizeof(cell.impassible));
            file.read(reinterpret_cast<char*>(&cell.is_there_player), sizeof(cell.is_there_player));
            file.read(reinterpret_cast<char*>(&cell.is_there_enemy), sizeof(cell.is_there_enemy));
            file.read(reinterpret_cast<char*>(&cell.trap), sizeof(cell.trap));
            file.read(reinterpret_cast<char*>(&cell.enemy_tower), sizeof(cell.enemy_tower));
            file.read(reinterpret_cast<char*>(&cell.x0), sizeof(cell.x0));
            file.read(reinterpret_cast<char*>(&cell.y0), sizeof(cell.y0));
        }
    }
        
    return !file.fail();
}
    

//вспомогательные для работы с массивами
void SaveManager::save_string_vector(std::ofstream& file, const std::vector<std::string>& vec) {
    int size = vec.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& str : vec) {
        int str_size = str.size();
        file.write(reinterpret_cast<const char*>(&str_size), sizeof(str_size));
        file.write(str.c_str(), str_size);
    }
}
    
std::vector<std::string> SaveManager::load_string_vector(std::ifstream& file) {
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::vector<std::string> result(size);
        
    for (int i = 0; i < size; ++i) {
        int str_size;
        file.read(reinterpret_cast<char*>(&str_size), sizeof(str_size));
            
        std::vector<char> buffer(str_size);
        file.read(buffer.data(), str_size);
        result[i] = std::string(buffer.data(), str_size);
    }
        
    return result;
}

