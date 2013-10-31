#include "constants.h"

#ifndef VALIDATE
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'K', 'H', 'A', 'D', 'N', 'C', 'R', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'M', 'E', 'N', 'G', 'S', 'K', 'U', 'M', 'E', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };

#elif VALIDATE == 1263
  char PRE[] = "PORTRAIT\\P";
  char FIRSTWORD[] = { 'A', 'D', 'V', 'I', 'S', 'O', 'R', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'A', 'R', 'C', 'H', 'O', 'N', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\PARBITER\\PABFID00.SMK";

#elif VALIDATE == 1471
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'F', 'L', 'A', 'A', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'I', 'K', 'E', 'R', 'R', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UFLAG5\\UF5FID00.SMK";

#elif VALIDATE == 1473
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'F', 'L', 'A', 'A', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'I', 'K', 'E', 'R', 'R', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UFLAG6\\UF6FID00.SMK";

#elif VALIDATE == 1475
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'F', 'L', 'A', 'A', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'I', 'K', 'E', 'R', 'R', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UFLAG7\\UF7FID00.SMK";

#elif VALIDATE == 1477
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'F', 'L', 'A', 'A', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'I', 'K', 'E', 'R', 'R', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UFLAG8\\UF8FID00.SMK";

#elif VALIDATE == 1479
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'F', 'L', 'A', 'A', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'I', 'K', 'E', 'R', 'R', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UHUNTERS\\UHUFID00.SMK";

#elif VALIDATE == 1485
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'F', 'L', 'A', 'A', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'J', 'I', 'M', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UIKERR\\UIKFID00.SMK";

#elif VALIDATE == 1491
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'F', 'L', 'A', 'A', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'K', 'E', 'R', 'R', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UJIM\\URAFID00.SMK";

#elif VALIDATE == 1498
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'I', 'K', 'E', 'R', 'R', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'K', 'H', 'A', 'D', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UKERR\\UKEFID00.SMK";

#elif VALIDATE == 1505
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'I', 'K', 'E', 'R', 'R', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'M', 'E', 'N', 'G', 'S', 'K', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UKHAD\\NCRFID00.SMK";

#elif VALIDATE == 1509
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'K', 'H', 'A', 'D', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'P', 'S', 'I', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UMENGSK\\UMEFID00.SMK";

#elif VALIDATE == 1514
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'M', 'E', 'N', 'G', 'S', 'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'S', 'H', 'A', 'R', 'D', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UPSI\\UPSFID00.SMK";

#elif VALIDATE == 1516
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'P', 'S', 'I', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'T', 'A', 'S', 'S', 'A', 'D', 'A', 'R', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\USHARD\\USHFID00.SMK";

#elif VALIDATE == 1518
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'S', 'H', 'A', 'R', 'D', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'Z', 'A', 'S', 'Z', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UTASSADAR\\UTAFID00.SMK";

#elif VALIDATE == 1523
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'T', 'A', 'S', 'S', 'A', 'D', 'A', 'R', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'Z', 'E', 'R', 'A', 'T', 'U', 'L', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UZASZ\\FID00.SMK";

#elif VALIDATE == 1529
  char PRE[] = "PORTRAIT\\U";
  char FIRSTWORD[] = { 'Z', 'A', 'S', 'Z', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\UZERATUL\\UZEFID00.SMK";

#elif VALIDATE == 1536
  char PRE[] = "PORTRAIT\\Z";
  char FIRSTWORD[] = { 'A', 'A', 'A', 'A', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
  char LASTWORD[]  = { 'A', 'V', 'E', 'N', 'G', 'E', 'R', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '\0' };
  std::string ANSWER = "PORTRAIT\\ZADVISOR\\ZADFID00.SMK";
#endif

char POST[] = "FID00.SMK";

std::string savematchpath = "Found.txt";    // Standard name
char savelasttrypath[] = "LastTry.txt";
char str[MAXARRSIZE];
int size;
int hitnumber;
bool networkmode;
bool quiet;

unsigned long seeds[MAXARRSIZE][2][2];  // seeds[all chars in str except the last][(normal string, string with '\')][(seed1, seed2)]
unsigned long dwCryptTable[0x500];
