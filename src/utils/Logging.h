//
// Created by Kuba Jazdzyk on 8/16/19.
//

#ifndef MICROMOUSE_LOGGING_H
#define MICROMOUSE_LOGGING_H

#include <string>
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

namespace Log {
    static void print(const std::string message) {
        auto now = std::chrono::system_clock::now();
        auto now_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&now_t), "%Y/%m/%d %T");
        std::cout << ss.str() << ": " << message << std::endl;
    }
}

#endif //MICROMOUSE_LOGGING_H
