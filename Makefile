# Nom de l'exécutable et dossiers
EXEC = game_of_life.exe
SRC_DIR = src
INC_DIR = include

# Détection automatique des fichiers source
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:.cpp=.o)

# Options de compilation
CXX = g++
CXXFLAGS = -I$(INC_DIR) -IC:/raylib/raylib/src -Wall -Wextra -std=c++17
LDFLAGS = -LC:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm

LDFLAGS += -static

# Si NO_CONSOLE est défini, on ajoute -mwindows pour cacher la console
ifeq ($(NO_CONSOLE), true)
    LDFLAGS += -mwindows
endif

# Règle principale
$(EXEC): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Compilation des fichiers .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	cmd /C "del /F /Q $(OBJS) $(EXEC) 2>nul || exit 0"

# Rebuild complet
rebuild: clean $(EXEC)

.PHONY: clean rebuild
