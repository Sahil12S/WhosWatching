#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace SSEngine
{
    class AssetManager
    {
    public:
        AssetManager();
        ~AssetManager();

        void LoadTexture( const std::string& name, const std::string& fileName );
        sf::Texture& GetTexture( const std::string& name );

        void LoadFont( const std::string& name, const std::string& fileName );
        sf::Font& GetFont( const std::string& name );

        void LoadAudio( const std::string& name, const std::string& fileName );
        sf::SoundBuffer& GetAudio( const std::string& name );


    private:
        std::map<std::string, sf::Texture> m_Textures;
        std::map<std::string, sf::Font> m_Fonts;
        std::map<std::string, sf::SoundBuffer> m_Audios;
    };
}