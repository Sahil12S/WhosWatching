#include "TextureSelector.h"

namespace gui
{
    TextureSelector::TextureSelector( GameDataRef data, float x, float y, float width, float height, const std::string& texture_sheet ) :
        m_Data( std::move( data ) )
    {
        m_Bounds.setPosition( x, y );
        m_Bounds.setSize( sf::Vector2f( width, height ) );
        m_Bounds.setFillColor( sf::Color( 50, 50, 50, 100 ) );
        m_Bounds.setOutlineThickness( 1.f );
        m_Bounds.setOutlineColor( sf::Color( 255, 255, 255, 200 ) );

        m_Sheet.setTexture( m_Data->assets.GetTexture( texture_sheet ) );
        m_Sheet.setPosition( x, y );

        /*
         * Check if our bounds is well within available size of sheet
         * If it is, then set the texture
         */

        if ( m_Sheet.getGlobalBounds().width > m_Bounds.getGlobalBounds().width )
        {
            m_Sheet.setTextureRect( sf::IntRect( 0, 0, m_Bounds.getGlobalBounds().width, m_Sheet.getGlobalBounds().height ) );
        }

        if ( m_Sheet.getGlobalBounds().height > m_Bounds.getGlobalBounds().height )
        {
            m_Sheet.setTextureRect( sf::IntRect( 0, 0, m_Sheet.getGlobalBounds().width, m_Bounds.getGlobalBounds().height ) );
        }
    }
    
    TextureSelector::~TextureSelector()
    {
        
    }

    void TextureSelector::Update()
    {

    }

    void TextureSelector::Draw()
    {
        m_Data->window.draw( m_Bounds );
        m_Data->window.draw( m_Sheet );
    }
}