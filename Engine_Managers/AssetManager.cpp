#include "AssetManager.h"

AssetManager::AssetManager() = default;

AssetManager::~AssetManager() = default;

void AssetManager::LoadTexture(const std::string& name, const std::string& fileName)
{
    sf::Texture tex;

    if ( tex.loadFromFile( fileName ) )
    {
        m_Textures[name] = tex;
    }
    else
    {
        Error( "Error reading texture file", fileName )
        exit( -1 );
    }
}

sf::Texture& AssetManager::GetTexture(const std::string& name)
{
    try
    {
        return m_Textures.at( name );
    }
    catch ( std::exception& e)
    {
        Error( "No entry found for texture with name", name )
        exit( -1 );
    }
}

void AssetManager::LoadFont(const std::string& name, const std::string& fileName)
{
    sf::Font font;

    if ( font.loadFromFile( fileName ) )
    {
        m_Fonts[name] = font;
        // Debug( "Loaded font " + name )
    }
    else
    {
        Error( "Error reading font file", fileName )
        exit( -1 );
    }
}

sf::Font& AssetManager::GetFont(const std::string& name)
{
    try
    {
        return m_Fonts.at( name );
    }

    catch ( std::exception& e)
    {
        Error( "No entry found for font with name", name )
        exit( -1 );
    }
}

void AssetManager::LoadAudio(const std::string& name, const std::string& fileName)
{
    sf::SoundBuffer sb;

    if ( sb.loadFromFile( fileName ))
    {
        m_Audios[name] = sb;
    }
    else
    {
        Error( "Error reading audio file", fileName )
        exit( -1 );
    }
}

sf::SoundBuffer& AssetManager::GetAudio(const std::string& name)
{
    try
    {
        return m_Audios.at(name);
    }
    catch ( std::exception& e)
    {
        Error( "No entry found for audio with name", name )
        exit( -1 );
    }
}