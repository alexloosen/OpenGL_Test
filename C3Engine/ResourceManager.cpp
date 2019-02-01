#include "ResourceManager.h"

namespace C3Engine
{

	TextureCache ResourceManager::_textureCache;

	GLTexture ResourceManager::getTexture(std::string texturePath)
	{
		return _textureCache.getTexture(texturePath);
	}
}