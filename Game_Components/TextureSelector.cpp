#include "TextureSelector.h"

namespace gui
{
    TextureSelector::TextureSelector( GameDataRef data, float x, float y, float width, float height, const std::string& texture_sheet ) :
        m_Data( std::move( data ) )
    {
        m_GridSize = GRID_SIZE;
        m_Active = false;
        
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

        m_Selector.setPosition( x, y );
        
        // Do we need to pass this value from parameter?
        m_Selector.setSize( sf::Vector2f ( m_GridSize, m_GridSize ) );
        m_Selector.setFillColor( sf::Color::Transparent );
        m_Selector.setOutlineThickness( 1.f );
        m_Selector.setOutlineColor( sf::Color::Red );

    }
    
    TextureSelector::~TextureSelector()
    {
        
    }

    const bool& TextureSelector::GetActive( ) const
    {
        return m_Active;
    }

    void TextureSelector::Update( const sf::Vector2i& mousePostion )
    {
        if( m_Bounds.getGlobalBounds().contains( static_cast<sf::Vector2f>( mousePostion ) ) )
        {
            m_Active = true;
        }
        else
        {
            m_Active = false;
        }
        

        if ( m_Active )
        {
            m_MousePosGrid.x = ( mousePostion.x - static_cast<int>( m_Bounds.getPosition().x ) ) / static_cast<unsigned>( GRID_SIZE );
            m_MousePosGrid.y = ( mousePostion.y - static_cast<int>( m_Bounds.getPosition().y ) ) / static_cast<unsigned>( GRID_SIZE );

            m_Selector.setPosition( 
                m_Bounds.getPosition().x + m_MousePosGrid.x * GRID_SIZE,
                m_Bounds.getPosition().y + m_MousePosGrid.y * GRID_SIZE
            );
        }
    }

    void TextureSelector::Draw()
    {
        m_Data->window.draw( m_Bounds );
        m_Data->window.draw( m_Sheet );
        m_Data->window.draw( m_Selector );
    }
}