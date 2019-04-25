#include "GameSettingsState.h"
#include "MainMenuState.h"

namespace SSEngine
{
    // Initializers
    void GameSettingsState::InitKeyBinds()
    {
        Debug( "Settings State: Initializing Key bindings...")

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
    }

    void GameSettingsState::InitTextures()
    {
        Debug( "Settings State: Initializing Textures...")
        // Set Background
        m_Background.setSize( sf::Vector2f( m_Data->window.getSize() ) );
        m_Background.setFillColor( sf::Color(97, 143, 216) );
    }

    void GameSettingsState::InitFonts()
    {
        Debug( "Settings State: Initializing Key Fonts...")
        m_Data->assets.LoadFont( "Button Font", BUTTON_FONT_FILEPATH );
        m_Data->assets.LoadFont( "DDList Font", LIST_FONT_FILEPATH );
    }

    void GameSettingsState::InitSounds()
    {
        // Empty for now
    }

    /*
     * Initialize Buttons and Dropdown list
     */
    void GameSettingsState::InitComponents()
    {
        Debug( "Settings State: Initializing components...")

        // Set Buttons
        m_Buttons["Home"] = new Button( m_Data );
        m_Buttons["Exit"] = new Button( m_Data );
        m_Buttons["Back"] = new Button( m_Data );

        m_Buttons["Back"]->CreateButton( 25.f, 25.f, BUTTON_WIDTH, BUTTON_HEIGHT );
        m_Buttons["Exit"]->CreateButton( 2.f * SCREEN_WIDTH / 3.f - BUTTON_WIDTH / 2.f,
                                              SCREEN_HEIGHT - BUTTON_HEIGHT / 0.8f,
                                              BUTTON_WIDTH, BUTTON_HEIGHT );
        m_Buttons["Home"]->CreateButton( SCREEN_WIDTH / 3.f - BUTTON_WIDTH / 2.f,
                                              SCREEN_HEIGHT - BUTTON_HEIGHT / 0.8f,
                                              BUTTON_WIDTH, BUTTON_HEIGHT );

        std::vector<sf::Color> textColor = { sf::Color( TEXT_IDLE_FILL_COLOR ),
                                             sf::Color( TEXT_HOVER_FILL_COLOR ),
                                             sf::Color( TEXT_ACTIVE_FILL_COLOR ) };

        std::vector<sf::Color> buttonColor = { sf::Color( BUTTON_IDLE_FILL_COLOR ),
                                               sf::Color( BUTTON_HOVER_FILL_COLOR ),
                                               sf::Color( BUTTON_ACTIVE_FILL_COLOR ) };


        m_Buttons["Back"]->SetButtonProperties( "Button Font", "Back", BUTTON_TEXT_SIZE, textColor, buttonColor );
        m_Buttons["Exit"]->SetButtonProperties( "Button Font", "Exit", BUTTON_TEXT_SIZE, textColor, buttonColor );
        m_Buttons["Home"]->SetButtonProperties( "Button Font", "Home", BUTTON_TEXT_SIZE, textColor, buttonColor );

        // std::string list[] = { "abc", "def", "fgh", "ijk", "lmn" };
        std::string list[] = { "1920 x 1080", "1280 x 720", "800 x 600", "640 x 480" };

        m_DropdownList["RESOLUTION"] = new DropDownList( m_Data, "DDList Font", SCREEN_WIDTH / 2.f - LIST_WIDTH / 2.f, 400.f, list, 4 );
    }

    void GameSettingsState::InitVariables()
    {
        Debug( "Settings State: Initializing variables...")

        // Initialize HUD
        m_Hud = new HUD( m_Data );
        m_Hud->SetText( "Main Menu Font", "SETTINGS" , TITLE_SIZE, ( m_Data->window.getSize().x / 2.0f ), m_Data->window.getSize().y / 5.0f );
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

        for ( const auto& dl : m_DropdownList )
        {
            delete dl.second;
        }
        // delete m_DropdownList;
    }

    void GameSettingsState::Init()
    {
        Debug( "Settings State: Initializing..." )

        InitKeyBinds();
        InitTextures();
        InitSounds();
        InitFonts();
        InitVariables();
        InitComponents();
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
    

     void GameSettingsState::UpdateComponents( const float& dt )
     {
         for ( auto button : m_Buttons )
        {
            button.second->Update(m_Data->input.GetViewMousePosition());
        }

        for ( auto dl : m_DropdownList )
        {
            dl.second->Update(dt, m_Data->input.GetViewMousePosition());
        }
     }

    void GameSettingsState::Update(float dt)
    {
        m_Data->input.UpdateMousePosition( m_Data->window );

        UpdateComponents( dt );

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

        
        for ( auto dl : m_DropdownList )
        {
            dl.second->Draw();
        }

        // m_DropdownList["RESOLUTION"]->Draw();

        m_Data->window.display();
    }
}