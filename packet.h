#ifndef PACKET_H
#define PACKET_H

#include <ostream>

class Packet
{
	public:
		Packet();
		Packet( int newPriority, Node* newSource, 
			Node* newDestination, Node* newCurrentNode);
		Packet( const Packet &copiedPacket );

		//destructor
		~Packet();

		int getPriority();
		void sendToNode(Node* nodeLocation);
		bool atDestination();

	private:
		int priority;
		Node* source;
		Node* destination;
		Node* currentNode;
};

#endif
