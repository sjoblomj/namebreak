#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/wait.h>
//#include <sys/utsname.h>
//#include <sys/types.h>
//#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <getopt.h>

using namespace std;

string getCommandOutput(const char* command);


int main() {
    string out = getCommandOutput("ps ax | grep /usr/bin/Xorg");
    size_t pos;
    while((pos = out.find("tty")) != string::npos)
    {
        pos = pos + 3;
        if(out.substr(pos, 1) == getCommandOutput("fgconsole"))
{
            out = out.substr(pos);
cout << "Found this console: " << out[pos] << endl;
}        else
        {
            cout << out[pos] << endl;
            system("echo hi");
            string cmd = "chvt " + out.substr(pos, 1);
            cout << cmd << endl;
            system(cmd.c_str());
            //system("echo " + out.substr(pos, 1).c_str());
            //system("chvt " + out[pos]);
            break;
        }
    }
    return 0;
}



// Given a command to run, this function will return the output from
// running that command. The command "popen" is used to pipe the
// command output to this process.
string getCommandOutput(const char* command)
{
    FILE *in;
    char buff[512];
    stringstream ss;

    if(!(in = (popen(command, "r"))))
        cout << "ERROR\n";
    while(fgets(buff, sizeof(buff), in) != NULL)
        ss << buff;
    pclose(in);

    return ss.str();
}

