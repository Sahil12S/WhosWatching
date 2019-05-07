#ifndef PLAYER_H
#define PLAYER_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"
#include "Entity.h"
#include "../Game.h"
#include "../Game.h"
#include "../Game_Components/MovementComponent.h"
#include "../Game_Components/HUD.h"

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


    const float GetRemainingTime();
    const int GetScore();

    /* Functions */
    void Attack();

    void UpdateAnimation( const float& dt );

    void Update( const float& dt ) override;
    void Draw( sf::RenderTarget& target ) override;
};

#endif // PLAYER_H