#include "WeightedGraph.h"
#include "WeightedGraph.cpp"
#include "Packet.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Global Variable


int main (){

    // Variables
    WeightedGraph network(100);
	Packet *packets = new Packet[5];

	for(int i = 0; i < 5; i++){
		int x = rand() % 10;
		packets[i].energyConsumptionRequired = x;
	}

	for(int i = 0; i < 5; i++){
		cout << "Packet #" << i << " energy consumption per packet hop :";
		cout << packets[i].energyConsumptionRequired << endl;
	}

    srand(time(0));
    WeightedGraph::Vertex vertex[20];
    cout << endl << "Sensor edge vertex locations:" << endl;
    for (int i = 0; i < 20; i++){
        string label = to_string (i);
        vertex[i].setLabel(label);
        int energy = rand() % 50 + 50;
        vertex[i].setEnergy(energy);
        network.insertVertex(vertex[i]);
    }

    for (int i = 0; i < 20; i++){
        string node1 = to_string(i);
        for (int j = 1; j < 20; j++){
            string node2 = to_string(i+j); 
            network.insertEdge (node1, node2, rand() % 20 + 1);
        }
    }

	

    network.showStructure(); 
    network.showShortestPaths();
    return 0;
}
