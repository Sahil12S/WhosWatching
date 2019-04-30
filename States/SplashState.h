#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "State.h"
#include "../Game.h"
#include "MainMenuState.h"

class SplashState : public State
{
public:
    /*
        * Splash State doesn't need any key bindings
        */
    SplashState( GameDataRef data );

    void Init();

    void HandleInput( float dt );
    void Update( float dt );
    void Draw();

    // No need for any key bindings here
    // void InitKeyBinds();

private:
    GameDataRef m_Data;
    sf::Clock m_Clock;
    sf::Sprite m_BackgroundSprite;

    // std::map<std::string, int> m_KeyBinds;
};

#endif // SPLASH_STATE_H