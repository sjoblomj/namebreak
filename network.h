
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

#include "constants.h"
#include "utils.h"


int network(int, std::string, std::string, std::string, int);
void cleanup(CURL* curl);
std::string makeStringTransmittable(std::string in);
void sleep(int seconds);
void getSystemInfo(int &cores, std::string &os, std::string &osversion, std::string &hostname);
size_t writeCallback(char*, size_t, size_t, void*);

void network_handshake(int mode);
bool network_hit(int slashpos);
bool network_match(int slashpos);
bool network_sendhit(int slashpos, bool match);

#endif // NETWORK_H
