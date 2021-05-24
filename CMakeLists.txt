# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(robotHexapodControl)

add_library(robotHexapodControl src/board.cpp src/body.cpp src/cmdServo.cpp src/communication.cpp src/leftBackLeg.cpp src/leftFrontLeg.cpp src/leftMiddleLeg.cpp src/leg.cpp src/rightBackLeg.cpp src/rightFrontLeg.cpp src/rightMiddleLeg.cpp src/robotOverallMove.cpp)

# PUBLIC needed to make both hello.h and hello library available elsewhere in project
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(robotHexapodControl PUBLIC cxx_std_20)