#pragma once

#include "../pch.cpp"

#include "../Game.h"

namespace gui
{
    class HUD
    {
    private:
        GameDataRef m_Data;
        sf::Font font;
        
        sf::Vector2f offset;
        
        sf::Text m_Text;
    public:
        HUD( GameDataRef data );

        void SetText( const std::string& fontName, const std::string& text, const float& size, const float& x, const float& y  );

        void Move( const std::string& font, const float& x, const float& y );
        void Reset();

        void UpdateText( std::string& text );
        void Draw( sf::RenderTarget& target, bool isTitle = false);

    
    };
}