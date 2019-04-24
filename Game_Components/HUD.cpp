#include "HUD.h"

namespace SSEngine
{
    HUD::HUD(GameDataRef data ) : m_Data ( move ( data ) )
    {

    }

    void HUD::SetText(const std::string& fontName, const std::string& text, const float& size, const float& x, const float& y )
    {
        font = m_Data->assets.GetFont( fontName );
        m_Text.setFont( font );
        m_Text.setString( text );
        m_Text.setCharacterSize( size );
        m_Text.setFillColor( sf::Color::White );
        m_Text.setOrigin( m_Text.getGlobalBounds().width / 2,
                               m_Text.getGlobalBounds().height / 2 );
        // m_Text.setPosition( ( m_Data->window.getSize().x / 2.0f ), m_Data->window.getSize().y / 5.0f );
     
        m_Text.setPosition( x, y );
    }


    void HUD::Move( const std::string& font, const float& x, const float& y )
    {
        m_Text.setFont( m_Data->assets.GetFont( font ) );
        offset = sf::Vector2f( x, y );
        m_Text.move( offset );
    }
    
    void HUD::Reset()
    {
        m_Text.move( -offset );
        offset = sf::Vector2f( 0.f, 0.f );
    }

    void HUD::Draw( bool isTitle )
    {
        if ( isTitle )
        {
            m_Data->window.draw( m_Text );
        }
    }

    void HUD::UpdateText(std::string& text)
    {
        m_Text.setString( text );
    }
}
