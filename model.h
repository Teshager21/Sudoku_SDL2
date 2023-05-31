#pragma once
#include<string>
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
	typedef int(*tableArray3X4)[3][3][3];
	tableArray3X4 getArray();
private:
	int filledCells=30;
	int filledPositions[30];//={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int tableArray[3][3][3][3];
	std::string messages;
};
