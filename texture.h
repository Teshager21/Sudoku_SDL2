#pragma once
#include "GameEntity.h"
#include "AssetManager.h"


class Texture  {
private:
	SDL_Texture* m_textTexture;
	SDL_Surface* m_surface;
	SDL_Rect m_renderRect;
	Window* m_window;
	std::vector<int>mPosition;
	TTF_Font* m_font;
	SDL_Color m_color;
	std::string m_text;
public:
	Texture(std::string);
	Texture(std::string text, std::string fontPath, int size, SDL_Color color);
	~Texture();
	void renderText();
	SDL_Surface* GetSurface();
	void SetSrcRect(int x, int y);
	virtual void Render();


};

