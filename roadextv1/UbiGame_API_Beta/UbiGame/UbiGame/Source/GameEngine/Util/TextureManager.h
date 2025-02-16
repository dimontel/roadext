#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
	//TODO - if needed, move out of Engine part to some sort of loader on the game side of things
	namespace eTexture
	{
		enum type
		{
			None = -1,
			Player = 0,
			Tileset,
			BG,
			Particles,
			Phone,
			Finger,
			PhoneLong,
			PhoneRing,
			Smile,
			Count
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
		switch (texture)
		{
		case eTexture::Player:    return "player.png";
		case eTexture::Tileset:   return "tileset.png";
		case eTexture::BG:		  return "bg.png";
		case eTexture::Particles: return "particles.png";
		case eTexture::Phone: return "phone2.png";
		case eTexture::Finger: return "finger.png";
		case eTexture::PhoneLong: return "phone2.png";
		case eTexture::PhoneRing: return "ring.png";
		case eTexture::Smile: return "face.png";


		default:       return "UnknownTexType";
		}
	}

	class TextureManager
	{
	public:
		static TextureManager* GetInstance() { if (!sm_instance) sm_instance = new TextureManager(); return sm_instance; }
		~TextureManager();

		void LoadTextures();
		void UnLoadTextures();

		sf::Texture* GetTexture(eTexture::type texture) const { return m_textures[(int)texture]; }

	private:
		TextureManager();
		static TextureManager* sm_instance;

		sf::Texture* m_textures[eTexture::Count];
	};
}

namespace TextureHelper
{
	static sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture)
	{
		switch (texture)
		{
		case  GameEngine::eTexture::Player:  return sf::Vector2f(32.f, 32.f);
		case  GameEngine::eTexture::Tileset: return sf::Vector2f(32.f, 32.f);
		case  GameEngine::eTexture::BG:	     return sf::Vector2f(500.f, 500.f);
		case  GameEngine::eTexture::Particles: return sf::Vector2f(31.f, 32.f);
		case  GameEngine::eTexture::Phone: return sf::Vector2f(300.f, 660.f);
		case GameEngine::eTexture::Finger: return sf::Vector2f(29.f, 29.f);
		case GameEngine::eTexture::PhoneLong: return sf::Vector2f(300.f, 660.f);
		case GameEngine::eTexture::PhoneRing: return sf::Vector2f(134.f, 134.f);
		case GameEngine::eTexture::Smile: return sf::Vector2f(200.f, 200.f);


		default:							 return sf::Vector2f(-1.f, -1.f);
		}
	}
}

