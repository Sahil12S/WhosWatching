#ifndef ENTITY_H
#define ENTITY_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "../Game.h"
#include "../Game_Components/MovementComponent.h"
#include "../Game_Components/AnimationComponent.h"
#include "../Game_Components/HitboxComponent.h"

/* Forward declaration */
struct GameData;
typedef std::shared_ptr<GameData> GameDataRef;

class AnimationComponent;
class MovementComponent;
class HitboxComponent;

class Entity
{
protected:
    GameDataRef m_Data;

    sf::Sprite m_Sprite;

    MovementComponent* m_MC;
    AnimationComponent* m_AC;
    HitboxComponent* m_HC;

public:
    /* Constructors and Destructors*/
    Entity( GameDataRef data );
    virtual ~Entity();

    /* Component functions */
    void SetTexture( sf::Texture& tex );
    void CreateHitboxComponent( const float& offset_x, const float& offset_y,
                                const float& width, const float& height );
    void CreateMovementComponent( const float& maxVelocity, const float& acceleration, const float& deceleration );
    void CreateAnimationComponent( const std::string& texture );
    
    // Getters
    virtual const sf::Vector2f& GetPosition() const;

    // Setters
    virtual void SetPosition( sf::Vector2f position );

    /* Functions */
    virtual void Move( const float& dt, const float& dir_x, const float& dir_y );
    virtual void Update( const float& dt );
    virtual void Draw( sf::RenderTarget& target );
};

#endif // ENTITY_H