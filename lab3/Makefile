CXX			:= g++
CXX_FLAGS	:= -std=c++17

BIN			:= bin
SRC			:= src
EXECUTABLE	:= main
CHILD 		:= child

build: $(BIN)/$(EXECUTABLE)
	@echo "Building..."

run: clear build
	@echo "Executing..."
	$(BIN)/$(EXECUTABLE)

$(BIN):
	mkdir $@

$(BIN)/$(EXECUTABLE): $(BIN) | $(BIN)/$(CHILD)
	$(CXX) $(CXX_FLAGS) -o $@ $(SRC)/$(EXECUTABLE).cpp $(SRC)/myCalls.cpp $(SRC)/mFutex.cpp 

$(BIN)/$(CHILD): $(BIN)
	$(CXX) $(CXX_FLAGS) -o $@ $(SRC)/$(CHILD).cpp $(SRC)/myCalls.cpp $(SRC)/mFutex.cpp 

clear:
	@echo "Clearing..."
	-rm -r $(BIN)