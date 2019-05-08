#include "Player.h"

void Player::InitTextures()
{
    m_Data->assets.LoadTexture( "Player Sheet", PLAYER_SHEET_FILEPATH );
}

void Player::InitSounds()
{

}

void Player::InitVariables()
{
    m_IsAttacking = false;
    m_AttackCount = 0;
    m_CurrentFace = eAttackFaceRight;
    m_LastAttackFace = eNone;
}

void Player::InitComponents()
{

}

Player::Player( GameDataRef data ) : Entity( data ), m_Data( move( data ) )
{
    InitTextures();
    InitSounds();
    InitVariables();
    InitComponents();

    // Set acceleration and deceleration
    CreateMovementComponent( PLAYER_MOVEMENT_SPEED, 1500, 500 );
    CreateAnimationComponent( "Player Sheet" );
    // OffsetX, OffsetY, width, height
    CreateHitboxComponent( 35.f, 20.f, 30.f, 60.f );
    CreateAttributeComponent();

    // Animation name, animation timer, start pos X, start pos Y, frames X, frames Y, tile size
    // Lesser the timer, faster the animation speed
    m_AC->AddAnimation("IDLE", 15, 0, 0, 4, 1, TILE_WIDTH, TILE_HEIGHT );
    m_AC->AddAnimation("WALK", 10, 0, 1, 6, 1, TILE_WIDTH, TILE_HEIGHT );
    m_AC->AddAnimation("ATTACK0", 7, 0, 3, 6, 1, TILE_WIDTH, TILE_HEIGHT );
    m_AC->AddAnimation("ATTACK1", 7, 0, 4, 5, 1, TILE_WIDTH, TILE_HEIGHT );

    // Implement later
    // m_AC->AddAnimation("TURN_ATTACK", 67, 0, 5, 6, 1, TILE_WIDTH, TILE_HEIGHT );
}

Player::~Player()
{
}

const float Player::GetRemainingTime()
{
    return m_AttComp->timer;
}

const int Player::GetScore()
{
    return m_AttComp->points;
}

void Player::Attack()
{
    if ( m_LastAttackFace == eNone )
    {
        m_LastAttackFace = m_CurrentFace;
    }
    m_IsAttacking = true;
}

void Player::WinPoints()
{
    m_AttComp->UpdatePoints();
}

void Player::UpdateAnimation(const float &dt)
{
    if ( m_AttackClock.getElapsedTime().asSeconds() > 1.3f )
    {
        m_AttackCount = 0;
        m_AttackClock.restart();
        m_LastAttackFace = m_CurrentFace;
    }
    if ( m_IsAttacking )
    {
        /*
        // Set the origin in facing direction
        if ( m_Sprite.getScale().x < 0.f )  // Facing left
        {
            m_Sprite.setOrigin( 50.f + 2.f, 0.f );
            m_HC->UpdatePosition( 25.f, 10.f, 45.f, 70.f );
        }
        else    // Facing right
        {
            m_Sprite.setOrigin( 0.f + 2.f, 0.f );
            m_HC->UpdatePosition( 60.f, 10.f, 45.f, 70.f );
        }

        if ( m_AC->Play( "ATTACK"+ std::to_string(m_AttackCount), dt, true ) )
        {
            m_IsAttacking = false;
            m_AttackCount = (m_AttackCount + 1 ) % 2 ;
            m_AttackClock.restart().asSeconds();

            // Reset position after player is done attacking
            // Set the origin in facing direction
            if ( m_Sprite.getScale().x < 0.f )  // Facing left
            {
                m_Sprite.setOrigin( 50.f, 0.f );
                // m_HC->UpdatePosition( 50.f, 20.f, 30.f, 60.f );
            }
            else    // Facing right
            {
                m_Sprite.setOrigin( 0.f, 0.f );
                // m_HC->UpdatePosition( 50.f, 20.f, 30.f, 60.f );
            }
        }
        */
    }


    if ( m_MC->GetState( eIdle ) )
    {
        m_AC->Play("IDLE", dt);
    }
    else if ( m_MC->GetState( eMovingLeft ) )
    {
        m_CurrentFace = eAttackFaceLeft;

        if ( m_Sprite.getScale().x > 0.f )
        {
            // Set Proper origin
            m_Sprite.setOrigin(50.f, 0.f);
            m_Sprite.setScale(-SCALE_X, SCALE_Y);
        }
        m_AC->Play("WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity());
    }
    else if ( m_MC->GetState( eMovingRight ) )
    {
        m_CurrentFace = eAttackFaceRight;

        if (m_Sprite.getScale().x < 0.f)
        {
            m_Sprite.setOrigin(0.f, 0.f);
            m_Sprite.setScale(SCALE_X, SCALE_Y);
        }
        m_AC->Play("WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity());
    }
    else if ( m_MC->GetState( eMovingUp ) || m_MC->GetState( eMovingDown ) || m_MC->GetState( eMoving ) )
    {
        m_AC->Play("WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity());
    }

}

void Player::Update(const float& dt)
{
    m_AttComp->UpdateTime( dt );
    m_MC->Update( dt );
    UpdateAnimation( dt );
    m_HC->Update();
    
}

void Player::Draw( sf::RenderTarget& target )
{
    target.draw( m_Sprite );

    // m_HC->Draw( target );
}