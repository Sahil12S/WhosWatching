#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H

#include "../pch.cpp"
#include "../Game.h"
/*
 * Create a box around our sprite
 * Easy to manage sprite positions and collisions
 */

/* Forward declaration */
struct GameData;
typedef std::shared_ptr<GameData> GameDataRef;

class HitboxComponent
{
private:
    GameDataRef m_Data;

    sf::Sprite& m_Sprite;
    sf::RectangleShape m_Hitbox;
    sf::FloatRect m_NextPosition;

    float m_OffsetX;
    float m_OffsetY;

    float m_ShiftX;

public:
    HitboxComponent( GameDataRef data, sf::Sprite& sprite,
        const float& offset_x, const float& offset_y,
        const float& width, const float& height );
    virtual ~HitboxComponent();

    /* Functions */
    const sf::Vector2f& GetPosition() const;
    const sf::FloatRect GetGlobalBounds() const;

    /*
     * Help in predict what next position of hitbox will be
     * based on current velocity. This will help in deiciding collision
     */
    const sf::FloatRect& GetNextPosition( const sf::Vector2f& velocity );

    void SetPosition( const sf::Vector2f& position );
    void SetPosition( const float& x, const float& y );

    bool Intersects( const sf::FloatRect& rect );

    void UpdatePosition( const float& offset_x, const float& offset_y,
            const float& width, const float& height );

    void Update ( );
    void Draw( sf::RenderTarget& target );
};

#endif //HITBOX_COMPONENT_H