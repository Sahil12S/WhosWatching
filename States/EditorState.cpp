#include "EditorState.h"

// Initializers
void EditorState::InitVariables()
{
    m_Paused = false;

    m_textureRect = sf::IntRect( 0, 0, static_cast<int>( GRID_SIZE ), static_cast<int>( GRID_SIZE ) );
}

void EditorState::InitTextures()
{
    // m_Data->assets.LoadTexture( )
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

void EditorState::InitTexts()
{
    m_CursorText.setFont( m_Data->assets.GetFont( "Debug Font" ) );
    m_CursorText.setFillColor( sf::Color::White );
    m_CursorText.setCharacterSize( 20 );
    m_CursorText.setPosition( m_Data->input.GetViewMousePosition().x + 20, m_Data->input.GetViewMousePosition().y );
}

void EditorState::InitPauseMenu()
{
    m_PauseMenu = new PauseMenu( m_Data );
    m_PauseMenu->AddButton("Quit", m_Data->GfxSettings.resolution.height / 1.2f , "Quit");
}

void EditorState::InitButtons()
{
}

void EditorState::InitTileMap()
{
    m_TileMap = new TileMap( m_Data, 10, 10 );
}

void EditorState::InitGui()
{
    m_Hud = new gui::HUD(m_Data);
    m_Hud->SetText("Title Font", "Editor", TITLE_SIZE, ( m_Data->GfxSettings.resolution.width / 2.0f ), 
                        m_Data->GfxSettings.resolution.height / 6.0f );
    
    m_SelectorRect.setSize( sf::Vector2f (GRID_SIZE, GRID_SIZE) );
    m_SelectorRect.setFillColor( sf::Color(255, 255, 255, 150) );
    m_SelectorRect.setOutlineThickness( 1.f );
    m_SelectorRect.setOutlineColor( sf::Color::Green );
    m_SelectorRect.setTexture( &m_Data->assets.GetTexture( m_TileMap->GetTileSheet() ) );
    m_SelectorRect.setTextureRect( m_textureRect );

    m_TS = new gui::TextureSelector( m_Data, 20.f, 20.f, 500.f, 500.f, m_TileMap->GetTileSheet() );
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
    delete m_TS;
}

void EditorState::Init()
{
    Debug("Editor State: Initializing...")
    InitVariables();
    InitTextures();
    InitFonts();
    InitSounds();
    InitKeyBinds();
    InitTexts();
    InitPauseMenu();
    InitButtons();
    InitTileMap();
    InitGui();
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
        // Add texture
        if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && m_Data->input.GetKeyTime() )
        {
            m_TileMap->AddTile( m_Data->input.GetGridMousePosition().x, m_Data->input.GetGridMousePosition().y, 0, m_textureRect );
        }
        // Remove texture
        else if ( sf::Mouse::isButtonPressed( sf::Mouse::Right ) && m_Data->input.GetKeyTime() )
        {
            m_TileMap->RemoveTile( m_Data->input.GetGridMousePosition().x, m_Data->input.GetGridMousePosition().y, 0 );
        }

        // Change texture
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && m_Data->input.GetKeyTime() )
        {
            if ( m_textureRect.left < 400 )
            {
                m_textureRect.left += 100;
            }
        }
    }
}

void EditorState::UpdateButtons()
{
    for (auto button : m_Buttons)
    {
        button.second->Update(m_Data->input.GetViewMousePosition());
    }
}

void EditorState::UpdateGui()
{
    m_SelectorRect.setTextureRect( m_textureRect );
    m_SelectorRect.setPosition( m_Data->input.GetGridMousePosition().x * GRID_SIZE, 
        m_Data->input.GetGridMousePosition().y * GRID_SIZE );

    std::stringstream ss;
    ss << m_Data->input.GetViewMousePosition().x << ", " << m_Data->input.GetViewMousePosition().y << '\n' << 
        m_Data->input.GetGridMousePosition().x << ", " << m_Data->input.GetGridMousePosition().y << '\n' << 
        m_textureRect.left << " " << m_textureRect.top;
    m_CursorText.setString( ss.str() );
    m_CursorText.setPosition( m_Data->input.GetViewMousePosition().x + 20, m_Data->input.GetViewMousePosition().y );

    m_TS->Update( m_Data->input.GetWindowMousePosition() );

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
        UpdateButtons();
        UpdateGui();
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

    // Render GUI
    m_Data->window.draw( m_SelectorRect );
    m_TS->Draw();
    m_Data->window.draw( m_CursorText );
    
    if ( m_Paused )
    {
        m_PauseMenu->Draw();
    }

    // for (auto button : m_Buttons)
    // {
    //     button.second->Draw();
    // }
    // Draw coordinates on mouse pointer for debugging
    

    m_Data->window.display();

}