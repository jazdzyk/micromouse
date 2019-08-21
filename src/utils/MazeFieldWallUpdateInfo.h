//
// Created by Kuba Jazdzyk on 8/21/19.
//

#ifndef MICROMOUSE_MAZEFIELDWALLUPDATEINFO_H
#define MICROMOUSE_MAZEFIELDWALLUPDATEINFO_H

#include <src/maze/MazeField.h>
#include "Coordinate.h"

struct MazeFieldWallUpdateInfo {
    using WallSide = MazeField::WallSide;
    Coordinate coordinate;
    WallSide wallSide;
    bool shouldBeSet;

    MazeFieldWallUpdateInfo(const Coordinate &coordinate, WallSide wallSide, bool shouldBeSet)
            : coordinate(coordinate), wallSide(wallSide), shouldBeSet(shouldBeSet) {}
};

#endif //MICROMOUSE_MAZEFIELDWALLUPDATEINFO_H
