#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

namespace SSEngine
{
    class MovementComponent
    {
    private:
        sf::Sprite& m_Sprite;

        float m_MaxVelocity;
        float m_Acceleration;
        float m_Deceleration;

        sf::Vector2f m_Velocity;

        // Initializer functions

    public:
        MovementComponent( sf::Sprite& sprite, const float& maxVelocity,
                           const float& acceleration = 1.f, const float& deceleration = 1.f );
        virtual ~MovementComponent();

        // Getters & Setters
        const sf::Vector2f& GetVelocity() const;
        const float& GetMaxVelocity() const;

        void StopVelocity();

        const bool GetState( const unsigned short& state ) const;

        // Functions
        void Move( const float& dt, const float& dir_x, const float& dir_y);
        void Update( const float& dt );
    };
}



#endif //MOVEMENTCOMPONENT_H
