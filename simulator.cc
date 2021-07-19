#include "simulator.h"

using namespace std;

/**
 * load yaml file
 * @param ymlPath absolute path to yaml file storing bridge and team information
 */
int SIM::load(string ymlPath) {
  try{
    YAML::Node data = YAML::LoadFile(ymlPath);
    nBridge = data.size() - 1;
    bridges = vector<float>(nBridge + 1, -1);
    teams = vector<set<float, greater<float>>>();
    set<float, greater<float>> t;
    for (auto i : data[0]) {
      auto speed = i.as<float>();
      if (speed <= 0)
	throw "team member speed less than or equal to 0";
      t.insert(speed);
    }
    //bridges and teams are numbered from 1
    teams.push_back(t);
    for (int i = 1; i <= nBridge; ++i) {
      //each team is created by adding new member to the previous team
      auto length = data[i][0].as<float>();
      if (length <= 0)
	throw "bridge length less than or equal to 0";
      bridges[i] = length;
	
      auto t = teams[i - 1];
      for (auto n : data[i][1]) {
	float speed = n.as<float>();
	if (speed <= 0)
	  throw "team member speed less than or equal to 0";
	t.insert(speed);
      }
      teams.push_back(t);
    }
  } catch (...) {
    cerr << "[yaml file format error detected!] ";
    return -1;
  }
  return 0;
}
/**
 * The algorithm to solve cross the bridge problem
 * @param times the vector of crossing time of team members
 * @param sz the length of the bridge
 * @param id the id of the bridge
 * @return minimal time to cross the bridge
 * Accroding to the theorem in paper 
 * Rote, Günter. (2002). Crossing the Bridge at Night.. Bulletin of the EATCS. 78. 241-. 
 * The minimal time to cross the bridge is min{C[0], C[1] ... C[sz/2 - 1]} where
 * C[k] - C[k - 1] = 2 * times[1] - times[0] - times[sz - k * 2 - 1]
 * C[0] = (sz - 2) * times[0] + times[1] + times[2] + ... + times[sz - 1]
 *      = sum of all values in times + (sz - 3) * times[0]
 */
float SIM::algorithm(vector<float> &times, int sz, int id) {
  float sum = 0.0;
  for (float t : times) {
    sum += t;
  }

  //calculate the first crossing time C[0] 
  float res = sz > 1 ? sum + (sz - 3) * times[0] : sum;

  //calculate difference between C[k] and C[k - 1]
  //when difference > 0 then C[k - 1] is the minimal so far
  //when difference <= 0 then C[k] is the minimal so far
  for (int i = 0; i < sz / 2; ++i) {
    float dif = times[1] * 2 - times[0] - times[sz - (i + 1) * 2]; 
    res += dif > 0 ? 0 : dif;
  }
  cout << "[thread " << this_thread::get_id() << " finished] minimal time to cross bridge " << id << ": " << res << " minutes" << endl; 
  return res;
} 

/**
 * crossBridge method
 * @param length length of the bridge
 * @param team vector of team members' speed
 * @param id bridge id
 * return minimal crossing time
 */
float SIM::crossBridge(float length, set<float, greater<float>> &team, int id) {
  int sz = team.size();
  vector<float> times;
  //calculate crossing time for each team member
  for (float speed : team) {
    times.push_back(length / speed);
  }
  return algorithm(times, sz, id);
}
/**
 * run the simulator
 */
float SIM::run() {
  float totalTime = 0.0;
  //create a thread for each bridge
  vector<future<float>> tasks;
  for (int i = 1; i <= nBridge; ++i) {
    tasks.push_back(async(launch::async, &SIM::crossBridge, this, bridges[i], ref(teams[i]), i));
  }
  //run threads in parallel and aggregate the crossing time
  for (auto& task : tasks)
    totalTime += task.get();  
  cout << "total time to cross all bridges: " << totalTime << " minutes" << endl;
  return totalTime;
}

