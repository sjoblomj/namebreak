#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <getopt.h>

using namespace std;

// This program is a simple launcher for the namebreaking application.
// It will start up as many processes as there are CPU cores on the
// current computer. Between each process, there will be 5 seconds
// of idle time, before the next process starts. The processes will
// be run with a very low priority (through "nice -n 15"), in order
// to make sure the processes won't be in the way for a user wanting
// to use the computer for different tasks.
//
// If there is a file called ./namebreak in the home directory of the
// user, the launcher will read it. It will launch the application
// on the line that begins with "program=" in the ./namebreak file.
// It will also make sure the directory to save hits in exists (based
// on the line "dir="). If the file ./namebreak doesn't exist, the
// default values will be to start the program called "namebreak" in
// the users home directory.
//
// After all processes have been started, the computer will lock.
// If the program is run through a terminal in an X-session, then
// gnome-screensaver-command -l will be run. If the program is run
// through a virtual console, then vlock -c will be run.



// Compiling:
// Linux: g++ -o launcher launcher.cpp
// MinGW: No portable version :(


int getNumberOfCores();
void readPropertiesFile(string &prog, string &dir);
void sleep(int seconds);
bool isvirtualconsole();
string findterminal();
string findscreenlock();
string getCommandOutput(const char* command);
int changeConfigFiles(string prog, string dir, int processes);

int main(int argc, char* argv[])
{
    int processes = getNumberOfCores();
    bool newterminal = 1, screenlock = 1, quiet = 0;

    string prog, dir;
    readPropertiesFile(prog, dir);

    int c;
    while(true)
    {
        int option_index = 0;
        static struct option long_options[] =
        {
            {"no-terminal",   no_argument,       0, 't'},
            {"no-screenlock", no_argument,       0, 'l'},
            {"quiet",         no_argument,       0, 'q'},
            {"processes",     required_argument, 0, 'p'},
            {"config",        no_argument,       0, 'c'},
            {"version",       no_argument,       0, 'v'},
            {"help",          no_argument,       0, 'h'},
            {0, 0, 0, 0}
        };

        c = getopt_long(argc, argv, "tlqp:cvh", long_options,
                        &option_index);

        if(c == -1)
            break;

        switch(c)
        {
            case 't':
                newterminal = 0;
                break;

            case 'l':
                screenlock = 0;
                break;

            case 'q':
                quiet = 1;
                break;

            case 'p':
                if(atoi(optarg) > 0)
                    processes = atoi(optarg);
                break;

            case 'c':
                return changeConfigFiles(prog, dir, processes);

            case 'v':
                cout << "Namebreaker Launcher\n";
                cout << "Version 0.5\n";
                cout << "Written by Johan Sjöblom (Ojan), 2013\n";
                cout << "Licensed under GPL 2.0 or newer.\n";
                return 0;

            case 'h':
                cout << "Launcher program for the Namebreaking application\n";
                cout << "Usage: " << argv[0] << " [OPTION]\n\n";
                cout << "Valid options are these:\n";
                cout << "  -t, --no-terminal       Do not start the Namebreaker in a new terminal window\n";
                cout << "  -l, --no-screenlock     Do not lock the screen after starting the Namebreaker\n";
                cout << "  -q, --quiet             Namebreaker won't print out non-important information\n";
                cout << "  -p, --processes=NUMBER  Start NUMBER of processes. Default is as many as the\n";
                cout << "                          computer has cores. NUMBER must be greater than 0.\n";
                cout << "  -c, --config            Enter configuration preferences and exit.\n";
                cout << "  -v, --version           Display version information and exit\n";
                cout << "  -h, --help              Display this help and exit\n";
                return 0;

            case '?':
                break;
            default:
                abort();
        }
    }

    bool virtualconsole = isvirtualconsole();
    string terminal = findterminal();

    if(virtualconsole || !newterminal)
    {
        // Print info, and give the users 10 seconds to abort
        cout << "Will start " << processes
             << " processes. (Ctrl+C to abort)\n";
        for(int i = 10; i >= 0; i--)
        {
            cout << "\rStarting in " << i << " seconds. " << flush;
            sleep(1);
        }
        cout << flush << endl;
    }
    else
    {
        int status;
        pid_t terminallauncher = fork();
        // Fork. Open terminal in child.

        if(terminallauncher < 0)
        {
            cout << "Error when trying to fork\n";
            exit(-1);
        }
        if(terminallauncher == 0)
        {
            stringstream ss;
            ss << processes;
            string tmp = terminal + " -e \"" + argv[0] + " -t" +
                         (!screenlock ? "l" : "")  +
                         (quiet ? "q" : "") + "p " + ss.str() + "\"";
            system(tmp.c_str());
            return 0;
        }
        else
        {
            while(waitpid(terminallauncher, &status, WNOHANG) == 0)
                sleep(1);
            return 0;
        }
    }


    prog += " --hitsdir " + dir;


    // Start programs with nice -n 15, which should give
    // them a (very) low priority.
    string programstartcmd;
    if(virtualconsole)
        programstartcmd = "nice -n 15 " + prog + " -q";
    else
        programstartcmd = terminal + " -e \"nice -n 15 " + prog +
                        (quiet ? " -q" : "") + "\"";
        //programstartcmd = "gnome-terminal -e \"" + prog + "\"";


    pid_t *childPids = NULL;
    pid_t p;

    // Allocate array of child PIDs
    childPids = (pid_t*)malloc(processes * sizeof(pid_t));

    // Start up children
    for(int i = 0; i < processes; i++)
    {
        p = fork();
        if(p < 0)
        {
            cout << "Error when trying to fork\n";
            free(childPids);
            exit(-1);
        }
        if(p == 0)
        {
            // Child process: Start the program with the
            // programstartcmd command.
            system(programstartcmd.c_str());
            exit(0);
        }
        else
        {
            // Parent (ie launcher). Remember the child and
            // start a new one in a few seconds.
            childPids[i] = p;
            sleep(5);
        }
    }


    if(screenlock)
    {
        string cmd = findscreenlock();
        if(cmd != "")
            system(cmd.c_str());
    }


    // Wait for children to exit
    int stillWaiting = 1;
    while(stillWaiting)
    {
        // Assume we're done, and change the flag otherwise.
        stillWaiting = 0;

        for(int i = 0; i < processes; i++)
        {
            if(childPids[i] > 0)
            {
                if(waitpid(childPids[i], NULL, WNOHANG) != 0)
                {
                    // Child is done
                    childPids[i] = 0;
                }
                else
                {
                    // Still waiting on this child
                    stillWaiting = 1;
                }
            }
            // Give up timeslice and prevent hard loop.
            // This may not work on all flavors of Unix
            // Sleep for a very long time - this is most
            // likely less resource demanding than
            // constantly looping. It will take a very
            // long time until the launcher finishes, but
            // we don't really expect the namebreaker
            // to ever finish - its better to be nice
            // with the resources.
            sleep(1024);
        }
    }

    // Cleanup
    free(childPids);


    cout << "DONE!!!" << endl;
    return 0;
}



