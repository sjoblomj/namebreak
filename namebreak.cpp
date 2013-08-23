
#include "namebreak.h"
using namespace std;

// Compile with
// g++ -lcurl -O3 -o namebreak constants.cpp general.cpp namebreak.cpp portrait_fast.cpp portrait_slow.cpp network.cpp utils.cpp
// i586-mingw32msvc-g++ -O3 -o namebreak.exe constants.cpp general.cpp namebreak.cpp portrait_fast.cpp portrait_slow.cpp network.cpp utils.cpp


int main(int argc, char* argv[])
{
    InitializeCryptTable();
    stringstream ss;

    networkmode = true;
    quiet = false;
    hitnumber = 0;
    bool loadfile = false, matchesonly = false;
    string filename, dir = ".";

    int c;
    while(true)
    {
        int option_index = 0;
        static struct option long_options[] =
        {
            {"locally",         no_argument,       0, 'l'},
            {"quiet",           no_argument,       0, 'q'},
            {"hitsdir",         required_argument, 0, 'd'},
            {"match-search",    required_argument, 0, 'm'},
            {"no-match-search", required_argument, 0, 'n'},
            {"version",         no_argument,       0, 'v'},
            {"help",            no_argument,       0, 'h'},
            {0, 0, 0, 0}
        };

        c = getopt_long(argc, argv, "lqd:m:n:vh", long_options,
                        &option_index);

        if(c == -1)
            break;

        switch(c)
        {
            case 'l':
                networkmode = 0;
                break;

            case 'q':
                quiet = 1;
                break;

            case 'd':
                dir = optarg;
                break;

            case 'm':
                loadfile = 1;
                matchesonly = 1;
                filename = optarg;
                break;

            case 'n':
                loadfile = 1;
                matchesonly = 0;
                filename = optarg;
                break;

            case 'v':
                ss << "Namebreaker\n";
                ss << "Version 0.5\n";
                ss << "Written by Johan Sjöblom (Ojan), 2011-2013\n";
                ss << "Licensed under GPL 2.0 or newer.\n";
                print(ss.str(), 0);
                return 0;

            case 'h':
                ss << "Namebreaker\n";
                ss << "Usage: " << argv[0] << " [OPTION]... [FILE]...\n\n";
                ss << "Will brute-force the file names that created hash values in MPQ files. If used\n";
                ss << "without options, the namebreaker will connect to a server to obtain work, and\n";
                ss << "submit any hits there.\n\n";
                ss << "Valid options are these:\n";
                ss << "  -l, --locally          Run Locally, ie don't connect to server. Will begin at\n";
                ss << "                         the value in LastTry.txt and save results to Found.txt\n";
                ss << "  -q, --quiet            Won't print out non-important information\n";
                ss << "  -d, --hitsdir=DIRECTORY\n";
                ss << "                         Save hits to Found#.txt in DIRECTORY, where # is the\n";
                ss << "                         next number that isn't already present\n";
                ss << "  -m, --match-search=FILENAME\n";
                ss << "                         Load the file FILENAME and search for any entry that\n";
                ss << "                         is a match (for both CODENAME1 and CODENAME2). Exit\n";
                ss << "                         when done.\n";
                ss << "  -n, --no-match-search=FILENAME\n";
                ss << "                         Load the file FILENAME and display all entries that\n";
                ss << "                         are no valid matches. Exit when done.\n";
                ss << "  -v, --version          Display version information and exit\n";
                ss << "  -h, --help             Display this help and exit\n";
                print(ss.str(), 0);
                return 0;

            case '?':
                break;
            default:
                return(1);
        }
    }


    if(loadfile)
        return loadFromFile(filename.c_str(), matchesonly);


    if(networkmode)
    {
        setOutputFile(dir);   // Only do this if we are in network mode.
        network_handshake(0);
    }
    else
    {
        signal(SIGINT, terminate);
        if(loadData() != 0)
        {
            ss << "Could not load " << savelasttrypath << ". Exiting\n";
            print(ss.str(), 1);
            return -1;
        }
    }


    if(size < 5)
    {
        runLoopGeneral();
        ss << "1st search done. Size is " << size << endl;
        print(ss.str(), 0);
        ss.str("");
    }
    if(size < 8)
    {
        runLoopSlow();
        ss << "2nd search done. Size is " << size << endl;
        print(ss.str(), 0);
        ss.str("");
    }
    runLoopFast();
    ss << "3rd search done. Size is " << size << endl;
    print(ss.str(), 0);
    return 0;
}







// The encryption and hashing functions use a number table in their
// procedures. This table must be initialized before the functions are
// called the first time.
void InitializeCryptTable()
{
    unsigned long seed   = 0x00100001;
    unsigned long index1 = 0;
    unsigned long index2 = 0;
    int   i;

    for (index1 = 0; index1 < 0x100; index1++)
    {
        for (index2 = index1, i = 0; i < 5; i++, index2 += 0x100)
        {
            unsigned long temp1, temp2;

            seed  = (seed * 125 + 3) % 0x2AAAAB;
            temp1 = (seed & 0xFFFF) << 0x10;

            seed  = (seed * 125 + 3) % 0x2AAAAB;
            temp2 = (seed & 0xFFFF);

            dwCryptTable[index2] = (temp1 | temp2);
        }
    }
}


