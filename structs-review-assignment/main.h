
#include <iostream>
#include "activity.h"

void loadActivities(std::istream &is, Activity arr[], size_t &size);

void insert(Activity arr[], size_t &size, Activity it, size_t pos);

char mainInput();

void addNew(Activity arr[], size_t &size);

void listActivity(Activity arr[], size_t &size);

void searchName(Activity arr[], size_t &size);

void searchType(Activity arr[], size_t &size);