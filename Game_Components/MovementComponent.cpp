#include "MovementComponent.h"
#include "../DEFINITIONS.h"

namespace SSEngine
{
    MovementComponent::MovementComponent( sf::Sprite& sprite, const float& maxVelocity,
            const float& acceleration, const float& deceleration ) :
            m_Sprite( sprite ), m_MaxVelocity ( maxVelocity ),
            m_Acceleration( acceleration ), m_Deceleration( deceleration )
    {
    }

    MovementComponent::~MovementComponent() = default;

    const sf::Vector2f &MovementComponent::GetVelocity() const
    {
        return m_Velocity;
    }

    const bool MovementComponent::GetState(const unsigned short& state) const
    {
        switch ( state )
        {
            case eIdle:
                if ( m_Velocity.x == 0.f && m_Velocity.y == 0.f)
                    return true;
                break;

            case eMoving:
                if ( m_Velocity.x != 0.f || m_Velocity.y != 0.f)
                    return true;
                break;

            case eMovingLeft:

                if ( m_Velocity.x < 0.f && m_Velocity.x >= -m_MaxVelocity )
                    return true;
                break;

            case eMovingRight:

                if (m_Velocity.x > 0.f && m_Velocity.x <= m_MaxVelocity )
                    return true;
                break;

            case eJumping:
                if (m_Velocity.y < 0.f)
                    return true;
                break;

            case eFalling:
                if (m_Velocity.y > 0.f)
                    return true;
                break;

            case eRunningLeft:
                if ( m_Velocity.x < -m_MaxVelocity )
                    return true;
                break;

            case eRunningRight:
                if ( m_Velocity.x > m_MaxVelocity )
                    return true;
                break;

            default:
                return false;
        }
        return false;
    }

    void MovementComponent::Move( const float& dt, const float& dir_x, const float& dir_y )
    {
        /*m_Velocity.x += dir_x * m_Acceleration;
        m_Velocity.y += dir_y * m_Acceleration;*/
        m_Velocity.x = dir_x * m_MaxVelocity;

        // We are considering jump as dir_y
        m_Velocity.y = dir_y;
        m_Sprite.move( m_Velocity * dt );
    }

    void MovementComponent::Update(const float &dt)
    {
        m_Sprite.move( m_Velocity * dt );
        // When using acceleration and deceleration
        // which we are not using this time

        /*if (this->m_Velocity.x > 0.f) //Check for positive x
        {
            //Max velocity check
            if (this->m_Velocity.x > this->m_MaxVelocity)
                this->m_Velocity.x = this->m_MaxVelocity;

            //Deceleration
            this->m_Velocity.x -= m_Deceleration * dt;
            if (this->m_Velocity.x < 0.f)
                this->m_Velocity.x = 0.f;
        }
        else if(this->m_Velocity.x < 0.f) //Check for negative x
        {
            //Max velocity check
            if (this->m_Velocity.x < -this->m_MaxVelocity)
                this->m_Velocity.x = -this->m_MaxVelocity;

            //Deceleration
            this->m_Velocity.x += m_Deceleration * dt;
            if (this->m_Velocity.x > 0.f)
                this->m_Velocity.x = 0.f;
        }

        if (this->m_Velocity.y > 0.f) //Check for positive y
        {
            //Max velocity check
            if (this->m_Velocity.y > this->m_MaxVelocity)
                this->m_Velocity.y = this->m_MaxVelocity;

            //Deceleration
            this->m_Velocity.y -= m_Deceleration * dt;
            if (this->m_Velocity.y < 0.f)
                this->m_Velocity.y = 0.f;
        }
        else if (this->m_Velocity.y < 0.f) //Check for negative y
        {
            //Max velocity check
            if (this->m_Velocity.y < -this->m_MaxVelocity)
                this->m_Velocity.y = -this->m_MaxVelocity;

            //Deceleration
            this->m_Velocity.y += m_Deceleration * dt;
            if (this->m_Velocity.y > 0.f)
                this->m_Velocity.y = 0.f;
        }

        m_Sprite.move( m_Velocity * dt );*/
    }

    const float &MovementComponent::GetMaxVelocity() const
    {
        return m_MaxVelocity;
    }

    void MovementComponent::StopVelocity()
    {
        m_Velocity.x = 0.f;
        m_Velocity.y = 0.f;
    }
}