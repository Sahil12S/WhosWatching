#ifndef TILE_H
#define TILE_H

#include "../pch.cpp"
#include "../Game.h"

class Tile
{
private:
    GameDataRef m_Data;

protected:
    sf::RectangleShape m_Shape;
    short m_Type;
    bool m_Collision;
    bool m_Hidden;

public:
    // Tile( GameDataRef data );
    Tile( GameDataRef data, unsigned grid_x, unsigned grid_y, float gridSizeF, 
        const std::string& texture_name, const sf::IntRect& texture_rect,
        bool collision = false, short type = 0 );
    virtual ~Tile();

    // Return tile properties as string
    const short& getType() const;
    const bool GetCollision() const;
    bool Hidden() const;
    const sf::Vector2f& GetPosition() const;
    const sf::FloatRect GetGlobalBounds() const;
    const std::string GetAsString() const;

    const bool Intersects( const sf::FloatRect bounds ) const;

    void Hide();
    void Update();
    void Draw( sf::RenderTarget& target );
};

#endif // TILE_H
