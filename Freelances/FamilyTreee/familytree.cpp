#include "familytree.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor
FamilyTree::FamilyTree() {}

int FamilyTree::findPersonIndex(const string& name) const 
{
    for (size_t i = 0; i < people.size(); ++i) 
        if (people[i].getName() == name)
            return static_cast<int>(i);

    return -1;
}

void FamilyTree::addPerson(string name, int birthYear) 
{
    if (findPersonIndex(name) != -1)
        std::cout << "Person " << name << " already exists." << std::endl;
    
    people.push_back(Person(name, birthYear));
}

bool FamilyTree::setParentChild(string parentName, string childName, bool isMother) 
{

    int parentIdx = findPersonIndex(parentName);
    int childIdx = findPersonIndex(childName);

    if (parentIdx == -1 || childIdx == -1) 
        return false;

    if (isMother)
        people[childIdx].setMotherName(parentName);
    else
        people[childIdx].setFatherName(parentName);

    people[parentIdx].addChildName(childName);

    return true;
}

bool FamilyTree::loadFromFile(const string& peopleFile, const string& relationshipsFile) 
{
    ifstream pf(peopleFile);
    ifstream rf(relationshipsFile);

    if (!pf.is_open() || !rf.is_open()) 
        return false;
   
    string name;
    int birthYear;

    while (pf >> name >> birthYear) 
        addPerson(name, birthYear);

    string fatherName, motherName, childName;

    while (rf >> fatherName >> motherName >> childName) 
    {
        if (findPersonIndex(childName) == -1 || findPersonIndex(motherName) == -1 || findPersonIndex(fatherName) == -1)
            continue;

        bool motherCheck = setParentChild(motherName, childName, true);   // isMother = true
        bool fatherCheck = setParentChild(fatherName, childName, false);  // isMother = false
    }

    pf.close();
    rf.close();

    return true;
}

vector<string> FamilyTree::findAncestors(const string& name, int generations) const 
{
    vector<string> result;

    if (generations <= 0) return result;

    int idx = findPersonIndex(name);
    if (idx == -1) return result;

    string mother = people[idx].getMotherName();
    string father = people[idx].getFatherName();

    if (!mother.empty()) 
    {
        result.push_back("Generation " + to_string(generations) + ": " + mother);
        vector<string> motherAncestors = findAncestors(mother, generations - 1);
        result.insert(result.end(), motherAncestors.begin(), motherAncestors.end());
    }

    if (!father.empty()) 
    {
        result.push_back("Generation " + to_string(generations) + ": " + father);
        vector<string> fatherAncestors = findAncestors(father, generations - 1);
        result.insert(result.end(), fatherAncestors.begin(), fatherAncestors.end());
    }

    return result;
}

vector<string> FamilyTree::findDescendants(const string& name, int generations) const 
{
    vector<string> result;

    if (generations <= 0) return result;

    int idx = findPersonIndex(name);
    if (idx == -1) return result;

    const vector<string>& children = people[idx].getChildrenNames();
    for (const string& childName : children) 
    {
        result.push_back(to_string(generations) + childName);
        vector<string> childDescendants = findDescendants(childName, generations - 1);
        result.insert(result.end(), childDescendants.begin(), childDescendants.end());
    }

    return result;
}

void FamilyTree::displayPerson(const string& name) const 
{
    int idx = findPersonIndex(name);
    
    if (idx == -1) 
        return;

    const Person& p = people[idx];
    const string FN = p.getFatherName();
    const string MN = p.getMotherName();

    cout << "Name: " << p.getName() << endl;
    cout << "Birth Year: " << p.getBirthYear() << endl;
    
    cout << "Parents: ";
    if(FN == "" && MN == "")
        cout << "None";
    else if(FN == "")
        cout << MN << " (mother)";
    else if(MN == "")
        cout << FN << " (father)";
    else
        cout << FN << " (father), " << MN << " (mother)";

    cout << endl;


    cout << "Children: ";
    vector<string> children = p.getChildrenNames();
    if(children.size() == 0)
        cout << "None";

    
    else for (size_t i = 0; i < children.size(); ++i) 
    {
        cout << children[i];

        if (i != children.size() - 1) 
            cout << ", ";
    }
    cout << endl;

}

void FamilyTree::displayAllPeople() const 
{

    for (const Person& p : people) 
    {
        displayPerson(p.getName());
        cout << "------------------------" << endl;
    }
}

