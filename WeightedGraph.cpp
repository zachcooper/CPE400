/**
 * @file
 * @author  Zach Cooper
 * @section DESCRIPTION
 * This program is the implementation file for WeightedGraph.cpp. The member functions of the weighted graph 
 * class will be implemented in this file.
 */
#include "WeightedGraph.h"
#include <iostream>
#include <string>

/**
Constructs an empty WeightedGraph.
@param
WeightedGraph constructs an empty weighted graph with passed max size.
@pre
WeightedGraph is passed max number of vertices.
@post
WeightedGraphs paramaters remain unchanged.
@exception
WeightedGraph none.
@algorithm
WeightedGraph none.
@return 
WeightedGraph none.
*/
WeightedGraph::WeightedGraph ( int maxNumber ){
	maxSize = maxNumber;
	size = 0;
	vertexList = new Vertex [maxNumber];
	adjMatrix = new int [maxNumber*maxNumber];
	pathMatrix = new int [maxNumber*maxNumber];
	
	for ( int row = 0; row < maxSize; row++ ){
		for ( int col = 0; col < maxSize; col++ ){
			setEdge (  row, col, INFINITE_EDGE_WT );
			setPath (  row, col, INFINITE_EDGE_WT );
		}
	}
}

/**
Constructs a copy of a WeightedGraph.
@param
WeightedGraph constructs a copy of another weighted graph
@pre
WeightedGraph is passed another weighted graph
@post
WeightedGraphs paramaters remain unchanged.
@exception
WeightedGraph none.
@algorithm
WeightedGraph none.
@return 
WeightedGraph none.
*/
WeightedGraph::WeightedGraph ( const WeightedGraph& other ){
	if ( other.isEmpty() )
		return;
	maxSize = other.maxSize;
	size = other.size;
	clear();
	for ( int i = 0; i < other.size; i++ ){
		vertexList[i] = other.vertexList[i];
	}
	for ( int i = 0; i < other.size; i++ ){
		adjMatrix[i] = other.adjMatrix[i];
	}
}

/**
Overloads the = operator for weighted graphs
@param
operator= overloades the = for weighted graphs
@pre
operator= is passed the other weighted graoh to be equated
@post
operator= paramaters remain unchanged.
@exception
operator= none.
@algorithm
operator= none.
@return 
operator= returns *this.
*/
WeightedGraph& WeightedGraph:: operator= ( const WeightedGraph& other ){
	if ( this == &other )
		return *this;
	maxSize = other.maxSize;
	size = other.size;
	clear();
	for ( int i = 0; i < other.size; i++ ){
		vertexList[i] = other.vertexList[i];
	}
	for ( int i = 0; i < other.size; i++ ){
		adjMatrix[i] = other.adjMatrix[i];
	}
	return *this;
}

/**
Deallocates the memory for vertexList, adjMatrix, pathMatrix.
@param
~WeightedGraph deallocates the memory for vertexList, adjMatrix, pathMatrix.
@pre
~WeightedGraph none.
@post
~WeightedGraph none.
@exception
~WeightedGraph none.
@algorithm
~WeightedGraph none.
@return 
~WeightedGraph none.
*/
WeightedGraph::~WeightedGraph (){
	clear();
	delete [] vertexList;
	delete [] adjMatrix;
	delete [] pathMatrix;
	vertexList = NULL;
	adjMatrix = NULL;
	pathMatrix = NULL;
}

/**
Inserts new vertex into weighted graph.
@param
insertVertex inserts a new vertex into the list of vertices.
@pre
insertVertex newVertex
@post
insertVertex constatnt paramater.
@exception
insertVertex logic error.
@algorithm
insertVertex none.
@return 
insertVertex none.
*/
void WeightedGraph::insertVertex ( const Vertex& newVertex ) throw ( logic_error ){
	for ( int i = 0; i < size; i++ ){
		if ( vertexList[i].getLabel() == newVertex.getLabel() ){
			vertexList[i].setColor( newVertex.getColor() );
		}
	}
	vertexList[size].setLabel(newVertex.getLabel());
	vertexList[size].setColor(newVertex.getColor());
	vertexList[size].setEnergy(newVertex.getEnergy());
	size++;         
}

/**
Inserts new edge into weighted graph.
@param
insertEdge inserts a new edge into the weighted graph.
@pre
insertEdge two vertices ( labels ) and a weight.
@post
insertEdge strings remain constant, weight is updated.
@exception
insertEdge logic error.
@algorithm
insertEdge none.
@return 
insertEdge none.
*/
void WeightedGraph::insertEdge ( const string& v1, const string& v2, int wt ) throw ( logic_error ){
	Vertex retrieved;
	if ( retrieveVertex ( v1, retrieved ) && retrieveVertex ( v2, retrieved ) ){
		setEdge ( getIndex (v1), getIndex (v2), wt );
		setEdge ( getIndex (v2), getIndex (v1), wt );
		cout << "Size = " << size << ", index of sensor_v1 = " << getIndex( v1 ) << ", index of sensor_v2 = " << getIndex( v2 ) << endl;
	} 
	
}

