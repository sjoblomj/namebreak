#include "constants.h"

char FIRSTWORD[] = { 'K', 'H', 'A', 'D', 'N', 'C', 'R', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' } ;
char LASTWORD[]  = { 'M', 'E', 'N', 'G', 'S', 'K', 'U', 'M', 'E', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
//char FIRSTWORD[] = { 'A', 'R', 'B', 'I', 'T', 'E', 'D', 'D', 'D', 'D', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
//char LASTWORD[]  = { 'A', 'R', 'B', 'I', 'T', 'E', 'S', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
 char FIRSTVALIDATEWORD[] = { 'A', 'R', 'B', 'I', 'T', 'E', 'D', 'D', 'D', 'D', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
 char LASTVALIDATEWORD[]  = { 'A', 'R', 'B', 'I', 'T', 'E', 'S', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
// char PRE[]  = "PORTRAIT\\P";
 char PRE[]  = "PORTRAIT\\U";
char POST[] = "FID00.SMK";

std::string savematchpath = "Found.txt";    // Standard name
char savelasttrypath[] = "LastTry.txt";
char str[MAXARRSIZE];
int size;
int hitnumber;
std::list<hitdata> hitqueue;
bool networkmode;
bool quiet;

unsigned long seeds[MAXARRSIZE][2][2];	// seeds[all chars in str except the last][(normal string, string with '\')][(seed1, seed2)]
unsigned long dwCryptTable[0x500];
