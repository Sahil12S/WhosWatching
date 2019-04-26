#include "Game.h"
#include "States/SplashState.h"

namespace SSEngine
{
    Game::Game(unsigned int width, unsigned int height, std::string title)
    {
        srand( time( NULL ) );
        m_Data->videoModes = sf::VideoMode::getFullscreenModes();
        sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
        bool fullscreen = true;
        bool vertical_sync_enabled = false;
        unsigned antialiasing_level = 0;

        m_Data->windowSettings.antialiasingLevel = antialiasing_level;
        
        if ( fullscreen )
        {
            m_Data->window.create( window_bounds, title, sf::Style::Fullscreen, m_Data->windowSettings );
        }
        else
        {
            m_Data->window.create( window_bounds, title, sf::Style::Close | sf::Style::Titlebar, m_Data->windowSettings );
        }
        
        m_Data->window.setFramerateLimit( 60 );
        m_Data->window.setVerticalSyncEnabled( vertical_sync_enabled );

        m_Data->machine.AddState( StateRef( new SplashState ( m_Data ) ) );

        Run();
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
}