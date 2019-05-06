#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "../Game.h"
#include "../Game_Components/Button.h"
#include "../Game_Components/HUD.h"


class PauseMenu
{
private:
    /* Variables */
    GameDataRef m_Data;

    gui::HUD* m_Hud;

    sf::RectangleShape m_Background;
	sf::RectangleShape m_Container;

    std::map<std::string, gui::Button*> m_Buttons;

    void InitTextures();
    void InitFonts();
    void InitVariables();


public:
    PauseMenu( GameDataRef data );
    virtual ~PauseMenu();

    std::vector<std::string, gui::Button*> GetButtons();


    const bool IsButtonPressed( const std::string& key );

    void AddButton( const std::string key, 
                const float y, 
                const std::string text );



    void Update( const sf::Vector2i& mousePosWindow );

    void Draw( sf::RenderTarget& target );
};

#endif // PAUSE_MENU_H