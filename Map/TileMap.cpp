#include "TileMap.h"


void TileMap::Clear()
{
    /*
    * Delete all the tiles
    */
    for ( size_t x = 0; x < m_MapSize.x; x++ )
    {
        for ( size_t y = 0; y < m_MapSize.y; y++ )
        {
            for ( size_t z = 0; z < m_Layers; z++ )
            {
                delete m_Map[x][y][z];
                m_Map[x][y][z] = nullptr;
            }
            m_Map[x][y].clear();
        }
        m_Map[x].clear();
    }
    m_Map.clear();
}

TileMap::TileMap( GameDataRef data, unsigned width, unsigned height, const std::string& texture_file ) : m_Data( std::move( data ) )
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

    m_TextureFile = texture_file;

    m_Data->assets.LoadTexture( "Tiles", m_TextureFile );

}

TileMap::~TileMap()
{
    Clear();
}

const std::string TileMap::GetTileSheet() const
{
    return "Tiles";
}

void TileMap::AddTile( const unsigned& x, const unsigned& y, const unsigned& z, const sf::IntRect& texture_rect, const bool& collision, const short& type )
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
            m_Map[x][y][z] = new Tile( m_Data, x, y, m_GridSizeF, "Tiles", texture_rect, collision, type );
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
                        out_file << x << " " << y << " " << z << " " << m_Map[x][y][z]->getAsString() << " ";
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

void TileMap::LoadFromFile( const std::string file_name )
{
    std::ifstream in_file;
   in_file.open( file_name );

    if( in_file.is_open() )
    {
        sf::Vector2u size;
        unsigned gridSize = 0;
        unsigned layers = 0;
        std::string texture_file = "";
        unsigned x = 0;
        unsigned y = 0;
        unsigned z = 0;
        unsigned texRectX = 0;
        unsigned texRectY = 0; 
        bool collision = false;
        short type = 0;

        // Load basic variables
        in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

        // Load tiles
        m_GridSizeF = static_cast<float>( gridSize );
        m_GridSizeU = gridSize;
        m_Layers = layers;
        m_MapSize.x = size.x;
        m_MapSize.y = size.y;
        m_TextureFile = texture_file;

        Clear();
        
        // Initialize map
        m_Map.resize( m_MapSize.x, std::vector< std::vector< Tile* > >() );

        for ( int x = 0; x < m_MapSize.x; x++ )
        {
            m_Map[x].resize( m_MapSize.y, std::vector< Tile* >() );

            for ( int y = 0; y < m_MapSize.y; y++ )
            {
                m_Map[x][y].resize( m_Layers, nullptr );
            }
        }

        m_Data->assets.LoadTexture( "Tiles", m_TextureFile );

        // Load all tiles
        while ( in_file >> x >> y >> z >> texRectX >> texRectY >> collision >> type )
        {
            m_Map[x][y][z] = new Tile( m_Data, x , y , m_GridSizeF, "Tiles", sf::IntRect( texRectX, texRectY, m_GridSizeU, m_GridSizeU ), collision, type );
        }

    }
    else
    {
        Error( "ERROR: Tilemap couldn't be loaded from file: ", file_name )
    }

    in_file.close();
 
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