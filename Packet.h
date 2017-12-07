#ifndef PACKET_H
#define PACKET_H

#include "WeightedGraph.h"

#include <ostream>

struct Packet{
	int energyConsumptionRequired;
	int source;//source;
	int dest;//destination;
    bool isOnline = true;
};


#endif