// Based on code from StormLib.
unsigned long HashString_orig(const char *lpszString, unsigned long dwHashType)
{
//    assert(lpszString);
//    assert(dwHashType <= MPQ_HASH_FILE_KEY);

    unsigned long seed1 = 0x7FED7FEDL;
    unsigned long seed2 = 0xEEEEEEEEL;
    int ch;

    while (*lpszString != 0)
    {
        ch = toupper(*lpszString++);

        seed1 = dwCryptTable[(dwHashType * 0x100) + ch] ^ (seed1 + seed2);
        seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
    }
    return seed1;
}

unsigned long HashString(const char *lpszString)
{
    // Assume that lpszString is uppercase
    unsigned long seed1 = 0x7FED7FEDL;
    unsigned long seed2 = 0xEEEEEEEEL;
    int ch;

    while(*lpszString != 0)
    {
        ch = *lpszString++;

        seed1 = dwCryptTable[0x100 + ch] ^ (seed1 + seed2);
        seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
    }
    return seed1;
}



unsigned long HashString_seed2(const char *lpszString)
{
    // Assume that lpszString is uppercase
    unsigned long  seed1 = 0x7FED7FEDL;
    unsigned long  seed2 = 0xEEEEEEEEL;
    int ch;

    while(*lpszString != 0)
    {
        ch = *lpszString++;

        seed1 = dwCryptTable[0x100 + ch] ^ (seed1 + seed2);
        seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
    }
    return seed2;
}








void InitializeSeedsTable()
{
	seeds[0][0][0] = HashString(PRE);
	seeds[0][0][1] = HashString_seed2(PRE);

	int a = 1;
	int chi, offset;
	unsigned long seed2, tmp;

	// seeds[0][0][0] = default starting seed1 - shouldn't be changed
	// seeds[0][1][0] = undefined
	// seeds[1][0][0] = seed1 for K*
	// seeds[1][1][0] = undefined
	// seeds[2][0][0] = seed1 for KI*
	// seeds[2][1][0] = undefined
	// seeds[3][0][0] = seed1 for KI]*
	// seeds[3][1][0] = undefined
	// seeds[4][0][0] = seed1 for KI]F*
	// seeds[4][1][0] = seed1 for KI]\F*
	// seeds[5][0][0] = seed1 for KI]F3*
	// seeds[5][1][0] = seed1 for KI]\F3*
	// seeds[6][0][0] = seed1 for KI]F3W*
	// seeds[6][1][0] = seed1 for KI]\F3W*

	for( ; a < size - 2; a++)   // if size=6, then this is 0 - 3
    {
		chi = str[a - 1];
		offset = chi + 0x100;

		seed2 = seeds[a - 1][0][1];
		seeds[a][0][0] = dwCryptTable[offset] ^ (seeds[a - 1][0][0] + seed2);
		seeds[a][0][1] = chi + seeds[a][0][0] + seed2 + (seed2 << 5) + 3;
    }
    // a = size - 2
    chi = str[a - 1];
    offset = chi + 0x100;

    // Insert the letter at index 0
    seed2 = seeds[a - 1][0][1];
    seeds[a][0][0] = dwCryptTable[offset] ^ (seeds[a - 1][0][0] + seed2);
    seeds[a][0][1] = chi + seeds[a][0][0] + seed2 + (seed2 << 5) + 3;

    // Insert /, then the letter at index 1
    seed2 = seeds[a - 1][0][1];
    tmp            = 0x2DEB6BC0 ^ (seeds[a - 1][0][0] + seed2);
    seed2          = 95  + tmp + seed2 + (seed2 << 5);
    seeds[a][1][0] = dwCryptTable[offset] ^ (tmp + seed2);
    seeds[a][1][1] = chi + seeds[a][1][0] + seed2 + (seed2 << 5) + 3;


    // For the remaining char:
    a++;
    chi = str[a - 1];
    offset = chi + 0x100;

    seed2 = seeds[a - 1][0][1];
    seeds[a][0][0] = dwCryptTable[offset] ^ (seeds[a - 1][0][0] + seed2);
    seeds[a][0][1] = chi + seeds[a][0][0] + seed2 + (seed2 << 5) + 3;
    seed2 = seeds[a - 1][1][1];
    seeds[a][1][0] = dwCryptTable[offset] ^ (seeds[a - 1][1][0] + seed2);
    seeds[a][1][1] = chi + seeds[a][1][0] + seed2 + (seed2 << 5) + 3;
}




char getNextChar(char ch)
{
	if((ch >= 'A' && ch < '[') || (ch >= '0' && ch < '9') || (ch >= '+' && ch < '.'))
		return ch + 1;
	if(ch == '9')
		return 'A';
	if(ch == ' ')
		return '(';
	if(ch == '(')
		return ')';
	if(ch == ')')
		return '+';
	if(ch == '.')
		return '0';
	if(ch == '[')
		return ']';
	if(ch == ']')
		return '_';
	return FIRSTCHAR;
}
//char validChars[] = {' ', '(', ')', '+', ',', '-', '.', '0' - '9', 'A' - 'Z', '[', '\\', ']', '_' };
