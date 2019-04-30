#include "TileMap.h"

namespace SSEngine
{
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


    }

    TileMap::~TileMap()
    {
        /*
         * Delete all the tiles
         */

        for ( auto& x : m_Map )
        {
            for ( auto& y : x )
            {
                for ( auto& z : y )
                {
                    delete z;
                }
            }
        }
    }

    void TileMap::AddTile( const unsigned& x, const unsigned& y, const unsigned& z )
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
                m_Map[x][y][z] = new Tile( m_Data, x, y, m_GridSizeF );
            }
        }
    }

    void TileMap::RemoveTile()
    {
        
    }


    void TileMap::Update()
    {

    }

    void TileMap::Draw()
    {
        for( auto& x : m_Map )
        {
            for( auto& y : x )
            {
                for( auto& z : y )
                {
                    if ( z != nullptr )
                    {
                        z->Draw();
                    }
                }
            }
        }
        
    }
}