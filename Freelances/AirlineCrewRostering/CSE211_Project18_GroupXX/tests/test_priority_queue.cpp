#include <iostream>
#include <data_structures/PriorityQueue.hpp>

int main() {
    using namespace ds;
    PriorityQueue<int> pq;
    if (!pq.isEmpty()) { std::cerr << "Fail: empty at start" << std::endl; return 1; }

    pq.push(10);
    pq.push(5);
    pq.push(20);
    pq.push(15);

    if (pq.getSize() != 4) { std::cerr << "Fail: size expected 4" << std::endl; return 1; }

    int v = pq.pop();
    if (v != 20) { std::cerr << "Fail: expected 20, got " << v << std::endl; return 1; }
    if (pq.getSize() != 3) { std::cerr << "Fail: size expected 3" << std::endl; return 1; }

    v = pq.pop();
    if (v != 15) { std::cerr << "Fail: expected 15, got " << v << std::endl; return 1; }

    v = pq.pop();
    if (v != 10) { std::cerr << "Fail: expected 10, got " << v << std::endl; return 1; }

    v = pq.pop();
    if (v != 5) { std::cerr << "Fail: expected 5, got " << v << std::endl; return 1; }

    if (!pq.isEmpty()) { std::cerr << "Fail: expected empty" << std::endl; return 1; }

    std::cout << "PriorityQueue tests passed\n";
    return 0;
}
