#ifndef TILE_H
#define TILE_H

#include "../pch.cpp"
#include "../Game.h"

namespace SSEngine
{
    class Tile
    {
    private:
        GameDataRef m_Data;

    protected:
        sf::RectangleShape m_Shape;

    public:
        // Tile( GameDataRef data );
        Tile( GameDataRef data, float x, float y, float gridSizeF );
        virtual ~Tile();

        void Update();
        void Draw();
    };
}

#endif // TILE_H
