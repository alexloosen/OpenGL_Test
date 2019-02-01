#include "TextureCache.h"
#include "ImageLoader.h"

TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string texturePath)
{

	auto mapIterator = _textureMap.find(texturePath);
	if (mapIterator == _textureMap.end())
	{
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);
		_textureMap.insert(make_pair(texturePath,newTexture));
		return newTexture;
	}
	return mapIterator->second;
}
