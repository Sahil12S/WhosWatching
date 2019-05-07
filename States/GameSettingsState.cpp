#include "GameSettingsState.h"
#include "MainMenuState.h"

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
    m_Data->assets.LoadFont( "Title Font", SCREEN_FONT_FILEPATH );
    m_Data->assets.LoadFont( "Hack Font", SCREEN_FONT_FILEPATH2 );
    m_Data->assets.LoadFont( "Button Font", BUTTON_FONT_FILEPATH );
    m_Data->assets.LoadFont( "DDList Font", LIST_FONT_FILEPATH );
    m_Data->assets.LoadFont( "Text Font", TEXT_FONT_FILEPATH );
    m_Data->assets.LoadFont( "Debug Font", DEBUG_FONT_FILEPATH );
}

void GameSettingsState::InitSounds()
{
    // Empty for now
}

void GameSettingsState::InitVariables()
{
    Debug( "Settings State: Initializing variables...")

    // Initialize HUD
    m_Hud = new gui::HUD( m_Data );
    m_Hud->SetText( "Title Font", "SETTINGS" , TITLE_SIZE, ( m_Data->window.getSize().x / 2.0f ), m_Data->window.getSize().y / 5.0f );
    
    m_Modes = sf::VideoMode::getFullscreenModes();

    clock.restart().asSeconds();
    movedLeft = false;
    srand((unsigned)time(0));
}

/*
* Initialize Buttons and Dropdown list
*/
void GameSettingsState::InitComponents()
{
    Debug( "Settings State: Initializing components...")

    // Set Buttons
    m_Buttons["Home"] = new gui::Button( m_Data );
    m_Buttons["Apply"] = new gui::Button( m_Data );
    m_Buttons["Back"] = new gui::Button( m_Data );

    m_Buttons["Back"]->CreateButton( 25.f, 25.f, BUTTON_WIDTH, BUTTON_HEIGHT );
    m_Buttons["Apply"]->CreateButton( 2.f * m_Data->window.getSize().x / 3.f - BUTTON_WIDTH / 2.f,
                                            m_Data->window.getSize().y - BUTTON_HEIGHT / 0.4f,
                                            BUTTON_WIDTH, BUTTON_HEIGHT );
    m_Buttons["Home"]->CreateButton(  m_Data->window.getSize().x / 3.f - BUTTON_WIDTH / 2.f,
                                            m_Data->window.getSize().y - BUTTON_HEIGHT / 0.4f,
                                            BUTTON_WIDTH, BUTTON_HEIGHT );

    std::vector<sf::Color> textColor = { sf::Color( TEXT_IDLE_FILL_COLOR ),
                                            sf::Color( TEXT_HOVER_FILL_COLOR ),
                                            sf::Color( TEXT_ACTIVE_FILL_COLOR ) };

    std::vector<sf::Color> buttonColor = { sf::Color( BUTTON_IDLE_FILL_COLOR ),
                                            sf::Color( BUTTON_HOVER_FILL_COLOR ),
                                            sf::Color( BUTTON_ACTIVE_FILL_COLOR ) };


    m_Buttons["Back"]->SetButtonProperties( "Button Font", "Back", BUTTON_TEXT_SIZE, textColor, buttonColor );
    m_Buttons["Apply"]->SetButtonProperties( "Button Font", "Apply", BUTTON_TEXT_SIZE, textColor, buttonColor );
    m_Buttons["Home"]->SetButtonProperties( "Button Font", "Home", BUTTON_TEXT_SIZE, textColor, buttonColor );

    // std::string list[] = { "abc", "def", "fgh", "ijk", "lmn" };
    std::string list[] = { "1920 x 1080", "1280 x 720", "800 x 600", "640 x 480" };
    std::vector< std::string > modes_str;
    for ( auto& mode : m_Modes )
    {
        modes_str.emplace_back( std::to_string( mode.width ) + " x " + std::to_string( mode.height ) );
    }

    m_DropdownList["Resolution"] = new gui::DropDownList( m_Data, "DDList Font",  m_Data->window.getSize().x / 2.f - LIST_WIDTH / 2.f, 400.f, modes_str.data(), modes_str.size() );
}

void GameSettingsState::InitTexts()
{
    m_OptionsText.setFont( m_Data->assets.GetFont( "Text Font" ) );
    m_OptionsText.setCharacterSize( 30 );
    m_OptionsText.setPosition( 500.f, 400.f );
    m_OptionsText.setFillColor( sf::Color( 255, 255, 255, 200 ) );
    m_OptionsText.setString( 
        "Resoultion\n\nFullscreen\n\nVsync\n\nAnti-Aliasing"
    );
}

GameSettingsState::GameSettingsState( GameDataRef data) : m_Data ( move( data ) )
{}

GameSettingsState::~GameSettingsState()
{
    Debug( "[DEBUG] Destructor of Game Settings state")
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
    InitTexts();
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

        
    }

    // Go back to Main Menu on Button click or Escape
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( m_KeyBinds["QUIT"] ) ) ||
            m_Buttons["Home"]->isPressed() )
    {
        // If there are more than 1 state in stack, remove all but active one
        m_Data->machine.ClearStates();
        m_Data->machine.AddState( StateRef ( new MainMenuState ( m_Data ) ), true );
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

    if ( m_Buttons["Apply"]->isPressed() )
    {
        // TODO: for test, remove later
        m_Data->GfxSettings.resolution = m_Modes[ m_DropdownList["Resolution"]->getActiveElementId() ];
        m_Data->window.create( m_Data->GfxSettings.resolution, m_Data->GfxSettings.title, sf::Style::Default );
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
    
    // Handle title animation
    if ( !movedLeft && clock.getElapsedTime().asSeconds() > ( 2 + static_cast<int>( 4 * rand() / ( RAND_MAX + 1.f ) ) ) )
    {
        m_Hud->Move( "Hack Font", -50.f, 0.f );
        movedLeft = true;
        clock.restart().asSeconds();
    }

    if ( movedLeft && clock.getElapsedTime().asSeconds() > ( 4 + static_cast<int>( 5.f * rand() / ( RAND_MAX + 1.f ) ) ) / 10.f )
    {
        m_Hud->Reset();
        movedLeft = false;
        clock.restart().asSeconds();
    }

    UpdateComponents( dt );

}

void GameSettingsState::Draw()
{
    m_Data->window.clear();

    m_Data->window.draw( m_Background );

    m_Hud->Draw( m_Data->window );

    for ( auto button : m_Buttons )
    {
        button.second->Draw( m_Data->window );
    }
    
    for ( auto dl : m_DropdownList )
    {
        dl.second->Draw( m_Data->window );
    }

    m_Data->window.draw( m_OptionsText );

    // Draw coordinates on mouse pointer for debugging
    sf::Text mouseText;
    mouseText.setPosition( m_Data->input.GetViewMousePosition().x + 20, m_Data->input.GetViewMousePosition().y );
    mouseText.setFont( m_Data->assets.GetFont( "Debug Font" ) );
    mouseText.setCharacterSize( 20 );
    std::stringstream ss;
    ss << m_Data->input.GetViewMousePosition().x << ", " << m_Data->input.GetViewMousePosition().y;
    mouseText.setString( ss.str() );
    m_Data->window.draw( mouseText );

    m_Data->window.display();
}