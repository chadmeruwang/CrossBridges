#include "simulator.h"

using namespace std;

vector<float> computeRange(float length, set<float, greater<float>>& team) {
  vector<float> times;
  int n = team.size();
  for (auto speed : team)
    times.push_back(length / speed);
  float maxTime = times.back();
  float minTime = times[0];
  return {(n + 1)* minTime, (n + 2) * maxTime};  
}

int main() {
  SIM sim;
  cout << "input test: " << endl;
  cout << "1. load yaml file with correct format: ";
  if (sim.load("test/correct.yaml") == 0)
    cout << "pass" << endl;
  else
    cout << "fail" << endl;
  cout << "2. load yaml file missing original team: ";
  if (sim.load("test/miss_orig.yaml") == -1)
    cout << "pass" << endl;
  else
    cout << "fail" << endl;
  cout << "3. load yaml file with wrong team speed number ( <=0 ): ";
  if (sim.load("test/wrong_speed.yaml") == -1)
    cout << "pass" << endl;
  else
    cout << "fail" << endl;
  cout << "4. load yaml file with wrong bridge length number ( <=0 ): ";
  if (sim.load("test/wrong_bridge.yaml") == -1)
    cout << "pass" << endl;
  else
    cout << "fail" << endl;
  cout << "5. load yaml file with wrong layout: ";
  if (sim.load("test/wrong_layout.yaml") == -1)
    cout << "pass" << endl;
  else
    cout << "fail" << endl;
  cout << "output test: " <<endl;
  sim.load("input.yaml");
  cout.setstate(ios_base::failbit);
  float res = sim.run();
  cout.clear();
  cout << "1. result >= 0 ?: ";
  if (res >= 0)
    cout << "pass" << endl;
  else
    cout << "fail" << endl;
  cout << "2. individual result valid ?: ";
  int i = 1;
  for (; i < sim.bridges.size(); ++i) {
    vector<float> r = computeRange(sim.bridges[i], sim.teams[i]);
    cout.setstate(ios_base::failbit);
    float res = sim.crossBridge(sim.bridges[i], sim.teams[i], i); 
    cout.clear();
    if (res < r[0] || res > r[1]) {
      cout << "fail" << endl;
      break;
    } 
  }
  if (i == sim.bridges.size())
    cout << "pass" << endl;
}
