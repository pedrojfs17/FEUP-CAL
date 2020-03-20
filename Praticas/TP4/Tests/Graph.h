/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	int indegree;          // auxiliary field used by topsort
	bool processing;       // auxiliary field used by isDAG

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	friend class Graph<T>;
};

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v) const;
public:
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;
	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	// TODO (4 lines)
	// HINT: use the findVertex function to check if a vertex already exists
	if (findVertex(in) != NULL)
	    return false;

    this->vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	// TODO (6 lines)
	// HINT: use findVertex to obtain the actual vertices
	// HINT: use the next function to actually add the edge
	Vertex<T> * src = findVertex(sourc), * des = findVertex(dest);

	if (src == NULL || des == NULL)
	    return false;

	src->addEdge(des, w);
	return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	// TODO (1 line)
	this->adj.push_back(Edge<T>(d, w));
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	// TODO (5 lines)
	// HINT: Use "findVertex" to obtain the actual vertices.
	// HINT: Use the next function to actually remove the edge.
    Vertex<T> * src = findVertex(sourc), * des = findVertex(dest);

    return !(src == NULL || des == NULL || !src->removeEdgeTo(des));

}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	// TODO (6 lines)
	// HINT: use an iterator to scan the "adj" vector and then erase the edge.
	typename vector<Edge<T>>::iterator it = adj.begin();

	while (it != adj.end()) {
	    if ((*it).dest == d) {
	        adj.erase(it);
	        return true;
	    }
	    it++;
	}

	return false;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
	// TODO (10 lines)
	// HINT: use an iterator to scan the "vertexSet" vector and then erase the vertex.
	// HINT: take advantage of "removeEdgeTo" to remove incoming edges.
	typename vector<Vertex<T> *>::iterator it = vertexSet.begin(), aux = vertexSet.end();

	while(it != vertexSet.end()) {
	    if ((*it)->info == in)
	        aux = it;
	    else if (aux != vertexSet.end())
            (*it)->removeEdgeTo(*aux);
	    it++;
	}

	if (aux != vertexSet.end()) {
        // Delete the edges of the elements before
        it = vertexSet.begin();
        while (it != aux) {
            (*it)->removeEdgeTo(*aux);
            it++;
        }

        vertexSet.erase(aux);
        return true;
    }

	return false;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
	// TODO (7 lines)
	vector<T> res;
	typename vector<Vertex<T> *>::const_iterator it = vertexSet.begin();

	while (it != vertexSet.end()) {
        (*it)->visited = false;
	    it++;
	}

	it = vertexSet.begin();

	while(it != vertexSet.end()) {
	    if (!(*it)->visited)
	        dfsVisit(*it, res);
	    it++;
	}

	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	// TODO (7 lines)
    v->visited = true;
    res.push_back(v->info);
    typename vector<Edge<T>>::const_iterator it = v->adj.begin();
    while (it != v->adj.end()) {
        if (!(*it).dest->visited)
            dfsVisit((*it).dest, res);
        it++;
    }
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
	// TODO (22 lines)
	// HINT: Use the flag "visited" to mark newly discovered vertices .
	// HINT: Use the "queue<>" class to temporarily store the vertices.
	vector<T> res;
    typename vector<Vertex<T> *>::const_iterator it = vertexSet.begin();
    while (it != vertexSet.end()) {
        (*it)->visited = false;
        it++;
    }
    Vertex<T>* src = findVertex(source);
    Vertex<T>* v;
    queue<Vertex<T>*> Q;
    Q.push(src);

    while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        res.push_back(v->info);
        typename vector<Edge<T>>::const_iterator it2 = v->adj.begin();
        while (it2 != v->adj.end()) {
            if (!(*it2).dest->visited) {
                Q.push((*it2).dest);
                (*it2).dest->visited = true;
            }
            it2++;
        }
    }

	return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {
	// TODO (26 lines)
    // Step 1
    typename vector<Vertex<T> *>::const_iterator it = vertexSet.begin();
    while (it != vertexSet.end()) {
        (*it)->indegree = 0;
        it++;
    }

    // Step 2
    it = vertexSet.begin();
    while (it != vertexSet.end()) {
        typename vector<Edge<T>>::const_iterator it2 = (*it)->adj.begin();
        while (it2 != (*it)->adj.end()) {
            (*it2).dest->indegree++;
            it2++;
        }
        it++;
    }

    // Step 3
    queue<Vertex<T>*> C;

    // Step 4
    it = vertexSet.begin();
    while (it != vertexSet.end()) {
        if ((*it)->indegree == 0)
            C.push(*it);
        it++;
    }

    // Step 5
    vector<T> res;
    Vertex<T>* v;

    // Step 6
    typename vector<Edge<T>>::const_iterator it2;
    while (!C.empty()) {
        // Step 7
        v = C.front();
        C.pop();

        // Step 8
        res.push_back(v->info);

        // Step 9
        it2 = v->adj.begin();
        while (it2 != v->adj.end()) {
            // Step 10
            (*it2).dest->indegree--;

            // Step 11
            if ((*it2).dest->indegree == 0)
                C.push((*it2).dest);
            it2++;
        }
    }

    // Step 12
    if (res.size() != vertexSet.size())
        res.clear();

    return res;
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
	// TODO (28 lines, mostly reused)
    typename vector<Vertex<T> *>::const_iterator it = vertexSet.begin();

    while (it != vertexSet.end()) {
        (*it)->visited = false;
        it++;
    }

    Vertex<T>* src = findVertex(source), *v;
    inf = src->info;
    queue<Vertex<T>*> Q;
    Q.push(src);
    typename vector<Edge<T>>::const_iterator it2;

    int count, maxCount = 0;

    while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        count = 0;
        it2 = v->adj.begin();
        while (it2 != v->adj.end()) {
            if (!(*it2).dest->visited) {
                count++;
                Q.push((*it2).dest);
                (*it2).dest->visited = true;
            }
            it2++;
        }
        if (count > maxCount) {
            maxCount = count;
            inf = v->info;
        }
    }

    return maxCount;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
	// TODO (9 lines, mostly reused)
	// HINT: use the auxiliary field "processing" to mark the vertices in the stack.
    typename vector<Vertex<T> *>::const_iterator it = vertexSet.begin();
    while (it != vertexSet.end()) {
        (*it)->processing = false;
        it++;
    }
    it = vertexSet.begin();

    while(it != vertexSet.end()) {
        if (!(*it)->processing) {
            if (!dfsIsDAG(*it))
                return false;
        }
        it++;
    }

	return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
	// TODO (12 lines, mostly reused)
    v->processing = true;
    typename vector<Edge<T>>::const_iterator it = v->adj.begin();
    while (it != v->adj.end()) {
        if (!(*it).dest->processing) {
            if (!dfsIsDAG((*it).dest))
                return false;
            it++;
        }
        else
            return false;
    }
    v->processing = false;
	return true;
}

#endif /* GRAPH_H_ */
