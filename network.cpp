
#include "network.h"
using namespace std;
string data; // will hold the site contents


void network_handshake(int mode)
{
    int ret, no = 0;

    // Begin by emptying the hitqueue. If we could send without
    // problems, we sleep 3 seconds (in order not to drown the server
    // in requests to handle). If there were problems with sending,
    // we sleep 60 seconds, and hope we are more lucky connecting then.
    while(!hitqueue.empty())
    {
        hitdata e = hitqueue.front();
        int mode  = (e.getMatch() ? 3 : 2);
        ret = network(mode, e.getString(), int2str(e.getSlashPos()),
                      int2str(e.getHitNumber()), no++);

        if(ret == 0)        // OK
        {
            hitqueue.pop_front();
            sleep(3);
        }
        else if(ret == 1)   // Abandon range
            hitqueue.clear();
        else                // Error sending. Wait and retry
            sleep(60);
    }
    ret = -1; no = 0;

    // Attempt to get a new range, until we succeed.
    while(ret < 0)
    {
        ret = network(mode, "", int2str(-1), int2str(hitnumber), no++);
        if(ret < 0)
            sleep(60);
    }
}
bool network_hit  (int slashpos) { return network_sendhit(slashpos, 0);}
bool network_match(int slashpos) { return network_sendhit(slashpos, 1);}

bool network_sendhit(int slashpos, bool match)
{
    // Place in queue
    string temp = str;
    hitqueue.push_back(hitdata(hitnumber, slashpos, match, temp));

    // Get the first element in queue, which is usually, but not
    // neccessarily, the one we just inserted.
    hitdata e = hitqueue.front();
    int mode  = (e.getMatch() ? 3 : 2);
    int ret   = network(mode, e.getString(), int2str(e.getSlashPos()),
                        int2str(e.getHitNumber()), 0);

    if(ret == 0)
        hitqueue.pop_front();
    if(ret == 1)
        hitqueue.clear();

    // Return 1 if ret is 1, otherwise 0.
    return (ret > 0);
}



size_t writeCallback(char* buf, size_t size, size_t nmemb, void* /*up*/)
{
    // buf is a pointer to the data that curl has for us
    // size*nmemb is the size of the buffer

    for(int c = 0; c < (int)(size * nmemb); c++)
        data.push_back(buf[c]);
    return size * nmemb; // tell curl how many bytes we handled
}


