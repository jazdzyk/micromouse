//
// Created by Kuba Jazdzyk on 8/21/19.
//

#ifndef MICROMOUSE_MAZEFIELDVIEWDELEGATE_H
#define MICROMOUSE_MAZEFIELDVIEWDELEGATE_H


#include <vector>
#include <src/utils/MazeFieldWallUpdateInfo.h>

/**
 * MazeFieldViewDelegate is a protocol delegating methods from MazeFieldView class.
 */
class MazeFieldViewDelegate {
public:
    using MazeFieldViewInfo = std::vector<MazeFieldWallUpdateInfo>;

    /**
     * A method which delegates work when MazeFieldWall was set.
     *
     * @param info a struct containing info about the maze field related to the wall
     */
    virtual void mazeFieldWallDidSet(const MazeFieldViewInfo &info) = 0;

    /**
     * MazeFieldViewDelegate class destructor.
     */
    virtual ~MazeFieldViewDelegate() = default;
};


#endif //MICROMOUSE_MAZEFIELDVIEWDELEGATE_H
