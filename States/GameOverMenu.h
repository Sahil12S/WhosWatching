#ifndef GAME_OVER_MENU_H
#define GAME_OVER_MENU_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "../Game.h"
#include "../Game_Components/Button.h"
#include "../Game_Components/HUD.h"


class GameOverMenu
{
private:
    /* Variables */
    GameDataRef m_Data;

    gui::HUD* m_Hud;
    gui::HUD* message;

    sf::RectangleShape m_Background;
	sf::RectangleShape m_Container;

    std::map<std::string, gui::Button*> m_Buttons;

    std::vector<std::string> lossMessages;

    void fix_newlines( std::string& s );

    void InitTextures();
    void InitFonts();
    void InitVariables();
    void InitMessages();
    void InitGui();


public:
    GameOverMenu( GameDataRef data );
    virtual ~GameOverMenu();

    std::vector<std::string, gui::Button*> GetButtons();


    const bool IsButtonPressed( const std::string& key );

    void AddButton( const std::string key, 
                const float y, 
                const std::string text );

    void SetMessage( bool win, const std::string& s );

    void Update( const sf::Vector2i& mousePosWindow );

    void Draw( sf::RenderTarget& target );
};

#endif // GAME_OVER_MENU_H