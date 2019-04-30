#include "Game.h"
#include "States/SplashState.h"

void Game::InitVariables()
{
    srand( time( NULL ) );
    dt = 0.f;
}

void Game::InitGraphicsSettings()
{
    m_Data->GfxSettings.LoadFromFile("Config/graphics.ini");
}

void Game::InitWindow()
{
    if ( m_Data->GfxSettings.fullscreen )
    {
        m_Data->window.create(
                            m_Data->GfxSettings.resolution,
                            m_Data->GfxSettings.title,
                            sf::Style::Fullscreen,
                            m_Data->GfxSettings.contextSettings );
    }
    else
    {
        m_Data->window.create(
                            m_Data->GfxSettings.resolution,
                            m_Data->GfxSettings.title,
                            sf::Style::Titlebar | sf::Style::Close,
                            m_Data->GfxSettings.contextSettings );
    }

    m_Data->window.setFramerateLimit( m_Data->GfxSettings.frameRateLimit );
    m_Data->window.setVerticalSyncEnabled( m_Data->GfxSettings.verticalSync );
}

void Game::InitStates()
{
    m_Data->machine.AddState( StateRef( new SplashState ( m_Data ) ) );
}


Game::Game()
{        
    InitVariables();
    InitGraphicsSettings();
    InitWindow();
    InitStates();
}


void Game::UpdateDt()
{
    /*
        * Updates the dt variable with time it takes to update & render one frame
        */
    dt = m_Clock.restart().asSeconds();
}

void Game::Run()
{
    float newTime, frameTime, interpolation;

    float currentTime = m_Clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while ( m_Data->window.isOpen() )
    {
        UpdateDt();
        m_Data->machine.ProcessStateChange();

        // newTime = m_Clock.getElapsedTime().asSeconds();

        // frameTime = newTime - currentTime;

        // if ( frameTime > 0.25f )
        // {
        //     frameTime = 0.25f;
        // }

        // currentTime = newTime;
        // accumulator += frameTime;

        // while ( accumulator >= dt )
        // {
        m_Data->machine.GetActiveState()->HandleInput( dt );
        m_Data->machine.GetActiveState()->Update( dt );

            // accumulator -= dt;
        // }

        // interpolation = accumulator / dt;
        m_Data->machine.GetActiveState()->Draw( );
    }
}