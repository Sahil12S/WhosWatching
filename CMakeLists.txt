cmake_minimum_required(VERSION 3.13)
project(cmpe219)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_COMPILER  /usr/bin/g++)
set(CMAKE_C_COMPILER /usr/bin/gcc)

set(SOURCE_FILES main.cpp States/State.h "Engine_Managers/StateMachine.cpp" "Engine_Managers/StateMachine.h" "Engine_Managers/InputManager.cpp" "Engine_Managers/InputManager.h" "Engine_Managers/AssetManager.cpp" "Engine_Managers/AssetManager.h" Game.cpp Game.h States/SplashState.cpp States/SplashState.h DEFINITIONS.h States/MainMenuState.cpp States/MainMenuState.h States/PauseState.cpp States/PauseState.h States/GameState.cpp States/GameState.h States/GameSettingsState.cpp States/GameSettingsState.h Entities/Player.cpp Entities/Player.h Entities/Entity.cpp Entities/Entity.h "Game_Components/HUD.cpp" "Game_Components/HUD.h" "Game_Components/Button.cpp" "Game_Components/Button.h" Game_Components/MovementComponent.cpp Game_Components/MovementComponent.h Game_Components/AnimationComponent.cpp Game_Components/AnimationComponent.h Game_Components/HitboxComponent.cpp Game_Components/HitboxComponent.h)

add_executable(cmpe219 ${SOURCE_FILES})

set(EXECUTABLE_NAME ${PROJECT_NAME})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()