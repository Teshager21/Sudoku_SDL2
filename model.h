#pragma once
#include<string>
class Model {
public:
	Model();
	~Model();
	bool init();
	void generateFilledPositions(int(&filledPositions)[30], const int filledCells);
	bool isElementofArray(int(&arr)[30], int value);
	void populateInitialCells();
	bool isItRepeated(std::string scope, int scopeSpecifier, double value);
	void receiveInput( int position, int value);
	bool checkSelectedPosition(int selectedPosition);
	bool isgameWon();
	std::string getMessages();
	void setMessages(std::string message);
private:
	int filledCells;
	int filledPositions[30];
	int tableArray[3][3][3][3];
	std::string messages;
};
