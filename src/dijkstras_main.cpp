#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <string>

int main() {
    {
        cout << "\nTesting small.txt" << endl;
        string filename = "small.txt";
        Graph G;

        try {
            file_to_graph(filename, G);
            cout << "Graph has " << G.numVertices << " vertices." << endl;
        
            int source = 0;
            vector<int> previous(G.numVertices, -1);
            
            vector<int> distances = dijkstra_shortest_path(G, source, previous);

            for (int i = 0; i < G.numVertices; ++i) {
                cout << "Path from " << source << " to " << i << ": ";
                
                if (distances[i] == INF) {
                    cout << "No path exists" << endl;
                    continue;
                }
                
                vector<int> path = extract_shortest_path(distances, previous, i);
                print_path(path, distances[i]);
            }
        }
        catch (const runtime_error& e) {
            cerr << "Error with small.txt: " << e.what() << endl;
        }
    }

    {
        cout << "\nTesting medium.txt" << endl;
        string filename = "medium.txt";
        Graph G;

        try {
            file_to_graph(filename, G);
            cout << "Graph has " << G.numVertices << " vertices." << endl;
        
            int source = 0;
            vector<int> previous(G.numVertices, -1);
            
            vector<int> distances = dijkstra_shortest_path(G, source, previous);

            for (int i = 0; i < G.numVertices; ++i) {
                cout << "Path from " << source << " to " << i << ": ";
                
                if (distances[i] == INF) {
                    cout << "No path exists" << endl;
                    continue;
                }
                
                vector<int> path = extract_shortest_path(distances, previous, i);
                print_path(path, distances[i]);
            }
        }
        catch (const runtime_error& e) {
            cerr << "Error with medium.txt: " << e.what() << endl;
        }
    }

    {
        cout << "\n Testing large.txt" << endl;
        string filename = "large.txt";
        Graph G;

        try {
            file_to_graph(filename, G);
            cout << "Graph has " << G.numVertices << " vertices." << endl;
        
            int source = 0;
            vector<int> previous(G.numVertices, -1);
            
            vector<int> distances = dijkstra_shortest_path(G, source, previous);

            for (int i = 0; i < G.numVertices; ++i) {
                cout << "Path from " << source << " to " << i << ": ";
                
                if (distances[i] == INF) {
                    cout << "No path exists" << endl;
                    continue;
                }
                
                vector<int> path = extract_shortest_path(distances, previous, i);
                print_path(path, distances[i]);
            }
        }
        catch (const runtime_error& e) {
            cerr << "Error with large.txt: " << e.what() << endl;
        }
    }

    {
        cout << "\nTesting largest.txt" << endl;
        string filename = "largest.txt";
        Graph G;

        try {
            file_to_graph(filename, G);
            cout << "Graph has " << G.numVertices << " vertices." << endl;
        
            int source = 0;
            vector<int> previous(G.numVertices, -1);
            
            vector<int> distances = dijkstra_shortest_path(G, source, previous);

            for (int i = 0; i < G.numVertices; ++i) {
                cout << "Path from " << source << " to " << i << ": ";
                
                if (distances[i] == INF) {
                    cout << "No path exists" << endl;
                    continue;
                }
                
                vector<int> path = extract_shortest_path(distances, previous, i);
                print_path(path, distances[i]);
            }
        }
        catch (const runtime_error& e) {
            cerr << "Error with largest.txt: " << e.what() << endl;
        }
    }

    return 0;
}