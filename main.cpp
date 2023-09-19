#include "LinkedList.h"

/*ADVANTAGES/DISADVANTAGES LINKED LIST
Advantages - Linked lists are very easy to expand
Disadvantages - Linked lists have to be itterated through and therefore are not 
good if you are trying to randomly access information */


/*ADVANTAGES/DISADVANTAGES ARRAY
Advantages - Arrays are very easy to find information that are in a random spot in the structure
Disadvantages - Arrays are not good for expanding because you must rewrite the whole array when you need to expand it
because it is all seqential in memory*/




using std::ofstream;
using std::ifstream;
using std::cout;
using std::cin;
using std::string;

//in main because i could not get strings to work with the typename 
template <typename T1, typename T2> //will be used for command and description
class LinkedList // Linked List class
{
private:
    node *pHead;
public:
    LinkedList() // Constructor
    {
        pHead = NULL; 
    }
    ~LinkedList() // Destructor
    {
        node* pNew;
        
        while (pHead != NULL) 
        {
            pNew = pHead;
            pHead = pHead->pNext;
            free(pNew);
        }
        //deletes each node from the head onward
    };
    node *getHead() // Finds and returns the head
    {
        return pHead;
    }
    void insertAtFront(T1 command, T2 description) // Inserts a new node at the front 
    {
        node *newNode = new node;
        newNode->command = command;
        newNode->description = description;
        newNode->pNext = NULL;
        newNode->commandused = false;
        newNode->descriptionused = false;
        //creates a new node using the information passed in
        if (pHead == NULL) //checks to see if the current pointer is empty
        {
            pHead = newNode;
        }
        else
        {
            newNode->pNext = pHead;
            pHead = newNode;
            //itterates to the next pointer in the list
        }
    }
    void removeNode(T1 command) // Removes a node based off a command
    {
        node *pPrev = NULL;
        node *pTemp = pHead;
        while (pTemp->command != command && pTemp != NULL)  // itterates through the list to find
        {                                                   // the node that matches the command
            pPrev = pTemp;                                  // or until reaches end
            pTemp = pTemp->pNext;
        }
        if (pTemp->command == command) // if command matched is gound
        {
            if (pPrev != NULL) //if first in list
            {
                pPrev->pNext = pTemp->pNext;
                free(pTemp);
            }
            else 
            {
                pHead = pTemp->pNext;
            }
        }
    }
};
void writeList(LinkedList<string, string> in) // File reading and writing
{
    ofstream outfile; 
    outfile.open("commands.csv");
    if (!outfile.is_open()) 
    {
        cout << "Error opening commands file";
    }

    node *pTemp = in.getHead();
    
    while (pTemp != NULL) 
    {
        
        outfile << pTemp->command << ", \"" << pTemp->description << "\"\n";
        pTemp = pTemp->pNext;
    }

    outfile.close();
}

void writeProfiles(profile profiles[100]) 
{
    ofstream outfile;
    outfile.open("profiles.csv");
    if (!outfile.is_open()) {
        cout << "Error opening profiles file";
    }

    

    for (int i = 0; !profiles[i].name.empty(); i++) {

        outfile << profiles[i].name << ", " << profiles[i].score << "\n";
    }

    outfile.close();
}

void readList(LinkedList<string, string>* out)  //reads the commands from the csv file and inserts them into the file
{
    ifstream infile;
    infile.open("commands.csv");
    if (!infile.is_open()) {
        cout << "Error opening commands file";
    }

    string line, temp, temp2;

    while (getline(infile, line)) {
        std::stringstream str(line);

        getline(str, temp, ',');
        getline(str, temp2, ',');
        temp2.erase(0,2);
        temp2.pop_back();

        out->insertAtFront(temp, temp2);
    }

    infile.close();
}

void readProfiles(profile (&profiles)[100]) 
{
    ifstream infile;
    infile.open("profiles.csv");
    if (!infile.is_open())
    {
        cout << "Error opening profile file";
    }
    
    string line, temp, temp2;
    int i = 0;
    while (getline(infile, line)) {
        std::stringstream str(line);
        
        getline(str, temp, ',');
        getline(str, temp2, ',');
        temp2.erase(0, 1);
        profile newProfile;
        newProfile.name = temp;
        newProfile.score = stoi(temp2);
        profiles[i] = newProfile;
        i++;
    }
    
    infile.close();
}


void printRules() // print rules
{
    cout << "\n\nRules:\nA command will be shown along with three choices. One of these choices is the correct description\n";
    cout << "You must enter the number that corresponds with the correct choice\nIf you're right you score goes up by one and if you're wrong it go down by one\n";
    // Print rules
    cout << "Press anything to return to the menu...\n";
    getchar(); // wait for input and go back to menu
    getchar();
}

