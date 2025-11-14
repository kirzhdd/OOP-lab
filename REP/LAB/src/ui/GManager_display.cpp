#include "GManager.h"

void GManager::display_lifes(){
    int lifes = manager.get_player_lifes();
    move(MY_WINDOW::HEIGHT + 4, 0);
    printw("L I F E S");

    move(MY_WINDOW::HEIGHT + 5, 0);
    clrtoeol();
    int i = 0;
    for(int j = 0; j < lifes; j++){
        mvaddch(MY_WINDOW::HEIGHT + 5, i, '<');
        mvaddch(MY_WINDOW::HEIGHT + 5, i + 1, '3');
        i += 3;
    }
    refresh();
}

void GManager::display_combat(){
    bool close_combat = manager.get_player_is_close_combat();
    move(3, 3*MY_WINDOW::WIDTH + 5);
    clrtoeol();
    if(close_combat){
        printw("COMBAT: CLOSE");
        move(4, 3*MY_WINDOW::WIDTH + 5); clrtoeol();
        printw("DMG: 4");
    } else {
        printw("COMBAT: LONG-RANGE");
        move(4, 3*MY_WINDOW::WIDTH + 5); clrtoeol();
        printw("DMG: 2");
    }
}

void GManager::display_moves(){
    move(1, 3*MY_WINDOW::WIDTH + 5);
    clrtoeol();
    printw("MOVE #%d", manager.get_moves());
}

void GManager::display_controls(){
    move(1, 5*MY_WINDOW::WIDTH);
    printw("C O N T R O L S");
    move(3, 5*MY_WINDOW::WIDTH); printw("q: exit");
    move(5, 5*MY_WINDOW::WIDTH); printw("h: shift left");
    move(6, 5*MY_WINDOW::WIDTH); printw("j: shift down");
    move(7, 5*MY_WINDOW::WIDTH); printw("k: shift up");
    move(8, 5*MY_WINDOW::WIDTH); printw("l: shift right");
    move(10, 5*MY_WINDOW::WIDTH); printw("a: hit left");
    move(11, 5*MY_WINDOW::WIDTH); printw("s: hit down");
    move(12, 5*MY_WINDOW::WIDTH); printw("w: hit up");
    move(13, 5*MY_WINDOW::WIDTH); printw("d: hit right");
    move(15, 5*MY_WINDOW::WIDTH); printw("c: switch combat");
}

void GManager::display_spells_controls(){
    move(17, 5*MY_WINDOW::WIDTH); printw("x: choose spell");
    move(18, 5*MY_WINDOW::WIDTH); printw("d: activate Direct Damage spell");
    move(19, 5*MY_WINDOW::WIDTH); printw("a: activate Area spell");
    move(20, 5*MY_WINDOW::WIDTH); printw("t: activate Trap spell");

    move(22, 5*MY_WINDOW::WIDTH); printw("m: SAVE GAME");
    move(23, 5*MY_WINDOW::WIDTH); printw("n: LOAD LAST SAVING");

    move(6, 4*MY_WINDOW::WIDTH); printw("DD  : dmg=4; range=4");
    move(7, 4*MY_WINDOW::WIDTH); printw("Area: dmg=4; range=2x2");
    move(8, 4*MY_WINDOW::WIDTH); printw("Trap: dmg=4; range=0");

    

    move(25, 5*MY_WINDOW::WIDTH); printw("tap w/a/s/d after");
    move(26, 5*MY_WINDOW::WIDTH); printw("spell activation");
    move(27, 5*MY_WINDOW::WIDTH); printw("to choose");
    move(28, 5*MY_WINDOW::WIDTH); printw("direction");

}

void GManager::display_enemy_tower(){
    move(1, 4*MY_WINDOW::WIDTH); printw("I N F O R M A T I O N");
    move(3, 4*MY_WINDOW::WIDTH);
    printw("ENEMY TOWER");
    move(4, 4*MY_WINDOW::WIDTH);
    if(manager.get_enemy_tower_time_to_kill()){
        mvhline(getcury(stdscr), 4*MY_WINDOW::WIDTH, ' ', 5*MY_WINDOW::WIDTH);
        printw("IS READY TO KILL");
    } else {
        mvhline(getcury(stdscr), 4*MY_WINDOW::WIDTH, ' ', 5*MY_WINDOW::WIDTH);
        printw("is not ready to kill");
    }
}


void GManager::display_need_to_do(){
    move(10, 4*MY_WINDOW::WIDTH); printw("L E V E L: %d", manager.get_level());
    move(12, 4*MY_WINDOW::WIDTH); printw("LEVEL'S  G O A L");
    switch(manager.get_level()){
        case 1:
            move(13, 4*MY_WINDOW::WIDTH); printw("close combat = 5");
            break;
        case 2:
            move(13, 4*MY_WINDOW::WIDTH); printw("range combat = 5");
            break;
        case 3:
            move(13, 4*MY_WINDOW::WIDTH); printw("all spells = 10  ");
            break;
    }

    move(15, 4*MY_WINDOW::WIDTH); printw("ENEMIES'S HEALTH: %d", manager.get_level() + 1);
}