int getNumberOfCores()
{
#if defined(WIN32)
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#else
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}


void sleep(int seconds)
{
#if defined(WIN32)
        Sleep(seconds * 1000);
#else
        struct timespec delay;
        delay.tv_sec  = seconds;
        delay.tv_nsec = 0;
        if(nanosleep(&delay, NULL))
            cout << "nanosleep error\n";
#endif
}

void readPropertiesFile(string &prog, string &dir)
{
    string home = getenv("HOME");
    stringstream ss;
    ss << home << "/.namebreak";
    ifstream inputfile(ss.str().c_str());  // Open the file
    if(!inputfile.is_open())               // Unable to read file.
    {
        prog = "";
        dir  = "";
    }
    else
    {
        const int MAXLINESIZE = 100;
        char line[MAXLINESIZE];
        char  tmp[MAXLINESIZE];
        for(int i = 0; !inputfile.eof(); i++)
        {
            inputfile.getline(line, MAXLINESIZE);
            char *pch = strstr(line, "program=");
            if(pch != NULL)
            {
                strcpy(tmp, pch + strlen("program="));
                prog = tmp;
                if(tmp[0] == '~')
                {
                    strcpy(tmp, pch + strlen("program=") + 1);
                    stringstream ss;
                    ss << home << tmp;
                    prog = ss.str();
                }
            }
            pch = strstr(line, "dir=");
            if(pch != NULL)
            {
                strcpy(tmp, pch + strlen("dir="));
                dir = tmp;
                if(tmp[0] == '~')
                {
                    strcpy(tmp, pch + strlen("dir=") + 1);
                    stringstream ss;
                    ss << home << tmp;
                    dir = ss.str();
                }

                // Create the output directory if it doesn't exist.
                struct stat st = {0};
                if(stat(dir.c_str(), &st) == -1)
                    mkdir(dir.c_str(), 0700);
            }
        }
    }
    inputfile.close();
}


