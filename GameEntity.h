#ifndef _GAMEENTITITY_H
#define _GAMEENTITITY_H
#include<vector>
#include<SDL2/SDL.h>


class GameEntity {


private:
	std::vector<int>mPosition;
public:
	void SetPosition(int x, int y);
	std::vector<int> GetPosition();
	GameEntity(int x, int y);
	GameEntity();
	~GameEntity();
	/*virtual void Update();
	virtual void Render();*/

};



#endif
