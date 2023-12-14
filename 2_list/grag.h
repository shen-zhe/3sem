

class my_Graph {
public:
    int vertices;
    DoublyLinkedList<pair<int, int>>* adjacencyList;

    my_Graph(int V) : vertices(V) {
        adjacencyList = new DoublyLinkedList<pair<int, int>>[V];
    }

    void addEdge(int u, int v, int weight) {
        adjacencyList[u].push_back(make_pair(v, weight));
        adjacencyList[v].push_back(make_pair(u, weight)); // For undirected graph
    }

    void dijkstra(int start) {
        DoublyLinkedList<int> distance;
        DoublyLinkedList<bool> visited;

        for (int i = 0; i < vertices; ++i) {
            distance.push_back(INF);
            visited.push_back(false);
        }

        distance[start]->data = 0;

        for (int count = 0; count < vertices - 1; ++count) {
            int u = -1;
            // Find the vertex with the minimum distance that is not yet visited
            for (int i = 0; i < vertices; ++i) {
                if (!visited[i]->data && (u == -1 || distance[i]->data < distance[u]->data)) {
                    u = i;
                }
            }

            visited[u]->data = true;

            for (const auto& neighbor : adjacencyList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!visited[v]->data && distance[v]->data > distance[u]->data + weight) {
                    distance[v]->data = distance[u]->data + weight;
                }
            }
        }

        // Вывод кратчайших расстояний от начальной вершины
        cout << "Shortest distances from vertex " << start << ":\n";
        for (int i = 0; i < vertices; ++i) {
            cout << "To " << i << ": " << distance[i]->data << endl;
        }

    }

    ~my_Graph() {
        delete[] adjacencyList;
    }
};