#ifndef TEXTURE_SELECTOR_H
#define TEXTURE_SELECTOR_H

#include "../pch.cpp"
#include "../Game.h"

namespace gui
{
    class TextureSelector
    {
        private:
            GameDataRef m_Data;

            sf::RectangleShape m_Bouns;
            sf::Sprite m_Sprite;

        public:
            TextureSelector( GameDataRef m_Data, float x, float y, float width, float height, const std::string& texture_sheet );
            virtual ~TextureSelector();


    };
}
#endif // TEXTURE_SELECTOR_H