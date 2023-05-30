#pragma once
#include "window.h"
#include "model.h"

class Controller{

	Model& model;
	Window& window;

public:
	Controller(Model& model, Window& window);
	~Controller();
	void handleKeyEvents(int selectedValue, SDL_Rect& cursor);
	void handleKeyboardEvents(SDL_Event& event, SDL_Rect& cursor, SDL_Rect& cursor2, SDL_Rect& cursor3 );
	void handleCursorKeys(SDL_Event& event, SDL_Rect& cursor, SDL_Rect& cursor2, SDL_Rect& cursor3);

};