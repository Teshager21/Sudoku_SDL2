#include "texture.h"
#include <iostream>

Texture::Texture(std::string path ) : m_textTexture(nullptr) {

}

Texture::Texture(std::string text, std::string fontPath, int size,SDL_Color color) {
	m_window = Window::getInstance();
	m_font = AssetManager::GetInstance()->GetFont(fontPath, size);
	m_color = color;
	m_text = text;
	m_surface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_color);	
	if (m_surface == NULL) {
		printf("Error in text render:%s\n", TTF_GetError());
		return;
	}
	if (m_surface == NULL && (strcmp(TTF_GetError(), "Text has zero width") != 0)) {
		printf("Error in text render:%s\n", TTF_GetError());
		return;
	}
}

Texture::~Texture() {
	SDL_DestroyTexture(m_textTexture);
	m_textTexture = NULL;
	m_window= NULL;
}

SDL_Surface* Texture::GetSurface() { return m_surface; }

void Texture::Render() {
	SDL_RenderCopy(&m_window->getRenderer(), m_textTexture, NULL, &m_renderRect);
 }

void Texture::SetSrcRect(int x, int y) {
	m_renderRect.x = x;
	m_renderRect.y = y;
}

void Texture::renderText() {
	m_renderRect.w = m_surface->w;
	m_renderRect.h = m_surface->h;
	
	SDL_SetRenderDrawColor(&m_window->getRenderer(), 255, 255, 255, 0);
	SDL_RenderDrawRect(&m_window->getRenderer(), &m_renderRect);
	m_textTexture = SDL_CreateTextureFromSurface(&m_window->getRenderer(), m_surface);
	SDL_RenderCopy(&m_window->getRenderer(), m_textTexture, NULL, &m_renderRect);
	SDL_FreeSurface(m_surface);
}
 