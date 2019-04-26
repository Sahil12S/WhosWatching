#include "PauseState.h"
#include "MainMenuState.h"

namespace SSEngine
{
    PauseState::PauseState(SSEngine::GameDataRef data) : m_Data( std::move( data ) )
    {

    }

    PauseState::~PauseState()
    {
        delete m_Hud;
        for ( const auto& button : m_Buttons )
        {
            delete button.second;
        }
    }

    void PauseState::InitTextures()
    {
        // Set Background
        m_Background.setSize( sf::Vector2f( m_Data->window.getSize() ) );
        m_Background.setFillColor( sf::Color(97, 143, 216) );
    }

    void PauseState::InitFonts()
    {
        m_Data->assets.LoadFont( "Main Menu Font", SCREEN_FONT_FILEPATH );
        m_Data->assets.LoadFont( "Button Font", BUTTON_FONT_FILEPATH );
    }

    void PauseState::InitSounds()
    {

    }

    void PauseState::InitComponents()
    {
        m_Buttons["Home"] = new Button( m_Data );
        m_Buttons["Quit"] = new Button( m_Data );
        m_Buttons["Back"] = new Button( m_Data );

        m_Buttons["Back"]->CreateButton(  m_Data->window.getSize().x / 3.f - BUTTON_WIDTH / 2.f,
                                               m_Data->window.getSize().y - BUTTON_HEIGHT / 0.4f,
                                              BUTTON_WIDTH, BUTTON_HEIGHT );
        m_Buttons["Quit"]->CreateButton( 2.f *  m_Data->window.getSize().x / 3.f - BUTTON_WIDTH / 2.f,
                                               m_Data->window.getSize().y - BUTTON_HEIGHT / 0.4f,
                                              BUTTON_WIDTH, BUTTON_HEIGHT );


        std::vector<sf::Color> textColor = { sf::Color( TEXT_IDLE_FILL_COLOR ),
                                             sf::Color( TEXT_HOVER_FILL_COLOR ),
                                             sf::Color( TEXT_ACTIVE_FILL_COLOR ) };

        std::vector<sf::Color> buttonColor = { sf::Color( BUTTON_IDLE_FILL_COLOR ),
                                               sf::Color( BUTTON_HOVER_FILL_COLOR ),
                                               sf::Color( BUTTON_ACTIVE_FILL_COLOR ) };

        m_Buttons["Back"]->SetButtonProperties( "Button Font", "Back", BUTTON_TEXT_SIZE, textColor, buttonColor );
        m_Buttons["Quit"]->SetButtonProperties( "Button Font", "Quit", BUTTON_TEXT_SIZE, textColor, buttonColor );
    }

    void PauseState::InitVariables()
    {
        m_Hud = new HUD( m_Data );
        m_Hud->SetText( "Main Menu Font", "PAUSED" , TITLE_SIZE, ( m_Data->window.getSize().x / 2.0f ), m_Data->window.getSize().y / 5.0f );

        clock.restart().asSeconds();
        movedLeft = false;
        srand((unsigned)time(0));
    }

    void PauseState::InitKeyBinds()
    {
        std::fstream ifs ( PAUSE_STATE_KEY_BIND_FILEPATH );

        if ( ifs.is_open() )
        {
            std::string keyAction;
            std::string key;

            while( ifs >> keyAction >> key )
            {
                m_KeyBinds[keyAction] = m_Data->input.getSupportedKeys().at( key );
            }
        }

        Debug( "Key binds initialized for Paused State" )
    }

    void PauseState::Init()
    {
        Debug( "**Initialized** Pause State" )

        InitTextures();
        InitFonts();
        InitSounds();
        InitComponents();
        InitVariables();
        InitKeyBinds();
    }

    void PauseState::HandleInput( float dt )
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

            if ( m_Buttons["Back"]->isPressed() ||
                sf::Keyboard::isKeyPressed( sf::Keyboard::Key( m_KeyBinds["RESUME"] ) ) )
            {
                m_Data->machine.RemoveState();
            }

            if ( m_Buttons["Quit"]->isPressed() )
            {
                m_Data->machine.ClearStates();
                m_Data->machine.AddState( StateRef( new MainMenuState( m_Data ) ), true );
            }

        }
    }

    void PauseState::Update(float dt)
    {
        m_Data->input.UpdateMousePosition( m_Data->window );

        if ( !movedLeft && clock.getElapsedTime().asSeconds() > ( 2 + static_cast<int>( 4 * rand() / ( RAND_MAX + 1.f ) ) ) )
        {
            // std::string font = "H"
            m_Hud->Move( "Hack Font", -50.f, 0.f );
            movedLeft = true;
            clock.restart().asSeconds();
        }

        if ( movedLeft && clock.getElapsedTime().asSeconds() > ( 4 + static_cast<int>( 5.f * rand() / ( RAND_MAX + 1.f ) ) ) / 10.f )
        {
            // Debug( "Move back");
            // m_Hud->Move( "Main Menu Font", 50.f , 0.f );
            m_Hud->Reset();
            movedLeft = false;
            clock.restart().asSeconds();
        }

        // Update mouse position for buttons
        for ( auto button : m_Buttons )
        {
            button.second->Update(m_Data->input.GetViewMousePosition());
        }
    }

    void PauseState::Draw()
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
