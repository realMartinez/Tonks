# CMakeList.txt : CMake project for Tonks, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Tonks "Tonks.cpp" "Tonks.h"  "MapGen.cpp" "MapGen.h" "PlayerInput.h" "PlayerInput.cpp"  "GameStage.h" "GameStage.cpp"   "MainMenuStage.h" "MainMenuStage.cpp"  "GameDataStructs.h")

# TODO: Add tests and install targets if needed.
