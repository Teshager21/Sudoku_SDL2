#pragma once
#include "window.h"
#include "model.h"
#include"texture.h"
#include "AssetManager.h"
#include <iostream>
#include "solver.h"

class Controller{

	Model* mModel;
	Window* mWindow;
	Texture* m_textTexture;
	AssetManager* mAssetManager;
	Solver* mSolver;

public:
	Controller();
	~Controller(); 
	bool run();
	void newGame();
	void handleKeyEvents(int selectedValue);
	void handleKeyboardEvents(SDL_Event& event);
	void pollEvents();
	void renderTable();
	void displayMessage();
	void grayFixedCells();
	void grayCell(int pos);
	void displayArray(SDL_Color color);
	void displayFixedPositions();
	void displayVariablePositions();
	void displayCandidates();
	void displayAcandidate(int position,int candidateValue);
	void displayCellCandidates(int position,std::vector<int>cands);

}; 