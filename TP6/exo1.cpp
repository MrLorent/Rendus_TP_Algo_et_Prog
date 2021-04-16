#include "tp6.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;

void Graph::buildFromAdjenciesMatrix(int **adjacencies, int nodeCount)
{
	/**
	  * Make a graph from a matrix
	  * first create all nodes, add it to the graph then connect them
	  * this->appendNewNode
	  * this->nodes[i]->appendNewEdge
	  */
    for(int i=0; i<nodeCount; i++){
        this->appendNewNode(new GraphNode(i));
    }

    for(int i=0; i<nodeCount; i++){
        for(int j=0; j<nodeCount; j++){
            if(adjacencies[i][j] != 0){
                this->nodes[i]->appendNewEdge(this->nodes[j],adjacencies[i][j]);
            }
        }
    }

}

void Graph::deepTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[])
{
	/**
      * Fill nodes array by travelling graph starting from first
      * and using recursivity
	  */
    nodes[nodesSize] = first;
    nodesSize++;
    visited[first->value] = true;

    Edge * tmp = first->edges;

    while(tmp != NULL){
        if(!visited[tmp->destination->value]){
            deepTravel(tmp->destination, nodes, nodesSize, visited);
        }
        tmp = tmp->next;
    }

}

void Graph::wideTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[])
{
	/**
	 * Fill nodes array by travelling graph starting from first and using queue
	 * nodeQueue.push(a_node)
	 * nodeQueue.front() -> first node of the queue
	 * nodeQueue.pop() -> remove first node of the queue
	 * nodeQueue.size() -> size of the queue
	 */
	std::queue<GraphNode*> nodeQueue;
	nodeQueue.push(first);


    while(!nodeQueue.empty()){
        GraphNode * current = nodeQueue.front();
        nodeQueue.pop();
        nodes[nodesSize] = current;
        nodesSize++;
        visited[current->value] = true;

        Edge * tmp = current->edges;

        while(tmp != NULL){
            if(!visited[tmp->destination->value]){
                nodeQueue.push(tmp->destination);
            }
            tmp = tmp->next;
        }
    }
}

bool Graph::detectCycle(GraphNode *first, bool visited[])
{
	/**
	  Detect if there is cycle when starting from first
	  (the first may not be in the cycle)
	  Think about what's happen when you get an already visited node
	**/
    bool cycle = false;
    std::queue<GraphNode*> nodeQueue;
    nodeQueue.push(first);


    while(!nodeQueue.empty() && !cycle){
        GraphNode * current = nodeQueue.front();
        nodeQueue.pop();
        visited[current->value] = true;

        Edge * tmp = current->edges;

        while(tmp != NULL && !cycle){
            if(tmp->destination == first){
                cycle = true;
            }else{
                if(!visited[tmp->destination->value]){
                    nodeQueue.push(tmp->destination);
                }
            }
            tmp = tmp->next;
        }
    }

    return cycle;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 150;
	w = new GraphWindow();
	w->show();

	return a.exec();
}
