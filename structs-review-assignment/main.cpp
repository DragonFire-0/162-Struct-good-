//*****************************************************************************
// Author: Chancellor Field
// Assignment: Structs review
// Date: 4/6/25
// Description: 
// Sources: 
//*****************************************************************************

#include <iostream>
#include <fstream>
#include <cstring> // https://en.cppreference.com/w/cpp/header/cstring
#include "activity.h"
#include "main.h"

using namespace std;

size_t MAX_ACTIVITIES = 30;

int main() {
  //Variable decloration
  size_t activitiesSize = 0;
  Activity activities[MAX_ACTIVITIES];
  char choice = 'a';

  //File reading
  ifstream fin = ifstream("activities.txt"); 
  loadActivities(fin, activities, activitiesSize);

  cout << "Welcome";

  //Main loop
  while (choice != 'q'){
    choice = mainInput();

    if (choice == 'a'){ //Add a new activity
      addNew(activities, activitiesSize);
    }

    else if (choice == 'b'){ //List activities by name
      printAll(cout, activities, activitiesSize);
    }

    else if (choice == 'c'){ //List activities for a location
      searchLocation(activities, activitiesSize);
    }
    
    else if (choice == 'd'){ //List activities of a Type
      searchType(activities, activitiesSize);
    }
    
    else if (choice == 'e'){ //Remove an activity
      removeAct(activities, activitiesSize);
    }
    
    else if (choice == 'f'){ //Search by activity name
      searchName(activities, activitiesSize);
    }

    else if (choice != 'q'){ //Error message if entered invalid option
      cout << "Invalid option!! Please try again!" << endl;
    }
  }


  //File writing
  ofstream fout = ofstream("Activities.txt"); 

  exportToFile(fout, activities, activitiesSize);

  return 0;
}



// Skiing;Mt Hood Meadows;Difficult;6;0
void loadActivities(istream &fin, Activity arr[], size_t &size) {
  char const DELIMITER = ';';
  size = 0;
  while(fin && !fin.peek() != EOF){
    Activity tempAct;
    // read data from file
    fin.getline(tempAct.name, Activity::MAX_CHARS, DELIMITER);
    fin.getline(tempAct.location, Activity::MAX_CHARS, DELIMITER);
    fin.getline(tempAct.level, Activity::MAX_CHARS, DELIMITER);
    fin >> tempAct.rating;
    fin.get(); // Remove delimiter
    fin >> tempAct.type;
    fin.get(); // Remove \n newline character

    // find sorted position
    int pos = 0;

    // refactored to not use while true
    bool next = true;
    while(next) {
      if (pos == size) {
        next = false;
      } else if(strcmp(arr[pos].name, tempAct.name) > 0) {
        pos++;
      } else {
        next = false;
      }
    }
    
    // insert at position
    insert(arr, size, tempAct, pos);

    //Orders the activities by name
    orderActivity(arr, size);
  }
}

void exportToFile(ofstream &is, Activity arr[], size_t &size){
  char const DELIMITER = ';';
  
  for (int i = 0; i < size; i++){
    is << arr[i]. name << DELIMITER
    << arr[i].location << DELIMITER
    << arr[i].level << DELIMITER
    << arr[i].rating << DELIMITER
    << arr[i].type;
    //If it is not the last activity make a new line
    if (i < size-1){
      is << endl;
    }
  }

}

void insert(Activity arr[], size_t &size, Activity tempAct, size_t pos) {
  for(size_t i = size + 1; i > pos; i-- ) {
    arr[i] = arr[i-1];
  }
  arr[pos] = tempAct;
  size++;
}

char mainInput(){
  char tempChoice;
  cout << endl << "Pick an option from below:" << endl
  << "(a)Add a new activity" << endl
  << "(b)List activities by name" << endl
  << "(c)List activities by location" << endl
  << "(d)List activities by Type" << endl
  << "(e)Remove an activity" << endl
  << "(f)Search by activity name" << endl
  << "(q)Quit" << endl;
  cin >> tempChoice;
  cout << endl << endl;
  return tempChoice;
} 

void addNew(Activity arr[], size_t &size){
  cout << "Enter the activity name (50 characters or less): ";
  //Ignores newline
  cin.ignore(1);
  writeSpace(arr[size].name);
  
  cout << "Enter the activity location (50 characters or less): ";
  writeSpace(arr[size].location);
  
  cout << "Enter the activity level: ";
  writeSpace(arr[size].level);

  cout << "Enter the activity rating: ";
  cin >> arr[size].rating;
  while (!(cin >> arr[size].rating)) {
    cin.clear(); //clear bad input flag
    cin.ignore(100, '\n'); //discard input
    cout << "Invalid rating! Please enter a valid rating!" << endl
      << "Enter the activity rating: ";
  }

  cout << "Enter Type number(0-Athletics, 1-Food, 2-Arts, 3-Games, and 4-Others): ";
  cin >> arr[size].type;
    
  size++;

  //Reorders the array so that the new activity is ordered alphabetically
  orderActivity(arr, size);
}

