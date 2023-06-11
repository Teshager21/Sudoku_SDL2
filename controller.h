#pragma once
#include "window.h"
#include "model.h"
#include"texture.h"
#include "AssetManager.h"

class Controller{

	Model& model;
	Window* mWindow;
	Texture* m_textTexture;
	AssetManager* mAssetManager;

public:
	Controller(Model& model);
	~Controller(); 
	bool run();
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