#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

class InputManager
{
private:
    /*
        * Key map so that player can change key bindings
        */
    std::map<std::string, int> m_SupportedKeys;

    sf::Vector2i m_MousePosScreen;
    sf::Vector2i m_MousePosWindow;
    sf::Vector2f m_MousePosView;
    sf::Vector2i m_MousePosGrid;

    float m_KeyTime;
    float m_KeyTimeMax;

public:
    InputManager();
    ~InputManager();

    bool IsSpriteClicked( const sf::Sprite& object, sf::Mouse::Button button, sf::RenderWindow& window );

    void InitKeys();

    void UpdateMousePosition(sf::RenderWindow &window, sf::View* view = nullptr);
    void UpdateKeyTime( const float& dt );

    sf::Vector2i GetScreenMousePosition();
    sf::Vector2i GetWindowMousePosition();
    sf::Vector2f GetViewMousePosition();
    sf::Vector2i GetGridMousePosition();
    const bool GetKeyTime();

    std::map<std::string, int>& getSupportedKeys();
};

#endif // INPUT_MANAGER_H