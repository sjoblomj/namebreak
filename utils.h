#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>     // For exit()
#include <signal.h>

#include "namebreak.h"
#include "constants.h"

void setOutputFile(std::string dir);
std::string int2str(int i);
void terminate(int /*param*/);
int loadData();
int loadFromFile(const char* filename, bool matchesonly);
void print(std::string message, bool important);

#endif // UTILS_H
