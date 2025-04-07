#ifndef ACTIVITY_CPP
#define ACTIVITY_CPP

#include <iostream>
#include "activity.h"


void print(std::ostream &os, Activity &it) {
    os << it.name << '\t';
    os << it.location << '\t';
    os << it.level << '\t';
    os << it.rating << '\t';
    os << it.type << '\n';
}
  
  
void printAll(std::ostream &os, Activity arr[], size_t size) {
    for(size_t i = 0; i < size; i++) {
        print(os, arr[i]);
    }
}

#endif