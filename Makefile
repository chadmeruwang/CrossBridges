CXX=g++
CXX_FLAGS= -std=c++11 -pthread

all: cross_bridge_simulator simulator_test

cross_bridge_simulator: simulator.cc cross_bridge_simulator.cc libyaml-cpp.a 
	$(CXX) -o $@ $(CXX_FLAGS) $^
simulator_test: simulator.cc simulator_test.cc libyaml-cpp.a
	$(CXX) -o $@ $(CXX_FLAGS) $^
clean:
	rm -rf simulator_test cross_bridge_simulator ./*.o
