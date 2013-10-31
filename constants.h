#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifndef VALIDATE
  #define CODENAME1 0x63755CA3
  #define CODENAME2 0xBCEBEE13

#elif VALIDATE == 1263
  // "PORTRAIT\\PARBITER\\PABFID00.SMK"
  #define CODENAME1 0xFDCCB560
  #define CODENAME2 0x54C5E0A2

#elif VALIDATE == 1471
  // "PORTRAIT\\UFLAG5\\UF5FID00.SMK"
  #define CODENAME1 0x2F15F6D4
  #define CODENAME2 0x9467505E

#elif VALIDATE == 1473
  // "PORTRAIT\\UFLAG6\\UF6FID00.SMK"
  #define CODENAME1 0x15530812
  #define CODENAME2 0xAD2F22F7

#elif VALIDATE == 1475
  // "PORTRAIT\\UFLAG7\\UF7FID00.SMK"
  #define CODENAME1 0x07219696
  #define CODENAME2 0x5E66ACDA

#elif VALIDATE == 1477
  // "PORTRAIT\\UFLAG8\\UF8FID00.SMK"
  #define CODENAME1 0x7BBBE5A0
  #define CODENAME2 0x522EC3A0

#elif VALIDATE == 1479
  // "PORTRAIT\\UHUNTERS\\UHUFID00.SMK"
  #define CODENAME1 0x74C284A2
  #define CODENAME2 0x39C1365E

#elif VALIDATE == 1485
  // "PORTRAIT\\UIKERR\\UIKFID00.SMK"
  #define CODENAME1 0xFCFF300B
  #define CODENAME2 0x6021BEA9

#elif VALIDATE == 1491
  // "PORTRAIT\\UJIM\\URAFID00.SMK"
  #define CODENAME1 0xCEAEB86A
  #define CODENAME2 0x06D11B73

#elif VALIDATE == 1498
  // "PORTRAIT\\UKERR\\UKEFID00.SMK"
  #define CODENAME1 0xC7F89CB3
  #define CODENAME2 0x216ECC68

#elif VALIDATE == 1505
  // "PORTRAIT\\UKHAD\\NCRFID00.SMK"
  #define CODENAME1 0x7189B3F7
  #define CODENAME2 0xA3FE828E

#elif VALIDATE == 1509
  // "PORTRAIT\\UMENGSK\\UMEFID00.SMK"
  #define CODENAME1 0x27251B30
  #define CODENAME2 0x55E98CAE

#elif VALIDATE == 1514
  // "PORTRAIT\\UPSI\\UPSFID00.SMK"
  #define CODENAME1 0x93871D9C
  #define CODENAME2 0xA393EE05

#elif VALIDATE == 1516
  // "PORTRAIT\\USHARD\\USHFID00.SMK"
  #define CODENAME1 0x0B3E0809
  #define CODENAME2 0xA5036079

#elif VALIDATE == 1518
  // "PORTRAIT\\UTASSADAR\\UTAFID00.SMK"
  #define CODENAME1 0x8A56F3AE
  #define CODENAME2 0x08FDF0ED

#elif VALIDATE == 1523
  // "PORTRAIT\\UZASZ\\FID00.SMK"
  #define CODENAME1 0x858E6D7F
  #define CODENAME2 0xFA6ACFFD

#elif VALIDATE == 1529
  // "PORTRAIT\\UZERATUL\\UZEFID00.SMK"
  #define CODENAME1 0xF829C049
  #define CODENAME2 0xBB0ED2C9

#elif VALIDATE == 1536
  // "PORTRAIT\\ZADVISOR\\ZADFID00.SMK"
  #define CODENAME1 0x5FE41318
  #define CODENAME2 0x8CBE9FF5
#endif


#define MAXARRSIZE 20
#define FIRSTCHAR ' '

#include <string>


extern char FIRSTWORD[];
extern char LASTWORD[];
extern char PRE[];
extern char POST[];
extern std::string ANSWER;

extern std::string savematchpath;
extern char savelasttrypath[];
extern char str[];
extern int size;
extern int hitnumber;
extern bool networkmode;
extern bool quiet;

extern unsigned long seeds[][2][2]; // seeds[all chars in str except the last][(normal string, string with '\')][(seed1, seed2)]
extern unsigned long dwCryptTable[];
#endif
