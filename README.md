# CPE 400: Energy Conservation Routing Protocol
Zach Cooper (CSE undergraduate University of Nevada, Reno)
Roniel Padua (CSE undergraduate University of Nevada, Reno)
Austin Ogilvie (CSE undergraduate University of Nevada, Reno)

In this project, a simulation is created of a network with sensor nodes. This is implemented as a graph in our code. The weights of edges as well as the energy existing on a vertex is randomized each time the program is run. There also exists a packet object and these are created with their own random source and destinations, as well as cost for sending. We have implemented an energy conservation routing protocol that uses this graph and will find the best route that will conserve the most energy through each iteration for each packet. Conversely, there is a path-finding method implemented using Dijkstra's algrorithm for comparison purposes to prove that our algorithm is more efficient at conserving energy throughout the system, allowing for it to stay online longer.  

# Dependencies, Building, and Running

## Dependency Instructions
This project is dependent upon C++11, and should be compiled with accordingly.

## Building and Running
In order to compile and build the project into an executable, please use the following command in the terminal where the project files are located:  
```bash
g++ -std=c++11 energyConservation.cpp -o ECG  
```

The program can then be executed simply by executing:  
```bash
./ECG  
```

## Understanding Output
After executing, the program will output several things in the terminal:  
  
It will output the energy consumption that is required for the packet to be passed through for one hop. This value is used in decrementing the energy from each vertex node.  
  
The location of the sensor edge vertex locations will be shown.  
  
The list of sensor nodes will be outputted along with their initial energy levels. These energy levels are what's used in calculating the optimal energy conservation route for a packet.  
  
The edge matrix is shown with the vertices and their edge weights with connecting vertices in the network.  
  
A path matrix is shown given showing the cost of the shortest path from one node to a corresponding node in the matrix.  
  
For each packet, the source and destination is shown and the list of vertices visited will be shown in sequence. Also output are the list of energy remaining per node and the total amount of energy in the system remaining after the packet traversal.  
  
For comparison purposes, the same is shown using Dijkstra's algorithm, and from observing the energy remaining overall after each packet traversal, it can typically be observed that the energy conservation routing algorithm is more efficient at conserving energy than Dijkstra's algorithm is.
