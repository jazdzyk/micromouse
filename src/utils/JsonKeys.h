//
// Created by Kuba Jazdzyk on 8/17/19.
//

#ifndef MICROMOUSE_JSONKEYS_H
#define MICROMOUSE_JSONKEYS_H

#include <QtCore/QString>

namespace {
    struct JsonKeys {
        using Key = const QString;

        // Maze-related
        static Key MAZE_MODE;
        static Key SIMULATION_MODE;
        static Key FIELDS;

        // MazeField-related
        static Key TYPE;
        static Key WALL;
        static Key COORD;
        static Key VERTICAL;
        static Key HORIZONTAL;
        static Key LEFT;
        static Key RIGHT;
        static Key TOP;
        static Key BOTTOM;

        // MazeWall-related
        static Key ACTIVE;
        static Key BLOCKED;
        static Key SIDE;

    };

    // Maze-related
    JsonKeys::Key JsonKeys::MAZE_MODE = "MAZE_MODE";
    JsonKeys::Key JsonKeys::SIMULATION_MODE = "SIMULATION_MODE";
    JsonKeys::Key JsonKeys::FIELDS = "FIELDS";

    // MazeField-related
    JsonKeys::Key JsonKeys::TYPE = "TYPE";
    JsonKeys::Key JsonKeys::WALL = "WALL";
    JsonKeys::Key JsonKeys::LEFT = "LEFT";
    JsonKeys::Key JsonKeys::RIGHT = "RIGHT";
    JsonKeys::Key JsonKeys::TOP = "TOP";
    JsonKeys::Key JsonKeys::BOTTOM = "BOTTOM";
    JsonKeys::Key JsonKeys::COORD = "COORD";
    JsonKeys::Key JsonKeys::VERTICAL = "VERT";
    JsonKeys::Key JsonKeys::HORIZONTAL = "HORIZ";

    // MazeWall-related
    JsonKeys::Key JsonKeys::ACTIVE = "ACTIVE";
    JsonKeys::Key JsonKeys::BLOCKED = "BLOCKED";
    JsonKeys::Key JsonKeys::SIDE = "SIDE";
}

#endif //MICROMOUSE_JSONKEYS_H
