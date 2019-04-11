#include "Player.h"

namespace SSEngine
{
    void Player::InitTextures()
    {
        m_Data->assets.LoadTexture( "Player Sheet", PLAYER_SHEET_FILEPATH );
    }

    void Player::InitSounds()
    {

    }

    void Player::InitVariables()
    {
        // Trigger variables
        m_IsJumping = false;
        m_IsFalling = false;
        m_IsMovingLeft = false;
        m_IsMovingRight = false;
        m_IsDucking = false;
        m_IsGrownUp = true;
        m_IsPowered = false;
        m_RunningFactor = 1.f;
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

        CreateMovementComponent( PLAYER_MOVEMENT_SPEED, 0, 0 );
        CreateAnimationComponent( "Player Sheet" );

        // Animation name, animation timer, start pos X, start pos Y, frames X, frames Y, tile size
        m_AC->AddAnimation("IDLE", 0.f, 0, 2, 1, 1, TILE_WIDTH, TILE_HEIGHT );
        m_AC->AddAnimation("WALK", WALK_ANIMATION_DURATION, 1, 2, 3, 1, TILE_WIDTH, TILE_HEIGHT );
        m_AC->AddAnimation("JUMP", 0.f, 5, 2, 1, 1, TILE_WIDTH, TILE_HEIGHT );
        m_AC->AddAnimation("FALL", 0.f, 5, 2, 1, 1, TILE_WIDTH, TILE_HEIGHT );
        m_AC->AddAnimation("GROWN_UP_IDLE", 0.f, 0, 0, 1, 1, TILE_WIDTH, TILE_HEIGHT * 2 );
        m_AC->AddAnimation("GROWN_UP_WALK", WALK_ANIMATION_DURATION, 1, 0, 3, 1, TILE_WIDTH, TILE_HEIGHT * 2 );
        m_AC->AddAnimation("GROWN_UP_JUMP", 0.f, 5, 0, 1, 1, TILE_WIDTH, TILE_HEIGHT * 2 );
        m_AC->AddAnimation("GROWN_UP_FALL", 0.f, 5, 0, 1, 1, TILE_WIDTH, TILE_HEIGHT * 2 );
        m_AC->AddAnimation("GROWN_UP_DUCK", 0.f, 6, 0, 1, 1, TILE_WIDTH, TILE_HEIGHT * 2 );

        // Hit box size for mario
        CreateHitboxComponent( 0.f, 0.f, 20.f, 32.f );
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

    void Player::MoveLeft()
    {
        m_IsMovingLeft = true;
    }
    void Player::StopLeft()
    {
        m_IsMovingLeft = false;
    }

    void Player::MoveRight()
    {
        m_IsMovingRight = true;
    }
    void Player::StopRight()
    {
        m_IsMovingRight = false;
    }

    void Player::Run()
    {
        m_RunningFactor = RUNNING_FACTOR;
    }
    void Player::StopRunning()
    {
        m_RunningFactor = 1.f;
    }

    void Player::Jump()
    {
        if ( !m_IsFalling && !m_JustJumped )
        {
            m_IsJumping = true;
            m_JustJumped = true;
            m_IsFalling = false;
            m_IsDucking = false;
            m_MovementClock.restart();
        }
    }

    void Player::Duck()
    {
        if ( !m_IsJumping && !m_IsFalling )
        {
            m_IsDucking = true;
        }
    }

    void Player::StopDuck()
    {
        m_IsDucking = false;
    }

    /*void Player::StopJump()
    {
        m_IsJumping = false;
    }

    void Player::StopFalling()
    {
        m_IsFalling = false;
    }*/

    void Player::UpdateAnimation(const float &dt)
    {
        if ( m_MC->GetState( eIdle ) && !m_IsJumping )
        {
            if ( !m_IsGrownUp )
            {
                m_AC->Play("IDLE", dt);
            }
            else if ( !m_IsDucking )
            {
                m_AC->Play("GROWN_UP_IDLE", dt);
            }
        }
        else if ( m_MC->GetState( eMovingLeft ) )
        {
            if ( m_Sprite.getScale().x > 0.f )
            {
                m_Sprite.setOrigin(16.f, 0.f);
                m_Sprite.setScale(-SCALE_X, SCALE_Y);
            }
            if ( !m_IsGrownUp )
            {
                m_AC->Play("WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity());
            }
            else if ( !m_IsDucking )
            {
                m_AC->Play("GROWN_UP_WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity());
            }
        }
        else if ( m_MC->GetState( eMovingRight ) )
        {
            if (m_Sprite.getScale().x < 0.f)
            {
                m_Sprite.setOrigin(0.f, 0.f);
                m_Sprite.setScale(SCALE_X, SCALE_Y);
            }
            if ( !m_IsGrownUp )
            {
                m_AC->Play("WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity());
            }
            else if ( !m_IsDucking )
            {
                m_AC->Play("GROWN_UP_WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity());
            }
        }
        else if ( m_MC->GetState( eRunningLeft ) )
        {
            if ( m_Sprite.getScale().x > 0.f )
            {
                m_Sprite.setOrigin(16.f, 0.f);
                m_Sprite.setScale(-SCALE_X, SCALE_Y);
            }
            if ( !m_IsGrownUp )
            {
                m_AC->Play("WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity() * m_RunningFactor );
            }
            else if ( !m_IsDucking )
            {
                m_AC->Play("GROWN_UP_WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity() * m_RunningFactor );
            }
        }
        else if ( m_MC->GetState( eRunningRight ) )
        {
            if (m_Sprite.getScale().x < 0.f)
            {
                m_Sprite.setOrigin(0.f, 0.f);
                m_Sprite.setScale(SCALE_X, SCALE_Y);
            }
            if ( !m_IsGrownUp )
            {
                m_AC->Play("WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity() * m_RunningFactor );
            }
            else if ( !m_IsDucking )
            {
                m_AC->Play("GROWN_UP_WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity() * m_RunningFactor );

            }
        }
        else if ( m_MC->GetState( eJumping ) )
        {
            if ( !m_IsGrownUp )
            {
                m_AC->Play("JUMP", dt );
            }
            else if ( !m_IsDucking )
            {
                m_AC->Play("GROWN_UP_JUMP", dt );
            }
        }
        else if ( m_MC->GetState( eFalling ) )
        {
            if ( !m_IsGrownUp )
            {
                m_AC->Play( "FALL", dt );
            }
            else if ( !m_IsDucking )
            {
                m_AC->Play( "GROWN_UP_FALL", dt );

            }
        }
    }

    void Player::Update(float dt)
    {
        if ( m_IsMovingLeft )
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
        }

        m_HC->Update();

    }

    void Player::Draw()
    {
        m_Data->window.draw( m_Sprite );

        m_HC->Draw();
    }
}
