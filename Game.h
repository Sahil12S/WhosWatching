#ifndef GAME_H
#define GAME_H

#include "pch.cpp"

#include "Engine_Managers/AssetManager.h"
#include "Engine_Managers/InputManager.h"
#include "Engine_Managers/StateMachine.h"
#include "Engine_Managers/GraphicsSettings.h"
#include "Entities/Entity.h"

struct GameData
{
    StateMachine machine;
    AssetManager assets;
    InputManager input;
    sf::RenderWindow window;
    GraphicsSettings GfxSettings;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
private:
    float dt;
    // const float dt = 1.0f / 60.0f;

    sf::Clock m_Clock;

    GameDataRef m_Data = std::make_shared<GameData>();
    // GraphicsSettings* m_Gfx;

    void InitVariables();
    void InitGraphicsSettings();
    void InitWindow();
    void InitStates();

    void UpdateDt();

public:
    Game();
    void Run();
};

#endif // GAME_H