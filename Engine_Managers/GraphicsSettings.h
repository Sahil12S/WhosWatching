#ifndef GRAPHICS_SETTINGS_H
#define GRAPHICS_SETTINGS_H

#include "../pch.cpp"

namespace SSEngine
{
class GraphicsSettings
{
    private:

    public:
    GraphicsSettings();

    // Variables
    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    void SaveToFile( const std::string& path );
    void LoadFromFile( const std::string& path );
            
};
}

#endif // GRAPHICS_SETTINGS_H