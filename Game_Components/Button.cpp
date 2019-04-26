#include "Button.h"

namespace SSEngine
{
    Button::Button(SSEngine::GameDataRef data) : m_Data( std::move ( data ) )
    {
        m_ButtonState = eBtnIdle;
    }

    Button::~Button() = default;

    void Button::CreateButton( float x, float y, float width, float height)
    {
        m_Shape.setSize( sf::Vector2f( width, height ) );
        m_Shape.setPosition( sf::Vector2f( x, y ) );
    }

    void Button::SetButtonProperties(const std::string &fontName, const std::string &text,
                                     unsigned int characterSize,
                                     const std::vector<sf::Color>& textColors,
                                     const std::vector<sf::Color>& buttonColors,
                                     const std::vector< sf::Color >& outlineColors, unsigned short id )
    {
        m_ButtonState = eBtnIdle;
        m_Id = id;

        m_TextIdleColor = textColors[0];
        m_TextHoverColor = textColors[1];
        m_TextActiveColor = textColors[2];

        m_BtnIdleColor = buttonColors[0];
        m_BtnHoverColor = buttonColors[1];
        m_BtnActiveColor = buttonColors[2];

        m_OutlineIdleColor = outlineColors[0];
        m_OutlineHoverColor = outlineColors[1];
        m_OutlineActiveColor = outlineColors[2];

        m_Shape.setFillColor( m_BtnIdleColor );
        m_Shape.setOutlineColor( m_OutlineIdleColor );
        m_Shape.setOutlineThickness( 1 );

        m_Font = m_Data->assets.GetFont( fontName );
        m_Text.setFont( m_Font );
        m_Text.setString( text );
        //( 97, 143, 216 )
        m_Text.setFillColor( m_TextIdleColor );
        m_Text.setCharacterSize( characterSize );

        // Set in the middle of button
        m_Text.setPosition(
                m_Shape.getPosition().x +
                m_Shape.getGlobalBounds().width / 2.0f -
                m_Text.getGlobalBounds().width / 2.0f,
                m_Shape.getPosition().y +
                m_Shape.getGlobalBounds().height / 2.0f -
                m_Text.getGlobalBounds().height / 2.0f );


    }

    sf::RectangleShape &Button::GetButton()
    {
        return m_Shape;
    }

    const bool Button::isPressed() const
    {
        if ( m_ButtonState == eBtnActive)
        {
            return true;
        }
        return false;
    }

    const std::string Button::getText() const
    {
        return m_Text.getString();
    }

    const short unsigned& Button::getId() const
    {
        return m_Id;
    }

    void Button::setText( std::string text )
    {
        m_Text.setString( text );
    }

    void Button::setId( const short unsigned id )
    {
        m_Id = id;
    }

    void Button::Update(const sf::Vector2f& mousePosition)
    {
        // Update button hover with mouse position
        m_ButtonState = eBtnIdle;

        // Hover
        if( m_Shape.getGlobalBounds().contains( mousePosition ) )
        {
            m_ButtonState = eBtnHover;

            // Active
            if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
            {
                m_ButtonState = eBtnActive;
            }
        }

        // Set the button color
        switch ( m_ButtonState )
        {
            case eBtnIdle:
                m_Shape.setFillColor( m_BtnIdleColor );
                m_Text.setFillColor( m_TextIdleColor );
                m_Text.setOutlineColor( m_OutlineIdleColor );
                break;
            case eBtnHover:
                m_Shape.setFillColor( m_BtnHoverColor );
                m_Text.setFillColor( m_TextHoverColor );
                m_Text.setOutlineColor( m_OutlineHoverColor );
                break;
            case eBtnActive:
                m_Shape.setFillColor( m_BtnActiveColor );
                m_Text.setFillColor( m_TextActiveColor );
                m_Text.setOutlineColor( m_OutlineActiveColor );
                break;

            default:
                m_Shape.setFillColor( sf::Color::Red );
                m_Text.setFillColor( sf::Color::Blue );
                m_Text.setOutlineColor( sf::Color::Green );
                break;
        }

    }

    void Button::Draw()
    {
        m_Data->window.draw( m_Shape );
        m_Data->window.draw( m_Text );
    }
}