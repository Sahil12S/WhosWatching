#include "InputManager.h"

namespace SSEngine
{
    InputManager::InputManager()
    {
        Debug( "Input Manager Initialized" )
        InitKeys();
    }

    InputManager::~InputManager() = default;

    bool InputManager::IsSpriteClicked(const sf::Sprite& object, sf::Mouse::Button button, sf::RenderWindow &window)
    {
        if ( sf::Mouse::isButtonPressed( button ) )
        {
            // Draw a rectangle across sprite
            sf::IntRect buttonRect ( (int)object.getPosition().x, (int)object.getPosition().y,
                                     (int)object.getGlobalBounds().width, (int)object.getGlobalBounds().height );

            if ( buttonRect.contains( sf::Mouse::getPosition( window ) ) )
            {
                return true;
            }
        }
        return false;
    }

    void InputManager::InitKeys()
    {
        std::ifstream ifs ( GENERAL_KEY_BIND_FILEPATH );

        if ( ifs.is_open() )
        {
            std::string key;
            int keyValue = 0;

            while ( ifs >> key >> keyValue )
            {
                m_SupportedKeys[key] = keyValue;
            }
        }

        ifs.close();

        Debug( "Default Key binds initialized" )
    }

    std::map<std::string, int>& InputManager::getSupportedKeys()
    {
        return m_SupportedKeys;
    }

    void InputManager::UpdateMousePosition(sf::RenderWindow &window)
    {
        m_MousePosScreen = sf::Mouse::getPosition();
        m_MousePosWindow = sf::Mouse::getPosition( window );
        m_MousePosView = window.mapPixelToCoords( sf::Mouse::getPosition( window ) );
    }

    sf::Vector2i InputManager::GetScreenMousePosition()
    {
        return m_MousePosScreen;
    }

    sf::Vector2i InputManager::GetWindowMousePosition()
    {
        return m_MousePosWindow;
    }

    sf::Vector2f InputManager::GetViewMousePosition()
    {
        return m_MousePosView;
    }
}