void removeAct(Activity arr[], size_t &size){
  int numRemove = -1;
  printAll(cout, arr, size);
  cout << "Pick the index to remove: ";
  cin >> numRemove;
  //Sets numRemove in line with the array
  numRemove--;

  for (int i = 0; i < size; i++){
    //If t is more than low
    if (i > numRemove){
      //Gets rid of the lowest number
      arr[i-1] = arr[i];
    }
  }
  cout << "Activity Removed" << endl;
  size--;
}

void orderActivity(Activity arr[], size_t &size){
  //Temp activity to be minipluated so the main arr does not break
  Activity temp[MAX_ACTIVITIES]; 
  //Temp activity to be writen to
  Activity temp2[MAX_ACTIVITIES];
  //Number tracking the lowest point
  int low = 0;
  int numRun = 0;

  //Copies the array into a temp array
  for (int i = size; i >= 0; i--){
    temp[i] = arr[i];
  }

  //printGuide(cout);

  //Runs through the enitre array
  for (int i = size; i > 0; i--){
    
    //Resets low
    low = 0;
    
    //Runs through the array minus howevermany spots
    for (int t = 1; t < i; t++){
      int j = 0;
      //Runs until j is the max or the names are not equal
      while (j < arr[0].MAX_CHARS && temp[low].name[j] == temp[t].name[j]){
        j++;
      }

      //If the current low is higher than the checked number
      //Low starts at 0 and t starts at 1
      if (temp[low].name[j] > temp[t].name[j]){
        //Sets the low to checked number
        low = t;
      }
    }
    
    temp2[numRun] = temp[low];
    numRun++;

    for (int t = 0; t < i; t++){
      //If t is more than low
      if (t > low){
        //Gets rid of the lowest number
        temp[t-1] = temp[t];
      }
    }
  }

  for (int i = 0; i <= size; i++){
    arr[i] = temp2[i];
  }
  
}

void searchName(Activity arr[], size_t &size){
  //Creates a char array that is the max characters that a name can be
  int maxChar = arr[0].MAX_CHARS + 1;
  char search[maxChar] = {0};
  bool found = false;

  cout << "Enter name to search for: ";
  //Ignores newline
  cin.ignore(1);
  writeSpace(search);

  printGuide(cout);
  
 
  char* pch; //Char pointer
  
  //Runs through for each activity
  for (int i = 0; i < size; i++){
    //Compares the name with search
    pch = strstr (arr[i].name, search);
    if (pch != NULL){
      cout << i + 1;
      print(cout,arr[i]);
      found = true;
    }
  }
  
  if (found != true){
    cout << "No match found" << endl;
  }
}

void searchLocation(Activity arr[], size_t &size){
  //Creates a char array that is the max characters that a name can be
  int maxChar = arr[0].MAX_CHARS + 1;
  char search[maxChar] = {0};
  bool found = false;

  
  cout << "Enter name to search for: ";

  cin.ignore(1);
  writeSpace(search);

  printGuide(cout);
  
 
  char* pch; //Char pointer
  
  //Runs through for each activity
  for (int i = 0; i < size; i++){
    //Compares the location with search
    pch = strstr (arr[i].location, search);
    if (pch != NULL){
      cout << i+1;
      print(cout,arr[i]);
      found = true;
    }
  }
  
  if (found != true){
    cout << "No match found" << endl;
  }
}

void searchType(Activity arr[], size_t &size){
  int search = -1;  
  bool found = false;

  cout << "Enter Type number(0-Athletics, 1-Food, 2-Arts, 3-Games, and 4-Others): ";
  cin >> search;

  printGuide(cout);
  for (int i = 0; i < size; i++){
    if (search == arr[i].type){
      cout << i + 1;
      print(cout, arr[i]);
      found = true;
    }
  }
  //Outputs a message if no match was found
  //Which message depends on if the number searched is withing range
  if (found != true){
    if (search >=0 && search <=4){
      cout << "No match found" << endl;
    }
    else {
      cout << "Invalid number" << endl;
    }
  }
}

void writeSpace(char arr[]){
  char ch; 
  int cNum = 0; //Character num
  
  //Writes until newline
  while (cin.get(ch) && ch != '\n') {
    arr[cNum] = ch;
    cNum++;
  }

}