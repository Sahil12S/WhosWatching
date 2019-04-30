#include "MainMenuState.h"
#include "GameState.h"
#include "GameSettingsState.h"
#include "EditorState.h"

MainMenuState::MainMenuState(GameDataRef data) : m_Data(std::move(data))
{
}

MainMenuState::~MainMenuState()
{
    delete m_Hud;
    for (const auto &button : m_Buttons)
    {
        delete button.second;
    }
}

void MainMenuState::InitTextures()
{
    // Use sprites for background
    m_Background.setSize(sf::Vector2f(m_Data->window.getSize()));
    m_Background.setFillColor(sf::Color(97, 143, 216));
}

void MainMenuState::InitFonts()
{
    m_Data->assets.LoadFont("Title Font", SCREEN_FONT_FILEPATH);
    m_Data->assets.LoadFont("Button Font", BUTTON_FONT_FILEPATH);
    m_Data->assets.LoadFont("Hack Font", SCREEN_FONT_FILEPATH2);
    // m_Data->assets.LoadFont( "Debug Font", DEBUG_FONT_FILEPATH );
}

void MainMenuState::InitSounds()
{
}

void MainMenuState::InitComponents()
{
    //Draw Buttons
    m_Buttons["Play"] = new gui::Button(m_Data);
    m_Buttons["Exit"] = new gui::Button(m_Data);
    m_Buttons["Settings"] = new gui::Button(m_Data);
    m_Buttons["Editor"] = new gui::Button(m_Data);

    // Set Button Properties
    m_Buttons["Exit"]->CreateButton(m_Data->GfxSettings.resolution.width / 2.0f - BUTTON_WIDTH / 2.0f,
                                    m_Data->GfxSettings.resolution.height - BUTTON_HEIGHT / 0.4f,
                                    BUTTON_WIDTH, BUTTON_HEIGHT);

    m_Buttons["Settings"]->CreateButton(m_Data->window.getSize().x / 2.0f - BUTTON_WIDTH / 2.0f,
                                        m_Buttons["Exit"]->GetButton().getPosition().y - BUTTON_HEIGHT / 0.8f,
                                        BUTTON_WIDTH, BUTTON_HEIGHT);

    m_Buttons["Editor"]->CreateButton(m_Data->GfxSettings.resolution.width / 2.0f - BUTTON_WIDTH / 2.0f,
                                    m_Buttons["Settings"]->GetButton().getPosition().y - BUTTON_HEIGHT / 0.8f,
                                    BUTTON_WIDTH, BUTTON_HEIGHT);

    m_Buttons["Play"]->CreateButton(m_Data->GfxSettings.resolution.width / 2.0f - BUTTON_WIDTH / 2.0f,
                                    m_Buttons["Editor"]->GetButton().getPosition().y - BUTTON_HEIGHT / 0.8f,
                                    BUTTON_WIDTH, BUTTON_HEIGHT);

    // Set Text and Button colors

    std::vector<sf::Color> textColor = {sf::Color(TEXT_IDLE_FILL_COLOR),
                                        sf::Color(TEXT_HOVER_FILL_COLOR),
                                        sf::Color(TEXT_ACTIVE_FILL_COLOR)};

    std::vector<sf::Color> buttonColor = {sf::Color(BUTTON_IDLE_FILL_COLOR),
                                          sf::Color(BUTTON_HOVER_FILL_COLOR),
                                          sf::Color(BUTTON_ACTIVE_FILL_COLOR)};

    m_Buttons["Exit"]->SetButtonProperties("Button Font", "Exit", BUTTON_TEXT_SIZE, textColor, buttonColor);
    m_Buttons["Settings"]->SetButtonProperties("Button Font", "Settings", BUTTON_TEXT_SIZE, textColor, buttonColor);
    m_Buttons["Editor"]->SetButtonProperties("Button Font", "Editor", BUTTON_TEXT_SIZE, textColor, buttonColor);
    m_Buttons["Play"]->SetButtonProperties("Button Font", "Play", BUTTON_TEXT_SIZE, textColor, buttonColor);
}

