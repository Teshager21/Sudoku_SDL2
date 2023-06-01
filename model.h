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
	int getMembers(int w, int x, int y, int z);
private:
	int filledCells=30;
	int filledPositions[30]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	//int m_tableArray[3][3][3][3];
	int m_tableArray[3][3][3][3]{ {{0,0,0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}} };
	std::string messages;
};
