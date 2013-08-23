#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAXARRSIZE 30
#define FIRSTCHAR ' '
#define CODENAME1 0x63755CA3
#define CODENAME2 0xBCEBEE13
#define VALIDATECODENAME1 0xfdccb560
#define VALIDATECODENAME2 0x54c5e0a2

#include <string>
#include <list>

// Class for storing information about the hits we generate.
// The hitqueue is a list of this class. It is used in networking
// mode, when there is an error sending data.
class hitdata
{
public:
    hitdata(int h, int p, bool m, std::string s)
    {
        hitno    = h;
        slashpos = p;
        match    = m;
        str      = s;
    }
    int getHitNumber()      { return hitno; }
    int getSlashPos()       { return slashpos; }
    std::string getString() { return str; }
    bool getMatch()         { return match; }

private:
    int hitno;
    int slashpos;
    std::string str;
    bool match;
};


extern char FIRSTWORD[];
extern char LASTWORD[];
extern  char FIRSTVALIDATEWORD[];
extern  char LASTVALIDATEWORD[];
extern char PRE[];
extern char POST[];

extern std::string savematchpath;
extern char savelasttrypath[];
extern char str[];
extern int size;
extern int hitnumber;
extern std::list<hitdata> hitqueue;
extern bool networkmode;
extern bool quiet;

extern unsigned long seeds[][2][2];	// seeds[all chars in str except the last][(normal string, string with '\')][(seed1, seed2)]
extern  unsigned long dwCryptTable[];
#endif
