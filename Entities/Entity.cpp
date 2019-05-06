#include "Entity.h"

/* Constructors & Destructors */
Entity::Entity( GameDataRef data ) : m_Data( std::move( data ) )
{
    m_MC = nullptr;
    m_AC = nullptr;
    m_HC = nullptr;
    m_Sprite.setScale( 2.f, 2.f );
}

Entity::~Entity()
{
    delete m_MC;
    delete m_AC;
    delete m_HC;
}

/* Component functions */
void Entity::SetTexture( sf::Texture& tex )
{
    m_Sprite.setTexture( tex );
    m_Sprite.scale( 2.0f, 2.0f );
}

void Entity::CreateHitboxComponent( const float& offset_x, const float& offset_y,
        const float& width, const float& height )
{
    m_HC = new HitboxComponent( m_Data, m_Sprite, offset_x, offset_y, width, height );
}

void Entity::CreateMovementComponent(const float& maxVelocity, const float& acceleration, const float& deceleration )
{
    m_MC = new MovementComponent( m_Sprite, maxVelocity, acceleration, deceleration );
}

void Entity::CreateAnimationComponent(const std::string& texture)
{
    m_AC = new AnimationComponent( m_Data, m_Sprite, texture );
}

/* Functions */
const sf::Vector2f& Entity::GetPosition() const
{
    return m_Sprite.getPosition();
}

void Entity::SetPosition(sf::Vector2f position )
{
    m_Sprite.setPosition( position .x - m_Sprite.getGlobalBounds().width / 2,
                            position .y );
                            // position .y - m_Sprite.getGlobalBounds().height / 2 );
    m_Sprite.setScale( SCALE_X, SCALE_Y ); // Todo: use definition
}

void Entity::Move(const float &dt, const float &dir_x, const float &dir_y)
{
    if ( m_MC )
    {
        m_MC->Move( dt, dir_x, dir_y);
    }
    // m_Sprite.move( m_MC->GetVelocity() * dt );
}

void Entity::Update(const float& dt)
{

}

void Entity::Draw( sf::RenderTarget& target )
{
}