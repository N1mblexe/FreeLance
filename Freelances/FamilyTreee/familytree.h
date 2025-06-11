#ifndef FAMILY_TREE_H
#define FAMILY_TREE_H

#include "person.h"
#include <string>
#include <vector>
using namespace std;

class FamilyTree {
private:
    vector<Person> people;
    int findPersonIndex(const string& name) const;

public:
    // Constructor
    FamilyTree();

    // Tree management methods
    bool loadFromFile(const string& peopleFile, const string& relationshipsFile);
    void addPerson(string name, int birthYear);
    bool setParentChild(string parentName, string childName, bool isMother);

    // Query methods
    vector<string> findAncestors(const string& name, int generations) const;
    vector<string> findDescendants(const string& name, int generations) const;

    // Display methods
    void displayPerson(const string& name) const;
    void displayAllPeople() const;
};

#endif
