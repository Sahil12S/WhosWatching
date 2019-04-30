#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
    title = "DEFAULT";
    resolution = sf::VideoMode::getDesktopMode();
    fullscreen = true;
    verticalSync = false;
    frameRateLimit = 120;
    contextSettings.antialiasingLevel = 0;
    videoModes = sf::VideoMode::getFullscreenModes();
}


// Save to file
void GraphicsSettings::SaveToFile( const std::string& path )
{
    std::ofstream ofs( "../" + path );

    if ( ofs.is_open() )
    {
        ofs << title;
        ofs << resolution.width << resolution.height;
        ofs << fullscreen;
        ofs << frameRateLimit;
        ofs << verticalSync;
        ofs << contextSettings.antialiasingLevel;
    }

    ofs.close();
}

// Load from file
void GraphicsSettings::LoadFromFile( const std::string& path )
{
    std::ifstream ifs( "../" + path );

    if ( ifs.is_open() )
    {
        std::getline( ifs, title );
        ifs >> resolution.width >> resolution.height;
        ifs >> fullscreen;
        ifs >> frameRateLimit;
        ifs >> verticalSync;
        ifs >> contextSettings.antialiasingLevel;
    }

    ifs.close();
}