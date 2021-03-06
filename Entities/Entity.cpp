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
    delete m_AttComp;
}

/* Component functions */
void Entity::SetTexture( sf::Texture& tex )
{
    m_Sprite.setTexture( tex );
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

void Entity::CreateAttributeComponent()
{
    m_AttComp = new AttributeComponent();
}

/* Functions */
const sf::Vector2f& Entity::GetPosition() const
{
    if( m_HC )
    {
        return m_HC->GetPosition();
    }

    return m_Sprite.getPosition();
}

const sf::Vector2i Entity::GetGridPosition( const int& gridSizeI ) const
{
    if ( m_HC )
    {
        return sf::Vector2i( 
            static_cast<int>( m_HC->GetPosition().x ) / gridSizeI,
            static_cast<int>( m_HC->GetPosition().y ) / gridSizeI
        );
    }
    return sf::Vector2i( 
        static_cast<int>( m_Sprite.getPosition().x ) / gridSizeI,
        static_cast<int>( m_Sprite.getPosition().y ) / gridSizeI
    );
}

const sf::FloatRect Entity::GetGlobalBounds() const
{
    if( m_HC )
    {
        return m_HC->GetGlobalBounds();
    }
    return m_Sprite.getGlobalBounds();
}

const sf::FloatRect Entity::GetNextPositionBounds( const float& dt ) const
{
    if( m_HC && m_MC )
    {
        return m_HC->GetNextPosition( m_MC->GetVelocity() * dt );
    }
    return sf::FloatRect( -1, -1, -1, -1 ); 
}

void Entity::SetPosition( const float& x, const float& y )
{
    if ( m_HC )
    {
        m_HC->SetPosition( x, y );
    }
    else
    {
        m_Sprite.setPosition( x, y );
    }
}


void Entity::Move(const float &dt, const float &dir_x, const float &dir_y)
{
    if ( m_MC )
    {
        m_MC->Move( dt, dir_x, dir_y);
    }
}

void Entity::StopVelocity()
{
    if( m_MC )
    {
        m_MC->StopVelocity();
    }
}

void Entity::StopVelocityX()
{
    if( m_MC )
    {
        m_MC->StopVelocityX();
    }
}

void Entity::StopVelocityY()
{
    if( m_MC )
    {
        m_MC->StopVelocityY();
    }
}
void Entity::Update(const float& dt)
{

}

void Entity::Draw( sf::RenderTarget& target )
{
}