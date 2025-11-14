#pragma once
#include <ncurses.h>
#include <vector>
#include <string>
#include "../saving/Saving.h"
#include "../game/utils/Values.h"
#include "../saving/SaveManager.h"
#include "../game/manager/Manager.h"
#include "GField.h"

class GManager{
private:
    GField gfield;
    Manager manager;
    SaveManager save_manager;

public:
    GManager();
    GManager(int height, int width, int hand_size, int level);
    GManager(int heigt, int width, std::vector<std::string> spells, int level);
    ~GManager();

    std::vector<std::string> get_reset_spells();

    void start_work();
    bool work();
    void end_work(bool pass);

private:
    void display_lifes();
    void display_combat();
    void display_moves();
    void display_controls();
    void display_spells_controls();
    void display_my_spells();
    void display_choose_spell();
    void display_enemy_tower();
    void display_spell_was_choosed(char c);
    void display_spell_was_used(bool was);
    void display_killed();
    void display_need_to_do();
    void display_save_game(bool success);
    void display_load_game(bool success);
    void print_win();
    void print_big_game_over(); 


    Saving serialize() const;
    void deserialize(const Saving& data);
};
