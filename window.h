#pragma once
#include<string.h>
#include<SDL2/SDL.h>
#include<string>
#include<strings.h>
#include<array>
#include<SDL2/SDL_ttf.h>

#define fps 2
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

class Window {
private:
	Window(const std::string& title, int width, int height);
	~Window();

public:
	int m_margin=80;
public:
	
	bool init();
	void CapFrameRate(Uint32 starting_tick);
	inline bool isClosed() const { return m_running; };
	int getCellSize();
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
	void handleMouseClicks(SDL_Event& event);
	
private:
		
		std::string m_title;
		int m_width=700;
		int m_height=700;
		int m_cellSize=80;
		
		int m_cursorPos[2] = { m_margin,m_margin };

		bool m_running = true;
		SDL_Window *m_window=nullptr;
		SDL_Renderer *m_renderer;
		SDL_Surface* m_surface = nullptr;
		std::array<SDL_Rect,30> m_grayRects;
		static Window* sInstance;
};


