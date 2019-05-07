#include "HitboxComponent.h"

HitboxComponent::HitboxComponent( GameDataRef data, sf::Sprite& sprite,
        const float& offset_x, const float& offset_y,
        const float& width, const float& height ) :
        m_Data( std::move( data ) ), m_Sprite( sprite ), m_OffsetX( offset_x ), m_OffsetY( offset_y )
{

    m_NextPosition.left = 0.f;
    m_NextPosition.top = 0.f;
    m_NextPosition.width = width;
    m_NextPosition.height = height;

    m_Hitbox.setPosition( m_Sprite.getPosition().x + offset_x, m_Sprite.getPosition().y + offset_y );
    m_Hitbox.setSize( sf::Vector2f( width, height ) );
    m_Hitbox.setFillColor( sf::Color::Transparent );
    m_Hitbox.setOutlineThickness( - 1.f );
    m_Hitbox.setOutlineColor( sf::Color::Magenta );
}

HitboxComponent::~HitboxComponent()
{

}

const sf::Vector2f& HitboxComponent::GetPosition() const
{
    return m_Hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::GetGlobalBounds() const
{
    return m_Hitbox.getGlobalBounds();
}

const sf::FloatRect& HitboxComponent::GetNextPosition( const sf::Vector2f& velocity )
{
    m_NextPosition.left = m_Hitbox.getPosition().x + velocity.x;
    m_NextPosition.top = m_Hitbox.getPosition().y + velocity.y;

    return m_NextPosition;
}

void HitboxComponent::SetPosition( const sf::Vector2f& position )
{
    m_Hitbox.setPosition( position );
    m_Sprite.setPosition( position.x - m_OffsetX, position.y - m_OffsetY );
}

void HitboxComponent::SetPosition( const float& x, const float& y )
{
    m_Hitbox.setPosition( x, y );
    m_Sprite.setPosition( x - m_OffsetX, y - m_OffsetY );
}

bool HitboxComponent::Intersects(const sf::FloatRect& rect)
{
    return m_Hitbox.getGlobalBounds().intersects( rect );
}

// void HitboxComponent::UpdatePosition( const float& offset_x, const float& offset_y,
//         const float& width, const float& height )
// {
//     m_Hitbox.setSize( sf::Vector2f( width, height ) );

//     m_OffsetX = offset_x;
//     m_OffsetY = offset_y;

//     // m_Hitbox.setPosition( m_Sprite.getPosition().x + offset_x + m_ShiftX,
//     //                       m_Sprite.getPosition().y + offset_y );
// }

void HitboxComponent::Update()
{
    // m_Hitbox.setPosition( m_Sprite.getPosition().x + m_OffsetX + m_ShiftX,
    //         m_Sprite.getPosition().y + m_OffsetY );
    m_Hitbox.setPosition( m_Sprite.getPosition().x + m_OffsetX, m_Sprite.getPosition().y + m_OffsetY );
}

void HitboxComponent::Draw( sf::RenderTarget& target )
{
    target.draw( m_Hitbox );
}