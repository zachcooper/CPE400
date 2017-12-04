#include "WeightedGraph.h"
#include "WeightedGraph.cpp"
#include "Packet.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Global Variable

void findLowestEnergyPath(WeightedGraph::Vertex vertices[], Packet packet);
void dijkstra(WeightedGraph::Vertex vertices[], WeightedGraph &net, Packet packet);


int main (){

    srand(time(0));

    // Variables
    WeightedGraph network(100);
	Packet *packets = new Packet[5];

	for(int i = 0; i < 5; i++){
		int x = rand() % 10;
		packets[i].energyConsumptionRequired = x;
	}

	for(int i = 0; i < 5; i++){
		int src = rand() % 20;
		int dst = rand() % 20;
		while( src == dst)
		{
			dst = rand() % 20;
		}
		packets[i].source = src;
		packets[i].dest = dst;
		
	}

	for(int i = 0; i < 5; i++){
		cout << "Packet #" << i << " energy consumption per packet hop :";
		cout << packets[i].energyConsumptionRequired << endl;
	}

    WeightedGraph::Vertex vertex[20];
    cout << endl << "Sensor edge vertex locations:" << endl;
    for (int i = 0; i < 20; i++){
        string label = to_string(i);
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

    cout << "SRC: " << packets[0].source << " DST: " << packets[0].dest << endl;

    findLowestEnergyPath(vertex, packets[0]);

    dijkstra(vertex, network, packets[0]);

    return 0;
}

int maxPower(int energyRemaining[], bool sptSet[])
{
	int max = 0, max_index;

	for(int i = 0; i < 20; i++)
	{
		if(sptSet[i] == false && energyRemaining[i] >= max)
		{
			max = energyRemaining[i], max_index = i;
		}
	}
	return max_index;
}

int printSoln(int energyRemaining[], int n)
{
	cout << "Energy remaining after packet traversal" << endl;
	for(int i = 0; i < 20; i++)
		cout << i << " " << energyRemaining[i] << endl;
}

void findLowestEnergyPath(WeightedGraph::Vertex vertices[], Packet packet)
{
	int energyRemaining[20];
	bool sptSet[20];

	for(int i = 0; i < 20; i++)
	{
		energyRemaining[i] = vertices[i].getEnergy();
		sptSet[i] = false;
	}

	//energyRemaining[packet.source] = 0;

	int j = 0, u = -1;

	while(j < 19 && u != packet.dest)
	{
		u = maxPower(energyRemaining, sptSet);
		vertices[u].setEnergy(vertices[u].getEnergy()-packet.energyConsumptionRequired);
		cout << "Packet is traveling through vertex: " << u << endl;

		sptSet[u] = true;

		energyRemaining[u] -= packet.energyConsumptionRequired;
		j++;
	}

	printSoln(energyRemaining, 20);
}

int minDistance(WeightedGraph &net, bool sptSet[], int loc)
{
	int min = 1000, min_index, weight;

	for(int i = 0; i < 20; i++)
	{

		net.getEdgeWeight(to_string(loc), to_string(i), weight);
		if(sptSet[i] == false && weight <= min)
		{
			min = weight, min_index = i;
		}
	}
	return min_index;
}

void dijkstra(WeightedGraph::Vertex vertices[], WeightedGraph &net, Packet packet)
{

	int energyRemaining[20];
	int dist[20];
	bool sptSet[20];

	for(int i = 0; i < 20; i++)
	{
		dist[i] = 1000;
		energyRemaining[i] = vertices[i].getEnergy();
		sptSet[i] = false;
	}

	dist[packet.source] = 0;

	//energyRemaining[packet.source] = 0;

	int j = 0, u = -1;

	while(j < 19 && u != packet.dest)
	{
		u = minDistance(net, sptSet, j);
		vertices[u].setEnergy(vertices[u].getEnergy()-packet.energyConsumptionRequired);
		cout << "Dijkstra Packet is traveling through vertex: " << u << endl;

		sptSet[u] = true;

		energyRemaining[u] -= packet.energyConsumptionRequired;
		j++;
	}

	printSoln(energyRemaining, 20);
}
