cmake_minimum_required(VERSION 3.10)
project(MyGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(NCURSES REQUIRED ncurses)

set(SOURCES
    src/main.cpp
    
    # entities
    src/game/entities/Enemy.cpp
    src/game/entities/Entity.cpp
    src/game/entities/Player.cpp
    src/game/entities/EnemyTower.cpp
    
    # manager
    src/game/manager/Cell.cpp
    src/game/manager/Field.cpp
    src/game/manager/Manager.cpp
    src/game/manager/Manager_get.cpp
    src/game/manager/Manager_in.cpp
    
    # utils
    src/game/utils/Functions.cpp
    src/game/utils/Point.cpp

    # spells
    src/game/spells/ARSpell.cpp
    src/game/spells/DDSpell.cpp
    src/game/spells/TrapSpell.cpp
    src/game/spells/Hand.cpp
    
    # ui
    src/ui/Game.cpp
    src/ui/GCell.cpp
    src/ui/GField.cpp
    src/ui/GManager.cpp
    src/ui/GManager_display.cpp

    #saving
    src/saving/SaveManager.cpp
)

add_executable(my_game ${SOURCES})

target_include_directories(my_game PRIVATE
    src
    src/game
    src/game/entities
    src/game/manager
    src/game/spells
    src/utils
    src/ui
    src/saving
)

target_link_libraries(my_game ${NCURSES_LIBRARIES})
target_compile_options(my_game PRIVATE -Wall -Wextra -g)
