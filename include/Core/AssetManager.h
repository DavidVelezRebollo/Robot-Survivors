#pragma once

#include <string>
#include <unordered_map>

namespace sf
{
	class Texture;
}

class AssetManager
{
	public:

		static AssetManager* getInstance();

		~AssetManager();

		void clear();

		sf::Texture* loadTexture(const char* assetPath);
		void unloadTextures();

		sf::Texture* getTexture(const char* assetPath) const;


	private:

		static AssetManager* s_instance;

		std::unordered_map<std::string, sf::Texture*> m_texturePathToTexture;
};