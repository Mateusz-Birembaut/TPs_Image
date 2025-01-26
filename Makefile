CXXFLAGS = -Wall -Wextra -I. -std=c++11
LDFLAGS = 
LDLIBS = 

# Répertoires
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Fichiers sources
SRC = $(wildcard $(SRC_DIR)/*.cpp)

# Fichiers objets
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# Nom de l'exécutable
EXE = app

# Cible par défaut
all: $(BIN_DIR)/$(EXE)

# Compilation de l'exécutable
$(BIN_DIR)/$(EXE): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Exécution du programme avec des arguments
.PHONY: run
run: all
	./$(BIN_DIR)/$(EXE) $(ARGS)