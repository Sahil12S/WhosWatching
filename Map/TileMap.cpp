#include "TileMap.h"

namespace SSEngine
{
    TileMap::TileMap( GameDataRef data ) : m_Data( std::move( data ) )
    {
        Debug( "Got in tileMap" )
        m_GridSizeF = GRID_SIZE;
        m_GridSizeU = static_cast<unsigned>( m_GridSizeF );
        m_Layers = LAYERS;
        m_MapSize.x = 30;
        m_MapSize.y = 18;

        // Initialize map
        m_Map.resize( m_MapSize.x, std::vector< std::vector< Tile* > >() );

        for ( int x = 0; x < m_MapSize.x; x++ )
        {
            m_Map[x].resize( m_MapSize.y, std::vector< Tile* >() );
            for ( int y = 0; y < m_MapSize.y; y++ )
            {
                m_Map[x][y].resize( m_Layers, new Tile( m_Data, x * m_GridSizeF, y * m_GridSizeF, m_GridSizeF ) );
            }
        }


    }

    TileMap::~TileMap()
    {
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
                    z->Draw();
                }
            }
        }
        
    }
}