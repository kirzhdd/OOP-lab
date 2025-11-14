#include "GManager.h"

GManager::GManager() {}
GManager::GManager(int height, int width, int hand_size, int level) {
    gfield = GField(height, width);
    manager = Manager(height, width, hand_size, level);
}

GManager::GManager(int height, int width, std::vector<std::string> spells, int level) {
    gfield = GField(height, width);
    manager = Manager(height, width, spells, level);
}
GManager::~GManager() {}


void GManager::start_work(){
    initscr(); //активируем окно терминала
    noecho(); //чтобы вводимые символы не отображались
    keypad(stdscr, TRUE); //включаем считывание клавиш
    gfield = manager.sync(); //получаем логическое поле
    gfield.draw(); //рисуем поле
    refresh(); //обновляем
}

bool GManager::work(){
    bool condition = true; //персонаж живой || уровень не пройден
    char c;
    while(condition){
        display_lifes();
        display_moves();
        display_combat();
        display_my_spells();
        display_enemy_tower();
        display_spells_controls();
        display_killed();
        display_need_to_do();
        display_controls(); 


        c = getch();
        switch(c){
            //выходим из игры на q
            case 'q':{
                //заканчиваем работу и выходим из функции
                return false;} 
            
            //управляем персонажем
            case 'l': case 'k': case 'j': case 'h':
            case 'w': case 'a' : case 's' : case 'd':
            case 'c':{
                //обноыляем condition не умер ли персонаж
                condition = manager.process(c, manager.get_level());
                break;}

            //используем заклинание на x
            case 'x':{
                display_choose_spell();
                char spell_c = getch(); //выбираем какое заклинание юзаем
                display_spell_was_choosed(spell_c);
                char direction_c = getch(); //выбираем куда бьем
                bool was = manager.use_spell(spell_c, direction_c);       
                display_spell_was_used(was); //показываем, ударили или нет
                break;}

            //сохраняемся на m
            case 'm': {
                Saving data = serialize();
                display_save_game(save_manager.save_game(data));
                break;}
            //загружаемся на n
            case 'n':{
                Saving data;
                display_load_game(save_manager.load_game(data));
                deserialize(data);
                break;}
        }

        gfield = manager.sync(); //получаем логическое поле
        gfield.draw(); //рисуем
        refresh(); //обновляем
    }

    //обновляем condition не прошли ли мы уровень
    condition = manager.check_condition(manager.get_level());
    return condition;
}

void GManager::end_work(bool pass){
    clear(); //очищаем наше окошко
    if(!pass) print_big_game_over(); //если мы не прошли игру - рисуем game over
    if(pass) print_win(); //если прошли - рисуем победу
    getch(); //type any key to exit
    endwin(); //закрываем окошко
    return;
}


//для перехода на след уровень нам нужно сбросить половину заклинаний
//мы возвращаем полсписка заклинаний для создания нового уровня с ними же
std::vector<std::string> GManager::get_reset_spells(){
    return manager.get_reset_spells();
}


//для сохранения и загрузки
Saving GManager::serialize() const{
    Saving result;
    result.manager = manager.serialize();
    result.gfield = gfield.serialize();
    return result;
}


void GManager::deserialize(const Saving& data){
    manager.deserialize(data.manager);
    gfield.deserialize(data.gfield);
}
