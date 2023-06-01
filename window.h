#pragma once
#include<string>
#include<SDL.h>
class Window {
public:
	Window(const std::string &title, int width, int height);
	~Window();
	bool init();
	inline bool isClosed() const { return m_running; };
	double getCellSize();
	int drawGrid();
	void handleCursorKeys(SDL_Event& event);
	SDL_Renderer& getRenderer();
	void drawCursor();
	int getCursorPos(int x);
	bool getState();
	void setState(bool state);
private:
		std::string m_title;
		int m_width=700;
		int m_height=700;
		int m_cellSize=60;
		int m_cursorPos[2] = { 20 + m_cellSize,20 + m_cellSize };

		bool m_running = true;
		SDL_Window *m_window=nullptr;
		SDL_Renderer *m_renderer;
};


