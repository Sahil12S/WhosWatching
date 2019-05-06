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

public:
    // Tile( GameDataRef data );
    Tile( GameDataRef data, unsigned grid_x, unsigned grid_y, float gridSizeF, 
        const std::string& texture_name, const sf::IntRect& texture_rect,
        bool collision = false, short type = 0 );
    virtual ~Tile();

    // Return tile properties as string
    const std::string getAsString() const;

    void Update();
    void Draw( sf::RenderTarget& target );
};

#endif // TILE_H