void GManager::display_my_spells(){
    move(10, 3*MY_WINDOW::WIDTH + 5);
    printw("MY S P E L L S:");

    //!!
    for(int i = 11; i < 11 + manager.get_hand_max_count(); i++){
        move(i, 3*MY_WINDOW::WIDTH + 5); mvhline(getcury(stdscr), 3*MY_WINDOW::WIDTH + 5, ' ', 5*MY_WINDOW::WIDTH);
    }

    //!!
    std::vector<std::string> my_spells = manager.hand_get_my_spells();
    
    for(int i = 11; i < 11 + my_spells.size(); i++){
        move(i, 3*MY_WINDOW::WIDTH + 5);
        printw("%s", (my_spells[i - 11].c_str()));
    }
}


void GManager::display_choose_spell(){
    move(MY_WINDOW::HEIGHT + 4, 2*MY_WINDOW::WIDTH);
    printw("CHOOSE SPELL     ");
}

void GManager::display_spell_was_choosed(char c){
    bool is_there_spell = manager.get_hand_can_use_spell(c);

    move(MY_WINDOW::HEIGHT + 4, 2*MY_WINDOW::WIDTH);
    if(is_there_spell){
        switch(c){
            case 'd':
                printw("SPELL Direct Damage ACTIVATED");
                break;
            case 'a':
                printw("SPELL Area Damage ACTIVATED");
                break;
            case 't':
                printw("SPELL Trap ACTIVATED");
                break;
        }
    } else {
        printw("THERE IS NOT THAT SPELL");
        move(MY_WINDOW::HEIGHT + 5, 2*MY_WINDOW::WIDTH +3);
        printw("TYPE ANY KEY TO CONTINUE");
    }
    
}

void GManager::display_spell_was_used(bool was){
    if(was){
       move(MY_WINDOW::HEIGHT + 4, 2*MY_WINDOW::WIDTH);
       printw("SPELL WAS USED                       ");
    } else {
       move(MY_WINDOW::HEIGHT + 4, 2*MY_WINDOW::WIDTH);
       printw("SPELL WAS'NT USED                    ");
    }
}

void GManager::display_killed(){
    std::map<char, int> killed = manager.get_killed();
    move(MY_WINDOW::HEIGHT + 7, 0); clrtoeol(); printw("close combat = %d", killed['c']);
    move(MY_WINDOW::HEIGHT + 8, 0); clrtoeol(); printw("range combat = %d", killed['r']);
    move(MY_WINDOW::HEIGHT + 9, 0); clrtoeol(); printw("dd spell = %d", killed['d']);
    move(MY_WINDOW::HEIGHT + 10, 0); clrtoeol(); printw("area spell = %d", killed['a']);
    move(MY_WINDOW::HEIGHT + 11, 0); clrtoeol(); printw("set traps = %d", killed['t']);
}

void GManager::display_save_game(bool success){
    move(MY_WINDOW::HEIGHT + 15, 0); clrtoeol();
    if(success){
        printw("Saved");
    } else {
        printw("NOT SAVED: (error) Cannot open save file for writing");
    }
}

void GManager::display_load_game(bool success){
    move(MY_WINDOW::HEIGHT + 15, 0); clrtoeol();
    if(success){
        printw("Loaded");
    } else {
        printw("NOT LOADED: (error) Cannot open save file for writing");
    }
}

void GManager::print_win(){
    std::vector<std::string> win = {
        "__        ___ _   _ ",
        "\\ \\      / (_) \\ | |",
        " \\ \\ /\\ / /| |  \\| |",
        "  \\ V  V / | | |\\  |",
        "   \\_/\\_/  |_|_| \\_|"
    };
    
    int start_y = (LINES - win.size()) / 2;
    
    for (size_t i = 0; i < win.size(); ++i) {
        int start_x = (COLS - win[i].length()) / 2;
        mvprintw(start_y + i, start_x, "%s", win[i].c_str());
    }

    std::string exit_text = "type any key to exit";
    int text_y = start_y + win.size() + 1;
    int text_x = (COLS - exit_text.length()) / 2;
    mvprintw(text_y, text_x, "%s", exit_text.c_str());
}

void GManager::print_big_game_over() {
    std::vector<std::string> game_over = {
        "   ____    _    __  __ _____      ___  _   _ _____ ____  ",
        "  / ___|  / \\  |  \\/  | ____|    / _ \\| | | | ____|  _ \\ ",
        " | |  _  / _ \\ | |\\/| |  _|     | | | | | | |  _| | |_) |",
        " | |_| |/ ___ \\| |  | | |___    | |_| | |_| | |___|  _ < ",
        "  \\____/_/   \\_\\_|  |_|_____|    \\___/ \\___/|_____|_| \\_\\"
    };
    
    int start_y = (LINES - game_over.size()) / 2;
    
    for (size_t i = 0; i < game_over.size(); ++i) {
        int start_x = (COLS - game_over[i].length()) / 2;
        mvprintw(start_y + i, start_x, "%s", game_over[i].c_str());
    }

    std::string exit_text = "tap any key to exit";
    int text_y = start_y + game_over.size() + 1; // +1 для отступа
    int text_x = (COLS - exit_text.length()) / 2;
    mvprintw(text_y, text_x, "%s", exit_text.c_str());
}

