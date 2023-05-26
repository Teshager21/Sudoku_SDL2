#pragma once
#include<string>
#include<SDL.h>
class Window {
	Window(const std::string &title, int width, int height);
	~Window();
	bool init();
	inline bool isClosed() const { return m_closed; };
private:
		std::string m_title;
		int m_width=700;
		int m_height=700; 

		bool m_closed = false;
		SDL_Window *m_window=nullptr;




};