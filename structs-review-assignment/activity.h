
// For each activity, you need to keep track of
// Activity name (e.g., Skiing)
// ii. Activity location (e.g., Mt Hood Meadows)
// iii. Activity Level (e.g., Easy, Difficult, Not for the faint of heart etc.)
// iv. Rating (e.g., 1-10 about how fun the experience is)
// v. Type: athletic, food, arts, games, or others - have about 5 different Types of
// activities for the user to choose from


#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <iostream>
# include <cstddef> // for https://en.cppreference.com/w/cpp/types/size_t

class Activity {   // can also use struct Activity
public:        // Only if using class keyword
    static const size_t MAX_CHARS = 50;

    char name[MAX_CHARS + 1] = {0};     
    char location[MAX_CHARS + 1] = {0};
    char level[MAX_CHARS + 1] = {0};
    int rating;    // 1 - 10
    int type;      // 0 - 4
};


void print(std::ostream &os, Activity &it);

void printAll(std::ostream &os, Activity arr[], size_t size);

void printGuide(std::ostream &os);

#endif