#include "GameOverMenu.h"
#include "MainMenuState.h"

void GameOverMenu::InitTextures()
{
    // Set Background
    m_Background.setSize( sf::Vector2f( m_Data->GfxSettings.resolution.width, m_Data->GfxSettings.resolution.height ) );
    m_Background.setFillColor( sf::Color(5, 53, 130, 100) );

    m_Container.setSize( sf::Vector2f( m_Data->GfxSettings.resolution.width / 4.f, m_Data->GfxSettings.resolution.height ));
    m_Container.setFillColor( sf::Color(5, 53, 130, 200) );
    m_Container.setPosition( sf::Vector2f( m_Data->GfxSettings.resolution.width / 2.f - m_Container.getSize().x / 2.f,
                                    20.f ));
}

void GameOverMenu::InitFonts()
{
    m_Data->assets.LoadFont( "Title Font", SCREEN_FONT_FILEPATH );
    m_Data->assets.LoadFont( "Button Font", BUTTON_FONT_FILEPATH );
    m_Data->assets.LoadFont( "Hud Font", TEXT_FONT_FILEPATH );
}

void GameOverMenu::InitVariables()
{
    srand( time( NULL ) );
}

// Not a good way
void GameOverMenu::fix_newlines( std::string& s )
{
    size_t start_pos = 0;
    while((start_pos = s.find("\\n", start_pos)) != std::string::npos) {
         s.replace(start_pos, 2, "\n");
         start_pos += 1;
    }
    // std::cout << "=> " << s << '\n';
}

void GameOverMenu::InitMessages()
{
    std::ifstream in_file;
    in_file.open( MESSAGES_FILEATH );

    std::string line;

    while( std::getline( in_file, line ) )
    {
        fix_newlines( line );
        lossMessages.emplace_back( line );
    }

    in_file.close();

    // for( auto& it : lossMessages )
    // {
    //     std::cout << it << '\n';
    // }
}


void GameOverMenu::InitGui()
{
    m_Hud = new gui::HUD( m_Data );
    message = new gui::HUD( m_Data );

    m_Hud->SetText( "Title Font", "Game Over" ,
        TITLE_SIZE, ( m_Container.getPosition().x + m_Container.getSize().x / 2.f ),
        m_Data->window.getSize().y / 6.0f );
    
    
}

GameOverMenu::GameOverMenu(GameDataRef data) : m_Data( std::move( data ) )
{
    Debug( "Game Over Menu: Initializing...")
    InitTextures();
    InitFonts();
    InitVariables();
    InitMessages();
    InitGui();
}

GameOverMenu::~GameOverMenu()
{
    Debug( "[DEBUG] Destructor of Game Over Menu")
    delete m_Hud;
    delete message;
    for ( const auto& button : m_Buttons )
    {
        delete button.second;
    }
}

const bool GameOverMenu::IsButtonPressed( const std::string& key )
{
    return m_Buttons[key]->isPressed();
}

void GameOverMenu::AddButton( const std::string key, 
                const float y, 
                const std::string text)
{
    m_Buttons[key] = new gui::Button( m_Data );
    m_Buttons[key]->CreateButton(  m_Container.getPosition().x + m_Container.getSize().x / 2.f - BUTTON_WIDTH / 2.f,
                                y, BUTTON_WIDTH, BUTTON_HEIGHT );

    std::vector<sf::Color> textColor = { sf::Color( TEXT_IDLE_FILL_COLOR ),
                                        sf::Color( TEXT_HOVER_FILL_COLOR ),
                                        sf::Color( TEXT_ACTIVE_FILL_COLOR ) };

    std::vector<sf::Color> buttonColor = { sf::Color( BUTTON_IDLE_FILL_COLOR ),
                                        sf::Color( BUTTON_HOVER_FILL_COLOR ),
                                        sf::Color( BUTTON_ACTIVE_FILL_COLOR ) };
    
    m_Buttons[key]->SetButtonProperties( m_Data->assets.GetFont( "Button Font" ), text, BUTTON_TEXT_SIZE, textColor, buttonColor );
}

void GameOverMenu::SetMessage( bool win )
{
    std::string msg;
    if ( win )
    {
        msg = "Congrats!! You saved it.";
    }
    else
    {
        msg = lossMessages[ rand() % lossMessages.size() ];
    }
    message->SetText( "Hud Font",  msg,
        35.f, ( m_Container.getPosition().x + m_Container.getSize().x / 2.f ),
        m_Data->window.getSize().y / 3.0f );
}

void GameOverMenu::Update( const sf::Vector2i& mousePosWindow )
{
    // Update mouse position for buttons
    for ( auto& button : m_Buttons )
    {
        button.second->Update( sf::Vector2f( mousePosWindow ) );
    }
}

void GameOverMenu::Draw( sf::RenderTarget& target )
{

    target.draw( m_Background );
    target.draw( m_Container );
    m_Hud->Draw( target );
    // if( loose )
    message->Draw( target );

    for ( auto button : m_Buttons )
    {
        button.second->Draw( target );
    }

}