/**
Retrieves a vertex.
@param
retrieveVertex determins if a vertex exists within the graph
@pre
retrieveVertex const string, vertex to update
@post
retrieveVertex updats vData ( vertex passed by reference )
@exception
retrieveVertex none.
@algorithm
retrieveVertex none.
@return 
retrieveVertex bool.
*/
bool WeightedGraph::retrieveVertex ( const string& v, Vertex& vData ) const{

	for ( int y = 0; y < size; y++ ){
		if ( vertexList[y].getLabel() == v ){
			vData.setLabel(vertexList[y].getLabel());
			vData.setColor(vertexList[y].getColor());
			return true;
		}
	}
	return false;
}

/**
Determinins if egde is within the graph
@param
getEdgeWeight determins if an edge exsists in weighted graph using vertices and edges.
@pre
getEdgeWeight const string, const string, weight by reference.
@post
getEdgeWeight const strings, weight updated.
@exception
getEdgeWeight logic error.
@algorithm
getEdgeWeight none,
@return 
getEdgeWeight bool.
*/
bool WeightedGraph::getEdgeWeight ( const string& v1, const string& v2, int& wt ) const throw ( logic_error ){
	Vertex weight;
	if ( retrieveVertex ( v1, weight ) && retrieveVertex ( v2, weight ) && getEdge( getIndex ( v1 ), getIndex ( v2 ) ) != INFINITE_EDGE_WT ){
		wt = getEdge ( getIndex ( v1 ), getIndex ( v2 ) );
		return true;
	} 
	return false;
}

/**
Removes vertex from weighted graph.
@param
removeVertex removes vertex and edges of vertices.
@pre
removeVertex const string.
@post
removeVertex const strings.
@exception
removeVertex logic error.
@algorithm
removeVertex none,
@return 
removeVertex none.
*/
void WeightedGraph::removeVertex ( const string& v ) throw ( logic_error ){
	Vertex removed;
	int removeIndex = -1;
	if ( retrieveVertex ( v, removed )){
		removeIndex = getIndex ( v );
		for ( int i = removeIndex; i < size; i++ ){
				vertexList[i] = vertexList[i+1];
				for  ( int j = 0; j < size; j++ ){
					setEdge ( i, j, getEdge ( i+1, j ) );
				}
		}
		for ( int i = 0; i < size; i++ ){
				for  ( int j = removeIndex; j < size; j++ ){
					setEdge ( i, j, getEdge ( i, j+1 ) ); 
				}
		}
		size--;
	}
}

/**
Removes edge from weighted graph.
@param
removeVertex removes edge from weighted graph using set edge.
@pre
removeVertex const string vertices.
@post
removeVertex const strings.
@exception
removeVertex logic error.
@algorithm
removeVertex none,
@return 
removeVertex none.
*/
void WeightedGraph::removeEdge ( const string& v1, const string& v2 ) throw ( logic_error ){
	Vertex removed;
	if ( retrieveVertex ( v1, removed ) && retrieveVertex ( v2, removed ) ){
		setEdge ( getIndex (v1), getIndex (v2), INFINITE_EDGE_WT );
		setEdge ( getIndex (v2), getIndex (v1), INFINITE_EDGE_WT );
	} 
}

/**
Clears the weighted graph of all vertices and edges.
@param
clear clears the weighted graph of all vertices and edges.
@pre
clear none.
@post
clear none.
@exception
clear none.
@algorithm
clear none,
@return 
clear none.
*/
void WeightedGraph::clear (){
	for ( int i = 0; i < size; i++ ){
			for  ( int j = 0; j < size; j++ ){
				if ( getEdge ( i, j ) != INFINITE_EDGE_WT )
					removeEdge ( vertexList[i].getLabel(), vertexList[j].getLabel());
			}
	}
	while ( size != 0 )
		removeVertex ( vertexList[0].getLabel() );
}

/**
Determines if graph is empty or not.
@param
isEmpty determines if graph is empty or not.
@pre
isEmpty none.
@post
isEmpty none.
@exception
isEmpty none.
@algorithm
isEmpty none,
@return 
isEmpty bool.
*/
bool WeightedGraph::isEmpty () const{
	if ( size == 0 )
		return true;
	return false;
}

/**
Determines if graph is full or not.
@param
isFull determines if graph is full or not.
@pre
isFull none.
@post
isFull none.
@exception
isFull none.
@algorithm
isFull none,
@return 
isFull bool.
*/
bool WeightedGraph::isFull () const{
	if ( size == maxSize )
		return true;
	return false;
}

