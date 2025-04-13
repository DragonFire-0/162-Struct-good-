#ifndef ACTIVITY_CPP
#define ACTIVITY_CPP

#include <iostream>
#include "activity.h"


void print(std::ostream &os, Activity &it) {
    os.width(25); os << it.name;
    os.width(25); os << it.location;
    os.width(25); os << it.level;
    os.width(10); os << it.rating;

    // 0 could be Athletics, 1 could be Food, 2 could be Arts, 3 could be Games, and 4 could be Others
    if (it.type == 0){
        os.width(10); os << "Athletic" << '\n';
    }
    if (it.type == 1){
        os.width(10); os << "Food" << '\n';
    }
    if (it.type == 2){
        os.width(10); os << "Arts" << '\n';
    }
    if (it.type == 3){
        os.width(10); os << "Games" << '\n';
    }
    if (it.type == 4){
        os.width(10); os << "Other" << '\n';
    }

    //os.width(5); os << it.type << '\n';
}
  
  
void printAll(std::ostream &os, Activity arr[], size_t size) {
    printGuide(os);
    for(size_t i = 0; i < size; i++) {
        os << i+1;
        print(os, arr[i]);
    }
}

void printGuide(std::ostream &os){
    os.width(26); os << "Name";
    os.width(25); os << "Location";
    os.width(25); os << "Level";
    os.width(10); os << "Rating";
    os.width(10); os << "Type" << '\n';
}

#endif