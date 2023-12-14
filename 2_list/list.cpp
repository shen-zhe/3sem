#include "bibl.h"


int main() {
    
    my_Graph g(100);
    Graph h(100);

    for (int i = 0; i < 1000; ++i) {
        int source = rand() % 100;
        int destination = rand() % 100;
        int weight = rand() % 100 + 1; // Вес случайный от 1 до 100

        g.addEdge(source, destination, weight);
        h.addEdge(source, destination, weight);
    }

    //--------------------мой список---------------

    auto start = high_resolution_clock::now();
    int startVertex = 0;
    g.dijkstra(startVertex);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    auto c1 = duration.count();
    cout << "Your implementation time: " << c1 << " nanoseconds" << endl;

    //----------------------библиотека STL------------------

    start = high_resolution_clock::now();
    startVertex = 0;
    h.dijkstra(startVertex);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end - start);
    auto c2 = duration.count();
    cout << "Your implementation time: " << c2 << " nanoseconds" << endl;

    cout << "time different: "<< c1 - c2 << " nanoseconds" << endl;

    return 0;
}

