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
	int filledCells=38;
	int filledPositions[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int cachedFilledPositions[38]={0,3,5,7,9,11,13,14,21,23,24,26,27,31,38,42,43,48,50,51,53,55,56,58,59,60,61,62,64,65,71,73,74,75,76,77,78,79};
	int m_variablePositions[51]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	std::vector<int> variablePositions;
	int mBoard[9][9]{ {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} ,{0,0,0,0,0,0,0,0,0} };
	int mCachedBoard[9][9]{ {8,0,0,9,0,1,0,2,0},{2,0,3,0,6,4,0,0,0},{0,0,0,6,0,3,7,0,8} ,{1,0,0,0,9,0,0,0,0} ,{0,0,8,0,0,0,9,6,0} ,{0,0,0,6,0,3,7,0,8} ,{0,9,5,0,8,6,2,7,1} ,{0,4,1,0,0,0,0,0,3} ,{0,8,2,1,3,5,6,4,0} };
	std::string messages;
	std::map<int,std::vector<int>> mCandidatePositions;
	bool mCachedGame=true;


private:
	Model();
	~Model();

};
