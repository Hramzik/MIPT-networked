

CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
BIN_DIR = bin

server: server.cpp socket_tools.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) server.cpp socket_tools.cpp -o $(BIN_DIR)/server

client: client.cpp socket_tools.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) client.cpp socket_tools.cpp -o $(BIN_DIR)/client

