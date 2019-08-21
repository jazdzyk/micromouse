//
// Created by Kuba Jazdzyk on 8/21/19.
//

#ifndef MICROMOUSE_MAZEFIELDVIEWDELEGATE_H
#define MICROMOUSE_MAZEFIELDVIEWDELEGATE_H


#include <vector>
#include <src/utils/MazeFieldWallUpdateInfo.h>

class MazeFieldViewDelegate {
public:
    using MazeFieldViewInfo = std::vector<MazeFieldWallUpdateInfo>;

    virtual void mazeFieldWallDidSet(const MazeFieldViewInfo &info) = 0;
    virtual ~MazeFieldViewDelegate() = default;
};


#endif //MICROMOUSE_MAZEFIELDVIEWDELEGATE_H
