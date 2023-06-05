#pragma once
#include<string>
#include<vector>
class Model {
public:
	Model();
	~Model();
	bool init();
	void generateFilledPositions();
	bool isElementofArray(int(&arr)[30], int value);
	void populateInitialCells();
	bool isItRepeated(std::string scope, int scopeSpecifier, double value);
	void receiveInput( int position, int value);
	bool checkSelectedPosition(int selectedPosition);
	bool isgameWon();
	std::string getMessages();
	void setMessages(std::string message);
	int getMembers(int x, int y);
	int getFilledPosition(int x);
	int GetFilledCells();
	std::vector<int>getVariablePositions();
	//bool isElementofArray(int selectedPosition);
private:
	int filledCells=30;
	int filledPositions[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int m_variablePositions[51]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	std::vector<int> variablePositions;
	int m_tableArray[9][9]{ {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} };
	std::string messages;
};
