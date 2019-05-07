cmake_minimum_required(VERSION 3.7)

add_compile_options( -Wall -Wextra -Wpedantic )

project( WhosWatching )

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_COMPILER  /usr/bin/g++)
set(CMAKE_C_COMPILER /usr/bin/gcc)


set( SOURCE_FILES main.cpp pch.cpp Game.cpp 
Engine_Managers/StateMachine.cpp Engine_Managers/InputManager.cpp 
Engine_Managers/AssetManager.cpp Engine_Managers/GraphicsSettings.cpp 
States/SplashState.cpp States/MainMenuState.cpp States/PauseMenu.cpp 
States/GameState.cpp States/GameSettingsState.cpp States/EditorState.cpp 
Entities/Entity.cpp Entities/Player.cpp 
Game_Components/HUD.cpp Game_Components/Button.cpp Game_Components/MovementComponent.cpp 
Game_Components/AnimationComponent.cpp Game_Components/HitboxComponent.cpp 
Game_Components/DropDownList.h Game_Components/DropDownList.cpp 
Game_Components/AttributeComponent.cpp 
Game_Components/TextureSelector.cpp Tile/Tile.cpp Map/TileMap.cpp )

add_executable( WhosWatching ${SOURCE_FILES} )

set( EXECUTABLE_NAME ${PROJECT_NAME} )

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()