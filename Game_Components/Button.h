#ifndef BUTTON_H
#define BUTTON_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "../Game.h"

namespace SSEngine
{
    class Button
    {
    private:
        GameDataRef m_Data;

        // Shape of our button
        sf::RectangleShape m_Shape;

        // Text font for button
        sf::Font m_Font;

        // Text for button
        sf::Text m_Text;

        sf::Color m_TextIdleColor;
        sf::Color m_TextHoverColor;
        sf::Color m_TextActiveColor;

        sf::Color m_BtnIdleColor;
        sf::Color m_BtnHoverColor;
        sf::Color m_BtnActiveColor;

        unsigned short m_ButtonState;

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
        void SetButtonProperties( const std::string& fontName, const std::string& text,
                                  unsigned int characterSize,
                                  const std::vector<sf::Color>& textColors,
                                  const std::vector< sf::Color >& buttonColors );

        sf::RectangleShape& GetButton();

        // Accessors
        const bool isPressed() const;
        const std::string getText() const;

        // Modifiers
        void setText( std::string text );

        void Update( const sf::Vector2f& mousePosition );

        // Draw the button
        void Draw();


    };
}

#endif // BUTTON_H