void displayMenu() 
{
    cout << endl
        << "Menu:\n"
        << "1. Display a person's information\n"
        << "2. Find ancestors of a person\n"
        << "3. Find descendants of a person\n"
        << "4. Add a new person\n"
        << "5. Add a parent-child relationship\n"
        << "6. Exit\n"
        << "Enter choice: ";
}
void printByGeneration(const std::vector<std::string>& input)
{
    std::vector<int> gens;

    for (const std::string& item : input) {
        if (item.empty()) continue;

        int gen = item[0] - '0';

        bool found = false;
        for (size_t i = 0; i < gens.size(); ++i) {
            if (gens[i] == gen) {
                found = true;
                break;
            }
        }
        if (!found) {
            gens.push_back(gen);
        }
    }

    for (size_t i = 0; i < gens.size(); ++i) {
        for (size_t j = i + 1; j < gens.size(); ++j) {
            if (gens[i] > gens[j]) {
                int temp = gens[i];
                gens[i] = gens[j];
                gens[j] = temp;
            }
        }
    }

    int maxGen = gens.empty() ? 0 : gens.back();

    for (int i = static_cast<int>(gens.size()) - 1; i >= 0; --i) {
        int gen = gens[i];

        std::cout << "Generation " << gens.size() - gen + 1 << ": ";

        bool first = true;
        for (const std::string& item : input) {
            if (!item.empty() && (item[0] - '0') == gen) {
                std::string name = item.substr(1);
                if (!first) std::cout << ", ";
                std::cout << name;
                first = false;
            }
        }
        std::cout << std::endl;
    }
}


int main() {
    FamilyTree familyTree;

    string peopleFile, relationshipsFile;
    cout << "Enter people file name: ";
    getline(cin, peopleFile);
    cout << "Enter relationships file name: ";
    getline(cin, relationshipsFile);

    if (!familyTree.loadFromFile(peopleFile, relationshipsFile)) {
        cout << "Failed to load family tree files.\n";
        return 1;
    }

    cout << "Family tree loaded successfully!\n";

    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Enter person name: ";
            string name;
            getline(cin, name);
            familyTree.displayPerson(name);

        }
        else if (choice == 2)
        {
            cout << "Enter person name: ";
            string name;
            getline(cin, name);
            cout << "Enter number of generations to search: ";
            int generations;
            cin >> generations;
            cin.ignore();

            vector<string> ancestors = familyTree.findAncestors(name, generations);
            cout << "Ancestors of " << name << " (up to " << generations << " generations):\n";
            if (ancestors.empty())
            {
                cout << "No known ancestors for " << name << ".\n";
            }
            else
            {
                std::reverse(ancestors.begin(), ancestors.end());
                for (const auto& ancestor : ancestors) {
                    cout << ancestor << "\n";
                }
            }

        }
        else if (choice == 3)
        {
            cout << "Enter person name: ";
            string name;
            getline(cin, name);
            cout << "Enter number of generations to search: ";
            int generations;
            cin >> generations;
            cin.ignore();

            vector<string> descendants = familyTree.findDescendants(name, generations);

            cout << "Descendants of " << name << " (up to " << generations << " generations):\n";
            if (descendants.empty()) {
                cout << "No known descendants for " << name << ".\n";
            }
            else {
                printByGeneration(descendants);
            }

        }
        else if (choice == 4)
        {
            cout << "Enter name: ";
            string name;
            getline(cin, name);
            cout << "Enter birth year: ";
            int birthYear;
            cin >> birthYear;
            cin.ignore();

            familyTree.addPerson(name, birthYear);
        }
        else if (choice == 5)
        {
            cout << "Enter parent name: ";
            string parentName;
            getline(cin, parentName);
            cout << "Is this parent a mother (m) or father (f)? ";
            char parentType;
            cin >> parentType;
            cin.ignore();

            cout << "Enter child name (or type '-' for no child): ";
            string childName;
            getline(cin, childName);

            if (childName == "-") {
                cout << "No child name entered. Relationship not added.\n";
                continue;
            }

            bool isMother = (parentType == 'm' || parentType == 'M');
            bool success = familyTree.setParentChild(parentName, childName, isMother);

            if (success) {
                cout << "Relationship added successfully.\n";
            }
            else {
                cout << "Person not found: " << parentName << "\n";
                cout << "Failed to add relationship.\n";
            }

        }
        else if (choice == 6) {
            cout << "Goodbye!\n";
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
