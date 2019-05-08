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

    bool isQuestion;

    void InitVariables();
    void InitTexture();
    void InitButtons();

public:
    Callout( GameDataRef data, const std::string& font_name, const std::string& texture_file );
    virtual ~Callout();

    bool IsButtonPressed( const std::string& key );
    void AddButton( 
        const std::string key, 
        const float y, 
        const std::string text );

    void Update( const sf::Vector2i& mousePosWindow, const std::string& text );
    void Draw( sf::RenderTarget& target );
};


#endif // CALLOUT_H