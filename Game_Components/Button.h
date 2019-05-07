#ifndef BUTTON_H
#define BUTTON_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "../Game.h"

namespace gui
{

    class Button
    {
    private:
        GameDataRef m_Data;

        // Button
        sf::RectangleShape m_Shape;
        sf::Font m_Font;
        sf::Text m_Text;

        sf::Color m_TextIdleColor;
        sf::Color m_TextHoverColor;
        sf::Color m_TextActiveColor;

        sf::Color m_BtnIdleColor;
        sf::Color m_BtnHoverColor;
        sf::Color m_BtnActiveColor;

        sf::Color m_OutlineIdleColor;
        sf::Color m_OutlineHoverColor;
        sf::Color m_OutlineActiveColor;

        unsigned short m_ButtonState;
        unsigned short m_Id;

    public:
        Button( GameDataRef data );
        ~Button();

        /*
        * Set properties of button you want to draw
        * Position x, y
        * Width and Height
        * Text, font type
        * Vector of colors ( or we can set them same for all buttons )
        */
        void CreateButton( float x, float y, float width, float height );
        void SetButtonProperties( const sf::Font& font, const std::string& text,
                                unsigned int characterSize,
                                const std::vector<sf::Color>& textColors,
                                const std::vector< sf::Color >& buttonColors,
                                const std::vector< sf::Color >& outlineColors = { sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent },
                                unsigned short id = 0 );

        sf::RectangleShape& GetButton();

        // Accessors
        bool isPressed() const;
        const std::string getText() const;
        const short unsigned& getId() const;

        // Modifiers
        void setText( std::string text );
        void setId( const short unsigned id );

        void Update( const sf::Vector2f& mousePosition );

        // Draw the button
        void Draw( sf::RenderTarget& target );


    };

}
#endif // BUTTON_H