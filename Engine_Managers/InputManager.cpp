#include "InputManager.h"

namespace SSEngine
{
InputManager::InputManager()
{
    Debug( "Input Manager Initialized" )
    InitKeys();
    m_KeyTime = 0.f;
    m_KeyTimeMax = 20.f;
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
    else
    {
        Error( "Input Manager: Key binding file not found", GENERAL_KEY_BIND_FILEPATH )
    }
    

    ifs.close();

    Debug( "Input Manager: Initializing default key binds" )
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
    m_MousePosGrid = sf::Vector2u (
        static_cast<unsigned>( m_MousePosView.x ) / static_cast<unsigned>( GRID_SIZE ),
        static_cast<unsigned>( m_MousePosView.y ) / static_cast<unsigned>( GRID_SIZE )
    );

}

void InputManager::UpdateKeyTime( const float& dt )
{
    if ( m_KeyTime < m_KeyTimeMax)
    {
        m_KeyTime += 100.f * dt;
    }  
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

sf::Vector2u InputManager::GetGridMousePosition()
{
    return m_MousePosGrid;
}

const bool InputManager::GetKeyTime()
{
    if ( m_KeyTime >= m_KeyTimeMax )
	{
		m_KeyTime = 0.f;
		return true;
	}

	return false;
}

}