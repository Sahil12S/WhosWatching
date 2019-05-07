#include "TileMap.h"


void TileMap::Clear()
{
    /*
    * Delete all the tiles
    */
    for ( size_t x = 0; x < m_MaxSizeWorldGrid.x; x++ )
    {
        for ( size_t y = 0; y < m_MaxSizeWorldGrid.y; y++ )
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
    m_MaxSizeWorldGrid.x = width;
    m_MaxSizeWorldGrid.y = height;
    m_MaxSizeWorldF.x = static_cast<float>( width ) * GRID_SIZE;
    m_MaxSizeWorldF.y =  static_cast<float>( height ) * GRID_SIZE;

    fromX = 0;
    toX = 0;
    fromY = 0;
    toY = 0;
    layer = 0;

    // Initialize map
    m_Map.resize( m_MaxSizeWorldGrid.x, std::vector< std::vector< Tile* > >() );

    for ( int x = 0; x < m_MaxSizeWorldGrid.x; x++ )
    {
        m_Map[x].resize( m_MaxSizeWorldGrid.y, std::vector< Tile* >() );

        for ( int y = 0; y < m_MaxSizeWorldGrid.y; y++ )
        {
            // m_Map[x][y].resize( m_Layers, new Tile( m_Data, x * m_GridSizeF, y * m_GridSizeF, m_GridSizeF ) );
            m_Map[x][y].resize( m_Layers, nullptr );
        }
    }

    m_TextureFile = texture_file;

    m_Data->assets.LoadTexture( "Tiles", m_TextureFile );

    m_CollisionBox.setSize( sf::Vector2f( GRID_SIZE, GRID_SIZE ) );
    m_CollisionBox.setFillColor( sf::Color( 255, 0, 0, 50 ) );
    m_CollisionBox.setOutlineColor( sf::Color::Red );
    m_CollisionBox.setOutlineThickness( -1.f );
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
    
    if ( x < m_MaxSizeWorldGrid.x && x >= 0 &&
        y < m_MaxSizeWorldGrid.y && y >= 0 &&
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
    
    if ( x < m_MaxSizeWorldGrid.x && x >= 0 &&
        y < m_MaxSizeWorldGrid.y && y >= 0 &&
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
        out_file << m_MaxSizeWorldGrid.x << " " << m_MaxSizeWorldGrid.y << '\n'
            << m_GridSizeU << '\n'
            << m_Layers << '\n'
            << m_TextureFile << '\n';

        for ( size_t x = 0; x < m_MaxSizeWorldGrid.x; x++ )
        {
            for ( size_t y = 0; y < m_MaxSizeWorldGrid.y; y++ )
            {
                for ( size_t z = 0; z < m_Layers; z++ )
                {
                    if ( m_Map[x][y][z] != nullptr )
                    {
                        out_file << x << " " << y << " " << z << " " << m_Map[x][y][z]->GetAsString() << " ";
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
        m_MaxSizeWorldGrid.x = size.x;
        m_MaxSizeWorldGrid.y = size.y;
        m_TextureFile = texture_file;

        Clear();
        
        // Initialize map
        m_Map.resize( m_MaxSizeWorldGrid.x, std::vector< std::vector< Tile* > >() );

        for ( int x = 0; x < m_MaxSizeWorldGrid.x; x++ )
        {
            m_Map[x].resize( m_MaxSizeWorldGrid.y, std::vector< Tile* >() );

            for ( int y = 0; y < m_MaxSizeWorldGrid.y; y++ )
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

void TileMap::UpdateCollision( Entity* entity, const float& dt  )
{
    // Collision with window
    if( entity->GetPosition().x < 0.f )
    {
        entity->SetPosition( 0.f, entity->GetPosition().y );
        entity->StopVelocityX();
    }
    else if( entity->GetPosition().x + entity->GetGlobalBounds().width > m_MaxSizeWorldF.x )
    {
        entity->SetPosition( m_MaxSizeWorldF.x - entity->GetGlobalBounds().width, entity->GetPosition().y );
        entity->StopVelocityX();
    }
    
    if( entity->GetPosition().y < 0.f )
    {
        entity->SetPosition( entity->GetPosition().x, 0.f );
        entity->StopVelocityY();
    }
    else if( entity->GetPosition().y + entity->GetGlobalBounds().height > m_MaxSizeWorldF.y )
    {
        entity->SetPosition( entity->GetPosition().x, m_MaxSizeWorldF.y - entity->GetGlobalBounds().height );
        entity->StopVelocityY();
    }

    // Collision with tiles
    layer = 0;
    
    fromX = entity->GetGridPosition( m_GridSizeU ).x - 1;
    if( fromX < 0 )
    {
        fromX = 0;
    }
    else if ( fromX > m_MaxSizeWorldGrid.x )
    {
        fromX = m_MaxSizeWorldGrid.x;
    }

    toX = entity->GetGridPosition( m_GridSizeU ).x + 3;
    if( toX < 0 )
    {
        toX = 0;
    }
    else if ( toX > m_MaxSizeWorldGrid.x )
    {
        toX = m_MaxSizeWorldGrid.x;
    }

    fromY = entity->GetGridPosition( m_GridSizeU ).y - 1;
    if( fromY < 0 )
    {
        fromY = 0;
    }
    else if ( fromY > m_MaxSizeWorldGrid.y )
    {
        fromY = m_MaxSizeWorldGrid.y;
    }

    toY = entity->GetGridPosition( m_GridSizeU ).y + 3;
    if( toY < 0 )
    {
        toY = 0;
    }
    else if ( toY > m_MaxSizeWorldGrid.y )
    {
        toY = m_MaxSizeWorldGrid.y;
    }

    for ( size_t x = fromX; x < toX; x++ )
    {
        for ( size_t y = fromY; y < toY; y++ )
        {
            sf::FloatRect playerBounds = entity->GetGlobalBounds();
            sf::FloatRect wallBounds = m_Map[x][y][layer]->GetGlobalBounds();
            sf::FloatRect nextPositionBounds = entity->GetNextPositionBounds( dt );

            if(  m_Map[x][y][layer]->GetCollision() && m_Map[x][y][layer]->Intersects( nextPositionBounds ) )
            {
                // Bottom Collision
                if ( 
                    playerBounds.top < wallBounds.top &&
                    playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height &&
                    playerBounds.left < wallBounds.left + wallBounds.width &&
                    playerBounds.left + playerBounds.width > wallBounds.left 
                )
                {
                    entity->StopVelocityY();
                    entity->SetPosition( playerBounds.left, wallBounds.top - playerBounds.height );
                }
                // Top collision
                else if ( 
                    playerBounds.top > wallBounds.top &&
                    playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height &&
                    playerBounds.left < wallBounds.left + wallBounds.width &&
                    playerBounds.left + playerBounds.width > wallBounds.left 
                )
                {
                    entity->StopVelocityY();
                    entity->SetPosition( playerBounds.left, wallBounds.top + wallBounds.height );
                }

                // Right Collision
                if ( 
                    playerBounds.left < wallBounds.left &&
                    playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width && 
                    playerBounds.top < wallBounds.top + wallBounds.height &&
                    playerBounds.top + playerBounds.height > wallBounds.top
                )
                {
                    entity->StopVelocityX();
                    entity->SetPosition( wallBounds.left - playerBounds.width, playerBounds.top );
                }
                // Left collision
                else if ( 
                    playerBounds.left > wallBounds.left &&
                    playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width && 
                    playerBounds.top < wallBounds.top + wallBounds.height &&
                    playerBounds.top + playerBounds.height > wallBounds.top
                )
                {
                    entity->StopVelocityX();
                    entity->SetPosition (wallBounds.left + wallBounds.width, playerBounds.top );
                }
            }
        }
    }
}

void TileMap::Update()
{

}

void TileMap::Draw( sf::RenderTarget& target, Entity* entity )
{
    if ( entity )
    {
        layer = 0;

        fromX = entity->GetGridPosition( m_GridSizeU ).x - 1;
        if( fromX < 0 )
        {
            fromX = 0;
        }
        else if ( fromX > m_MaxSizeWorldGrid.x )
        {
            fromX = m_MaxSizeWorldGrid.x;
        }

        toX = entity->GetGridPosition( m_GridSizeU ).x + 3;
        if( toX < 0 )
        {
            toX = 0;
        }
        else if ( toX > m_MaxSizeWorldGrid.x )
        {
            toX = m_MaxSizeWorldGrid.x;
        }

        fromY = entity->GetGridPosition( m_GridSizeU ).y - 1;
        if( fromY < 0 )
        {
            fromY = 0;
        }
        else if ( fromY > m_MaxSizeWorldGrid.y )
        {
            fromY = m_MaxSizeWorldGrid.y ;
        }

        toY = entity->GetGridPosition( m_GridSizeU ).y + 3;
        if( toY < 0 )
        {
            toY = 0;
        }
        else if ( toY > m_MaxSizeWorldGrid.y )
        {
            toY = m_MaxSizeWorldGrid.y;
        }

        for ( size_t x = fromX; x < toX; x++ )
        {
            for ( size_t y = fromY; y < toY; y++ )
            {
                m_Map[x][y][layer]->Draw( target );
                if( m_Map[x][y][layer]->GetCollision() )
                {
                    m_CollisionBox.setPosition( m_Map[x][y][layer]->GetPosition() );
                    target.draw( m_CollisionBox );
                }
            }
        }
    }
    else
    {
        for ( size_t x = 0; x < m_MaxSizeWorldGrid.x; x++ )
        {
            for ( size_t y = 0; y < m_MaxSizeWorldGrid.y; y++ )
            {
                for ( size_t z = 0; z < m_Layers; z++ )
                {
                    if ( m_Map[x][y][z] != nullptr )
                    {
                        m_Map[x][y][z]->Draw( target );
                        if( m_Map[x][y][z]->GetCollision() )
                        {
                            m_CollisionBox.setPosition( m_Map[x][y][z]->GetPosition() );
                            target.draw( m_CollisionBox );
                        }
                    }
                }
            }
        }
    }
}