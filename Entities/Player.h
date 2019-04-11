#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../Game.h"
#include "../Game.h"
#include "../DEFINITIONS.h"
#include "../Game_Components/MovementComponent.h"

/*
    Properties of player
    - Walk
    - Run ( Accelerate )
    - Jump
    - Duck ( only when grown )
    - Die
    - Grow ( Power up )
    - Shoot ( Power )
*/

namespace SSEngine
{
    class Player : public Entity
    {
    private:
        GameDataRef m_Data;


        /* Variables */

        bool m_IsJumping;
        bool m_IsFalling;
        bool m_IsMovingLeft;
        bool m_IsMovingRight;
        bool m_IsDucking;

        float m_RunningFactor;


        bool m_JustJumped = false;

        // Clock to handle movements
        sf::Clock m_MovementClock;

        /* Variables to check for powers */
        bool m_IsGrownUp;
        bool m_IsPowered;


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

        /*
         * Jump()
         * StopJump()
         *          Toggles jumping action for player
         */
        void Jump();
        // void StopJump();

        /*
         * Duck()
         * StopDuck()
         *          Toggles ducking action for player
         */
        void Duck();
        void StopDuck();

        /*
         * MoveLeft()
         * StopLeft()
         *          Toggles left movement for player
         */
        void MoveLeft();
        void StopLeft();

        /*
         * MoveRight()
         * StopRight()
         *          Toggles right movement for player
         */
        void MoveRight();
        void StopRight();

        /*
         * Run()
         * StopRunning()
         *          Toggles if player is running or not.
         */
        void Run();
        void StopRunning();


        void UpdateAnimation( const float& dt );

        void Update( float dt ) override;
        void Draw() override;
    };
}

#endif // PLAYER_H