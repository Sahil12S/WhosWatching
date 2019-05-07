#include "Callout.h"

Callout::Callout( GameDataRef data, const std::string& font_name, const std::string& texture_file ) : m_Data( std::move( data ) )
{
    m_Background.setSize( sf::Vector2f( m_Data->GfxSettings.resolution.width, m_Data->GfxSettings.resolution.height ) );
    m_Background.setFillColor( sf::Color(5, 53, 130, 100) );

    // create sprite
    sprite.setTexture( m_Data->assets.GetTexture( texture_file ) );

    sprite.setPosition(
        m_Data->GfxSettings.resolution.width / 2 - sprite.getGlobalBounds().width / 2.f,
        m_Data->GfxSettings.resolution.height / 10
    );
    // std::cout << "check: " << sprite.getGlobalBounds().left << std::endl;

    font = m_Data->assets.GetFont( font_name );

    // Set font properties
    m_Text.setFont( font );
    m_Text.setFillColor( sf::Color::Black );
    m_Text.setCharacterSize( 35 );
    

    // Create button
    m_Buttons["close"] = new gui::Button( data );
    m_Buttons["close"]->CreateButton(
        sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 50.f ,
        sprite.getGlobalBounds().top + 50,
        50.f, 50.f);
    
    std::vector<sf::Color> textColor = {
        sf::Color(TEXT_IDLE_FILL_COLOR),
        sf::Color(TEXT_HOVER_FILL_COLOR),
        sf::Color(TEXT_ACTIVE_FILL_COLOR)
    };

    std::vector<sf::Color> buttonColor = {
        sf::Color(BUTTON_IDLE_FILL_COLOR),
        sf::Color(BUTTON_HOVER_FILL_COLOR),
        sf::Color(BUTTON_ACTIVE_FILL_COLOR)
    };
    m_Buttons["close"]->SetButtonProperties( font, "x", BUTTON_TEXT_SIZE, textColor, buttonColor);
}

Callout::~Callout()
{
    for ( auto it = m_Buttons.begin(); it != m_Buttons.end(); it++ )
    {
        delete it->second;
    }
}

void Callout::Update()
{

}

void Callout::Draw( sf::RenderTarget& target, const std::string& text )
{

    m_Text.setString( text );

    m_Text.setPosition( 
        sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2.f - m_Text.getGlobalBounds().width / 2.f,
        sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2.f - m_Text.getGlobalBounds().height / 2.f
    );

    target.draw( m_Background );
    target.draw( sprite );
    target.draw( m_Text );
    m_Buttons["close"]->Draw( target );
}