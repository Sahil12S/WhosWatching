#ifndef TILEMAP_H
#define TILEMAP_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "../Tile/Tile.h"
#include "../Game.h"

namespace SSEngine
{
    class Game;


    class TileMap
    {
    private:
        GameDataRef m_Data;

        float m_GridSizeF;
        unsigned m_GridSizeU;
        unsigned m_Layers;
        sf::Vector2f m_MapSize;

        // 3D vector to store tiles and layers
        std::vector< std::vector< std::vector< Tile* > > > m_Map;

    public:
        TileMap( GameDataRef data, unsigned int width, unsigned int height );
        virtual ~TileMap();
        
        const sf::Texture* GetTileSheet() const;

        void AddTile( const unsigned& x, const unsigned& y, const unsigned& z, const sf::IntRect& texture_rect );
        void RemoveTile( const unsigned& x, const unsigned& y, const unsigned& z );

        void Update();
        void Draw();

    };
}

#endif // TILEMAP_H
