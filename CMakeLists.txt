cmake_minimum_required(VERSION 3.14)
project(micromouse)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/lib/x86_64-linux-gnu/cmake")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_executable(micromouse main.cpp src/utils/Timer.cpp src/utils/Timer.h src/controllers/StartController.cpp src/controllers/StartController.h src/controllers/BaseController.cpp src/controllers/BaseController.h src/utils/Enums.h src/utils/SimulationSettings.h src/maze/Maze.cpp src/maze/Maze.h src/utils/Localizable.h src/utils/Logging.h src/utils/utils.h src/elements/RoundedPushButton.cpp src/elements/RoundedPushButton.h src/elements/RadioButtonGroupBox.cpp src/elements/RadioButtonGroupBox.h src/elements/DropDownGroupBox.cpp src/elements/DropDownGroupBox.h src/elements/CheckButtonGroupBox.cpp src/elements/CheckButtonGroupBox.h resources.qrc src/protocols/delegates/ReturnToPreviousControllerDelegate.h src/controllers/SimulationController.cpp src/controllers/SimulationController.h src/controllers/MazeController.cpp src/controllers/MazeController.h src/protocols/delegates/MazeControllerDelegate.h src/views/MazeView.cpp src/views/MazeView.h src/maze/MazeWall.cpp src/maze/MazeWall.h src/protocols/Serializable.h src/maze/MazeField.cpp src/maze/MazeField.h src/utils/Coordinate.h src/utils/JsonKeys.h src/maze/RandomMazeGenerator.cpp src/maze/RandomMazeGenerator.h src/views/MazeFieldView.cpp src/views/MazeFieldView.h src/protocols/delegates/MazeFieldViewDelegate.h src/utils/MazeFieldWallUpdateInfo.h src/protocols/delegates/MazeViewDelegate.h src/views/SimulationStateView.cpp src/views/SimulationStateView.h src/utils/Simulation.cpp src/utils/Simulation.h src/views/ArrowsView.cpp src/views/ArrowsView.h src/elements/ImageLabel.cpp src/elements/ImageLabel.h src/utils/Robot.h src/protocols/delegates/RobotDelegate.h src/utils/MazeSolver.h src/utils/DistanceSensor.h src/utils/SensorProtocol.h src/utils/RobotMotor.h src/protocols/delegates/SimulationDelegate.h)

target_link_libraries(micromouse Qt5::Core)
target_link_libraries(micromouse Qt5::Widgets)
target_link_libraries(micromouse Threads::Threads)