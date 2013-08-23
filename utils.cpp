#include "utils.h"
using namespace std;

// LOCAL //

void terminate(int /*param*/)
{
	ofstream out(savelasttrypath, ofstream::out | ofstream::trunc);
	out << str;
	out.close();
    stringstream ss;
	ss << "\t" << str << endl;
    print(ss.str(), 0);
	exit(1);
}

int loadData()
{
	fstream inputfile(savelasttrypath);	// Open the file
	if(inputfile.fail())
		return -1;

	// Fill str char by char with the data read
	int i = 0;
	while(!inputfile.eof())
		inputfile.get(str[i++]);
	str[i - 1] = '\0';
	inputfile.close();
    stringstream ss;
	ss << "Resuming at \"" << str << "\". Size is " << i - 1 << endl;
    print(ss.str(), 0);

	size = i - 1;
    return 0;
}



// NETWORK //

void setOutputFile(string dir)
{
    int i = 0;
    while(i < 1024)     // Some arbitrary limit
    {
        string str = dir + "/Found" + int2str(i) + ".txt";

        fstream file(str.c_str());
        if(!file.good())
        {
            file.close();

            ofstream file(str.c_str());
            file << "";
            file.close();

            savematchpath = str;
            string temp   = str + "\n";
            print(temp, 0);
            return;
        }
        file.close();
        i++;
    }
}






// BOTH //

string int2str(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}


void print(string message, bool important)
{
    if(important || !quiet)
        cout << message;
}



// NONE //

int loadFromFile(const char* filename, bool matchesonly)
{
	fstream inputfile(filename);	// Open the file
	if(inputfile.fail())            // Unable to read file.
		return -1;

    cout << "Analyzing input file...\n";
    const int MAXLINESIZE = 100;
    char line[MAXLINESIZE];
	for(int i = 0; !inputfile.eof(); i++)
    {
        inputfile.getline(line, MAXLINESIZE);
        if(line[0] == '\0')
            continue;
        for(int j = 0; line[j] != '\0'; j++)
            line[j] = toupper(line[j]);

        if(!matchesonly && (int)HashString(line) != CODENAME1)
            cout << "Line " << i << ": Not a valid hit! " << line << endl;
        if((unsigned int)HashString_orig(line, 2) == CODENAME2)
            cout << "Line " << i << ": MATCH!!! " << line << endl;
    }
    cout << "Analysis done.\n";
    inputfile.close();
	return 0;
}
