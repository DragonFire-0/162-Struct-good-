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

    //Need to make so it adds alphabetically
    if (choice == 'a'){ //Add a new activity
      addNew(activities, activitiesSize);
    }

    //I realize this will  be useless if I sort alphabetically
    else if (choice == 'b'){ //List activities by name
      //printAll(cout, activities, activitiesSize);
      listActivity(activities, activitiesSize);
    }

    else if (choice == 'c'){ //List activities for a location
    }
    
    //Done
    else if (choice == 'd'){ //List activities of a Type
      searchType(activities, activitiesSize);
    }
    
    //Needs
    else if (choice == 'e'){ //Remove an activity
      
    }
    
    else if (choice == 'f'){ //Search by activity name
      searchName(activities, activitiesSize);
    }

    else if (choice != 'q'){ 
      cout << "Invalid option!! Please try again!";
    }
    
 
  }
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
    cin >> arr[size].name;
    //cout << endl << endl << arr[size].name << endl << endl;
    
    cout << "Enter the activity location (50 characters or less): ";
    cin >> arr[size].location;

    cout << "Enter the activity level: ";
    cin >> arr[size].level;
    
    cout << "Enter the activity rating: ";
    cin >> arr[size].rating;
    
    cout << "Enter Type number(0-Athletics, 1-Food, 2-Arts, 3-Games, and 4-Others): ";
    cin >> arr[size].type;
    
    size++;
}

void listActivity(Activity arr[], size_t &size){
  Activity temp[MAX_ACTIVITIES];
  int low = 0;

  //Copies the array into a temp array
  for (int i = size; i >= 0; i--){
    temp[i] = arr[i];
  }

  printGuide(cout);
  //Runs through the enitre array
  for (int i = size; i > 0; i--){
    
    //Resets low
    low = 0;
    
    //Runs through the array minus howevermany spots
    for (int t = 1; t < i; t++){
      
      //If the current low is higher than the checked number
      //For checking name
      if (temp[low].name[0] > temp[t].name[0]){
        //Sets the low to checked number
        low = t;
      }
    }

    //Prints the lowest
    print(cout, temp[low]);

    for (int t = 0; t < i; t++){
      //If t is more than low
      if (t > low){
        //Gets rid of the lowest number
        temp[t-1] = temp[t];
      }
    }
  }
}

void searchName(Activity arr[], size_t &size){
  char search[arr[0].MAX_CHARS + 1] = {0};  
  bool found = false;

  cout << "Enter name to search for: ";
  cin >> search;

  printGuide(cout);
  for (int i = 0; i < size; i++){
    if (search == arr[i].name){
      print(cout, arr[i]);
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