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
    sf::Vector2f m_MapSize;

    std::string m_TextureFile;

    // 3D vector to store tiles and layers
    std::vector< std::vector< std::vector< Tile* > > > m_Map;

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

    void Update();
    void Draw( sf::RenderTarget& target );

};

#endif // TILEMAP_H
