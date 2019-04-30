#include "Tile.h"

namespace SSEngine
{
Tile::Tile( GameDataRef data, float x, float y, float gridSizeF ) : m_Data( std::move( data ) )
{
    m_Shape.setSize( sf::Vector2f( gridSizeF, gridSizeF ) );
    m_Shape.setFillColor( sf::Color::White );
    m_Shape.setOutlineThickness( 1.f );
    m_Shape.setOutlineColor( sf::Color::Black );
    m_Shape.setPosition( x * gridSizeF, y * gridSizeF );
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