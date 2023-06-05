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
	void pollEvents(Window& window);
	void renderTable(Window& window, Model& model);
	void displayMessage(Window& window, Model& model);
	void grayFixedCells(Model& model, Window& window);
	void grayCell(int pos, Window& window);
	void displayArray(Window& window, Model& model, SDL_Color color);
	void displayFixedPositions(Window& window, Model& model);
	void displayVariablePositions(Window& window, Model& model);

}; 