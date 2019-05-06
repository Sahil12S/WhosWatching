#include "EditorState.h"

// Initializers
void EditorState::InitVariables()
{
    m_Paused = false;

    m_TextureRect = sf::IntRect( 0, 0, static_cast<int>( GRID_SIZE ), static_cast<int>( GRID_SIZE ) );

    m_Collision = false;
    m_Type = TileType::eDefault;
}

void EditorState::InitView()
{
    m_MainView.setSize( sf::Vector2f( m_Data->GfxSettings.resolution.width, m_Data->GfxSettings.resolution.height ) );
    m_MainView.setCenter( sf::Vector2f( 
        m_Data->GfxSettings.resolution.width / 2.f, 
        m_Data->GfxSettings.resolution.height / 2.f ) );
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
    m_PauseMenu->AddButton("Save", m_Data->GfxSettings.resolution.height / 1.4f , "Save");
    m_PauseMenu->AddButton("Load", m_Data->GfxSettings.resolution.height / 1.6f , "Load");
}

void EditorState::InitTileMap()
{
    m_TileMap = new TileMap( m_Data, 10, 10, TILES_TEXTURE_FILEPATH );
}

void EditorState::InitGui()
{   
    m_SideBar.setSize( sf::Vector2f( 80.f, static_cast<float>( m_Data->GfxSettings.resolution.height ) ) );
    m_SideBar.setFillColor( sf::Color( 50, 50, 50, 100) );
    m_SideBar.setOutlineColor( sf::Color( 200, 200, 200, 150 ) );
    m_SideBar.setOutlineThickness( 1.f );

    m_Hud = new gui::HUD(m_Data);
    m_Hud->SetText("Title Font", "Editor", TITLE_SIZE, ( m_Data->GfxSettings.resolution.width / 2.0f ), 
                        m_Data->GfxSettings.resolution.height / 6.0f );
    
    m_SelectorRect.setSize( sf::Vector2f (GRID_SIZE, GRID_SIZE) );
    m_SelectorRect.setFillColor( sf::Color(255, 255, 255, 150) );
    m_SelectorRect.setOutlineThickness( 1.f );
    m_SelectorRect.setOutlineColor( sf::Color::Green );
    m_SelectorRect.setTexture( &m_Data->assets.GetTexture( m_TileMap->GetTileSheet() ) );
    m_SelectorRect.setTextureRect( m_TextureRect );

    // Area of texture selector
    m_TS = new gui::TextureSelector( m_Data, 20.f, 20.f, 500.f, 400.f, m_TileMap->GetTileSheet() );

}

EditorState::EditorState( GameDataRef data ) : m_Data( std::move( data ) )
{
}

EditorState::~EditorState()
{
    Debug( "[DEBUG] Destructor of Editor state")
    delete m_Hud;
    delete m_PauseMenu;
    delete m_TileMap;
    delete m_TS;
}

void EditorState::Init()
{
    Debug("Editor State: Initializing...")
    InitVariables();
    InitView();
    InitTextures();
    InitFonts();
    InitSounds();
    InitKeyBinds();
    InitTexts();
    InitPauseMenu();
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

    if( sf::Keyboard::isKeyPressed(( sf::Keyboard::Key( m_KeyBinds["MOVE_CAMERA_UP"] ) ) ) )
    {
        m_MainView.move( 0.f, -CAMERA_SPEED * dt );
    }
    else if( sf::Keyboard::isKeyPressed(( sf::Keyboard::Key( m_KeyBinds["MOVE_CAMERA_DOWN"] ) ) ) )
    {
        m_MainView.move( 0.f, CAMERA_SPEED * dt );
    }
    else if( sf::Keyboard::isKeyPressed(( sf::Keyboard::Key( m_KeyBinds["MOVE_CAMERA_LEFT"] ) ) ) )
    {
        m_MainView.move( -CAMERA_SPEED * dt, 0.f );
    }
    else if( sf::Keyboard::isKeyPressed(( sf::Keyboard::Key( m_KeyBinds["MOVE_CAMERA_RIGHT"] ) ) ) )
    {
        m_MainView.move( CAMERA_SPEED * dt, 0.f );
    }

    if ( sf::Keyboard::isKeyPressed(( sf::Keyboard::Key( m_KeyBinds["QUIT"] ) ) ) && m_Data->input.GetKeyTime() )
    {
        m_Paused = !m_Paused;
    }

    if ( !m_Paused )
    {
        if ( sf::Keyboard::isKeyPressed(( sf::Keyboard::Key( m_KeyBinds["TOGGLE_COLLISION"] ) ) ) && m_Data->input.GetKeyTime() )
        {
            m_Collision = !m_Collision;
        }
        else if ( sf::Keyboard::isKeyPressed(( sf::Keyboard::Key( m_KeyBinds["INCREASE_TYPE"] ) ) ) && m_Data->input.GetKeyTime() )
        {
            ++m_Type;
        }
        else if ( sf::Keyboard::isKeyPressed(( sf::Keyboard::Key( m_KeyBinds["DECREASE_TYPE"] ) ) ) && m_Data->input.GetKeyTime() )
        {
            --m_Type;
        }

        // Add texture
        if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && m_Data->input.GetKeyTime() )
        {
            if ( !m_SideBar.getGlobalBounds().contains( sf::Vector2f( m_Data->input.GetWindowMousePosition() ) ) )
            {
                if ( !m_TS->GetActive() )
                {
                    m_TileMap->AddTile( m_Data->input.GetGridMousePosition().x, m_Data->input.GetGridMousePosition().y, 0, m_TextureRect, m_Collision, m_Type );
                }
                else
                {
                    m_TextureRect = m_TS->GetTextureRect();
                }
            }
        }
        // Remove texture
        else if ( sf::Mouse::isButtonPressed( sf::Mouse::Right ) && m_Data->input.GetKeyTime() )
        {
            if ( !m_SideBar.getGlobalBounds().contains( sf::Vector2f( m_Data->input.GetWindowMousePosition() ) ) )
            {
                if ( !m_TS->GetActive() )
                {
                    m_TileMap->RemoveTile( m_Data->input.GetGridMousePosition().x, m_Data->input.GetGridMousePosition().y, 0 );
                }
            }
        }
    }
}

