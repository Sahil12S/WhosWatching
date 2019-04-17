#include "GameState.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "../DEFINITIONS.h"

#include <sstream>

namespace SSEngine
{
    GameState::GameState( GameDataRef data ) : m_Data( std::move( data ) )
    {
    }

    GameState::~GameState()
    {
        delete m_Player;
    }

    void GameState::InitTextures()
    {
        // Load game background
        // m_Data->assets.LoadTexture( "Game Background", GAME_BACKGROUND_FILEPATH );
        // m_BackgroundSprite.setTexture( m_Data->assets.GetTexture( "Game Background" ) );

        // Set Background position
        // m_BackgroundSprite.setPosition( 0, -( m_BackgroundSprite.getGlobalBounds().height - SCREEN_HEIGHT ) );
    }

    void GameState::InitFonts()
    {
        m_Data->assets.LoadFont( "Debug Font", DEBUG_FONT_FILEPATH );
    }

    void GameState::InitSounds()
    {
        // Nothing for now
    }

    void GameState::InitButtons()
    {
        // Nothing for now
    }

    void GameState::InitVariables()
    {
        // Initialize player & spawn it
        // TODO: Make collision with ground
        m_Player = new Player( m_Data );
        m_Player->SetPosition(sf::Vector2f(100, SCREEN_HEIGHT - 100));
    }

    void GameState::InitKeyBinds()
    {
        // Read Key Bindings from file
        std::ifstream ifs ( GAMESTATE_KEY_BIND_FILEPATH );

        if ( ifs.is_open() )
        {
            std::string keyAction;
            std::string key;
            while ( ifs >> keyAction >> key )
            {
                m_KeyBinds[keyAction] = m_Data->input.getSupportedKeys().at( key );
            }
        }

        ifs.close();

        Debug( "Key bindings initialized for Game State" )
    }

    void GameState::Init()
    {
        Debug( "**Initialized** Game State" )

        InitKeyBinds();
        InitTextures();
        InitFonts();
        InitSounds();
        InitButtons();
        InitVariables();
    }

    void GameState::HandleInput( float dt )
    {
        sf::Event event;

        while ( m_Data->window.pollEvent( event ) )
        {
            // Check for window close
            if ( sf::Event::Closed == event.type )
            {
                m_Data->machine.ClearStates();
                m_Data->machine.RemoveState();
                m_Data->window.close();
            }

            if ( sf::Event::KeyPressed == event.type )
            {
                // Go to Pause Screen if game is paused
                if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( m_KeyBinds["PAUSE"] ) ) )
                {
                    m_Data->machine.AddState( StateRef ( new PauseState ( m_Data )), false );
                }

                // Go to Main Menu on pressing of Escape
                if ( sf::Keyboard::isKeyPressed(( sf::Keyboard::Key( m_KeyBinds["QUIT"] ) ) ) )
                {
                    m_Data->machine.AddState( StateRef ( new MainMenuState ( m_Data )), true );
                }
            }
        }

        /*
         * Handle movements
         */

        // Walk Left
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( m_KeyBinds["MOVE_LEFT"] ) ) )
        {
            m_Player->Move( dt, -1.0f, 0.0f);
        }

        // Walk right
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( m_KeyBinds["MOVE_RIGHT"] ) ) )
        {
            m_Player->Move( dt, 1.0f, 0.0f);
        }

        // Walk Up
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( m_KeyBinds["MOVE_UP"] ) ) )
        {
            m_Player->Move( dt, 0.0f, -1.0f);
        }

        // Walk Down
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( m_KeyBinds["MOVE_DOWN"] ) ) )
        {
            m_Player->Move( dt, 0.0f, 1.0f);
        }
        // Attack ( Enter )
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( m_KeyBinds["ATTACK"] ) ) )
        {
            m_Player->Attack();
        }

        // Interact ( Use Space )

    }

    void GameState::Update(float dt)
    {
        m_Data->input.UpdateMousePosition( m_Data->window );
        m_Player->Update( dt );
    }

    void GameState::Draw()
    {
        m_Data->window.clear();
        m_Data->window.draw( m_BackgroundSprite );

        m_Player->Draw();

        // Draw coordinates on mouse pointer for debugging
        sf::Text mouseText;
        mouseText.setPosition( m_Data->input.GetViewMousePosition().x + 5, m_Data->input.GetViewMousePosition().y );
        mouseText.setFont( m_Data->assets.GetFont( "Debug Font" ) );
        mouseText.setCharacterSize( 20 );
        std::stringstream ss;
        ss << m_Data->input.GetViewMousePosition().x << ", " << m_Data->input.GetViewMousePosition().y;
        mouseText.setString( ss.str() );
        m_Data->window.draw( mouseText );

        m_Data->window.display();
    }
}