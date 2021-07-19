# CrossBridges #
A simulator simulating cross bridge problems with multiple bridges and team with new members added at each bridge. The simulator reads a yaml file with bridge and team information and returns the minimal to cross each bridge and the total time to cross all bridges.
## How to Build ##
1. Install cmake, make, g++.
2. Install [yaml-cpp](https://github.com/jbeder/yaml-cpp).
3. In current directory type
   ```
   make
   ```
5. two executables will be built 
   ```
   cross_bridge_simulator : the simulator to solve cross bridges problems
   simulator_test : the test program to validate the correctness of the code
   ```
5. To uninstall the simulator, run
   ```
   make clean
   ```
## run ##
