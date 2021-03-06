#ifndef NAMEBREAK_H
#define NAMEBREAK_H

#include <getopt.h>
#include <sstream>

#include "portrait_medium.h"
#include "portrait_upper.h"
#include "lowrange.h"
#include "constants.h"
#include "network.h"
#include "utils.h"

int main(int argc, char* argv[]);
void mainloop();
bool saveMatch(int stringtype, bool fast);
void InitializeCryptTable();
unsigned long HashString_orig(const char *lpszString, unsigned long dwHashType);
unsigned long HashString(const char *lpszString);
unsigned long HashString_seed2(const char *lpszString);
void InitializeSeedsTable();
char getNextChar(char ch);

#endif // NAMEBREAK_H
