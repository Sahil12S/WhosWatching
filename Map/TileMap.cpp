#include "TileMap.h"


TileMap::TileMap( GameDataRef data, unsigned width, unsigned height ) : m_Data( std::move( data ) )
{
    m_GridSizeF = GRID_SIZE;
    m_GridSizeU = static_cast<unsigned>( m_GridSizeF );
    m_Layers = LAYERS;
    m_MapSize.x = width;
    m_MapSize.y = height;

    // Initialize map
    m_Map.resize( m_MapSize.x, std::vector< std::vector< Tile* > >() );

    for ( int x = 0; x < m_MapSize.x; x++ )
    {
        m_Map[x].resize( m_MapSize.y, std::vector< Tile* >() );

        for ( int y = 0; y < m_MapSize.y; y++ )
        {
            // m_Map[x][y].resize( m_Layers, new Tile( m_Data, x * m_GridSizeF, y * m_GridSizeF, m_GridSizeF ) );
            m_Map[x][y].resize( m_Layers, nullptr );
        }
    }

    m_TextureFile = TILES_TEXTURE_FILEPATH;

    m_Data->assets.LoadTexture( "Tiles", m_TextureFile );

}

TileMap::~TileMap()
{
    /*
    * Delete all the tiles
    */

   std::cout << "descturctor called map" << std::endl;

    for ( size_t x = 0; x < m_MapSize.x; x++ )
    {
        for ( size_t y = 0; y < m_MapSize.y; y++ )
        {
            for ( size_t z = 0; x < m_Layers; z++ )
            {
                delete m_Map[x][y][z];
            }
        }
    }
}

const std::string TileMap::GetTileSheet() const
{
    return "Tiles";
}

void TileMap::AddTile( const unsigned& x, const unsigned& y, const unsigned& z, const sf::IntRect& texture_rect )
{
    /*
        * Take 2 indices of mouse position and add a tile to that position
        * ignore if mouse's position is outside the limits of our map
        */
    
    if ( x < m_MapSize.x && x >= 0 &&
        y < m_MapSize.y && y >= 0 &&
        z < m_Layers && z >= 0 )
    {
        if ( m_Map[x][y][z] == nullptr )
        {
            /* No tile at this location. Okay to add. */
            m_Map[x][y][z] = new Tile( m_Data, x, y, m_GridSizeF, "Tiles", texture_rect );
        }
    }
}

void TileMap::RemoveTile( const unsigned& x, const unsigned& y, const unsigned& z )
{
    /*
        * Take 2 indices of mouse position and remove a tile from that position
        * ignore if mouse's position is outside the limits of our map
        */
    
    if ( x < m_MapSize.x && x >= 0 &&
        y < m_MapSize.y && y >= 0 &&
        z < m_Layers && z >= 0 )
    {
        if ( m_Map[x][y][z] != nullptr )
        {
            /* Found tile at this location, remove it. */
            delete m_Map[x][y][z];
            m_Map[x][y][z] = nullptr;
        }
    }
    
}

void TileMap::SaveToFile( const std::string file_name )
{
    /*
     * Format:
     * BASIC
     * Size x y
     * gridSize
     * layers
     * texture file
     * 
     * ALL TILES
     * gridPos x y
     * Texture Rect x y
     * collision, type
    */

   std::ofstream out_file;
   out_file.open( file_name );

    if( out_file.is_open() )
    {
        // std::cout << "saving to file" << std::endl;
        out_file << m_MapSize.x << " " << m_MapSize.y << '\n'
            << m_GridSizeU << '\n'
            << m_Layers << '\n'
            << m_TextureFile << '\n';

        for ( size_t x = 0; x < m_MapSize.x; x++ )
        {
            for ( size_t y = 0; y < m_MapSize.y; y++ )
            {
                for ( size_t z = 0; z < m_Layers; z++ )
                {
                    if ( m_Map[x][y][z] != nullptr )
                    {
                        // MAKE SURE TO REMOVE LAST SPACE
                        out_file << m_Map[x][y][z]->getAsString() << " ";
                    }
                }
            }
        }
    }
    else
    {
        Error( "ERROR: Tilemap couldn't be saved to file: ", file_name )
    }

    out_file.close();
   
}

void LoadFromFile( const std::string file_name )
{

}

void TileMap::Update()
{

}

void TileMap::Draw()
{
    for ( size_t x = 0; x < m_MapSize.x; x++ )
    {
        for ( size_t y = 0; y < m_MapSize.y; y++ )
        {
            for ( size_t z = 0; z < m_Layers; z++ )
            {
                if ( m_Map[x][y][z] != nullptr )
                {
                    m_Map[x][y][z]->Draw();
                }
            }
        }
    }
    
}