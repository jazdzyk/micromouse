cmake_minimum_required(VERSION 3.14)
project(micromouse)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/lib/x86_64-linux-gnu/cmake")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_executable(micromouse main.cpp src/utils/Timer.cpp src/utils/Timer.h src/controllers/StartController.cpp src/controllers/StartController.h src/controllers/BaseController.cpp src/controllers/BaseController.h src/utils/Enums.h)

target_link_libraries(micromouse Qt5::Core)
target_link_libraries(micromouse Qt5::Widgets)