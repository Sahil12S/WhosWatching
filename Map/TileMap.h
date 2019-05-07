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
    int m_GridSizeI;
    int m_Layers;
    // Number of grids in world
    sf::Vector2i m_MaxSizeWorldGrid;
    // Size of grid ( num of grid x size of grid )
    sf::Vector2f m_MaxSizeWorldF;

    std::string m_TextureFile;
    sf::RectangleShape m_CollisionBox;

    // 3D vector to store tiles and layers
    std::vector< std::vector< std::vector< std::vector< Tile* > > > > m_Map;

    // Store tiles that we want to render later
    std::stack<Tile*> deferredRenderStack;

    // Culling
    int fromX;
    int toX;
    int fromY;
    int toY;
    int layer;

    // Clear: clears all the tiles from map
    void Clear();

public:
    TileMap( GameDataRef data, int width, int height, const std::string& texture_file );
    TileMap( GameDataRef data, const std::string file_name);
    virtual ~TileMap();
    
    const std::string GetTileSheet() const;
    const int GetLayerSize( const int& x, const int& y, const int& layer ) const;

    void AddTile( const int& x, const int& y, const int& z, const sf::IntRect& texture_rect, const bool& collision, const short& type );
    // Remove tile from map
    void RemoveTile( const int& x, const int& y, const int& z );
    // Save complete tilemap to a text file
    void SaveToFile( const std::string file_name );
    // Load map from a text file
    void LoadFromFile( const std::string file_name );

    void UpdateCollision( Entity* entity, const float& dt );

    void Update();

    // We can render using position rather than player
    void Draw( sf::RenderTarget& target, const sf::Vector2i& gridPosition );
    void RenderDeferred( sf::RenderTarget& target );

};

#endif // TILEMAP_H
