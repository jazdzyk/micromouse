//
// Created by Kuba Jazdzyk on 8/16/19.
//

#ifndef MICROMOUSE_LOCALIZABLE_H
#define MICROMOUSE_LOCALIZABLE_H


#include <QtCore/QString>
#include <map>

namespace Localizable {
    enum class PL {
        // labels
        ALGORITHM_MODE_ROBOT1_LABEL,
        ALGORITHM_MODE_ROBOT2_LABEL,

        RESULT_ROBOT1_LABEL,
        RESULT_ROBOT2_LABEL,
        RESULT_TIME_LABEL,
        RESULT_DISTANCE_LABEL,
        RESULT_SPEED_LABEL,

        RESULT_TIME_SUFFIX_LABEL,
        RESULT_DISTANCE_SUFFIX_LABEL,
        RESULT_SPEED_SUFFIX_LABEL,

        // buttons
        START_SIMULATION_BUTTON_START_CONTROLLER_TITLE,
        OWN_MAZE_BUTTON_TITLE,

        START_SIMULATION_BUTTON_SIMULATION_CONTROLLER_TITLE,
        PAUSE_SIMULATION_BUTTON_TITLE,
        RESET_SIMULATION_BUTTON_TITLE,

        ACCEPT_MAZE_BUTTON_TITLE,
        SAVE_MAZE_BUTTON_TITLE,
        LOAD_MAZE_BUTTON_TITLE,

        // radio buttons
        ONE_ROBOT_RADIO_BUTTON_TITLE,
        TWO_ROBOTS_RADIO_BUTTON_TITLE,
        MAZE_SIZE_256_RADIO_BUTTON_TITLE,
        MAZE_SIZE_576_RADIO_BUTTON_TITLE,
        MAZE_SIZE_1024_RADIO_BUTTON_TITLE,

        // group boxes
        SIMULATION_MODE_BOX_TITLE,
        MAZE_SIZE_MODE_BOX_TITLE,
        OWN_MAZE_MODE_BOX_TITLE,
        ALGORITHM_MODE_BOX_TITLE,

        // drop-downs
        LEFT_WALL_FOLLOWER_ALGORITHM_DROP_DOWN_TEXT,
        RIGHT_WALL_FOLLOWER_ALGORITHM_DROP_DOWN_TEXT,
        BRUTE_FORCE_ALGORITHM_DROP_DOWN_TEXT,
        WAVE_PROPAGATION_ALGORITHM_DROP_DOWN_TEXT,

        //file-dialog related
        OPEN_FILE_DIALOG_TEXT,
        SAVE_FILE_DIALOG_TEXT,
        MAZE_BINARY_FILE_DESCRIPTION,
    };

    using Locale = std::map<PL, QString>;

    static Locale pl = {
            {PL::ALGORITHM_MODE_ROBOT1_LABEL,                         "ROBOT 1"},
            {PL::ALGORITHM_MODE_ROBOT2_LABEL,                         "ROBOT 2"},

            {PL::RESULT_ROBOT1_LABEL,                                 "ROBOT 1"},
            {PL::RESULT_ROBOT2_LABEL,                                 "ROBOT 2"},
            {PL::RESULT_TIME_LABEL,                                   "CZAS:"},
            {PL::RESULT_DISTANCE_LABEL,                               "DYSTANS:"},
            {PL::RESULT_SPEED_LABEL,                                  "PRĘDKOŚĆ:"},

            {PL::RESULT_TIME_SUFFIX_LABEL,                            " s"},
            {PL::RESULT_DISTANCE_SUFFIX_LABEL,                        " pól"},
            {PL::RESULT_SPEED_SUFFIX_LABEL,                           " pola/s"},

            {PL::START_SIMULATION_BUTTON_START_CONTROLLER_TITLE,      "SYMULACJA"},
            {PL::OWN_MAZE_BUTTON_TITLE,                               "WŁASNY LABIRYNT"},

            {PL::START_SIMULATION_BUTTON_SIMULATION_CONTROLLER_TITLE, "START"},
            {PL::PAUSE_SIMULATION_BUTTON_TITLE,                       "WSTRZYMAJ"},
            {PL::RESET_SIMULATION_BUTTON_TITLE,                       "RESET"},

            {PL::ACCEPT_MAZE_BUTTON_TITLE,                            "OK"},
            {PL::SAVE_MAZE_BUTTON_TITLE,                              "ZAPISZ"},
            {PL::LOAD_MAZE_BUTTON_TITLE,                              "WCZYTAJ"},

            {PL::ONE_ROBOT_RADIO_BUTTON_TITLE,                        "1 ROBOT"},
            {PL::TWO_ROBOTS_RADIO_BUTTON_TITLE,                       "2 ROBOTY"},
            {PL::MAZE_SIZE_256_RADIO_BUTTON_TITLE,                    "256 PÓL"},
            {PL::MAZE_SIZE_576_RADIO_BUTTON_TITLE,                    "576 PÓL"},
            {PL::MAZE_SIZE_1024_RADIO_BUTTON_TITLE,                   "1024 POLA"},

            {PL::SIMULATION_MODE_BOX_TITLE,                           "TRYB SYMULACJI"},
            {PL::MAZE_SIZE_MODE_BOX_TITLE,                            "ROZMIAR LABIRYNTU"},
            {PL::OWN_MAZE_MODE_BOX_TITLE,                             "TWORZENIE LABIRYNTU"},
            {PL::ALGORITHM_MODE_BOX_TITLE,                            "WYBÓR ALGORYTMU"},

            {PL::LEFT_WALL_FOLLOWER_ALGORITHM_DROP_DOWN_TEXT,         "LEFT-WALLS-FOLLOWER"},
            {PL::RIGHT_WALL_FOLLOWER_ALGORITHM_DROP_DOWN_TEXT,        "RIGHT-WALLS-FOLLOWER"},
            {PL::BRUTE_FORCE_ALGORITHM_DROP_DOWN_TEXT,                "BRUTE FORCE"},
            {PL::WAVE_PROPAGATION_ALGORITHM_DROP_DOWN_TEXT,           "PROPAGACJA FALI"},

            {PL::OPEN_FILE_DIALOG_TEXT,                               "Otwórz stworzony wcześniej labirynt..."},
            {PL::SAVE_FILE_DIALOG_TEXT,                               "Zapisz stworzony labirynt..."},
            {PL::MAZE_BINARY_FILE_DESCRIPTION,                        "Binarny plik labiryntu (*.dat)"},
    };
}

#endif //MICROMOUSE_LOCALIZABLE_H
