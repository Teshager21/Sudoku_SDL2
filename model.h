#pragma once
#include<string.h>
#include<string>
#include<vector>
#include<map>
class Model {
public:
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
	int getValueAtPosition(int position);
	int getFilledPosition(int x);
	int GetFilledCells();
	std::vector<int>getVariablePositions();
	static Model* getInstance();
	std::map<int,std::vector<int>>* getCandidates();
	void setCandidateVector(int position,std::vector<int> vec);
	void setCandidateValue( int position,int value);
	std::vector<int> getCandidatesAtPosition(int pos);
	bool isItRepeatedValue(int position,int value);
	bool isPositionFilled(int position);

private:
    static Model* sInstance;
	int filledCells=30;
	int filledPositions[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int m_variablePositions[51]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	std::vector<int> variablePositions;
	int mBoard[9][9]{ {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} };
	std::string messages;
	std::map<int,std::vector<int>> mCandidatePositions;


private:
	Model();
	~Model();

};
