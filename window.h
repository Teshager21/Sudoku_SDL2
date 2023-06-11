#pragma once
#include<string>
#include<SDL.h>
#include<array>
#include<SDL_ttf.h>

#define fps 2
#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700

class Window {
private:
	Window(const std::string& title, int width, int height);
	~Window();
public:
	
	bool init();
	void CapFrameRate(Uint32 starting_tick);
	inline bool isClosed() const { return m_running; };
	double getCellSize();
	int drawGrid();
	void handleCursorKeys(SDL_Event& event);
	SDL_Renderer& getRenderer();
	void drawCursor();
	int getCursorPos(int x);
	bool getState();
	void setState(bool state);
	void getSurface();
	SDL_Rect& GetMemberOfGrayRects(int x);
	void SetMemberOfGrayRects(int pos, int x, int y);
	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);
	void ClearBackBuffer();
	void DrawTextTexture(SDL_Texture* texture);
	virtual void Render();
	static Window* getInstance();
	
private:
		
		std::string m_title;
		int m_width=700;
		int m_height=700;
		int m_cellSize=60;
		int m_cursorPos[2] = { 20 + m_cellSize,20 + m_cellSize };

		bool m_running = true;
		SDL_Window *m_window=nullptr;
		SDL_Renderer *m_renderer;
		SDL_Surface* m_surface = nullptr;
		std::array<SDL_Rect,30> m_grayRects;
		static Window* sInstance;
};


