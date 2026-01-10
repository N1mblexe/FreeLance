#include <iostream>
#include <data_structures/LinkedList.hpp>
#include <data_structures/Graph.hpp>
#include <data_structures/PriorityQueue.hpp>
#include <data_structures/HashMap.hpp>

int main() {
    using namespace ds;

    LinkedList<int> li;
    li.push_back(10);
    li.push_back(20);
    std::cout << "LinkedList size: " << li.getSize() << "\n";

    PriorityQueue<int> pq;
    pq.push(5);
    pq.push(15);
    std::cout << "PriorityQueue empty: " << pq.isEmpty() << "\n";

    HashMap<std::string,int> hm;
    hm.put("a", 42);
    int* v = hm.get("a");
    std::cout << "HashMap['a'] = " << (v ? *v : -1) << "\n";

    Graph g;
    g.addAirport("JFK");
    g.addAirport("LAX");
    g.addFlight("JFK", "LAX", "FL1", 300);
    auto verts = g.getVertices();
    std::cout << "Graph vertices present: " << (verts && !verts->isEmpty()) << "\n";

    return 0;
}
