#include "dijkstras.h"

struct Node {
    int vertex;
    int distance;
    
    Node(int v, int d) : vertex(v), distance(d) {}
    
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();
    
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    

    distances[source] = 0;
    pq.push(Node(source,0));

    while(!pq.empty()){
        int v2 = pq.top().vertex;
        pq.pop();

        if(visited[v2]){
            continue;
        }

        visited[v2] = true;

        for (const Edge& edge : G[v2]){
            int v1= edge.dst;
            int weight = edge.weight;
        if (!visited[v1] && distances[v2] != INF && distances[v2] + weight < distances[v1]) {
                distances[v1] = distances[v2] + weight;
                previous[v1] = v2;
                pq.push(Node(v1, distances[v1]));
            }
        }
    }
    
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    
    stack<int> s;
    for (int at = destination; at != -1; at = previous[at]) {
        s.push(at);
    }
    
    while (!s.empty()) {
        path.push_back(s.top());
        s.pop();
    }
    
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path exists" << endl;
        return;
    }
    
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    
    cout << " (edge cost: " << total << ")" << endl;
}