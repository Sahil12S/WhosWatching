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

            sf::RectangleShape m_Bounds;
            sf::Sprite m_Sheet;

        public:
            TextureSelector( GameDataRef data, float x, float y, float width, float height, const std::string& texture_sheet );
            ~TextureSelector();

            void Update();
            void Draw();
    };
}
#endif // TEXTURE_SELECTOR_H