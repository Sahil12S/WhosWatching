#include "EditorState.h"

namespace SSEngine
{
// Initializers
void EditorState::InitTextures()
{
    // Use sprites for background
    // m_Background.setSize(sf::Vector2f(m_Data->window.getSize()));
    // m_Background.setFillColor(sf::Color(97, 143, 216));
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

    m_TileMap = new TileMap( m_Data, 10, 10 );

    m_Paused = false;
}

void EditorState::InitComponents()
{
    m_SelectorRect.setSize( sf::Vector2f (GRID_SIZE, GRID_SIZE) );
    m_SelectorRect.setFillColor( sf::Color::Transparent );
    m_SelectorRect.setOutlineThickness( 1.f );
    m_SelectorRect.setOutlineColor( sf::Color::Green );

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
    delete m_TileMap;
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
    if ( !m_Paused )
    {
        if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && m_Data->input.GetKeyTime() )
        {
            m_TileMap->AddTile( m_Data->input.GetGridMousePosition().x, m_Data->input.GetGridMousePosition().y, 0 );
        }
        else if ( sf::Mouse::isButtonPressed( sf::Mouse::Right ) && m_Data->input.GetKeyTime() )
        {
            m_TileMap->RemoveTile( m_Data->input.GetGridMousePosition().x, m_Data->input.GetGridMousePosition().y, 0 );
        }

    }
}

void EditorState::UpdateComponents( const float& dt )
{
    m_SelectorRect.setPosition( m_Data->input.GetGridMousePosition().x * GRID_SIZE, 
        m_Data->input.GetGridMousePosition().y * GRID_SIZE );

    for (auto button : m_Buttons)
    {
        button.second->Update(m_Data->input.GetViewMousePosition());
    }

}

void EditorState::UpdateButtons()
{

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
    m_Data->input.UpdateMousePosition( m_Data->window );
    m_Data->input.UpdateKeyTime( dt );

    if ( !m_Paused )
    {
        UpdateComponents( dt );
        UpdateButtons();
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
    // m_Data->window.draw(m_Background);

    m_TileMap->Draw();

    if ( !m_Paused )
    {
        // m_Hud->Draw(true);   
        m_Data->window.draw( m_SelectorRect );
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