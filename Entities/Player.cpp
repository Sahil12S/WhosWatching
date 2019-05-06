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
    CreateHitboxComponent( 50.f, 20.f, 30.f, 60.f );

    // Animation name, animation timer, start pos X, start pos Y, frames X, frames Y, tile size
    // Lesser the timer, faster the animation speed
    m_AC->AddAnimation("IDLE", 15, 0, 0, 4, 1, TILE_WIDTH, TILE_HEIGHT );
    m_AC->AddAnimation("WALK", 10, 0, 1, 6, 1, TILE_WIDTH, TILE_HEIGHT );
    m_AC->AddAnimation("ATTACK0", 7, 0, 3, 6, 1, TILE_WIDTH, TILE_HEIGHT );
    m_AC->AddAnimation("ATTACK1", 7, 0, 4, 5, 1, TILE_WIDTH, TILE_HEIGHT );

    // Implement later
    // m_AC->AddAnimation("TURN_ATTACK", 67, 0, 5, 6, 1, TILE_WIDTH, TILE_HEIGHT );
}

Player::~Player() = default;

/*void Player::SetPosition(sf::Vector2f startPos)
{
    m_PlayerSprite.setTexture( m_WalkAnimationFrames.at( 0 ) );
    m_PlayerSprite.setPosition( startPos );
    m_PlayerSprite.scale( 2.0f, 2.0f );

    sf::Vector2f origin = sf::Vector2f( m_PlayerSprite.getGlobalBounds().width / 2,
                                        m_PlayerSprite.getGlobalBounds().height / 2 );

    m_PlayerSprite.setOrigin( origin );
    // Debug( m_PlayerSprite.getPosition().x )
}*/

void Player::Attack()
{
    if ( m_LastAttackFace == eNone )
    {
        m_LastAttackFace = m_CurrentFace;
    }
    m_IsAttacking = true;
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


        // If player's face during last attack was same as player's current face
        // Implement turn attack later
        /*if ( m_LastAttackFace == m_CurrentFace )
        {
            if ( m_AC->Play( "ATTACK"+ std::to_string(m_AttackCount), dt, true ) )
            {
                m_IsAttacking = false;
                m_AttackCount = (m_AttackCount + 1 ) % 2 ;
                m_AttackClock.restart().asSeconds();
                // m_JustAttacked = true;

                // Reset position after player is done attacking
                // Set the origin in facing direction
                if ( m_Sprite.getScale().x < 0.f )  // Facing left
                {
                    m_Sprite.setOrigin( 50.f, 0.f );
                    m_HC->UpdatePosition( 50.f, 20.f, 30.f, 60.f );
                }
                else    // Facing right
                {
                    m_Sprite.setOrigin( 0.f, 0.f );
                    m_HC->UpdatePosition( 50.f, 20.f, 30.f, 60.f );
                }
            }
        }
        else
        {
            m_LastAttackFace = m_CurrentFace;

            if ( m_AC->Play( "TURN_ATTACK", dt, true ) )
            {
                m_IsAttacking = false;
                m_AttackCount = 0 ;
                m_AttackClock.restart().asSeconds();
                // m_JustAttacked = true;

                // Reset position after player is done attacking
                // Set the origin in facing direction
                if ( m_Sprite.getScale().x < 0.f )  // Facing left
                {
                    m_Sprite.setOrigin( 50.f, 0.f );
                    m_HC->UpdatePosition( 50.f, 20.f, 30.f, 60.f );
                }
                else    // Facing right
                {
                    m_Sprite.setOrigin( 0.f, 0.f );
                    m_HC->UpdatePosition( 50.f, 20.f, 30.f, 60.f );
                }
            }
        }*/

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
                m_HC->UpdatePosition( 50.f, 20.f, 30.f, 60.f );
            }
            else    // Facing right
            {
                m_Sprite.setOrigin( 0.f, 0.f );
                m_HC->UpdatePosition( 50.f, 20.f, 30.f, 60.f );
            }
        }
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
    /*if ( m_IsMovingLeft )
    {
        Move( dt, -1.0f * m_RunningFactor, 0.0f);
        UpdateAnimation( dt );
    }
    else if ( m_IsMovingRight )
    {
        Move( dt, 1.0f * m_RunningFactor, 0.0f);
        UpdateAnimation( dt );
    }
    else if ( !m_IsJumping && !m_IsFalling && !m_IsMovingLeft && !m_IsMovingRight )
    {
        m_MC->StopVelocity();
        UpdateAnimation( dt );
    }

    // Jump
    if ( m_IsJumping )
    {
        Move( dt, 0.0f, -JUMP_SPEED );
        UpdateAnimation( dt );
    }
    // Fall
    else if ( m_IsFalling )
    {
        Move( dt, 0.0f, GRAVITY );
        UpdateAnimation( dt );
    }
    else if ( m_IsDucking )
    {
        Move( dt, 0.f, 0.f );
        m_AC->Play( "GROWN_UP_DUCK", dt );
    }

    if ( m_JustJumped && m_MovementClock.getElapsedTime().asSeconds() > JUMP_DURATION )
    {
        m_MovementClock.restart();
        m_IsJumping = false;
        m_JustJumped = false;
        m_IsFalling = true;
    }

    if ( m_Sprite.getPosition().y > SCREEN_HEIGHT - 100 )
    {
        m_IsFalling = false;
    }*/
    m_MC->Update( dt );
    UpdateAnimation( dt );

    m_HC->Update();

}

void Player::Draw( sf::RenderTarget& target )
{
    target.draw( m_Sprite );

    m_HC->Draw( target );
}