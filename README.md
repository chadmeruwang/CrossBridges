# CrossBridges #
A simulator solves cross bridge problem with multiple bridges and a team with new members join at each bridge. The simulator reads a yaml file with bridge and team information and returns the minimal time to cross each bridge and the total time to cross all bridges.
## How to Build (tested on Ubuntu 20.04.2 LTS) ##
1. Install cmake, make, g++.
2. Install [yaml-cpp](https://github.com/jbeder/yaml-cpp) as dynamic library with following steps
- git clone https://github.com/jbeder/yaml-cpp.git
- In "yaml-cpp" directory, type
```
mkdir build
cd  build
```
- In build directory, type (assuming you have sudo access)
```
cmake -DYAML_BUILD_SHARED_LIBS=ON ..
make
make install
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```
3. Now yaml-cpp has been installed as a dynamic library. Go to "CrossBridges" directory, type
   ```
   make
   ```
4. Two executables will be built 
   ```
   cross_bridge_simulator : the simulator to solve cross bridges problems
   simulator_test : the test program to validate correctness of the code
   ```
## How to Run/Test Simulator ##
1. ./cross_bridge_simulator path_to_input_yaml_file. For example
```
./cross_bridge_simulator input.yaml
```
2. Input file format. Take input.yaml as an example 
```
# the first line is a list of initial team members' speed ft/minute
- [100, 50, 20, 10]
# starting from the second line each list element is a list consisting
# bridge lengths (ft) and the speed of new members joined at this bridge
-
# first bridge' length is 100 ft
  - 100
# no new member added
  - []
-
  - 250
# a new member with speed 2.5 ft/minute joined
  - [2.5]
-
  - 150
  - [25, 15]

```
4. To run the test, just type 
```
./simulator_test
```
which does the function testing on input format/layout and output validation.

5. To stress test the simulator, simply go to "test" directory run the shell script yaml_generator.sh
```
./yaml_generator.sh big.yaml 1000
```
which generates a yaml file big.yaml with 1000 bridges. You can then run ./cross_bridge_simulator test/big.yaml to check the results

## Ideas to scale ##  
Currently the simulator is implemented as a multi-threaded application running on a single host. Each thread computes the minimal time to cross one bridge in parallel with other threads. You can scale the application up using more cores and larger memory. 

To scale it out on multiple hosts, you may extend the application easily using map-reduce architecture where a input yaml (potentially too large to fit into one machine's memory) is divided into N files each is fed into a simulator on one host. Then the machines compute local total crossing time in parallel which are then aggregated (reduced) to global total crossing time.    

