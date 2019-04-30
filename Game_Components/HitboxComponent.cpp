#include "HitboxComponent.h"

HitboxComponent::HitboxComponent( GameDataRef data, sf::Sprite& sprite,
        const float& offset_x, const float& offset_y,
        const float& width, const float& height ) :
        m_Data( std::move( data ) ), m_Sprite( sprite ), m_OffsetX( offset_x ), m_OffsetY( offset_y )
{

    m_ShiftX = (m_Sprite.getGlobalBounds().width - width) / 2.f ;

    m_Hitbox.setPosition( m_Sprite.getPosition().x + offset_x - m_ShiftX, m_Sprite.getPosition().y + offset_y );
    // m_Hitbox.setOrigin( m_Sprite.getOrigin() );

    m_Hitbox.setSize( sf::Vector2f( width, height ) );
    m_Hitbox.setFillColor( sf::Color::Transparent );
    m_Hitbox.setOutlineThickness( 1.f );
    m_Hitbox.setOutlineColor( sf::Color::Magenta );
}

HitboxComponent::~HitboxComponent()
{

}

bool HitboxComponent::CheckIntersects(const sf::FloatRect& rect)
{
    return m_Hitbox.getGlobalBounds().intersects( rect );
}

void HitboxComponent::UpdatePosition( const float& offset_x, const float& offset_y,
        const float& width, const float& height )
{
    m_Hitbox.setSize( sf::Vector2f( width, height ) );

    m_OffsetX = offset_x;
    m_OffsetY = offset_y;

    // m_Hitbox.setPosition( m_Sprite.getPosition().x + offset_x + m_ShiftX,
    //                       m_Sprite.getPosition().y + offset_y );
}

void HitboxComponent::Update()
{
    m_Hitbox.setPosition( m_Sprite.getPosition().x + m_OffsetX + m_ShiftX,
            m_Sprite.getPosition().y + m_OffsetY );
}

void HitboxComponent::Draw()
{
    m_Data->window.draw( m_Hitbox );
}