#ifndef TILEMAP_H
#define TILEMAP_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "../Tile/Tile.h"
#include "../Game.h"

class Game;


class TileMap
{
private:
    GameDataRef m_Data;

    float m_GridSizeF;
    unsigned m_GridSizeU;
    unsigned m_Layers;
    // Number of grids in world
    sf::Vector2u m_MaxSizeWorldGrid;
    // Size of grid ( num of grid x size of grid )
    sf::Vector2f m_MaxSizeWorldF;

    std::string m_TextureFile;
    sf::RectangleShape m_CollisionBox;

    // 3D vector to store tiles and layers
    std::vector< std::vector< std::vector< Tile* > > > m_Map;

    // Culling
    int fromX;
    int toX;
    int fromY;
    int toY;
    int layer;

    // Clear: clears all the tiles from map
    void Clear();

public:
    TileMap( GameDataRef data, unsigned int width, unsigned int height, const std::string& texture_file );
    virtual ~TileMap();
    
    const std::string GetTileSheet() const;

    void AddTile( const unsigned& x, const unsigned& y, const unsigned& z, const sf::IntRect& texture_rect, const bool& collision, const short& type );
    // Remove tile from map
    void RemoveTile( const unsigned& x, const unsigned& y, const unsigned& z );
    // Save complete tilemap to a text file
    void SaveToFile( const std::string file_name );
    // Load map from a text file
    void LoadFromFile( const std::string file_name );

    void UpdateCollision( Entity* entity );

    void Update();
    void Draw( sf::RenderTarget& target, Entity* entity = nullptr );

};

#endif // TILEMAP_H
