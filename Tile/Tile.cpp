#include "Tile.h"

namespace SSEngine
{
Tile::Tile( GameDataRef data, float x, float y, float gridSizeF, const std::string& texture_name, const sf::IntRect& texture_rect ) :
    m_Data( std::move( data ) )
{
    m_Shape.setSize( sf::Vector2f( gridSizeF, gridSizeF ) );
    m_Shape.setFillColor( sf::Color::White );
    // m_Shape.setOutlineThickness( 1.f );
    // m_Shape.setOutlineColor( sf::Color::Black );
    m_Shape.setPosition( x * gridSizeF, y * gridSizeF );
    m_Shape.setTexture( &m_Data->assets.GetTexture( texture_name ));
    m_Shape.setTextureRect( texture_rect );
}

Tile::~Tile()
{

}

void Tile::Update()
{

}

void Tile::Draw()
{
    m_Data->window.draw( m_Shape );
}
}