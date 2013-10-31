
#include "general.h"
using namespace std;

bool saveMatchGeneral()
{
    char temp[MAXARRSIZE];
	int i = 0, j = 0;
	while(PRE[i] != '\0')
		temp[j++] = PRE[i++];

    i = 0;
    while(str[i] != '\0')
        temp[j++] = str[i++];

	i = 0;
	while(POST[i] != '\0')
		temp[j++] = POST[i++];
	temp[j] = '\0';



    hitnumber++;
	ofstream out(savematchpath.c_str(), ofstream::app);
	out << temp;

    stringstream ss;
    if(hitnumber < 10)  ss << " ";
    if(hitnumber < 100) ss << " ";
    ss << hitnumber << ": " << temp;


    bool important = 0;
    if((unsigned int)HashString(temp) != CODENAME1)
    {
        ss << " No hit!! Codename1: " << hex << (int)HashString(temp);
        important = 1;
    }
    ss << " Codename2: ";

    string outputstr = ss.str();
    ss.str("");
    ss << hex << HashString_orig(temp, 2);
    for(int i = ss.str().length(); i < 16; i++)
        ss << " ";
    print(outputstr + ss.str(), important);

    bool restart = false;
    if(networkmode)
        restart = network_hit(0);

    if((unsigned int)HashString_orig(temp, 2) == CODENAME2)
	{
		print("\033[22;31m MATCH FOUND!!!!\n\n", 0);
		out << "  MATCH FOUND!!!!!!!!!!!!!\n\n";
        if(networkmode)
            network_match(0);
	}
	out << endl;
	out.close();


    // If we are to restart, then do a network handshake and
    // return true to indicate that we have a new range.
    if(networkmode && restart)
    {
        network_handshake(0);
        InitializeSeedsTable();
        return true;
    }
    //out(savelasttrypath, ofstream::out | ofstream::trunc);
	//out << str;
	//out.close();
    return false;
}





void runLoopGeneral()
{
    while(size <= 4)
	{
        char temp[MAXARRSIZE];
        int i = 0, j = 0;
        while(PRE[i] != '\0')
            temp[j++] = PRE[i++];

        i = 0;
        while(str[i] != '\0')
            temp[j++] = str[i++];

        i = 0;
        while(POST[i] != '\0')
            temp[j++] = POST[i++];
        temp[j] = '\0';


        if((int)HashString(temp) == CODENAME1)
            if(saveMatchGeneral())
                continue;
		getNextGeneral();
	}
}





void getNextGeneral()
{
	// str is for example "KHADNCR"
	// Increment the string
	char ch = getNextCharGeneral(str[size - 1]);
	str[size - 1] = ch;				// Increment the last char

	// Now the last char has been incremented. If all possible chars
	// have been tested, we need to increment the second last char, see
	// if all of them have been tested and if so increment the next one
	// in order etc. Eventually, all chars in all positions will have
	// been tested. When that happens, add in one more char and start
	// over with the one char longer word.
	if(ch == FIRSTCHAR)
	{
		int x, a;

        if(size == 1)
            str[0] = '_';
        else if(size == 2)
        {
            ch = getNextCharGeneral(str[0]);
            str[0] = ch;
            if(ch == FIRSTCHAR)
                str[0] = str[1] = '_';
        }
        else
        {
            // Increment chars in the other positions when neccessary:
            for(a = size - 2; a >= 0; a--)
            {
                ch = getNextCharGeneral(str[a]);
                str[a] = ch;
                if(ch != FIRSTCHAR)
                    break;
            }
		}

        // Now we have incremented the chars. We now need to test check
		// and see if all positions have been tested. If so, add one
		// more char to the string (ie '___' becomes '    ').

		// We check to see if we're finished by comparing the string
		// with the upper bound string (LASTWORD), char by char. If the
		// chars in position i are equal, check the next one. If we have
		// a position where the char is less than that in LASTWORD, we
		// know that we haven't reached the upper bound string yet. If
		// the char is greater in some place, we know that we have
		// reached the upper bound and thus need to expand the word.
//		for(i = lastincrementedindex; i < size; i++)
		for(x = 0; x < size; x++)
		{
			if(str[x] < LASTWORD[x])
				break;
			if(str[x] > LASTWORD[x])	// Expand word
			{
				size++;
                stringstream ss;
                ss << "String about to get expanded! \"" << str << "\" ";
				for(x = 0; x < size; x++)
					str[x] = FIRSTWORD[x];
				str[x] = '\0';

				ss << "New size: " << size << " \"" << str << "\"" << endl;
                print(ss.str(), 0);
				break;
			}
		}
	}
}

char getNextCharGeneral(char ch)
{
	if((ch >= 'A' && ch < '[') || (ch >= '+' && ch < '9'))
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
//char validChars[] = {' ', '(', ')', '+', ',', '-', '.', '/', '0' - '9', 'A' - 'Z', '[', '\\', ']', '_' };


