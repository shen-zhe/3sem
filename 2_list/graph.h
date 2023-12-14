
class Graph {
public:
    int vertices;
    list<pair<int, int>>* adjacencyList;

    Graph(int V) : vertices(V) {
        adjacencyList = new list<pair<int, int>>[V];
    }

    void addEdge(int u, int v, int weight) {
        adjacencyList[u].push_back(make_pair(v, weight));
        adjacencyList[v].push_back(make_pair(u, weight)); // For undirected graph
    }

    void dijkstra(int start) {
        int* distance = new int[vertices];
        bool* visited = new bool[vertices];

        for (int i = 0; i < vertices; ++i) {
            distance[i] = INF;
            visited[i] = false;
        }

        distance[start] = 0;

        for (int count = 0; count < vertices - 1; ++count) {
            int u = -1;
            // Find the vertex with the minimum distance that is not yet visited
            for (int i = 0; i < vertices; ++i) {
                if (!visited[i] && (u == -1 || distance[i] < distance[u])) {
                    u = i;
                }
            }

            visited[u] = true;

            for (const auto& neighbor : adjacencyList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!visited[v] && distance[v] > distance[u] + weight) {
                    distance[v] = distance[u] + weight;
                }
            }
        }

        // Вывод кратчайших расстояний от начальной вершины
        cout << "Shortest distances from vertex " << start << ":\n";
        for (int i = 0; i < vertices; ++i) {
            cout << "To " << i << ": " << distance[i] << endl;
        }

        delete[] distance;
        delete[] visited;
    }

    ~Graph() {
        delete[] adjacencyList;
    }
};
