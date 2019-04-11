#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace SSEngine
{
    class InputManager
    {
    public:
        InputManager();
        ~InputManager();

        bool IsSpriteClicked( const sf::Sprite& object, sf::Mouse::Button button, sf::RenderWindow& window );

        void InitKeys();

        void UpdateMousePosition(sf::RenderWindow &window);
        sf::Vector2i GetScreenMousePosition();
        sf::Vector2i GetWindowMousePosition();
        sf::Vector2f GetViewMousePosition();

        std::map<std::string, int>& getSupportedKeys();

    private:
        /*
         * Key map so that player can change key bindings
         */
        std::map<std::string, int> m_SupportedKeys;

        sf::Vector2i m_MousePosScreen;
        sf::Vector2i m_MousePosWindow;
        sf::Vector2f m_MousePosView;

    };
}