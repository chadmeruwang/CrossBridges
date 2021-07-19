#include "simulator.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "usage: ./cross_bridge_simulator path_to_yaml_file" << endl;
    return -1;
  }
  SIM sim;
  if (sim.load(argv[1]) == -1) {
    cout << endl;
    return -1;
  }
  sim.run();
  return 0;
}
