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
    Tile( GameDataRef data, float x, float y, float gridSizeF, const std::string& texture_name, const sf::IntRect& texture_rect );
    virtual ~Tile();

    // Return tile properties as string
    const std::string getAsString() const;

    void Update();
    void Draw();
};

#endif // TILE_H
