# GTEST_DIR = /path/to/googletest
# CPPFLAGS += -isystem $(GTEST_DIR)/include
# CXXFLAGS += -g -Wall -Wextra -pthread
# TESTS = tests

all:
	g++ source.cpp controller.cpp window.cpp model.cpp texture.cpp AssetManager.cpp GameEntity.cpp solver.cpp -lSDL2 -lSDL2main -lSDL2_ttf 


# all :$(TESTS)
# tests : test.cpp 
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
# clean :
# 	rm	-f	$(TESTS) *.o 

	g++	test/*.cpp controller.cpp texture.cpp window.cpp model.cpp AssetManager.cpp GameEntity.cpp solver.cpp -lgtest -lgtest_main -pthread  -lSDL2 -lSDL2main -lSDL2_ttf -o test.out