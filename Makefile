CXX=g++
CXX_FLAGS= -std=c++11 -I/usr/local/include -L/usr/local/lib -lyaml-cpp -pthread

all: cross_bridge_simulator simulator_test

cross_bridge_simulator: simulator.cc cross_bridge_simulator.cc 
	$(CXX) -o $@ $^ $(CXX_FLAGS)
simulator_test: simulator.cc simulator_test.cc
	$(CXX) -o $@ $^ $(CXX_FLAGS) 
clean:
	rm -rf simulator_test cross_bridge_simulator ./*.o
