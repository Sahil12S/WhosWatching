#ifndef TEXTURE_SELECTOR_H
#define TEXTURE_SELECTOR_H

#include "../pch.cpp"
#include "../Game.h"


namespace gui
{
    class Game;

    class TextureSelector
    {
        private:
            GameDataRef m_Data;

            float m_GridSize;
            bool m_Active;

            sf::RectangleShape m_Bounds;
            sf::Sprite m_Sheet;

            sf::RectangleShape m_Selector;
            sf::Vector2u m_MousePosGrid;
            sf::IntRect m_TextuerRect;
            

        public:
            TextureSelector( GameDataRef data, float x, float y, float width, float height, const std::string& texture_sheet );
            ~TextureSelector();

            // Accessors
            const bool& GetActive() const;

            void Update( const sf::Vector2i& mousePostion );
            void Draw();
    };
}
#endif // TEXTURE_SELECTOR_H