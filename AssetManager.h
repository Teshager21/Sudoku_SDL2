#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H
#include<map>
#include "window.h"

class AssetManager {

	static AssetManager* sInstance;
	
public:
	
	std::map<std::string, SDL_Texture*> m_textTextures;
	std::map<std::string, TTF_Font*> mFonts;
private:
	AssetManager();
	~AssetManager();
	
public:
	static AssetManager* GetInstance();
	TTF_Font* GetFont(std::string filename, int size);
};


#endif
