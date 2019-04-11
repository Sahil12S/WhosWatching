#include "MainMenuState.h"
#include "GameState.h"
#include "GameSettingsState.h"
#include "../DEFINITIONS.h"

namespace SSEngine
{
    MainMenuState::MainMenuState( GameDataRef data ) : m_Data ( std::move( data ) )
    {

    }

    MainMenuState::~MainMenuState()
    {
        delete m_Hud;
        for ( const auto& button : m_Buttons )
        {
            delete button.second;
        }
    }

    void MainMenuState::InitTextures()
    {
        // Use sprites for background
        m_Background.setSize( sf::Vector2f( m_Data->window.getSize() ) );
        m_Background.setFillColor( sf::Color(97, 143, 216) );
    }

    void MainMenuState::InitFonts()
    {
        m_Data->assets.LoadFont( "Main Menu Font", SCREEN_FONT_FILEPATH );
        m_Data->assets.LoadFont( "Button Font", BUTTON_FONT_FILEPATH );
        // m_Data->assets.LoadFont( "Debug Font", DEBUG_FONT_FILEPATH );
    }

    void MainMenuState::InitSounds()
    {

    }

    void MainMenuState::InitButtons()
    {
        //Draw Buttons
        m_Buttons["Play"] = new Button( m_Data );
        m_Buttons["Exit"] = new Button( m_Data );
        m_Buttons["Settings"] = new Button( m_Data );

        // Set Button Properties
        m_Buttons["Exit"]->SetButtonPosition( SCREEN_WIDTH / 2.0f - BUTTON_WIDTH / 2.0f, SCREEN_HEIGHT - BUTTON_HEIGHT / 0.8f );
        m_Buttons["Settings"]->SetButtonPosition( SCREEN_WIDTH / 2.0f - BUTTON_WIDTH / 2.0f, m_Buttons["Exit"]->GetButton().getPosition().y - BUTTON_HEIGHT / 0.8f );
        m_Buttons["Play"]->SetButtonPosition( SCREEN_WIDTH / 2.0f - BUTTON_WIDTH / 2.0f, m_Buttons["Settings"]->GetButton().getPosition().y - BUTTON_HEIGHT / 0.8f );

        // Set Text and Button colors

        std::vector<sf::Color> textColor = { sf::Color( TEXT_IDLE_FILL_COLOR ),
                                             sf::Color( TEXT_HOVER_FILL_COLOR ),
                                             sf::Color( TEXT_ACTIVE_FILL_COLOR ) };

        std::vector<sf::Color> buttonColor = { sf::Color( BUTTON_IDLE_FILL_COLOR ),
                                               sf::Color( BUTTON_HOVER_FILL_COLOR ),
                                               sf::Color( BUTTON_ACTIVE_FILL_COLOR ) };


        m_Buttons["Exit"]->SetButtonProperties( "Button Font", "Exit", BUTTON_TEXT_SIZE, textColor, buttonColor );
        m_Buttons["Settings"]->SetButtonProperties( "Button Font", "Settings", BUTTON_TEXT_SIZE, textColor, buttonColor );
        m_Buttons["Play"]->SetButtonProperties( "Button Font", "Play", BUTTON_TEXT_SIZE, textColor, buttonColor );
    }

    void MainMenuState::InitVariables()
    {
        m_Hud = new HUD( m_Data );
        m_Hud->SetTitle( "Main Menu Font", "WHO'S WATCHING??" );
    }

    // @override
    void MainMenuState::Init()
    {
        Debug( "**Initialized** Main menu state" )

        InitTextures();
        InitFonts();
        InitSounds();
        InitButtons();
        InitVariables();
        InitKeyBinds();
    }

    void MainMenuState::InitKeyBinds()
    {
        std::fstream ifs ( MAIN_MENU_KEY_BIND_FILEPATH );

        if ( ifs.is_open() )
        {
            std::string keyAction;
            std::string key;

            while( ifs >> keyAction >> key )
            {
                m_KeyBinds[keyAction] = m_Data->input.getSupportedKeys().at( key );
            }
        }
        Debug( "Key bindings initialized for main menu" )
    }

    // @override
    void MainMenuState::HandleInput( float dt )
    {
        sf::Event event;

        while ( m_Data->window.pollEvent( event ) )
        {
            // Check for game close
            if ( sf::Event::Closed == event.type || m_Buttons["Exit"]->isPressed() )
            {
                m_Data->machine.ClearStates();
                m_Data->machine.RemoveState();
                m_Data->window.close();
            }

            if ( m_Buttons["Play"]->isPressed() )
            {
                m_Data->machine.AddState( StateRef ( new GameState( m_Data ) ), true );
            }
            if ( m_Buttons["Settings"]->isPressed() )
            {
                m_Data->machine.AddState( StateRef ( new GameSettingsState( m_Data ) ), true );
            }

            /*if ( m_Data->input.IsSpriteClicked( m_PlayButton, sf::Mouse::Left, m_Data->window ) )
            {
                m_Data->machine.AddState( StateRef ( new GameState( m_Data ) ), true );
            }
            if ( m_Data->input.IsSpriteClicked( m_SettingsButton, sf::Mouse::Left, m_Data->window ) )
            {
                m_Data->machine.AddState( StateRef ( new GameSettingsState( m_Data ) ), true );
            }*/
        }
    }

    // @override
    void MainMenuState::Update(float dt)
    {
        m_Data->input.UpdateMousePosition( m_Data->window );

        for ( auto button : m_Buttons )
        {
            button.second->Update(m_Data->input.GetViewMousePosition());
        }
    }

    // @override
    void MainMenuState::Draw()
    {
        m_Data->window.clear();

        m_Data->window.draw( m_Background );
        /*m_Data->window.draw( m_PlayButton );
        m_Data->window.draw( m_ExitButton );
        m_Data->window.draw( m_SettingsButton );*/

        m_Hud->Draw( true );

        // m_Buttons["Settings"]->Draw();

        for ( auto button : m_Buttons )
        {
            button.second->Draw();
        }

        /* Remove later */
        /*sf::Text mouseText;
        mouseText.setPosition( m_Data->input.GetViewMousePosition().x + 5, m_Data->input.GetViewMousePosition().y );
        mouseText.setFont( m_Data->assets.GetFont( "Debug Font" ) );
        mouseText.setCharacterSize( 20 );
        std::stringstream ss;
        ss << m_Data->input.GetViewMousePosition().x << ", " << m_Data->input.GetViewMousePosition().y;
        mouseText.setString( ss.str() );
        m_Data->window.draw( mouseText );*/


        m_Data->window.display();
    }


}