void MainMenuState::InitVariables()
{
    m_Hud = new gui::HUD( m_Data );
    m_Hud->SetText("Title Font", "WHO'S WATCHING??", TITLE_SIZE, ( m_Data->GfxSettings.resolution.width / 2.0f ), m_Data->GfxSettings.resolution.height / 6.0f );
    clock.restart().asSeconds();
    movedLeft = false;

    srand((unsigned)time(0));
}

// @override
void MainMenuState::Init()
{
    Debug("**Initialized** Main menu state");

    InitTextures();
    InitFonts();
    InitSounds();
    InitComponents();
    InitVariables();
    InitKeyBinds();
}

void MainMenuState::InitKeyBinds()
{
    std::fstream ifs(MAIN_MENU_KEY_BIND_FILEPATH);

    if (ifs.is_open())
    {
        std::string keyAction;
        std::string key;

        while (ifs >> keyAction >> key)
        {
            m_KeyBinds[keyAction] = m_Data->input.getSupportedKeys().at(key);
        }
    }
    Debug("Key bindings initialized for main menu");
}

// @override
void MainMenuState::HandleInput(float dt)
{
    sf::Event event;

    while (m_Data->window.pollEvent(event))
    {
        // Check for game close
        if (sf::Event::Closed == event.type || m_Buttons["Exit"]->isPressed() && m_Data->input.GetKeyTime() )
        {
            m_Data->machine.ClearStates();
            m_Data->machine.RemoveState();
            m_Data->window.close();
        }

        /*if ( m_Data->input.IsSpriteClicked( m_PlayButton, sf::Mouse::Left, m_Data->window ) )
            {
                m_Data->machine.AddState( StateRef ( new GameState( m_Data ) ), true );
            }
            if ( m_Data->input.IsSpriteClicked( m_SettingsButton, sf::Mouse::Left, m_Data->window ) )
            {
                m_Data->machine.AddState( StateRef ( new GameSettingsState( m_Data ) ), true );
            }*/
    }

    if (m_Buttons["Play"]->isPressed() && m_Data->input.GetKeyTime() )
    {
        m_Data->machine.AddState(StateRef(new GameState(m_Data)), true);
    }
    if (m_Buttons["Editor"]->isPressed() && m_Data->input.GetKeyTime() )
    {
        m_Data->machine.AddState(StateRef(new EditorState(m_Data)), true);
    }
    if (m_Buttons["Settings"]->isPressed() && m_Data->input.GetKeyTime() )
    {
        m_Data->machine.AddState(StateRef(new GameSettingsState(m_Data)), true);
    }
}

// @override
void MainMenuState::Update(float dt)
{
    m_Data->input.UpdateMousePosition(m_Data->window);
    m_Data->input.UpdateKeyTime( dt );

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
        // m_Hud->Move( "Title Font", 50.f , 0.f );
        m_Hud->Reset();
        movedLeft = false;
        clock.restart().asSeconds();
    }

    for (auto button : m_Buttons)
    {
        button.second->Update(m_Data->input.GetViewMousePosition());
    }
}

// @override
void MainMenuState::Draw()
{
    m_Data->window.clear();

    m_Data->window.draw(m_Background);
    /*m_Data->window.draw( m_PlayButton );
        m_Data->window.draw( m_ExitButton );
        m_Data->window.draw( m_SettingsButton );*/

    m_Hud->Draw(true);

    // m_Buttons["Settings"]->Draw();

    for (auto button : m_Buttons)
    {
        button.second->Draw();
    }

    /* Remove later */
    /*sf::Text mouseText;
        mouseText.setPosition( m_Data->input.GetViewMousePosition().x + 5, m_Data->input.GetViewMousePosition().y );
        mouseText.setFont( m_Data->assets.GetFont( "Debug Font" ) );
        mouseText.setCharacterSize( 20 );
        std::stringstream ss;
        ss << m_Data->input.GetViewMousePosition().x << ", " << m_Data->input.GetViewMousePosition().y;
        mouseText.setString( ss.str() );
        m_Data->window.draw( mouseText );*/

    m_Data->window.display();
}