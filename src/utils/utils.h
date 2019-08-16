//
// Created by Kuba Jazdzyk on 8/16/19.
//

#ifndef MICROMOUSE_UTILS_H
#define MICROMOUSE_UTILS_H

namespace utils {
    template<typename T>
    void destruct(T *object) {
        delete object;
        object = nullptr;
    }
}

#endif //MICROMOUSE_UTILS_H
