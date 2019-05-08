#include "Callout.h"

void Callout::InitVariables()
{
    isQuestion = false;
}

void Callout::InitTexture()
{
    m_Background.setSize( sf::Vector2f( m_Data->GfxSettings.resolution.width, m_Data->GfxSettings.resolution.height ) );
    m_Background.setFillColor( sf::Color(5, 53, 130, 100) );
}

void Callout::InitButtons()
{
    // Create button
    std::vector<sf::Color> textColor = {
        sf::Color(TEXT_IDLE_FILL_COLOR),
        sf::Color(30, 114, 82, 250),
        sf::Color(TEXT_ACTIVE_FILL_COLOR)
    };

    std::vector<sf::Color> buttonColor = {
        sf::Color(BUTTON_IDLE_FILL_COLOR),
        sf::Color(BUTTON_HOVER_FILL_COLOR),
        sf::Color(BUTTON_ACTIVE_FILL_COLOR)
    };

    m_Buttons["Close"] = new gui::Button( m_Data );
    m_Buttons["True"] = new gui::Button( m_Data );
    m_Buttons["False"] = new gui::Button( m_Data );

    m_Buttons["Close"]->CreateButton(
        sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 50.f ,
        sprite.getGlobalBounds().top + 50,
        50.f, 50.f);

    m_Buttons["True"]->CreateButton(
        sprite.getGlobalBounds().left + 100.f ,
        sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 100.f,
        100.f, 50.f);
    m_Buttons["False"]->CreateButton(
        sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 200.f ,
        sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 100.f,
        100.f, 50.f);
    
    m_Buttons["Close"]->SetButtonProperties( font, "x", 35, textColor, buttonColor);
    m_Buttons["True"]->SetButtonProperties( font, "True", 35, textColor, buttonColor);
    m_Buttons["False"]->SetButtonProperties( font, "False", 35, textColor, buttonColor);
}

Callout::Callout( GameDataRef data, const std::string& font_name, const std::string& texture_file ) : m_Data( std::move( data ) )
{
    // create sprite
    sprite.setTexture( m_Data->assets.GetTexture( texture_file ) );

    sprite.setPosition(
        m_Data->GfxSettings.resolution.width / 2 - sprite.getGlobalBounds().width / 2.f,
        m_Data->GfxSettings.resolution.height / 10
    );

    font = m_Data->assets.GetFont( font_name );

    // Set font properties
    m_Text.setFont( font );
    m_Text.setFillColor( sf::Color::Black );
    m_Text.setCharacterSize( 35 );
    
    InitVariables();
    InitTexture();
    InitButtons();
}

Callout::~Callout()
{
    for ( auto it = m_Buttons.begin(); it != m_Buttons.end(); it++ )
    {
        delete it->second;
    }
}

bool Callout::IsButtonPressed( const std::string& key )
{
    return m_Buttons[key]->isPressed();
}


void Callout::Update( const sf::Vector2i& mousePosWindow, const std::string& text )
{
    m_Text.setString( text );

    m_Text.setPosition( 
        sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2.f - m_Text.getGlobalBounds().width / 2.f,
        sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2.f - m_Text.getGlobalBounds().height / 2.f
    );

    for ( auto& button : m_Buttons )
    {
        button.second->Update( sf::Vector2f( mousePosWindow ) );
    }
}

void Callout::Draw( sf::RenderTarget& target )
{
    target.draw( m_Background );
    target.draw( sprite );
    target.draw( m_Text );
    m_Buttons["Close"]->Draw( target );
    if( isQuestion )
    {
        m_Buttons["True"]->Draw( target );
        m_Buttons["False"]->Draw( target );
    }    
}