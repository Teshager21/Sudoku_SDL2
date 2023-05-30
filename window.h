#pragma once
#include<string>
#include<SDL.h>
class Window {
public:
	Window(const std::string &title, int width, int height);
	~Window();
	bool init();
	inline bool isClosed() const { return m_closed; };
	void pollEvents();
	double getCellSize();
	int drawGrid();
private:
		std::string m_title;
		int m_width=700;
		int m_height=700;
		int m_cellSize=70;
		int m_cursorPos[2] = { 0,0 };

		bool m_closed = false;
		SDL_Window *m_window=nullptr;
		SDL_Renderer *m_renderer;
};


