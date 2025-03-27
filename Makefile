RAYLIB_DIR = C:/raylib/raylib/src

EXEC = game_of_life.exe

SRC_DIR = src
INC_DIR = include

OS_NAME := $(shell echo $(OS))

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:.cpp=.o)

CXX = g++
CXXFLAGS = -I$(INC_DIR) -I$(RAYLIB_DIR) -Wall -Wextra -std=c++17

ifeq ($(OS_NAME), Linux)
	LDFLAGS = -L$(RAYLIB_DIR) -lraylib
else ifeq ($(OS_NAME), Windows_NT)
	LDFLAGS = -L$(RAYLIB_DIR) -lraylib -lopengl32 -lgdi32 -lwinmm
endif

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
