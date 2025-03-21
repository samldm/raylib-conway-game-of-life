EXEC = game_of_life.exe
SRC_DIR = src
INC_DIR = include

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:.cpp=.o)

CXX = g++
CXXFLAGS = -I$(INC_DIR) -IC:/raylib/raylib/src -Wall -Wextra -std=c++17
LDFLAGS = -LC:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm

LDFLAGS += -static

ifneq ($(CONSOLE), true)
    LDFLAGS += -mwindows
endif

$(EXEC): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	cmd /C "del /F /Q $(OBJS) $(EXEC) 2>nul || exit 0"

rebuild: clean $(EXEC)

.PHONY: clean rebuild
