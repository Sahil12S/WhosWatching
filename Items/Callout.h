#ifndef CALLOUT_H
#define CALLOUT_H

#include "../pch.cpp"
#include "../Game.h"
#include "../Game_Components/Button.h"

class Callout
{
private:
    GameDataRef m_Data;

    sf::RectangleShape m_Background;
    sf::Sprite sprite;

    sf::Text m_Text;
    sf::Font font;

    std::map< std::string, gui::Button* > m_Buttons;

public:
    Callout( GameDataRef data, const std::string& font_name, const std::string& texture_file );
    virtual ~Callout();

    void Update();
    void Draw( sf::RenderTarget& target, const std::string& text );
};


#endif // CALLOUT_H