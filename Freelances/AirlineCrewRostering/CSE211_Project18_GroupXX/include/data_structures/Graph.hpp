/**
 * @file Graph.hpp
 * @brief Simple graph structure representing airports and flights between them.
 */

#pragma once

#include "LinkedList.hpp"
#include <string>

namespace ds {

struct Edge;

/**
 * @struct Vertex
 * @brief Vertex representing an airport and its outgoing edges.
 */
struct Vertex {
    std::string name;
    LinkedList<Edge> edges;
    Vertex(std::string n);
    bool operator==(const Vertex& other) const;
};

/**
 * @struct Edge
 * @brief Edge representing a flight connection to another vertex.
 */
struct Edge {
    std::string toVertex;
    std::string flightId;
    int durationMinutes;
    bool operator==(const Edge& other) const;
};

/**
 * @class Graph
 * @brief Stores `Vertex` nodes and provides utility to add flights/airports.
 */
class Graph {
private:
    LinkedList<Vertex> vertices;

public:
    void addAirport(const std::string& code);
    void addFlight(const std::string& from, const std::string& to,
                   const std::string& id, int duration);

    LinkedList<Vertex>* getVertices();
};

}