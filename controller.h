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
	void pollEvents(SDL_Event& event,Window& window);
	void renderTable(Window& window, Model& model);
	void displayMessage(Window& window, Model& model);


}; 