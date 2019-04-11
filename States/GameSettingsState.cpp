#include "GameSettingsState.h"
#include "MainMenuState.h"
#include "../DEFINITIONS.h"

namespace SSEngine
{
    // Initializers
    void GameSettingsState::InitKeyBinds()
    {
        std::fstream ifs ( SETTINGS_STATE_KEY_BIND_FILEPATH );

        if ( ifs.is_open() )
        {
            std::string keyAction;
            std::string key;

            while( ifs >> keyAction >> key )
            {
                m_KeyBinds[keyAction] = m_Data->input.getSupportedKeys().at( key );
            }
        }

        Debug( "Key binds initialized for Settings State" )
    }

    void GameSettingsState::InitTextures()
    {
        // Set Background
        m_Background.setSize( sf::Vector2f( m_Data->window.getSize() ) );
        m_Background.setFillColor( sf::Color(97, 143, 216) );
    }

    void GameSettingsState::InitFonts()
    {
        m_Data->assets.LoadFont( "Button Font", BUTTON_FONT_FILEPATH );
    }

    void GameSettingsState::InitSounds()
    {
        // Empty for now
    }

    void GameSettingsState::InitButtons()
    {
        // Set Buttons
        m_Buttons["Home"] = new Button( m_Data );
        m_Buttons["Exit"] = new Button( m_Data );
        m_Buttons["Back"] = new Button( m_Data );

        m_Buttons["Back"]->SetButtonPosition( 25.f, 25.f );
        m_Buttons["Exit"]->SetButtonPosition( 2.f * SCREEN_WIDTH / 3.f - BUTTON_WIDTH / 2.f,
                                              SCREEN_HEIGHT - BUTTON_HEIGHT / 0.8f );
        m_Buttons["Home"]->SetButtonPosition( SCREEN_WIDTH / 3.f - BUTTON_WIDTH / 2.f,
                                              SCREEN_HEIGHT - BUTTON_HEIGHT / 0.8f );

        std::vector<sf::Color> textColor = { sf::Color( TEXT_IDLE_FILL_COLOR ),
                                             sf::Color( TEXT_HOVER_FILL_COLOR ),
                                             sf::Color( TEXT_ACTIVE_FILL_COLOR ) };

        std::vector<sf::Color> buttonColor = { sf::Color( BUTTON_IDLE_FILL_COLOR ),
                                               sf::Color( BUTTON_HOVER_FILL_COLOR ),
                                               sf::Color( BUTTON_ACTIVE_FILL_COLOR ) };


        m_Buttons["Back"]->SetButtonProperties( "Button Font", "Back", BUTTON_TEXT_SIZE, textColor, buttonColor );
        m_Buttons["Exit"]->SetButtonProperties( "Button Font", "Exit", BUTTON_TEXT_SIZE, textColor, buttonColor );
        m_Buttons["Home"]->SetButtonProperties( "Button Font", "Home", BUTTON_TEXT_SIZE, textColor, buttonColor );
    }

    void GameSettingsState::InitVariables()
    {
        // Initialize HUD
        m_Hud = new HUD( m_Data );
        m_Hud->SetTitle( "Main Menu Font", "SETTINGS" );
    }

    GameSettingsState::GameSettingsState(SSEngine::GameDataRef data) : m_Data ( move( data ) )
    {}

    GameSettingsState::~GameSettingsState()
    {
        delete m_Hud;
        for ( const auto& button : m_Buttons )
        {
            delete button.second;
        }
    }

    void GameSettingsState::Init()
    {
        Debug( "Game Settings State" )

        InitKeyBinds();

        // Assets
        InitTextures();
        InitSounds();
        InitFonts();

        InitVariables();

        InitButtons();
    }

    void GameSettingsState::HandleInput( float dt )
    {
        sf::Event event;

        while ( m_Data->window.pollEvent( event ) )
        {
            if ( sf::Event::Closed == event.type )
            {
                m_Data->machine.ClearStates();
                m_Data->machine.RemoveState();
                m_Data->window.close();
            }

            // Go back to Main Menu on Button click or Escape
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( m_KeyBinds["QUIT"] ) ) ||
                    m_Buttons["Home"]->isPressed() )
            {
                // If there are more than 1 state in stack, remove all but active one
                m_Data->machine.ClearStates();
                m_Data->machine.AddState( StateRef ( new MainMenuState ( m_Data ) ), true );
            }

            if ( m_Buttons["Exit"]->isPressed() )
            {
                m_Data->machine.RemoveState();
                m_Data->window.close();
            }

            // Go back to last active state or home
            if ( m_Buttons["Back"]->isPressed() )
            {
                if ( m_Data->machine.GetStatesCount() > 1 )
                {
                    m_Data->machine.RemoveState();
                }
                else
                {
                    m_Data->machine.AddState( StateRef ( new MainMenuState ( m_Data ) ), true );
                }
            }
        }
    }

    void GameSettingsState::Update(float dt)
    {
        m_Data->input.UpdateMousePosition( m_Data->window );

        for ( auto button : m_Buttons )
        {
            button.second->Update(m_Data->input.GetViewMousePosition());
        }
    }

    void GameSettingsState::Draw()
    {
        m_Data->window.clear();

        m_Data->window.draw( m_Background );

        m_Hud->Draw( true );

        for ( auto button : m_Buttons )
        {
            button.second->Draw();
        }

        m_Data->window.display();
    }
}