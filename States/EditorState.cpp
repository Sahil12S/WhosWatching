#include "EditorState.h"

namespace SSEngine
{
// Initializers
void EditorState::InitTextures()
{
    // Use sprites for background
    m_Background.setSize(sf::Vector2f(m_Data->window.getSize()));
    m_Background.setFillColor(sf::Color(97, 143, 216));
}

void EditorState::InitFonts()
{
    m_Data->assets.LoadFont("Title Font", SCREEN_FONT_FILEPATH);
    m_Data->assets.LoadFont("Hack Font", SCREEN_FONT_FILEPATH2);
    m_Data->assets.LoadFont("Button Font", BUTTON_FONT_FILEPATH);
    m_Data->assets.LoadFont("Debug Font", DEBUG_FONT_FILEPATH);
}

void EditorState::InitSounds()
{

}

void EditorState::InitKeyBinds()
{
    Debug( "Editor State: Initializing key bindings..." )

    // Read Key Bindings from file
    std::ifstream ifs ( EDITOR_STATE_KEY_BIND_FILEPATH );

    if ( ifs.is_open() )
    {
        std::string keyAction;
        std::string key;
        while ( ifs >> keyAction >> key )
        {
            std::cout << keyAction << key << std::endl;
            m_KeyBinds[keyAction] = m_Data->input.getSupportedKeys().at( key );
        }
    }

    ifs.close();

}

void EditorState::InitVariables()
{
    m_Hud = new HUD(m_Data);
    m_Hud->SetText("Title Font", "Editor", TITLE_SIZE, ( m_Data->GfxSettings.resolution.width / 2.0f ), 
                        m_Data->GfxSettings.resolution.height / 6.0f );

    m_Map = new TileMap( m_Data );

    m_Paused = false;
}

void EditorState::InitComponents()
{
    // m_Buttons["Cancel"] = new Button(m_Data);
    // m_Buttons["Cancel"]->CreateButton(m_Data->window.getSize().x / 13.f - BUTTON_WIDTH / 2.f,
    //                                         m_Data->window.getSize().y / 15.f - BUTTON_HEIGHT / 2.f,
    //                                         BUTTON_WIDTH, BUTTON_HEIGHT);

    // std::vector<sf::Color> textColor = {sf::Color(TEXT_IDLE_FILL_COLOR),
    //                                     sf::Color(TEXT_HOVER_FILL_COLOR),
    //                                     sf::Color(TEXT_ACTIVE_FILL_COLOR)};

    // std::vector<sf::Color> buttonColor = {sf::Color(BUTTON_IDLE_FILL_COLOR),
    //                                       sf::Color(BUTTON_HOVER_FILL_COLOR),
    //                                       sf::Color(BUTTON_ACTIVE_FILL_COLOR)};

    // m_Buttons["Cancel"]->SetButtonProperties("Button Font", "Cancel", BUTTON_TEXT_SIZE, textColor, buttonColor);

}



void EditorState::InitTexts()
{

}

void EditorState::InitPauseMenu()
{
    m_PauseMenu = new PauseMenu( m_Data );
    m_PauseMenu->AddButton("Quit", m_Data->GfxSettings.resolution.height / 1.2f , "Quit");
}

EditorState::EditorState( GameDataRef data ) : m_Data( std::move( data ) )
{

}

EditorState::~EditorState()
{
    delete m_Hud;
    for (const auto &button : m_Buttons)
    {
        delete button.second;
    }
    delete m_PauseMenu;
}

void EditorState::Init()
{
    Debug("Editor State: Initializing...")
    InitTextures();
    InitFonts();
    InitSounds();
    InitKeyBinds();
    InitVariables();
    InitComponents();
    InitTexts();
    InitPauseMenu();

}

void EditorState::HandleInput( float dt )
{
    sf::Event event;

    while (m_Data->window.pollEvent(event))
    {
        // Check for game close
        if (sf::Event::Closed == event.type )
        {
            m_Data->machine.ClearStates();
            m_Data->machine.RemoveState();
            m_Data->window.close();
        }
    }

    if ( sf::Keyboard::isKeyPressed(( sf::Keyboard::Key( m_KeyBinds["QUIT"] ) ) ) && 
                    m_Data->input.GetKeyTime() )
    {
        Debug( "Editor State: Game Paused" )
        if ( !m_Paused )
            m_Paused = true;
        else
            m_Paused = false;
    }
    // if (m_Buttons["Cancel"]->isPressed())
    // {
    //     m_Data->machine.AddState(StateRef(new MainMenuState(m_Data)), true);
    // }

}

void EditorState::UpdateComponents( const float& dt )
{
    for (auto button : m_Buttons)
    {
        button.second->Update(m_Data->input.GetViewMousePosition());
    }

}

void EditorState::UpdatePauseMenuButtons( )
{
    if ( m_PauseMenu->IsButtonPressed("Quit") && m_Data->input.GetKeyTime() )
    {
        m_Data->machine.AddState( StateRef ( new MainMenuState ( m_Data ) ), true );
    }
}

void EditorState::Update( float dt )
{
    m_Data->input.UpdateMousePosition(m_Data->window);
    m_Data->input.UpdateKeyTime( dt );

    if ( !m_Paused )
    {
        UpdateComponents( dt );
    }
    else
    {
        this->m_PauseMenu->Update( m_Data->input.GetWindowMousePosition() );
		this->UpdatePauseMenuButtons();
    }
}

void EditorState::Draw()
{
    m_Data->window.clear();
    m_Data->window.draw(m_Background);

    m_Map->Draw();

    if ( !m_Paused )
    {
        m_Hud->Draw(true);
    }
    else
    {
        m_PauseMenu->Draw();
    }
    

    // for (auto button : m_Buttons)
    // {
    //     button.second->Draw();
    // }
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
}