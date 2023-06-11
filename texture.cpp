#include "texture.h"
#include"window.h"
#include <iostream>

Texture::Texture(std::string path ) : m_textTexture(nullptr), m_width(0), m_height(0) {

}

Texture::Texture(std::string text, std::string fontPath, int size,SDL_Color color) {
	m_window = Window::getInstance(); 
	m_renderRect.x = 80;
	m_renderRect.y = 640;

	SDL_QueryTexture(m_textTexture, NULL,NULL, &m_width, &m_height);
    m_renderRect.w = m_width;
	m_renderRect.h = m_height;

}

Texture::~Texture() {
	SDL_DestroyTexture(m_textTexture);
	m_textTexture = NULL;
	m_window= NULL;
}

void Texture::SetPosition(int x, int y) {
	mPosition.at(0) = x;
	mPosition.at(1) = y;
}

void Texture::Render() {
	SDL_RenderCopy(&m_window->getRenderer(), m_textTexture, NULL, &m_renderRect);
	
 }

SDL_Rect* Texture::GetRenderRect() { return &m_renderRect; }

void Texture::renderText(const std::string& text, SDL_Color color , std::string filename, int size) {
	SDL_Surface* surface = TTF_RenderText_Solid(AssetManager::GetInstance()->GetFont(filename,size), text.c_str(), color);
	if (surface == NULL && TTF_GetError()!= "Text has zero width") {
		printf("Error in text render:%s\n", TTF_GetError());
		return ;
	}
	m_height = surface->h;
	m_width  = surface->w;
	m_renderRect.w = surface->w;
	m_renderRect.h = surface->h;
	
	SDL_SetRenderDrawColor(&Window::getInstance()->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(&Window::getInstance()->getRenderer(), &m_renderRect);
	m_textTexture = SDL_CreateTextureFromSurface(&Window::getInstance()->getRenderer(), surface);
	SDL_RenderCopy(&Window::getInstance()->getRenderer(), m_textTexture, NULL, &m_renderRect);
	SDL_FreeSurface(surface);
}
 