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
    isCallout = true;
    question = false;
    calloutMessage = "Today's world has gone rouge!!\nEveryone's personal items are at risk,\nnothing is safe. Hurry up!!\nSecure your accounts before time runs out.";
    answer = false;
    maxScore = 5;
    
}

void GameState::InitTextures()
{
    m_Data->assets.LoadTexture( "callout", CALLOUT_TEXTURE_FILEPATH );
}

void GameState::InitFonts()
{
    m_Data->assets.LoadFont( "Debug Font", DEBUG_FONT_FILEPATH );
    m_Data->assets.LoadFont( "Hud Font", TEXT_FONT_FILEPATH );
    m_Data->assets.LoadFont("Button Font", BUTTON_FONT_FILEPATH);
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
    hud["timer"] = new gui::HUD( m_Data );
    hud["timer"]->SetText("Hud Font", "Remaining Time: 0", 30, m_Data->GfxSettings.resolution.width / 6, m_Data->GfxSettings.resolution.height / 25 );
    hud["score"] = new gui::HUD( m_Data );
    hud["score"]->SetText("Hud Font", "Score: 0", 30, m_Data->GfxSettings.resolution.width / 1.2, m_Data->GfxSettings.resolution.height / 25 );
}

void GameState::InitTileMap()
{
    // m_Map = new TileMap( m_Data, "myMap.txt" );
    m_TileMap = new TileMap( m_Data, 15, 15, TILES_TEXTURE_FILEPATH );
    m_TileMap->LoadFromFile("myMap.txt");
}

void GameState::InitPlayers()
{
    // Initialize player & spawn it
    m_Player = new Player( m_Data );
    // m_Player->SetPosition( m_Data->GfxSettings.resolution.width / 2.f, m_Data->GfxSettings.resolution.height / 2.f );
    m_Player->SetPosition( 50.f, 300.f );
}

void GameState::InitCallout()
{
    m_Callout = new Callout( m_Data, "Hud Font",  "callout" );
}

void GameState::InitQuestions()
{
    std::ifstream in_file;
    in_file.open("../Resources/questions/questions.txt");
    std::string line;

    int i = 0;

    while( std::getline( in_file, line ) )
    {
        questionMap[i].first = line;
        std::getline( in_file, line );
        questionMap[i].second = stoi( line );
        i++;
    }

    in_file.close();
}

GameState::GameState( GameDataRef data ) : m_Data( std::move( data ) )
{
}

GameState::~GameState()
{
    Debug( "[DEBUG] Destructor of Game state")
    delete m_Player;
    delete m_TileMap;
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
    InitCallout();
    InitQuestions();

    m_CursorText.setFont( m_Data->assets.GetFont( "Debug Font" ) );
    m_CursorText.setFillColor( sf::Color::White );
    m_CursorText.setCharacterSize( 20 );
    m_CursorText.setPosition( m_Data->input.GetViewMousePosition().x + 20, m_Data->input.GetViewMousePosition().y );
}

void GameState::UpdateView( const float& dt )
{
    // To control large number of decimals, we floor it down
    m_View.setCenter( 
        std::floor( m_Player->GetPosition().x ),
        std::floor( m_Player->GetPosition().y ) 
    );

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
        if( isCallout )
        {
            isCallout = false;
            question = false;
        }
        else
        {
            m_Paused = !m_Paused;
        }
        
    }

    /*
    * Handle movements
    */
    if ( !m_Paused )
    {
        if( !isCallout )
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
        }
        // Attack ( Enter )
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( m_KeyBinds["ATTACK"] ) ) && m_Data->input.GetKeyTime() )
        {

            // std::cout <<"Attack pressed" << '\n';
            if( m_TileMap->TileInteractive( m_Player ) && !isCallout )
            {
                if( questionMap.size() > 0 )
                {
                    calloutMessage = questionMap.begin()->second.first;
                    answer = questionMap.begin()->second.second;
                    question = true;
                }
                else
                {
                    question = false;
                    calloutMessage = "";
                    answer = false;
                }
                // Open a callout box
                
                isCallout = true;
            }
        }

    }
}

void GameState::UpdateTileMap( const float& dt )
{
    m_TileMap->Update();
    m_TileMap->UpdateCollision( m_Player, dt );
}

void GameState::UpdatePauseMenuButtons( )
{
    if ( m_PauseMenu->IsButtonPressed("Quit") && m_Data->input.GetKeyTime() )
    {
        m_Data->machine.AddState( StateRef ( new MainMenuState ( m_Data ) ), true );
    }
}

