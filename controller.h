#pragma once
#include "window.h"
#include "model.h"

class Controller{

	Model& model;
	Window& window;

public:
	Controller(Model& model, Window& window);
	~Controller();
	void handleKeyEvents(int selectedValue, int (&cursorPos)[2]);
	void handleKeyboardEvents(SDL_Event& event, int (&cursorPos)[2]);
	void pollEvents(SDL_Event& event, bool& running, int(&cursorPos)[2]);


};