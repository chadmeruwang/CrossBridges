#include <iostream>
#include <fstream>
#include "yaml-cpp/yaml.h"
#include <future>
#include <thread>

using namespace std;

class SIM {
private:
  /**
   * The algorithm to solve cross the bridge problem
   * @param times the vector of crossing time of team members
   * @param sz the length of the bridge
   * @param id the id of the bridge
   * @return minimal time to cross the bridge
   */
  float algorithm(vector<float> &times, int sz, int id);

public:

  int nBridge; //number of bridges
  vector<float> bridges; //length values of bridges
  vector<set<float, greater<float>>> teams; //teams when reaching all bridges, descendingly sorted by speed  
  /**
   * load yaml file
   * @param ymlPath absolute path to yaml file storing bridge and team information
   */
  int load(string ymlPath);
  /**
   * crossBridge method
   * @param length length of the bridge
   * @param team vector of team members' speed
   * @param id bridge id
   * return minimal crossing time
   */
  float crossBridge(float length, set<float, greater<float>> &team, int id);
  /**
   * run the simulator
   */
  float run();
};