void EditorState::UpdateGui( const float& dt )
{
    m_TS->Update( dt, m_Data->input.GetWindowMousePosition() );

    if ( !m_TS->GetActive() )
    {
        m_SelectorRect.setTextureRect( m_TextureRect );
        m_SelectorRect.setPosition( m_Data->input.GetGridMousePosition().x * GRID_SIZE, 
            m_Data->input.GetGridMousePosition().y * GRID_SIZE );

    }

    std::stringstream ss;
    ss << "View Pos: " << m_Data->input.GetViewMousePosition().x << ", " << m_Data->input.GetViewMousePosition().y << '\n' << 
        "Grid Pos: " << m_Data->input.GetGridMousePosition().x << ", " << m_Data->input.GetGridMousePosition().y << '\n' << 
        "TexRect: " << m_TextureRect.left << " " << m_TextureRect.top << '\n' << 
        "Collision: " << m_Collision << '\n' <<
        "Type: " << m_Type << '\n';
    m_CursorText.setString( ss.str() );
    m_CursorText.setPosition( m_Data->input.GetViewMousePosition().x + 20, m_Data->input.GetViewMousePosition().y );


}

void EditorState::UpdatePauseMenuButtons( )
{
    if ( m_PauseMenu->IsButtonPressed("Quit") && m_Data->input.GetKeyTime() )
    {
        m_Data->machine.AddState( StateRef ( new MainMenuState ( m_Data ) ), true );
    }

    if ( m_PauseMenu->IsButtonPressed("Save") && m_Data->input.GetKeyTime() )
    {
        m_TileMap->SaveToFile("myMap.txt");
    }

    if ( m_PauseMenu->IsButtonPressed("Load") && m_Data->input.GetKeyTime() )
    {
        m_TileMap->LoadFromFile("myMap.txt");
    }

}

void EditorState::Update( float dt )
{
    m_Data->input.UpdateMousePosition( m_Data->window, &m_MainView );
    m_Data->input.UpdateKeyTime( dt );

    if ( !m_Paused )
    {
        UpdateGui( dt );
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
    
    m_Data->window.setView( m_MainView );
    m_TileMap->Draw( m_Data->window );

    // Render GUI
    if ( !m_TS->GetActive() )
    {
        m_Data->window.draw( m_SelectorRect );
    }

    m_Data->window.setView( m_Data->window.getDefaultView() );
    m_TS->Draw( m_Data->window );
    m_Data->window.draw( m_SideBar );

    m_Data->window.setView( m_MainView );
    m_Data->window.draw( m_CursorText );

    // m_Data->window.setView( m_Data->window.getDefaultView() );
    
    if ( m_Paused )
    {   
        m_Data->window.setView( m_Data->window.getDefaultView() );
        m_PauseMenu->Draw( m_Data->window );
    }

    // for (auto button : m_Buttons)
    // {
    //     button.second->Draw();
    // }
    // Draw coordinates on mouse pointer for debugging
    

    m_Data->window.display();

}