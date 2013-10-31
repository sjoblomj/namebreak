#ifndef LOWRANGE_H
#define LOWRANGE_H

#include "namebreak.h"

#ifdef VALIDATE
#include <cstring>
#endif

void getNextLowRange();
void runLoopLowRange(int upperlimit);
//bool saveMatchLowRange();
char getNextCharLowRange(char ch);

#endif // LOWRANGE_H
