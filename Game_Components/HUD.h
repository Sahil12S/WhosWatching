#pragma once

#include <SFML/Graphics.hpp>
#include "../Game.h"

namespace SSEngine
{
    class HUD
    {
    public:
        HUD( GameDataRef data );

        void SetTitle( const std::string& fontName, const std::string& text );

        void Draw( bool isTitle = false);
        void UpdateText( std::string& text );

    private:
        GameDataRef m_Data;

        sf::Text m_Title;
        sf::Text m_Text;
    };
}
