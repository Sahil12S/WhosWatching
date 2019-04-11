// #include "GameState.h"
#include "SplashState.h"
#include "MainMenuState.h"
#include "../DEFINITIONS.h"

namespace SSEngine
{
    SplashState::SplashState( GameDataRef data ) : m_Data( std::move( data ) )
    {}

    void SplashState::Init()
    {
        Debug( "**Initialized** Splash State" );
        // m_Data->assets.LoadTexture( "Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH );

        // m_BackgroundSprite.setTexture( m_Data->assets.GetTexture( "Splash State Background" ) );
    }

    void SplashState::HandleInput( float dt )
    {
        sf::Event event;

        while ( m_Data->window.pollEvent( event ) )
        {
            if ( sf::Event::Closed == event.type )
            {
                m_Data->machine.RemoveState();
                m_Data->window.close();
            }
        }
    }

    void SplashState::Update(float dt)
    {
        m_Data->input.UpdateMousePosition( m_Data->window );
        if ( m_Clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME )
        {
            m_Data->machine.AddState( StateRef ( new MainMenuState ( m_Data ) ), true );
        }

    }

    void SplashState::Draw()
    {
        m_Data->window.clear();
        m_Data->window.draw( m_BackgroundSprite );
        m_Data->window.display();
    }
}