#include"AssetManager.h"
#include<iostream>
#include<string>

AssetManager* AssetManager::sInstance = nullptr;
AssetManager::AssetManager() {

}
AssetManager::~AssetManager() {

}


TTF_Font* AssetManager::GetFont(std::string filename, int size) {
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);
	std::string key = fullPath + (char)size;
	if (mFonts[key] == NULL) {
		mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);
		if (mFonts[key] == nullptr)
			printf("Error loading font: %s\n", TTF_GetError());
	}
	return mFonts[key];
}



 AssetManager* AssetManager:: GetInstance() {
	if (!sInstance) {
		sInstance = new AssetManager;
	}
	return sInstance;
}