all:
	g++ source.cpp controller.cpp window.cpp model.cpp texture.cpp AssetManager.cpp GameEntity.cpp solver.cpp -lSDL2 -lSDL2main -lSDL2_ttf 