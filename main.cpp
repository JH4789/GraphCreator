using namespace std;
#include <iostream>
#include <cstring>
#include <string>
//Functions, wheeeeee!
void addVertex(bool occupancytable[], int adjacencytable[][20], char labeltable[]);
void addEdge(bool occupancytable[], int adjacencytable[][20], char labeltable[]);
void delEdge(bool occupancytable[], int adjacencytable[][20], char labeltable[]);
void printTable(bool occupancytable[], int adjacencytable[][20], char labeltable[]);
int returnOccupancy(bool occupancytable[]);
bool checkName(bool occupancytable[], char labeltable[], char input);
int findName(char labeltable[], char input);
void delVertex(bool occupancytable[], int adjacencytable[][20], char labeltable[]);
int main() {
  //These three are very important
  //The adjacency table is the adjacency table for print out
  //The occupancy table keeps track of which spots are taken in the matrix
  //The label table keeps track of the labels for each vertex
  int adjacencytable[20][20];
  char labeltable[20];
  bool occupancytable[20];
  //THe matrix and the occupancy table are filled in
  for(int i = 0; i < 20; i++) {
    for(int j = 0; j < 20; j++) {
      adjacencytable[i][j] = 0;
    }
  }
  for(int i = 0; i < 20; i++) {
    occupancytable[i] = false;
  }
  bool running = true;
  //Main looop very simple
  while(running == true) {
    cout << "Please enter your input: " << endl;
    char commandinput[10];
    cin >> commandinput;
    if(strcmp(commandinput, "ADD") == 0) {
      addVertex(occupancytable, adjacencytable, labeltable);
    }
    else if (strcmp(commandinput, "EDGE") == 0) {
      addEdge(occupancytable, adjacencytable, labeltable);
    }
    else if (strcmp(commandinput, "PRINT") == 0) {
      printTable(occupancytable, adjacencytable, labeltable);
    }
    
    else if (strcmp(commandinput, "DE") == 0) {
      delEdge(occupancytable, adjacencytable, labeltable);
    }
    else if (strcmp(commandinput, "DV") == 0) {
      delVertex(occupancytable, adjacencytable, labeltable);
    }
    else if (strcmp(commandinput, "QUIT") == 0) {
      running = false;
    }
    else {
      cout << "Please enter a valid input" << endl;
    }
  }
}
//Adds a vertex, marks off the index in the occupancy table as occupied
void addVertex(bool occupancytable[], int adjacencytable[][20], char labeltable[]) {
 
  cout << "Enter the name of the vertex that you want to add" << endl;
   char input;
  cin >> input;
 
  if(returnOccupancy(occupancytable) != -1) {
    int a = returnOccupancy(occupancytable);
    labeltable[a] = input;
    occupancytable[a] = true;
  }
  else {
    cout << "The table is empty!" << endl;
  }
  
}
//Deletes an edge, all it requires is resetting the value in the adjacency table
void delEdge(bool occupancytable[], int adjacencytable[][20], char labeltable[]) {
  char input1, input2;
  int weight;
  cout << "Please enter the name of the first vertex: " << endl;
  cin >> input1;
  if(checkName(occupancytable, labeltable, input1) == false) {
    cout << "Vertex not found! Please try again" << endl;
    return;
  }
  cout << "Please enter the name of the second vertex: " << endl;
  cin >> input2;
  if(checkName(occupancytable, labeltable, input2) == false) {
    cout << "Vertex not found! Please try again" << endl;
    return;
  }
  if(adjacencytable[findName(labeltable, input2)][findName(labeltable,input1)] == 0) {
    cout << "There is no edge here!" << endl;
  }
  else {
  adjacencytable[findName(labeltable, input2)][findName(labeltable,input1)] = 0;
  }
}
// "Frees" up space in the occupancy table and resets values in the adjacency table
void delVertex(bool occupancytable[], int adjacencytable[][20], char labeltable[]) {
  cout << "Enter the name of the vertex that you want to delete: " << endl;
  char input;
  cin >> input;
  if(checkName(occupancytable, labeltable, input) == true) {
    int i = findName( labeltable, input);
    occupancytable[i] = false;
    for(int j = 0; j < 20; j++) {
      adjacencytable[j][i] = 0;
    }
    for(int k = 0; k < 20; k++) {
      adjacencytable[i][k] = 0;
    }
    
  }
  else {
    cout << "Vertex not found! Please try again" << endl;
  }
}
//Checks for valid inputs and then marks it off on the adjacency table
void addEdge(bool occupancytable[], int adjacencytable[][20], char labeltable[]) {
  char input1, input2;
  int weight;
  cout << "Please enter the name of the first vertex: " << endl;
  cin >> input1;
  if(checkName(occupancytable, labeltable, input1) == false) {
    cout << "Vertex not found! Please try again" << endl;
    return;
  }
  cout << "Please enter the name of the second vertex: " << endl;
  cin >> input2;
  if(checkName(occupancytable, labeltable, input2) == false) {
    cout << "Vertex not found! Please try again" << endl;
    return;
  }
  if(input1 == input2) {
    cout << "A vertex can't be connected to itself! Please try again" << endl;
    return;
  }
  cout << "Please enter the weight of the edge: " << endl;
  cin >> weight;
  adjacencytable[findName(labeltable, input2)][findName(labeltable,input1)] = weight;
}
//Prints the labels on a 20 by 20 scale, checks if the space is "open" with the occupancy table as well
void printTable(bool occupancytable[], int adjacencytable[][20], char labeltable[]) {
  cout << "  ";
  for(int i = 0; i < 20; i++) {
    if(occupancytable[i] == true) {
      cout << labeltable[i] << " ";
    }
    else {
      cout << "  ";
    }
  }
  cout << endl;
  for(int i = 0; i < 20; i++) {
    if(occupancytable[i] == true) {
      cout << labeltable[i] << " ";
    }
    else {
      cout << "  ";
    }
    for(int j = 0; j < 20; j++) {
      cout << adjacencytable[i][j] << " ";
    }
    cout << endl;
  }
}
//Returns the first open space in the adjacency table
int returnOccupancy(bool occupancytable[]) {
  for(int i = 0; i < 20; i++) {
    if(occupancytable[i] == false) {
      return i;
    }
  }
  return -1;
}
//Checks if a certain label is present in the graph
bool checkName(bool occupancytable[], char labeltable[], char input) {
  for(int i = 0; i < 20; i++) {
    if(labeltable[i] == input && occupancytable[i] == true) {
      return true;
    }
  }
  return false;
}
//Finds the position of a label in the graph
int findName(char labeltable[], char input) {
  for(int i = 0; i < 20; i++) {
    if(labeltable[i] == input) {
      return i;
    }
  }
  //Should never happen because checkName() already filters out invalid cases
  return -1;
}