/**
Finds and displays the shortest paths between edges.
@param
showShortestPaths first finds the shortest path for each edge and then sets the new paths and displays them to the terminal.
@pre
showShortestPaths none.
@post
showShortestPaths none.
@exception
showShortestPaths none.
@algorithm
showShortestPaths none,
@return 
showShortestPaths none.
*/
void WeightedGraph::showShortestPaths (){
	for ( int a = 0; a < size; a++ ){
		for ( int b = 0; b < size; b++ ){
			setPath ( a, b, getEdge ( a, b ) );
		}
	setPath ( a, a, 0 );
	}
	
	for ( int c = 0; c < size; c++ ){
		for ( int d = 0; d < size; d++ ){
			for ( int e = 0; e < size; e++ ){
				if ( getPath ( c, d ) != INFINITE_EDGE_WT &&
					 getPath ( c, e ) != INFINITE_EDGE_WT &&
					 ( getPath ( c, d ) + getPath ( c, e ) ) < getPath ( d, e ) ){
					setPath ( d, e, ( getPath ( c, d ) + getPath ( c, e ) ) );	 
				}
			}
		}
	}
	cout << endl << "Path matrix : " << endl << '\t';
	for ( int col = 0 ; col < size ; col++ )
    	cout << col << '\t';
    cout << endl;
    for ( int row = 0 ; row < size ; row++ ){
        cout << row << '\t';
        for ( int col = 0 ; col < size ; col++ ){
        	int wt = getPath(row,col);
            if ( wt == INFINITE_EDGE_WT )
          		cout << "- \t";
            else
                cout << wt << '\t';
        }
        cout << endl;
	}	
}

/**
Determines if weighted graph has properly assigned colors.
@param
hasProperColoring determines if weighted graph has properly assigned colors using getColor and getEdge.
@pre
hasProperColoring none.
@post
hasProperColoring none.
@exception
hasProperColoring none.
@algorithm
hasProperColoring none,
@return 
hasProperColoring bool.
*/
bool WeightedGraph::hasProperColoring() const{
	for ( int i = 0; i < size; i++ ){
		for ( int j = 0; j < size; j++ ){
			if ( vertexList[i].getColor() == vertexList[j].getColor() && 
				 getEdge ( i, j ) != INFINITE_EDGE_WT ){
				 return false;
			}
		}
	}
	return true;
}

/**
Determines if all vertices have an even number of edges.
@param
areAllEven determines if all vertices have an even number of edges, using recursion.
@pre
areAllEven a col and number of hits both by reference
@post
areAllEven both col and number of hits are updated with each recursive function call.
@exception
areAllEven none.
@algorithm
areAllEven recurivesly calls itself with updated col and number of hits.
@return 
areAllEven bool ( base case ).
*/
bool WeightedGraph::areAllEven (int& col, int& hits){
	if ( col == size && hits == size )
		return true;
	if ( col == size )
		return false; 
	int count = 0;
	for ( int row = 0; row < size; row++){
		if ( getEdge ( row, col ) != INFINITE_EDGE_WT ){
			count++;
		}
	}
	if ( count%2 == 0 )
		hits++;
	col++;
	areAllEven ( col, hits );
}

/**
Returns the index of a given vertex
@param
getIndex determines the index of a given vertex.
@pre
getIndex const string.
@post 
getIndex const string.
@exception
getIndex none.
@algorithm
getIndex none,
@return 
getIndex int.
*/
int WeightedGraph::getIndex ( const string& v ) const{
    int j;
    for ( j = 0 ; j < size  &&  v.compare( vertexList[j].getLabel() ) != 0; j++ );
    return j;
}

/**
Returns edge.
@param
getEdge returns edge.
@pre
getEdge row and col
@post 
getEdge const paramaters.
@exception
getEdge none.
@algorithm
getEdge none,
@return 
getEdge int.
*/
int WeightedGraph::getEdge ( int row, int col ) const{
	return adjMatrix [ ( row * maxSize ) + col ];
}

/**
Returns path.
@param
getPath returns path.
@pre
getPath row and col
@post 
getPath const paramaters.
@exception
getPath none.
@algorithm
getPath none,
@return 
getPath int.
*/
int  WeightedGraph::getPath ( int row, int col ) const{
	return pathMatrix [ ( row * maxSize ) + col ];
}

/**
Sets edge.
@param
setEdge sets edge.
@pre
setEdge row, col and weight
@post 
setEdge weight is updataed.
@exception
setEdge none.
@algorithm
setEdge none,
@return 
setEdge none.
*/
void WeightedGraph::setEdge ( int row, int col, int wt){
	adjMatrix [ ( row * maxSize ) + col ] = wt;
}

/**
Sets path.
@param
setPath sets path.
@pre
setPath row, col and weight
@post 
setPath weight is updataed.
@exception
setPath none.
@algorithm
setPath none,
@return 
setPath none.
*/
void WeightedGraph::setPath ( int row, int col, int wt){
	pathMatrix [ ( row * maxSize ) + col ] = wt;
}

void WeightedGraph::showStructure () const{
    if ( size == 0 ) {
       cout << "Empty graph" << endl;
    } else {
       cout << endl << "Sensor list : " << endl;
	   cout << "Row" << '\t' << "Label" << '\t' << "Energy Level" << endl;
       for ( int row = 0 ; row < size ; row++ )
           cout << row << '\t' << vertexList[row].getLabel()
#if LAB12_TEST2
		<<"\t" << vertexList[row].getEnergy()
#endif
		<< endl;

       cout << endl << "Edge matrix : " << endl << '\t';
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t';
       cout << endl;
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
               int wt = getEdge(row,col);
               if ( wt == INFINITE_EDGE_WT )
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
    }
} 




