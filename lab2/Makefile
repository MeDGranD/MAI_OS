CXX			:= g++
CXX_FLAGS	:= -std=c++17 -pthread

BIN			:= bin
SRC			:= src
EXECUTABLE	:= main
CHILD 		:= child

build: $(BIN)/$(EXECUTABLE)
	@echo "Building..."

run: clear build
	@echo "Executing..."
	$(BIN)/$(EXECUTABLE) test.txt

$(BIN):
	mkdir $@

$(BIN)/$(EXECUTABLE): $(BIN)
	$(CXX) $(CXX_FLAGS) -o $@ $(SRC)/$(EXECUTABLE).cpp $(SRC)/myFunctions.cpp

clear:
	@echo "Clearing..."
	-rm -r $(BIN)