int network(int mode, string hit, string slashpos, string hitno,
    int attemptnumber)
{
    stringstream ss;
    string hostname, os, osversion;
    int cores;
    getSystemInfo(cores, os, osversion, hostname);

    // mode:
    // 0 == Handshake, first time, 1 == Handshake, report old range,
    // 2 == tell server of hit,    3 == tell server of a match
    string url = "http://thehomepageinternet.org/namebreak/";
    if(mode == 0)
        url += "hs.php?usr=" + hostname  + "&os="    + os +
               "&osversion=" + osversion + "&cores=" + int2str(cores);
    else if(mode == 1)
    {
        // We just finished with the range we worked on.
        // Sleep for 1 second, to make sure the server has had time
        // to process the hit that we just reported.
        sleep(1);
        string fst = makeStringTransmittable(FIRSTWORD);
        string lst = makeStringTransmittable(LASTWORD);
        url += "hs.php?usr=" + hostname + "&fst=" + fst + "&lst=" +
               lst + "&num=" + hitno;
    }
    else if(mode == 2)
    {
        string fst = makeStringTransmittable(FIRSTWORD);
        string lst = makeStringTransmittable(LASTWORD);
        string tmp = makeStringTransmittable(hit);
        url += "hit.php?usr=" + hostname + "&fst=" + fst + "&lst=" +
            lst + "&pos=" + slashpos + "&hit=" + tmp + "&num=" + hitno;
    }
    else if(mode == 3)
    {
        string fst = makeStringTransmittable(FIRSTWORD);
        string lst = makeStringTransmittable(LASTWORD);
        string tmp = makeStringTransmittable(hit);
        url += "match.php?usr=" + hostname + "&fst=" + fst + "&lst=" +
               "&pos=" + slashpos + "&match=" + tmp + "&num=" + hitno;
    }



    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_perform(curl);


    // mode:
    // 0 == Handshake, first time, 1 == Handshake, report old range,
    // 2 == tell server of hit,    3 == tell server of a match
    if(mode == 0 || mode == 1)
    {
        int i, j, lstsize, startatsize, datasize = data.size();
        if(data.find("#") == string::npos)
        {
            ss  << "\nAttempt " << attemptnumber
                << ": Got unexpected data from server: \""
                << data << "\"\n";
            print(ss.str(), 0);
            cleanup(curl);
            return -1;
        }

        // Read the first word
        for(i = 0, j = 0; i < datasize; i++)
        {
            if(data[i] == '\n')
                continue;
            if(data[i] == '#')
                break;
            FIRSTWORD[j++] = data[i];
        }
        size = j;
        for( ; j < MAXARRSIZE; j++)
            FIRSTWORD[j] = ' ';


        // Read the last word
        for(i = i + 1, j = 0; i < datasize; i++)
        {
            if(data[i] == '\0')
                break;
            if(data[i] == '#')
                break;
            LASTWORD[j++] = data[i];
        }
        lstsize = j;
        for( ; j < MAXARRSIZE; j++)
            LASTWORD[j] = '_';


        // Read the word to begin at
        for(i = i + 1, j = 0; i < datasize; i++)
        {
            if(data[i] == '\0')
                break;
            if(data[i] == '#')
                break;
            str[j++] = data[i];
        }
        str[j] = '\0';
        startatsize = j;


        // Read the number of hits int
        string nohits = "";
        for(i = i + 1; i < datasize; i++)
        {
            if(data[i] == '\0')
                break;
            nohits.push_back(data[i]);
        }
        hitnumber = atoi(nohits.c_str());


        // If we got no start word, begin at FIRSTWORD
        if(startatsize == 0)
        {
            for(i = 0; i < size; i++)
                str[i] = FIRSTWORD[i];
            str[i] = '\0';
        }


        if(lstsize != size || startatsize != size)
        {
            ss  << "\nAttempt " << attemptnumber
                << ": Ranges are of different sizes. First range is "
                << size << " chars: \"" << FIRSTWORD
                << "\" but the second range is " << lstsize
                << " chars: \"" << LASTWORD << "\".\n";
            print(ss.str(), 1);
            cleanup(curl);
            return -1;
        }


        ss << "Size: " << dec << size << endl;
        ss << "First: \"" << FIRSTWORD << "\"\n";
        ss << "Last : \"" << LASTWORD << "\"\n";
        ss << "Beginat : \"" << str << "\"\n";
        ss << "Hitnumber : \"" << hitnumber << "\"\n";
        print(ss.str(), 0);

        ofstream out(savematchpath.c_str(), ofstream::app);
        out << "\n\n\"" << FIRSTWORD << "\" - \"" << LASTWORD << "\"\n";
        out.close();
    }
    else if(mode == 2 || mode == 3)
    {
        if(data == "ok")
        {
            // Everything works as expected.
            ss << " Data sent.\n";
            print(ss.str(), 0);
        }
        else if(data == "no")
        {
            ss << "\nAbandoning range. About to ask server for new.\n";
            print(ss.str(), 0);
            cleanup(curl);
            sleep(1);
            return 1;
        }
        else
        {
            ss  << "\nAttempt " << attemptnumber << ": Queue size: "
                << hitqueue.size() << ". Got unexpected server "
                << "response when reporting hit: \"" << data << "\"\n";
            print(ss.str(), 0);
            cleanup(curl);
            return -1;
        }
    }

    cleanup(curl);
    return 0;
}

void cleanup(CURL* curl)
{
    data = "";
    curl_easy_cleanup(curl);
    curl_global_cleanup();
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
        {
            stringstream ss("nanosleep error\n");
            print(ss.str(), 1);
        }
#endif
}

string makeStringTransmittable(string in)
{
    string out = in.substr(0, size);

    for(int i = 0; i < (int)out.size(); i++)
    {
        if( out[i] == '+' )
            out[i] =  '=' ;
        if( out[i] == ' ' )
            out[i] =  '!' ;
    }
    return out;
}

void getSystemInfo(int &cores, string &os, string &osversion, string &hostname)
{
#if defined(WIN32)
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    cores = sysinfo.dwNumberOfProcessors;

    os = "Windows";
    osversion = "Unknown";
    hostname = "Windows";

#else
    cores = sysconf(_SC_NPROCESSORS_ONLN);

/*
struct utsname {
    char sysname[];    // Operating system name (e.g., "Linux")
    char nodename[];   // Name within "some implementation-defined
                                     network"
    char release[];    // OS release (e.g., "2.6.28")
    char version[];    // OS version
    char machine[];    // Hardware identifier
#ifdef _GNU_SOURCE
    char domainname[]; // NIS or YP domain name
#endif
};
*/
    struct utsname u_name;
    if(uname(&u_name) != -1)
    {
        os = u_name.sysname;
        osversion = u_name.release;
        hostname = u_name.nodename;
    }
    else
    {
        os = "Unknown";
        osversion = "Unknown";
        hostname = "Unknown";
    }
#endif
}
