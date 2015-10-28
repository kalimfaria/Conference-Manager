# ifndef DIJKSTRA_H
# define DIJKSTRA_H

#include <limits.h>
#include <iostream>
#include <vector>
# include <string>
using namespace std;
 
void printPath (vector<int>a , vector <int> b, vector<int> c, int  );

struct AdjListNode // node in an adj list
{
    int dest; // destination
    double weight; // weight
    AdjListNode* next;
	AdjListNode () { dest = weight = 0; next = NULL ;}
};
 
// an adjacency list-> linked list  =)
struct AdjList
{
public:
    AdjListNode *head;
	AdjList () { head = NULL; }//head pointer
};
 
// A graph is an array of adjacency lists. // -> an array of linked lists =)
// Size of array will be V (number of vertices in graph) (v by e )
struct Graph
{
    int V; 
    AdjList* array; 
	Graph () { V = 0;}
};
 
// A utility function to create a new adjacency list node
AdjListNode* newAdjListNode(int dest, double weight)
{
    AdjListNode* newNode = new AdjListNode;
    newNode->dest = dest;
    newNode->weight = weight;
    return newNode;
}
 
// A utility function that creates a graph of V vertices or an array of lists of the form V:Connected Edges
Graph* createGraph(int V)
{
    Graph* graph = new Graph;
    graph->V = V;
    graph->array = new AdjList [V]; 
     return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest, double weight)
{
    //( insertion at head operation only)
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    // Since graph is undirected, add an edge from dest to src also
	// if it was directed, then we would simply skip this part =D -> FIND OUT FIRST IF DIRECTED/UNDIRECTED
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
// Structure to represent a min heap node
struct MinHeapNode
{
    int  v;
    double dist;
};
 
// Structure to represent a min heap
struct MinHeap
{
    int size;      // Number of heap nodes present currently -> length factor
    int capacity;  // Capacity of min heap -> heapsize
    int *pos;     // This is needed for decreaseKey()
    MinHeapNode **array; // we can also use a vector here
	MinHeap () { size = capacity = 0; pos = NULL; } // constructor
};
 
// An initialiser for the MinHeapNode
MinHeapNode* newMinHeapNode(int v, double dist)
{
    MinHeapNode* minHeapNode = new MinHeapNode;
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
// A function to create a Min Heap
MinHeap* createMinHeap(int capacity)
{
    MinHeap* minHeap =  new MinHeap;
    minHeap->pos = new int [capacity]; // this is the index for the array/heap
    minHeap->size = 0; // because nothing is added yet =)
    minHeap->capacity = capacity;
    minHeap->array = new MinHeapNode *[capacity]; // so now, we have an array of minheapnodes which are not pointing at each other. Not a linked list
    return minHeap;
}
 
// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b)
{
    MinHeapNode* t = *a;
    *a = *b;
    *b = t; // copying nodes
}
 
// Position is needed for decreaseKey()
void minHeapify(MinHeap* minHeap, int index)
{
    int smallest, left, right;
    smallest = index; 
    left = 2 * index + 1; // left child
    right = 2 * index + 2; // right child
 
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != index) // leave the smallest where it is 
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *indexNode = minHeap->array[index];
 
        // Swap positions // update pointers
        minHeap->pos[smallestNode->v] = index;
        minHeap->pos[indexNode->v] = smallest;
 
        // Swap nodes // exchange values
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[index]);
 
        minHeapify(minHeap, smallest);
    }
}
 
// A  function to check if the given minHeap is ampty or not
int isEmpty(MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    // Store the root node
    MinHeapNode* root = minHeap->array[0];// the minimum value is always at 0 =D
 
    // Replace root node with last node
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; // BIGGEST VALUE
    minHeap->array[0] = lastNode; // pointers are repointed. Remember that the list is not a linked list, its an array of pointers
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    --(minHeap->size);
    minHeapify(minHeap, 0); // sifting 
 
    return root;
}
 
// Function to decreasy dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(MinHeap* minHeap, int v, double dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist; // new key =( SADNESS
 
    // Travel up while the complete tree is not heapified.
    // This is a O(height of tree) loop
    while (i && (minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)) // if dist of child is less than that of parent
    {
        // Swap this node with its parent // swap pointers
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2; // child
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i; // parent 
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 
        // move to parent index and then continue. Now we are sifting up
        i = (i - 1) / 2;
    }
}
 
// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(MinHeap *minHeap, int v) // because we need nodes to be labelled 1,2,3,4...
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
 
// A utility function used to print the solution that is store in an array
void printArr(double dist[], int n)
{
	string arr[15] = {"SEECS", "SCME", "SMME", "RCMS", "IGIS", "SADA", "NBS", "ASAB", "CAMP", "HQ", "SCEE", "IqbalSquare", "Gate10", "Gate1", "RCMMW"};
	
    cout << "Vertex Distance from Source" << endl;
    for (int i = 0; i < n; ++i)
		cout << arr[i] << "\t" << dist[i] << " metres" << endl;
}
 
// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra(Graph* graph, int src)
{
    int V = graph->V;// Get the number of vertices in graph
    double *dist =  new double [V];     // dist values used to pick minimum weight edge 
	vector <int> a ; // for u
	vector <int> b ; // for v
	vector <int> c ; // for sum of distances
 
	for (int i = 0; i < V; i++) // initialising 
		dist[i] = 0;
		 // helps pick the minimum edge to follow// sorted by distances
    MinHeap* minHeap = createMinHeap(V);
 
    // Initialize min heap with all vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX; // in other words, infinity
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
 
    // Make dist value of src vertex as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]); // from infinite to 0 =O
 
    // Initially size of min heap is equal to V. when we extract, it decreases
    minHeap->size = V;
 
    // In the following loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum distance value
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number
 
        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        AdjListNode* MinNode = graph->array[u].head;// accessing one index of adjacency list
        while (MinNode != NULL)
        {
            int v = MinNode->dest;
 
            // If shortest distance to v is not finalized yet, and weight of u-v
            // plus dist of u from src is less than dist value of v, then update
            // distance value of v
            if (isInMinHeap(minHeap, v) && (MinNode->weight + dist[u]) < dist[v])
            {
                dist[v] = dist[u] + MinNode->weight;
				a.push_back(u);
				b.push_back(v);
				c.push_back(dist[v]);
 
                // update distance value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            MinNode = MinNode->next; // just like in a linked list 
        }
    }
    printArr(dist, V);
	printPath(a,b,c,V);
}
 
void printPath (vector<int>a , vector <int> b, vector<int> c, int V )
{	
	for ( int i = a.size()-1; i >= 0; i-- )
	{
		for ( int j = i-1; j >= 0; j-- ) // moving further one step to the righ
			if (b[i] == b[j])
			{
				a.erase(a.begin()+j);
				b.erase(b.begin()+j);
				c.erase(c.begin()+j);
				i = a.size()-1;
				j = i - 1;
			}		
	}
	cout <<endl;
	/*for ( int i = 0; i < a.size(); i++ )
		cout << a[i] << " " << b[i] << " " << c[i]  << endl;*/
	
	int **paths = new int*[V];
	for ( int i = 0; i < V; i++ )
		paths[i] = new int[V];
	
	for ( int i = 0 ; i < V; i ++ )
		for ( int j = 0 ; j < V; j ++ )
			paths[i][j] = -1;
	int s = b.size();
	for ( int i = 0; i < s/*V-1*/; i++ )// starting from the bottom of the list
	{
		paths[i][V-1] = b[b.size()-1];	
		paths[i][V-2] = a[a.size()-1];
		int k = V-2;
		for ( int j = b.size()-1; j >= 0; j -- )
		{
			if ( b[j] == paths[i][k] )
			{
				k--;
				paths[i][k] = a[j];
			}
		}
		b.pop_back();
		a.pop_back();
	}
	cout << endl;
	string arr[15] = {"SEECS", "SCME", "SMME", "RCMS", "IGIS", "SADA", "NBS", "ASAB", "CAMP", "HQ", "SCEE", "IqbalSquare", "Gate10", "Gate1", "RCMMW"};
	
	cout << "Paths: " << endl;
	for ( int i = 0; i < V; i ++ )
	{
		for ( int j = 0; j < V; j ++ )
			if ( paths[i][j] != -1 )
			cout << arr[paths[i][j]] << " ";
		cout << endl;
	}
}
 
void NUSTShortestPath()
{
    int V =  15;
	string arr[15] = {"SEECS", "SCME", "SMME", "RCMS", "IGIS", "SADA", "NBS", "ASAB", "CAMP", "HQ", "SCEE", "IqbalSquare", "Gate10", "Gate1", "RCMMW"};
	
	cout << "\n\t Your way around NUST:" << endl;
	
	for ( int i = 0; i < 15; i++ )
		cout <<i << " " << arr[i] << endl;
	
	int i = 0;

	do
	{
		cout << "Please select your source location:" << endl;	
		cin >> i;
	} while ( i > 14 || i < 0 );

	
    Graph* graph = createGraph(V);
    addEdge(graph, 0, 2, 1356.73);
    addEdge(graph, 0, 9, 715.7);
    addEdge(graph, 0, 10, 910.67);
    addEdge(graph, 0, 14, 288.039);
	addEdge(graph, 0, 11, 790.206);
	addEdge(graph, 1, 5, 565.707);
	addEdge(graph, 1, 6, 834.556);
    addEdge(graph, 1, 7, 725.413);
	addEdge(graph, 1, 9, 921.741);
	addEdge(graph, 1, 12, 1119.16);
    addEdge(graph, 2, 10, 935.82);
	addEdge(graph, 3, 7, 50.3152);
    addEdge(graph, 3, 8, 38.7723);
    addEdge(graph, 4, 5, 92.9356);
    addEdge(graph, 4, 6, 239.724);
	addEdge(graph, 4, 11, 182.305);
	addEdge(graph, 5, 6, 204.624);
	addEdge(graph, 5, 8, 84.0953);
	addEdge(graph, 6, 12, 1027.91);
	addEdge(graph, 7, 11, 86.0585);
	addEdge(graph, 9, 11, 599.424);
	addEdge(graph, 9, 12, 1076.1);
	addEdge(graph, 10, 11, 698.512);
	addEdge(graph, 10, 13, 704.699);
	addEdge(graph, 11, 13, 485.027);
	addEdge(graph, 11, 14, 276.508);
		
	dijkstra(graph, i);
	
}


# endif