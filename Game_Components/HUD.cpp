#include "HUD.h"

namespace gui
{

    HUD::HUD(GameDataRef data ) : m_Data ( move ( data ) )
    {
        text = "";
    }

    const std::string& HUD::GetText() const
    {
        return text;
    }


    void HUD::SetText(const std::string& fontName, const std::string& text, const float& size, const float& x, const float& y )
    {
        this->text = text;
        font = m_Data->assets.GetFont( fontName );
        m_Text.setFont( font );
        m_Text.setString( text );
        m_Text.setCharacterSize( size );
        m_Text.setFillColor( sf::Color::White );
        m_Text.setOrigin( m_Text.getGlobalBounds().width / 2,
                                m_Text.getGlobalBounds().height / 2 );
        // m_Text.setPosition( ( m_Data->window.getSize().x / 2.0f ), m_Data->window.getSize().y / 5.0f );
        
        offset = sf::Vector2f( x, y );
        m_Text.setPosition( x, y );
    }


    void HUD::Move( const std::string& font, const float& x, const float& y )
    {
        m_Text.setFont( m_Data->assets.GetFont( font ) );
        m_Text.move( x, y );
    }

    void HUD::Reset()
    {
        m_Text.setFont( font );
        m_Text.setPosition( offset );
        // offset = sf::Vector2f( 0.f, 0.f );
    }
    
    void HUD::UpdateText( const std::string text)
    {
        m_Text.setString( text );
    }

    void HUD::Draw( sf::RenderTarget& target )
    {
        target.draw( m_Text );
    }

}