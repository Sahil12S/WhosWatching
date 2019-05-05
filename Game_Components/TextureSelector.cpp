#include "TextureSelector.h"

namespace gui
{
    TextureSelector::TextureSelector( GameDataRef data, float x, float y, float width, float height, const std::string& texture_sheet ) :
        m_Data( std::move( data ) )
    {
        m_GridSize = GRID_SIZE;
        m_Active = false;
        m_Hidden = false;
        float offset = 60.f;
        
        m_Bounds.setPosition( x + offset, y );
        m_Bounds.setSize( sf::Vector2f( width, height ) );
        m_Bounds.setFillColor( sf::Color( 50, 50, 50, 100 ) );
        m_Bounds.setOutlineThickness( 1.f );
        m_Bounds.setOutlineColor( sf::Color( 255, 255, 255, 200 ) );

        m_Sheet.setTexture( m_Data->assets.GetTexture( texture_sheet ) );
        m_Sheet.setPosition( x + offset, y );

        /*
         * Check if our bounds is well within available size of sheet
         * If it is, then set the texture
         */

        if ( m_Sheet.getGlobalBounds().width > m_Bounds.getGlobalBounds().width )
        {
            m_Sheet.setTextureRect( sf::IntRect( 0, 0, m_Bounds.getGlobalBounds().width, m_Sheet.getGlobalBounds().height ) );
        }

        if ( m_Sheet.getGlobalBounds().height > m_Bounds.getGlobalBounds().height )
        {
            m_Sheet.setTextureRect( sf::IntRect( 0, 0, m_Sheet.getGlobalBounds().width, m_Bounds.getGlobalBounds().height ) );
        }

        m_Selector.setPosition( x + offset, y );
        
        // Do we need to pass this value from parameter?
        m_Selector.setSize( sf::Vector2f ( m_GridSize, m_GridSize ) );
        m_Selector.setFillColor( sf::Color::Transparent );
        m_Selector.setOutlineThickness( 1.f );
        m_Selector.setOutlineColor( sf::Color::Red );

        m_TextuerRect.width = static_cast<int>( m_GridSize );
        m_TextuerRect.height = static_cast<int>( m_GridSize );


        // Drawing the button
        m_HideBtn = new gui::Button( m_Data );

        m_HideBtn->CreateButton(  20.f, 20.f, 30.f, 30.f );

        std::vector<sf::Color> textColor = { sf::Color( TEXT_IDLE_FILL_COLOR ),
                                                sf::Color( TEXT_HOVER_FILL_COLOR ),
                                                sf::Color( TEXT_ACTIVE_FILL_COLOR ) };

        std::vector<sf::Color> buttonColor = { sf::Color( BUTTON_IDLE_FILL_COLOR ),
                                                sf::Color( BUTTON_HOVER_FILL_COLOR ),
                                                sf::Color( BUTTON_ACTIVE_FILL_COLOR ) };

        m_Data->assets.LoadFont( "Button Font", BUTTON_FONT_FILEPATH );

        m_HideBtn->SetButtonProperties( "Button Font", "TS", 30.f, textColor, buttonColor );
    }

    TextureSelector::~TextureSelector()
    {
        delete m_HideBtn;
    }

    const bool& TextureSelector::GetActive( ) const
    {
        return m_Active;
    }

    const sf::IntRect& TextureSelector::GetTextureRect() const
    {
        return m_TextuerRect;
    }

    void TextureSelector::Update( const float& dt, const sf::Vector2i& mousePostion )
    {
        m_Data->input.UpdateKeyTime( dt );
        m_HideBtn->Update( static_cast<sf::Vector2f>( mousePostion ) );

        // Button should be in editor state controlling texture selector.
        if ( m_HideBtn->isPressed() && m_Data->input.GetKeyTime() )
        {
            m_Hidden = !m_Hidden;
        }

        if ( !m_Hidden )
        {
            if( m_Bounds.getGlobalBounds().contains( static_cast<sf::Vector2f>( mousePostion ) ) )
            {
                m_Active = true;
            }
            else
            {
                m_Active = false;
            }
            
            if ( m_Active )
            {
                m_MousePosGrid.x = ( mousePostion.x - static_cast<int>( m_Bounds.getPosition().x ) ) / static_cast<unsigned>( m_GridSize );
                m_MousePosGrid.y = ( mousePostion.y - static_cast<int>( m_Bounds.getPosition().y ) ) / static_cast<unsigned>( m_GridSize );

                m_Selector.setPosition( 
                    m_Bounds.getPosition().x + m_MousePosGrid.x * m_GridSize,
                    m_Bounds.getPosition().y + m_MousePosGrid.y * m_GridSize
                );

                m_TextuerRect.left = static_cast<int>( m_Selector.getPosition().x - static_cast<int>( m_Bounds.getPosition().x ) );
                m_TextuerRect.top = static_cast<int>( m_Selector.getPosition().y - static_cast<int>( m_Bounds.getPosition().y ) );
            }
        }
    }

    void TextureSelector::Draw()
    {
        m_HideBtn->Draw();

        if ( !m_Hidden )
        {
            m_Data->window.draw( m_Bounds );
            m_Data->window.draw( m_Sheet );
            if( m_Active )
            {
                m_Data->window.draw( m_Selector );
            }
        }
    }
}