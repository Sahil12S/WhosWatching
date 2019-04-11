#include "HUD.h"

namespace SSEngine
{
    HUD::HUD(GameDataRef data ) : m_Data ( move ( data ) )
    {

    }

    void HUD::SetTitle(const std::string& fontName, const std::string& text)
    {
        m_Title.setFont( m_Data->assets.GetFont( fontName ) );
        m_Title.setString( text );
        m_Title.setCharacterSize( 128 );
        m_Title.setFillColor( sf::Color::White );
        m_Title.setOrigin( m_Title.getGlobalBounds().width / 2,
                               m_Title.getGlobalBounds().height / 2 );
        m_Title.setPosition( ( m_Data->window.getSize().x / 2.0f ), m_Data->window.getSize().y / 5.0f );
    }

    void HUD::Draw( bool isTitle )
    {
        if ( isTitle )
        {
            m_Data->window.draw( m_Title );
        }
    }

    void HUD::UpdateText(std::string& text)
    {
        m_Text.setString( text );
    }
}
