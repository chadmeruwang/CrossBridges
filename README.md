# CrossBridges #
A simulator simulating cross bridge problems with multiple bridges and team with new members added at each bridge. The simulator reads a yaml file with bridge and team information and returns the minimal to cross each bridge and the total time to cross all bridges.
## How to Build ##
1. Install cmake, make, g++.
2. Install [yaml-cpp](https://github.com/jbeder/yaml-cpp).
3. In current directory, type
   ```
   make
   ```
4. two executables will be built 
   ```
   cross_bridge_simulator : the simulator to solve cross bridges problems
   simulator_test : the test program to validate the correctness of the code
   ```
## How to Run Simulator ##
1. ./cross_bridge_simulator path_to_input_yaml_file. For example
```
./cross_bridge_simulator input.yaml
```
2. Input file format. take input.yaml as an example 
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
