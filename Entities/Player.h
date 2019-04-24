#ifndef PLAYER_H
#define PLAYER_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"
#include "Entity.h"
#include "../Game.h"
#include "../Game.h"
#include "../Game_Components/MovementComponent.h"

/*
    Properties of player
    - Walk
    - Die
    - Attack
*/

namespace SSEngine
{
    class Player : public Entity
    {
    private:
        GameDataRef m_Data;

        /* Variables */
        bool m_IsAttacking;
        int m_AttackCount;
        AttackFace m_LastAttackFace;
        AttackFace m_CurrentFace;

        // sf::Clock m_MovementClock;
        // Clock to handle Attack
        sf::Clock m_AttackClock;

        /* Initializers */
        void InitTextures();
        void InitSounds();
        void InitVariables();
        void InitComponents();

    public:
        // Constructor / Destructor
        explicit Player( GameDataRef data );
        ~Player() override;


        /* Functions */
        void Attack();

        void UpdateAnimation( const float& dt );

        void Update( float dt ) override;
        void Draw() override;
    };
}

#endif // PLAYER_H