// http://unix.stackexchange.com/questions/47037/how-can-my-script-know-when-im-in-a-virtual-console-vs-an-xterm
// See if this is a virtual console or if this is run through an
// X-session. We see this by running "echo $DISPLAY", which should
// return empty if this is not an X-session.
bool isvirtualconsole()
{
    return getCommandOutput("echo $DISPLAY") == "\n";
}


// This function will try to find the users terminal of choise. That
// is done by looking if there is an x-terminal-emulator in
// /etc/alternatives/x-terminal-emulator. If so, that link is used
// as a terminal. If not, "gnome-terminal" is used as a fallback.
string findterminal()
{
    // Open the file
    ifstream inputfile("/etc/alternatives/x-terminal-emulator");
    if(!inputfile.is_open())    // Unable to read file.
        return "gnome-terminal";
    return "/etc/alternatives/x-terminal-emulator";
}


// Try to find the screen lock. Try to see if the user has installed
// any of the different screenlocks that we know about, using the
// "which" command. If we find one, return the command to lock the
// screen. If this is a virtual console, then clear the screen and
// use vlock. If none of the screenlocks that we know about seem to
// be installed, return "".
string findscreenlock()
{
    if(isvirtualconsole())
        return "clear && vlock -c";

    if(getCommandOutput("which gnome-screensaver-command") != "")
        return "gnome-screensaver-command -l";

    if(getCommandOutput("which xscreensaver-command") != "")
        return "xscreensaver-command -lock";

    return "";
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

int changeConfigFiles(string prog, string dir, int processes)
{
    ifstream inputfile;
    stringstream ss;
    string newprogpath, newdirpath, temp, newcustomcmd = "";
    bool newt, newl, newq;
    int newp = 0;

    cout << "Do you wish to edit the standard configuration of the namebreaker program and\n";
    cout << "the launcher? This will be saved to \"" << getenv("HOME") << "/.namebreak\" (y or n)\n";
    getline(cin, temp);
    if(temp == "y")
    {
        while(true)
        {
            cout << "Please enter the path to the namebreaker application.\n";
            if(prog != "")
                cout << "The current path is: " << prog << endl;
            getline(cin, newprogpath);

            ifstream inputfile(newprogpath.c_str());
            if(!inputfile.is_open())    // Unable to read file.
            {
                cout << "The file you entered does not seem to exist. Do you want to enter a new path?\n";
                cout << "Press 'y' to enter a new path, or 'n' to save the path you gave. (y or n)\n";
                getline(cin, temp);
                if(temp != "y")
                    break;
            }
        }

        cout << "\nPlease enter the path where the files with hits should be saved.\n";
        if(dir != "")
            cout << "The current path is: " << dir << endl;
        getline(cin, newdirpath);

        cout << "\nDo you wish to enter any flags and parameters? (y or n)\n";
        getline(cin, temp);
        if(temp == "y")
        {
            cout << "Start namebreaker in new terminal? Default is 'y'. (y or n)\n";
            getline(cin, temp);
            newt = temp == "y";

            cout << "Lock screen once the namebreaker has started? Default is 'y'. (y or n)\n";
            getline(cin, temp);
            newl = temp == "y";

            cout << "Run namebreaker quietly (only prints important info)? Default is 'n'. (y or n)\n";
            getline(cin, temp);
            newq = temp == "y";

            cout << "Default is to start as many processes as there are CPU cores on the computer.\n";
            cout << "You can enter a positive integer to start that many cores, or enter '0' to keep\n";
            cout << "the default of starting as many cores as there are CPU processes.\n";
            getline(cin, temp);
            ss << temp;
            if(!(ss >> newp))
                newp = 0;
            cout << newp << endl;
        }
    }
    if(newp <= 0)
        newp = processes;


    cout << "Do you wish to run a custom command instead of the default values you have\n";
    cout << "given? This will override all default preferences you have given, and is not\n";
    cout << "usually recommended. (y or n)\n";
    getline(cin, temp);
    if(temp == "y")
    {
        cout << "Enter the command to execute here:\n";
        getline(cin, newcustomcmd);
    }
    return 0;
}


// https://www.chalmers.se/insidan/EN/tools/it/computer-workplace/linux/background-jobs
// Expect can probably be used to automate that kinit requires password.
