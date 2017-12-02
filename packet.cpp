#ifndef PACKET_CPP
#define PACKET_CPP

#include "packet.h"

Packet::Packet
	(
		// data loaded via initializers
	) : priority(0)
{
	source = NULL;
	destination = NULL;
	currentNode = NULL;
}


Packet::Packet
	(
		int newPriority, Node* 
		newSource, Node* newDestination, 
		Node* newCurrentNode
	) : priority(newPriority)
{
	source = newSource;
	destination = newDestination;
	currentNode = newCurrentNode;
}


Packet::Packet
	(
		const Packet &copiedPacket
	) : priority(copiedPacket.priority)
{
	source = copiedPacket.source;
	destination = copiedPacket.destination;
	currentNode = copiedPacket.currentNode;
}


Packet::~Packet
	(
		// no parameters
	) 
{
	priority = 0;
	source = NULL;
	destination = NULL;
	currentNode = NULL;
}


int Packet::getPriority
	(
		// no parameters
	)
{
	return priority;
}


void Packet::sendToNode
	(
		Node* nodeLocation
	)
{
	if( currentNode != nodeLocation)
	{
		currentNode = nodeLocation;
	}
}

bool Packet::atDestination
	(
		// no parameters
	)
{
	if(currentNode == destination)
	{
		return true;
	}

	else
	{
		return false;
	}
}
