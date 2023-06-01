#pragma once
#include "window.h"
#include "model.h"

class Controller{

	Model& model;
	Window& window;

public:
	Controller(Model& model, Window& window);
	~Controller();
	void handleKeyEvents(int selectedValue, Window& window);
	void handleKeyboardEvents(SDL_Event& event);
	void pollEvents(SDL_Event& event, bool& running, int(&cursorPos)[2]);
	void renderTable(Window& window, Model& model);


}; 