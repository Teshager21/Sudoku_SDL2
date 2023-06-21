#include "texture.h"
#include <iostream>

Texture::Texture(std::string path ){

}

Texture::Texture(std::string text, std::string fontPath, int size,SDL_Color color) {
	m_textTexture=nullptr;
	m_window = Window::getInstance();
	m_font = AssetManager::GetInstance()->GetFont(fontPath, size);
	m_color = color;
	m_text = text;
	m_surface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_color);	
	//SDL_Color backgroundColor = { 0, 0, 0,1 }; // black color
	//SDL_FillRect(m_surface, NULL, SDL_MapRGBA(m_surface->format, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a));
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
void Texture::SetDrawColor(SDL_Color color) {
	m_drawColor = color;
}
void Texture::renderText() {
	m_renderRect.w = m_surface->w;
	m_renderRect.h = m_surface->h;
	//if(&m_drawColor==nullptr)
		SDL_SetRenderDrawColor(&m_window->getRenderer(), 255, 255, 255, 0);
		
	//else {
		///*Uint8 r, g, b, a;
		
		/*Uint32 pixel = SDL_MapRGBA(m_surface->format, m_drawColor.r, m_drawColor.g, m_drawColor.b, m_drawColor.a);
		std::cout << std::endl << "Colors are: " << m_drawColor.b << std::endl; */
		/*SDL_GetRGBA(pixel, m_surface->format, &r, &g, &b, &a);*/
		/*SDL_SetRenderDrawColor(&m_window->getRenderer(), 0, 0, 0, 0);
		std::cout << std::endl<<"Colors are: " << r << " " << g << " " << b << " " << a << std::endl;*/
	//}
		/*SDL_FillRect(m_surface, NULL, pixel);*/
	
	SDL_RenderDrawRect(&m_window->getRenderer(), &m_renderRect);
	m_textTexture = SDL_CreateTextureFromSurface(&m_window->getRenderer(), m_surface);
	SDL_RenderCopy(&m_window->getRenderer(), m_textTexture, NULL, &m_renderRect);
	SDL_FreeSurface(m_surface);
}
 