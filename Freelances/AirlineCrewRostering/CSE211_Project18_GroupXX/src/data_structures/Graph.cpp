#include "../../include/data_structures/Graph.hpp"

namespace ds {


Vertex::Vertex(std::string n) : name(n), edges() {}

bool Vertex::operator==(const Vertex& other) const { return name == other.name; }

bool Edge::operator==(const Edge& other) const { return flightId == other.flightId; }

void Graph::addAirport(const std::string& code) {
    vertices.push_back(Vertex(code));
}

void Graph::addFlight(const std::string& from, const std::string& to,
                      const std::string& id, int duration) {
    ListNode<Vertex>* curr = vertices.getHead();
    while (curr) {
        if (curr->data.name == from) {
            Edge newFlight = {to, id, duration};
            curr->data.edges.push_back(newFlight);
            return;
        }
        curr = curr->next;
    }
}

LinkedList<Vertex>* Graph::getVertices() { return &vertices; }

}  // namespace ds