void runGame(LinkedList<string, string> list, profile *playerProfile, profile (&profileList)[100]) // Runs the game
{

    if (playerProfile == NULL) { //gets player profile
        int i = 0;
        do {
            i++;
        } while(!profileList[i].name.empty());
        playerProfile = &profileList[i];
        cout << "\n\nInsert your profile name: \n";
        cin >> playerProfile->name;
        playerProfile->score = 0;
    }
    int score = playerProfile->score;

    int num = 0; // Asks for number of rounds (5-30)
    do {
        cout << "\n\nPlease select the number of rounds (5-30):\n";
        cin >> num;
    } while (num < 5 || num > 30);

    int numOfNodes = 0; // Count the number of items in the linked list
    node *pTemp = list.getHead();
    while (pTemp != NULL) { //checks the amount of nodes in the linked list containing commands 
        numOfNodes++;
        pTemp->commandused = false;
        pTemp->descriptionused = false;
        pTemp = pTemp->pNext;
    } //finds number of nodes in list
    for(int i = 0; i < num; i++) {
        int random;
        node *rightdescriptionNode;
        do { // gets random commands 
            rightdescriptionNode = list.getHead();
            random = rand() % numOfNodes;
            for(int i = 0; i < random; i++)
            {
                rightdescriptionNode = rightdescriptionNode->pNext;
            }
        } while (rightdescriptionNode->commandused);
        rightdescriptionNode->commandused = true;
        node *wrongdescription1 = list.getHead();
        node *wrongdescription2 = list.getHead();
        
        do { //gets second description 
            wrongdescription1 = list.getHead();
            random = rand() % numOfNodes;
            for (int i = 0; i < random; i++) {
                wrongdescription1 = wrongdescription1->pNext;
            }

        } while (wrongdescription1->commandused || wrongdescription1->descriptionused);
        wrongdescription1->descriptionused = true;
        do { //gets third description 
            wrongdescription2 = list.getHead();
            random = rand() % numOfNodes;
            for (int i = 0; i < random; i++) {
                wrongdescription2 = wrongdescription2->pNext;
            }
        
        } while (wrongdescription2->commandused || wrongdescription2->descriptionused);
        wrongdescription1->descriptionused = false;

        int randomDesc = rand() % 3;// Now we have the right description node and two other description nodes
        cout << "\n\nScore: " << score;
        cout << "\nWhich description matches: " << rightdescriptionNode->command << "\n";
        bool correct = false;
        int answer = 0;
        if (randomDesc == 0) { //if right decision is one
            cout << "1. " << rightdescriptionNode->description << "\n";
            cout << "2. " << wrongdescription1->description << "\n";
            cout << "3. " << wrongdescription2->description << "\n";
            do {
                cin >> answer;
            } while (answer < 1 || answer > 3);
            if (answer == 1) {
                correct = true;
            }

        }
        else if (randomDesc == 1) {// if right description is two
            cout << "1. " << wrongdescription1->description << "\n";
            cout << "2. " << rightdescriptionNode->description << "\n";
            cout << "3. " << wrongdescription2->description << "\n";
            do {
                cin >> answer;
            } while (answer < 1 || answer > 3);
            if (answer == 2) {
                correct = true;
            }
        }
        else { //if right description is three
            cout << "1. " << wrongdescription1->description << "\n";
            cout << "2. " << wrongdescription2->description << "\n";
            cout << "3. " << rightdescriptionNode->description << "\n";
            do {
                cin >> answer;
            } while (answer < 1 || answer > 3);
            if (answer == 3) {
                correct = true;
            }
        }

        if (correct) {
            score++;
        }
        else {
            score--;
        }
        

    }
    
    playerProfile->score = score;
    cout << "\n\n" << score << "\n\n";
}

profile* loadGame(profile profiles[100]) // Loads game
{
    profile newProfile;
    newProfile.score = 0;
    // Loads a profile and then runs the game with that profile
    string input;

    do {
        cout << "\n\nPlease input the name of your profile or type 'quit'\n";

        cin >> input;

        for (int i = 0; !profiles[i].name.empty(); i++) {
            if (input == profiles[i].name) {
                cout << "\nCurrent score: " << profiles[i].score;
                return &profiles[i];
            }
        }

        cout << "\nNo profile found with that name.\n";
    } while (input != "quit");
    return &newProfile;
}


void addCommand(LinkedList<string, string> *list) // Add command
{
    string name;
    string description;
    
    do {
        cout << "\n\nName of the command you would like to add (type 'quit' to exit): \n";
        cin >> name;
        node *pTemp = list->getHead();

        while (pTemp != NULL) {
            if (pTemp->command == name) {
                name = "INVALID";
                cout << "\nDuplicate name.\n";
            }
            pTemp = pTemp->pNext;
        }
    } while (name == "INVALID");
    // Adds a command to the linked list
    if (name == "quit") {
        return;
    }

    cout << "\nDescription of the command you would like to add: \n";
    cin >> description;

    list->insertAtFront(name, description);
}

void removeCommand(LinkedList<string, string> *list) // Remove command
{
    string name;
    do {
        cout << "\n\nName of the command you would like to remove (type 'quit' to exit): \n";
        cin >> name;
        node *pTemp = list->getHead();

        while (pTemp != NULL) {
            if (pTemp->command == name) {
                list->removeNode(name);
                return;
            }
            pTemp = pTemp->pNext;
        }
        cout << "\nThat command does not exist.\n";
    } while (name != "quit");
    // Removes a command from the linked list
    if (name == "quit") {
        return;
    }
}

int menu() 
{
    int userChoice = 0;
    do {
        cout << "\n\nPlease select an option listed below:\n";
        cout << "1. Game Rules\n";
        cout << "2. Play Game\n";
        cout << "3. Load Previous Game\n";
        cout << "4. Add Command\n";
        cout << "5. Remove Command\n";
        cout << "6. Exit\n";
        cin >> userChoice;
    } while (userChoice < 1 || userChoice > 6);

    return userChoice;
}

int main(int, char**)// Main
{
    srand(time(0));

    LinkedList<string, string> list;
    readList(&list);

    profile profileList[100];
    readProfiles(profileList);
    profile *playerProfile;

    int choice = 0;
    do {
        choice = menu();

        if (choice == 1) {
            printRules();
        }
        else if (choice == 2) {
            runGame(list, playerProfile, profileList);
        }
        else if (choice == 3) {
            playerProfile = loadGame(profileList);
            runGame(list, playerProfile, profileList);
        }
        else if (choice == 4) {
            addCommand(&list);
        }
        else if (choice == 5) {
            removeCommand(&list);
        }
    } while(choice != 6);

    
    writeList(list);
    writeProfiles(profileList);
    // Exit the game
}