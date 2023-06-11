#pragma once
#include "GameEntity.h"
#include "window.h"
#include<SDL.h>
#include "AssetManager.h"


class Texture  {
private:
	SDL_Texture* m_textTexture;
	int m_height;
	int m_width;
	SDL_Rect m_renderRect;
	Window* m_window;
	std::vector<int>mPosition;
public:
	Texture(std::string);
	Texture(std::string text, std::string fontPath, int size, SDL_Color color);
	~Texture();
	void renderText(const std::string& text, SDL_Color color, std::string filename, int size);
	SDL_Rect* GetRenderRect();
	void SetPosition(int x, int y);
	virtual void Render();

};

