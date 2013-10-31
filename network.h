
#ifndef NETWORK_H
#define NETWORK_H

#if defined(WIN32)
   #include <windows.h>
   #include <curl/curl.h>
#else
   #include <time.h>
   #include <curl/curl.h>

   #include <unistd.h>     // For getting os version
   #include <sys/utsname.h>
#endif

#include <stdlib.h>     // For atoi()
#include <sstream>
#include <fstream>
#include <list>

#include "constants.h"
#include "utils.h"


// If we are in validation mode, then send the
// validation id to the server
#ifndef VALIDATE
   #define urlvalidation ""
#else
   #define STRINGIFY(x) #x
   #define TOSTRING(x) STRINGIFY(x)

   #define urlvalidation "validate=" TOSTRING(VALIDATE) "&"
#endif

#define urlbase  (string)"http://thehomepageinternet.org/namebreak/"
#define urlmode0 (string)urlbase"hs.php?"urlvalidation
#define urlmode1 (string)urlbase"hs.php?"urlvalidation
#define urlmode2 (string)urlbase"hit.php?"urlvalidation
#define urlmode3 (string)urlbase"match.php?"urlvalidation



// Class for storing information about the hits we generate.
// The hitqueue is a list of this class. It is used when
// there is an error sending data.
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


int network(int, std::string, std::string, std::string, int);
void cleanup(CURL* curl);
std::string makeStringTransmittable(std::string in);
void sleep(int seconds);
void getSystemInfo(int &cores, std::string &os,
     std::string &osversion, std::string &hostname);
size_t writeCallback(char*, size_t, size_t, void*);

void network_handshake(int mode);
bool network_hit(int slashpos);
bool network_match(int slashpos);
bool network_sendhit(int slashpos, bool match);
extern std::list<hitdata> hitqueue;

#endif // NETWORK_H
