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


int main() {

  //Variable decluration
  size_t MAX_ACTIVITIES = 30;
  size_t activitiesSize = 0;
  Activity activities[MAX_ACTIVITIES];
  char choice = 'a';

  //File reading
  ifstream fin = ifstream("activities.txt"); 
  loadActivities(fin, activities, activitiesSize);

  cout << "Welcome" << endl;

  //Main loop
  while (choice != 'q'){
    choice = mainInput();
    if (choice == 'a'){ //Add a new activity
      addNew(activities, activitiesSize);
    }
    else if (choice == 'b'){ //List activities by name
      printAll(cout, activities, activitiesSize);
    }
    else if (choice == 'c'){ //List activities by location
      Activity tempAct = activities;
      for (int i = 0; i < 30, i++){

      }
    }
    else if (choice == 'd'){ //List activities by Type
      
    }
    else if (choice == 'e'){ //Remove an activity
      
    }
    else if (choice == 'f'){ //Search by activity name
      
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
  cout << "Pick an option from below:" << endl
  << "(a)Add a new activity" << endl
  << "(b)List activities by name" << endl
  << "(c)List activities by location" << endl
  << "(d)List activities by Type" << endl
  << "(e)Remove an activity" << endl
  << "(f)Search by activity name" << endl
  << "(q)Quit" << endl;
  cin >> tempChoice;
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