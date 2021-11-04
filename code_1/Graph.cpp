#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;


void Graph::addVertex(string name){
    //TODO
    vector<vertex*> ver = getVertices();
    for (int i = 0; i < ver.size(); i++) {
        if (ver[i]->name == name) {
            cout << ver[i]->name << " found." << endl;
            return;
        }
    }

    vertex* temp = new vertex;
    temp->name = name;
    vertices.push_back(temp);
}

void Graph::addEdge(string v1, string v2){
    //TODO
    vector<vertex*> ver = getVertices();
    vertex* vertex1 = NULL;
    vertex* vertex2 = NULL;
    for (int i = 0; i < ver.size(); i++) {
        if (ver[i]->name == v1) {
            vertex1 = ver[i];
        } else if (ver[i]->name == v2) {
            vertex2 = ver[i];
        }
    }

    if (vertex1 == NULL || vertex2 == NULL) {
        return;
    }

    adjVertex* temp = new adjVertex;
    temp->v = vertex2;
    vertex1->adj.push_back(*temp);

    adjVertex* temp2 = new adjVertex;
    temp2->v = vertex1;
    vertex2->adj.push_back(*temp2);
}

void Graph::displayEdges(){
    //TODO
    vector<vertex*> ver = getVertices();
    for (int i = 0; i < ver.size(); i++) {
        cout << ver[i]->name << " --> ";
        for (int j = 0; j < ver[i]->adj.size(); j++) {
            cout << ver[i]->adj[j].v->name << " ";
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex){
    //TODO
    vertex *vStart;
    vector<vertex*> ver = getVertices();
    queue<vertex*> q;

    for(int i = 0; i < ver.size(); i++)
    {
        if(ver[i]->name == sourceVertex)
        {
            vStart = ver[i];
        }
    }

    vStart->visited = true;
    q.push(vStart);

    vertex *curr;

    cout<< "Starting vertex (root): " << vStart->name << "-> ";

    while(!q.empty()){
        curr = q.front();
        q.pop();

        for(int i = 0; i < curr->adj.size(); i++)
        {
            if (curr->adj[i].v->visited == false) {
                curr->adj[i].v->visited = true;
                curr->adj[i].v->distance = curr->distance + 1;
                cout << curr->adj[i].v->name <<"("<< curr->adj[i].v->distance <<")"<< " ";
                q.push(curr->adj[i].v);
            }
        }
    }

    cout << endl << endl;
}

void BFTHelper(vector<vertex*>* seen, vertex* vStart) {
    queue<vertex*> q;

    vStart->visited = true;
    q.push(vStart);

    vertex *curr;

    while(!q.empty()){
        curr = q.front();
        q.pop();

        for(int i = 0; i < curr->adj.size(); i++)
        {
            if (curr->adj[i].v->visited == false) {
                curr->adj[i].v->visited = true;
                curr->adj[i].v->distance = curr->distance + 1;
                q.push(curr->adj[i].v);
                seen->push_back(curr->adj[i].v);
            }
        }
    }
}

int Graph::getConnectedBuildings() {
    //TODO
    vector<vertex*> vers = getVertices();
    vector<vertex*> *seen = new vector<vertex*>;
    vertex* temp = NULL;
    int counter = 1;

    BFTHelper(seen, vers[0]);

    for (int i = 1; i < vers.size(); i++) {
        bool isSeen = false;

        for (int j = 0; j < seen->size(); j++) {
            if (vers[i] == seen->at(j)) {
                isSeen = true;
            }
        }

        if (!isSeen) {
            counter++;
            BFTHelper(seen, vers[i]);
        }
    }

    return counter;
}