void GameState::UpdateCalloutButtons( const float& dt )
{
    if( m_Callout->IsButtonPressed("Close") && m_Data->input.GetKeyTime() )
    {
        isCallout = false;
    }
    
    if( question )
    {
        if ( m_Callout->IsButtonPressed("True") && m_Data->input.GetKeyTime() )
        {
            if( answer )
            {
                m_Player->WinPoints();
            }
            
            if( !questionMap.empty() )
            {
                questionMap.erase( questionMap.begin() );
            }
            isCallout = false;
            question = false;
            m_TileMap->Hide( m_Player );
        }
        else if ( m_Callout->IsButtonPressed("False") && m_Data->input.GetKeyTime() )
        {
            if( !answer )
            {
                m_Player->WinPoints();
            }
            if( !questionMap.empty() )
            {
                questionMap.erase( questionMap.begin() );
            }
            question = false;
            isCallout = false;
            m_TileMap->Hide( m_Player );
        }
    }

    if( m_Player->GetScore() >= maxScore )
    {
        // Get to game over state
        calloutMessage = "You succeeded in securing your account";
        // isCallout = true;
        // question = false;
        std::cout << calloutMessage << '\n';
        m_Paused = true;
    }
}

void GameState::UpdateGui()
{
    std::stringstream ss;
    ss << "View Pos: " << m_Data->input.GetViewMousePosition().x << ", " << m_Data->input.GetViewMousePosition().y << '\n' << 
        "Grid Pos: " << m_Data->input.GetGridMousePosition().x << ", " << m_Data->input.GetGridMousePosition().y << '\n';
    m_CursorText.setString( ss.str() );
    m_CursorText.setPosition( m_Data->input.GetViewMousePosition().x + 20, m_Data->input.GetViewMousePosition().y );
}

void GameState::Update(float dt)
{
    m_Data->input.UpdateMousePosition( m_Data->window, &m_View );
    m_Data->input.UpdateKeyTime( dt );
    
    UpdateGui();

    if ( !m_Paused )
    {
        if( !isCallout )
        {
            UpdateView( dt );
            UpdateTileMap( dt );
            m_Player->Update( dt );
        }
        else
        {
            m_Callout->Update( m_Data->input.GetWindowMousePosition(), calloutMessage );
            UpdateCalloutButtons( dt );
        }
        

        int rem_time = static_cast<int>( m_Player->GetRemainingTime() );
        if( rem_time <= 0 )
        {
            m_Paused = true;
        }
        hud["timer"]->UpdateText( "Remaining Time: " + std::to_string( rem_time ) );
        hud["score"]->UpdateText( "Score: " + std::to_string( m_Player->GetScore() ) );
    }
    else
    {
        this->m_PauseMenu->Update( m_Data->input.GetWindowMousePosition() );
		this->UpdatePauseMenuButtons();
    }
    
}

void GameState::Draw()
{
    // TODO: WORK WITH RENDER TEXTURE TO DISPLAY ALL AT ONCE
    m_Data->window.clear();

    m_Data->window.setView( m_View );
    m_TileMap->Draw( m_Data->window, m_Player->GetGridPosition( static_cast<int>( GRID_SIZE ) ) );

    m_Player->Draw( m_Data->window );
    m_TileMap->RenderDeferred( m_Data->window );

    m_Data->window.draw( m_CursorText );
    
    m_Data->window.setView( m_Data->window.getDefaultView() );
    hud["timer"]->Draw( m_Data->window );
    hud["score"]->Draw( m_Data->window );

    if( isCallout )
    {
        m_Callout->Draw( m_Data->window, question );
    }

    if ( m_Paused )
    {
        // m_Data->window.setView( m_Data->window.getDefaultView() );
        m_PauseMenu->Draw( m_Data->window );
    }

    m_Data->window.setView( m_View );
    m_Data->window.draw( m_CursorText );
    

    m_Data->window.display();

    /*
    m_RenderTexture.clear();
    m_RenderTexture.setView( m_View );
    m_Map->Draw( m_RenderTexture );

    m_Player->Draw( m_RenderTexture );

    if ( m_Paused )
    {
        m_RenderTexture.setView( m_RenderTexture.getDefaultView() );
        m_PauseMenu->Draw( m_RenderTexture );
    } 
    m_RenderTexture.display();

    m_Data->window.clear();
    m_RenderSprite.setTexture( m_RenderTexture.getTexture() );
    m_Data->window.draw( m_RenderSprite );
    m_Data->window.display();
    */
}