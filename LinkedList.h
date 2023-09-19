#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <time.h>

using std::ofstream;
using std::ifstream;
using std::cout;
using std::cin;
using std::string;

struct profile // Profile struct
{
    string name;
    int score;
};

struct node // Linked List code
{
    string command;
    string description;
    // Data points
    bool commandused;
    bool descriptionused; 
    // Boolean describe if command or description was used
    node *pNext;
    // Next node
};
