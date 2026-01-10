#pragma once

#include "LinkedList.hpp"
#include <string>

namespace ds {

    struct Edge;

    struct Vertex {
        std::string name;
        LinkedList<Edge> edges;
        Vertex(std::string n);

        bool operator==(const Vertex& other) const;
    };

    struct Edge {
        std::string toVertex; 
        std::string flightId; 
        int durationMinutes;
        bool operator==(const Edge& other) const;
    };

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