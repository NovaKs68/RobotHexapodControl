CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb
CXX_FLAG_END := -pthread

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   :=
EXECUTABLE  := main


all: $(BIN)/$(EXECUTABLE)

run: clean all; clear; ./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp; $(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES) $(CXX_FLAG_END)

clean: -rm $(BIN)/*