#ifndef TEXTURE_SELECTOR_H
#define TEXTURE_SELECTOR_H

#include "../pch.cpp"
#include "../Game.h"
#include "Button.h"

namespace gui
{
    class Game;

    class TextureSelector
    {
        private:
            GameDataRef m_Data;

            // Size of each tile
            float m_GridSize;
            // Check if texture selector is active ( mouse pointer is over it )
            bool m_Active;
            // Check if texture selector is hidden
            bool m_Hidden;

            // Button to toggle texture selector window
            gui::Button* m_HideBtn;

            // Bounds of texture selector area
            sf::RectangleShape m_Bounds;
            
            // To hold the sprite
            sf::Sprite m_Sheet;

            // Rectangle to select each tile
            sf::RectangleShape m_Selector;
            
            // Mouse position in grid
            sf::Vector2u m_MousePosGrid;
            sf::IntRect m_TextuerRect;
            

        public:
            TextureSelector( GameDataRef data, float x, float y, float width, float height, const std::string& texture_sheet );
            ~TextureSelector();

            // Accessors
            const bool& GetActive() const;
            const sf::IntRect& GetTextureRect() const;

            void Update( const float& dt, const sf::Vector2i& mousePostion );
            void Draw();
    };
}
#endif // TEXTURE_SELECTOR_H