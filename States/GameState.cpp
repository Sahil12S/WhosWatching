#include "GameState.h"
#include "MainMenuState.h"

void GameState::InitView()
{
    m_View.setSize( sf::Vector2f( m_Data->GfxSettings.resolution.width, m_Data->GfxSettings.resolution.height ) );
    m_View.setCenter(
        sf::Vector2f( 
            m_Data->GfxSettings.resolution.width / 2.f, 
            m_Data->GfxSettings.resolution.height / 2.f
        )
    );

    m_RenderSprite.setTexture( m_RenderTexture.getTexture() );
    m_RenderSprite.setTextureRect( 
        sf::IntRect(
            0,
            0,
            m_Data->GfxSettings.resolution.width,
            m_Data->GfxSettings.resolution.height
        )
    );
    
}

void GameState::InitVariables()
{
    m_Paused = false;
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

    Debug( "Game State: Initializing key bindings..." )
}

void GameState::InitPauseMenu()
{
    m_PauseMenu = new PauseMenu( m_Data );
    m_PauseMenu->AddButton("Quit", m_Data->GfxSettings.resolution.height / 1.2f , "Quit");
}

void GameState::InitComponents()
{
    // Nothing for now
}

void GameState::InitTileMap()
{
    m_Map = new TileMap( m_Data, 10, 10, TILES_TEXTURE_FILEPATH );
    m_Map->LoadFromFile("myMap.txt");
}

void GameState::InitPlayers()
{
    // Initialize player & spawn it
    m_Player = new Player( m_Data );
    m_Player->SetPosition(sf::Vector2f( m_Data->GfxSettings.resolution.width / 2.f, m_Data->GfxSettings.resolution.height / 2.f ) );
}

GameState::GameState( GameDataRef data ) : m_Data( std::move( data ) )
{
}

GameState::~GameState()
{
    Debug( "[DEBUG] Destructor of Game state")
    delete m_Player;
    delete m_Map;
    delete m_PauseMenu;
}
void GameState::Init()
{
    Debug( "Game State: Initializing..." )

    InitView();
    InitVariables();
    InitTextures();
    InitFonts();
    InitSounds();

    InitKeyBinds();
    InitPauseMenu();
    InitComponents();
    InitTileMap();
    InitPlayers();
}

void GameState::UpdateView( const float& dt )
{
    m_View.setCenter( m_Player->GetPosition() );

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

    }

    if ( sf::Keyboard::isKeyPressed(( sf::Keyboard::Key( m_KeyBinds["QUIT"] ) ) ) && 
                    m_Data->input.GetKeyTime() )
    {
        m_Paused = !m_Paused;
        // if ( !m_Paused )
        //     m_Paused = true;
        // else
        //     m_Paused = false;
    }

    /*
    * Handle movements
    */
    if ( !m_Paused )
    {
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

    }
    

    // Interact ( Use Space )

}

void GameState::UpdatePauseMenuButtons( )
{
    if ( m_PauseMenu->IsButtonPressed("Quit") && m_Data->input.GetKeyTime() )
    {
        m_Data->machine.AddState( StateRef ( new MainMenuState ( m_Data ) ), true );
    }
}

void GameState::Update(float dt)
{
    m_Data->input.UpdateMousePosition( m_Data->window, &m_View );
    m_Data->input.UpdateKeyTime( dt );

    if ( !m_Paused )
    {
        UpdateView( dt );
        m_Player->Update( dt );
    }
    else
    {
        this->m_PauseMenu->Update( m_Data->input.GetWindowMousePosition() );
		this->UpdatePauseMenuButtons();
    }
    
}

void GameState::Draw()
{
    m_Data->window.clear();
    // m_Data->window.draw( m_BackgroundSprite );
    
    m_RenderTexture.setView( m_View );
    m_Map->Draw();

    m_Player->Draw();

    if ( m_Paused )
    {
        m_RenderTexture.setView( m_RenderTexture.getDefaultView() );
        m_PauseMenu->Draw();
    }

    // Draw coordinates on mouse pointer for debugging
    // sf::Text mouseText;
    // mouseText.setPosition( m_Data->input.GetViewMousePosition().x + 5, m_Data->input.GetViewMousePosition().y );
    // mouseText.setFont( m_Data->assets.GetFont( "Debug Font" ) );
    // mouseText.setCharacterSize( 20 );
    // std::stringstream ss;
    // ss << m_Data->input.GetViewMousePosition().x << ", " << m_Data->input.GetViewMousePosition().y;
    // mouseText.setString( ss.str() );
    // m_Data->window.draw( mouseText );
    m_Data->window.draw( m_RenderSprite );
    m_Data->window.display();
}