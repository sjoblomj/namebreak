
#include "portrait_fast.h"
using namespace std;

bool saveMatchFast(int stringtype)
{
    char temp[MAXARRSIZE];
	int i = 0, j = 0;
	while(PRE[i] != '\0')
		temp[j++] = PRE[i++];


    if(stringtype == 0)
    {
        i = 0;
        while(str[i] != '\0')
            temp[j++] = str[i++];
    }
    else if(stringtype == 1)
    {
        i = 0;
        while((i < size - 3) && (str[i] != '\0'))
            temp[j++] = str[i++];
        temp[j++] = '\\';
        while(str[i] != '\0')
            temp[j++] = str[i++];
    }
    else
    {
        i = 0;
        while(str[i] != '\0')
            temp[j++] = str[i++];
        temp[j++] = '\\';
    }

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

    if(stringtype == 0) ss << " ";
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
        restart = network_hit(stringtype);

	if((unsigned int)HashString_orig(temp, 2) == CODENAME2)
	{
		print("\033[22;31m MATCH FOUND!!!!\n\n", 0);
		out << "  MATCH FOUND!!!!!!!!!!!!!\n\n";
        if(networkmode)
            network_match(stringtype);
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
    bool expanded = false;
	for(i = 0; i < size; i++)
    {
//cout << i << " " << str << " " << (char)str[i] << " " <<(char)LASTWORD[i] << endl;
        if(str[i] < LASTWORD[i])
            break;
        if(str[i] > LASTWORD[i])	// Expand word
        {
            expanded = true;
            if(!networkmode)
            {
                size++;
                ss.str("");
                ss << "String about to get expanded! \"" << str << "\" ";
                for(i = 0; i < size; i++)
                    str[i] = FIRSTWORD[i];
                str[i] = '\0';
                InitializeSeedsTable();

                ss << "New size: " << dec << size << " \"" << str << "\"" << endl;
                print(ss.str(), 0);
            }
            else
            {
                network_handshake(1);   // Get new range from network
                InitializeSeedsTable();
            }
            break;
        }
    }
    return expanded;
}





void runLoopFast()
{
	int ch, offset, i;
	unsigned long seed1, seed2;
	unsigned long seeda, seedb;
    InitializeSeedsTable();

Loop:
	while(true)
//for(int k = 0; k < 100; k++)
	{
		ch = str[size - 1];
		offset = 0x100 + ch;

		for(i = 1; i >= 0; i--)
		{
			seed2 = seeds[size - 1][i][1];
//if(i == 0) cout << (char)ch << " " << seeds[size][i][1] << " " << seed2 << " ";
			seeda = dwCryptTable[offset] ^ (seeds[size - 1][i][0] + seed2);	// Last letter
			seedb = ch + seeda + seed2 + (seed2 << 5) + 3;
//if(i == 0) cout << seedb << endl;
            seeda = seeda + seedb;
            seedb = seedb + (seedb << 5);


			seed1 = 0xC680EC6C ^ seeda;         		// F
			seed2 = 73 + seed1 + seedb;

			seed1 = 0x6A227D2F ^ (seed1 + seed2);		// I
			seed2 = 76 + seed1 + seed2 + (seed2 << 5);

			seed1 = 0x31A5E829 ^ (seed1 + seed2);		// D
			seed2 = 71 + seed1 + seed2 + (seed2 << 5);

			seed1 = 0x7EB0DBE0 ^ (seed1 + seed2);		// 0
			seed2 = 51 + seed1 + seed2 + (seed2 << 5);

			seed1 = 0x7EB0DBE0 ^ (seed1 + seed2);		// 0
			seed2 = 51 + seed1 + seed2 + (seed2 << 5);

			seed1 = 0x7DFB8384 ^ (seed1 + seed2);		// .
			seed2 = 49 + seed1 + seed2 + (seed2 << 5);

			seed1 = 0xD3723E97 ^ (seed1 + seed2);		// S
			seed2 = 86 + seed1 + seed2 + (seed2 << 5);

			seed1 = 0xE4D00ED6 ^ (seed1 + seed2);		// M
			seed2 = 80 + seed1 + seed2 + (seed2 << 5);


/*
{
char temp[MAXARRSIZE];
int k = 0, l = 0;
while(PRE[k] != '\0')
    temp[l++] = PRE[k++];
k = 0;
if(i == 0)
{
    while((k < size) && (str[k] != '\0'))
        temp[l++] = str[k++];
}
else
{
    while((k < size - 3) && (str[k] != '\0'))
        temp[l++] = str[k++];
    temp[l++] = '\\';
    while((k < size) && (str[k] != '\0'))
        temp[l++] = str[k++];
}
k = 0;
while(POST[k] != '\0')
    temp[l++] = POST[k++];
temp[l] = '\0';

unsigned long seedz = 0x8DF65112 ^ (seed1 + seed2);
if(seedz != HashString(temp))
{
cout << i << " Hashes don't match!\n";
cout << temp << " "<< str<< " " << seedz << " " << HashString(temp)<< endl <<endl;
}

//cout << "*" << temp << "*\n";
//cout << temp << " " << str << "\t" << seed1 << "\t" << HashString(temp) << endl;
// check if what we have calculated is correct:
//if(((0xC680EC6C ^ (seed1 + seed2)) == HashString(temp)))
//cout << "Hashes match!\n";
}
*/

			if(((int)(0x8DF65112 ^ (seed1 + seed2))) == CODENAME1)
			{
                // We have a seed matching CODENAME1. Output via
                // saveMatchFast. That method will expand the string,
                // if needed, and update the size. If the size is
                // updated, begin the next loop iteration.
                int oldsize = size;
				if(saveMatchFast(i) || size != oldsize)
                {
                    // Would be nice with a 'continue', but that would
                    // continue the inner loop and we want to continue the outer.
                    goto Loop;
                }
			}
		}

/*		seed2 = seeds[size - 1][0][1];

		seed1 = dwCryptTable[offset] ^ (seeds[size - 1][0][0] + seed2);	// Last letter
		seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
*/

		seed1 = 0x2DEB6BC0 ^ seeda;	            	// /
		seed2 = 95 + seed1 + seedb;

		seed1 = 0xC680EC6C ^ (seed1 + seed2);		// F
		seed2 = 73 + seed1 + seed2 + (seed2 << 5);

		seed1 = 0x6A227D2F ^ (seed1 + seed2);		// I
		seed2 = 76 + seed1 + seed2 + (seed2 << 5);

		seed1 = 0x31A5E829 ^ (seed1 + seed2);		// D
		seed2 = 71 + seed1 + seed2 + (seed2 << 5);

		seed1 = 0x7EB0DBE0 ^ (seed1 + seed2);		// 0
		seed2 = 51 + seed1 + seed2 + (seed2 << 5);

		seed1 = 0x7EB0DBE0 ^ (seed1 + seed2);		// 0
		seed2 = 51 + seed1 + seed2 + (seed2 << 5);

		seed1 = 0x7DFB8384 ^ (seed1 + seed2);		// .
		seed2 = 49 + seed1 + seed2 + (seed2 << 5);

		seed1 = 0xD3723E97 ^ (seed1 + seed2);		// S
		seed2 = 86 + seed1 + seed2 + (seed2 << 5);

		seed1 = 0xE4D00ED6 ^ (seed1 + seed2);		// M
		seed2 = 80 + seed1 + seed2 + (seed2 << 5);

/*
{
char temp[MAXARRSIZE];
int k = 0, l = 0;
while(PRE[k] != '\0')
	temp[l++] = PRE[k++];
k = 0;
while((k < size) && (str[k] != '\0'))
	temp[l++] = str[k++];
k = 0;
temp[l++] = '\\';
while(POST[k] != '\0')
	temp[l++] = POST[k++];
temp[l] = '\0';
int seedz = 0x8DF65112 ^ (seed1 + seed2);
cout << temp << " " <<  str << " " << hex<< (int)HashString(temp) << " " << ((int)(0x8DF65112 ^ (seed1 + seed2))) << " " << seedz << " " << CODENAME1 << endl;
}
*/
		if(((int)(0x8DF65112 ^ (seed1 + seed2))) == CODENAME1)
        {
			int oldsize = size;
            if(saveMatchFast(2) || size != oldsize)
                continue;
        }


		getNextFast();
	}
}



void getNextFast()
{
	// str is for example "KHADNCR"
	// Increment the string
	char ch = getNextChar(str[size - 1]);
	str[size - 1] = ch;				// Increment the last char

	// Now the last char has been incremented. If all possible chars
	// have been tested, we need to increment the second last char, see
	// if all of them have been tested and if so increment the next one
	// in order etc. Eventually, all chars in all positions will have
	// been tested. When that happens, add in one more char and start
	// over with the one char longer word.
	if(ch == FIRSTCHAR)
	{
		int a;

		// Increment chars in the other positions when neccessary:
		for(a = size - 2; a >= 0; a--)
		{
			ch = getNextChar(str[a]);
			str[a] = ch;
			if(ch != FIRSTCHAR)
				break;
		}




//cout << hex << (int)seeds[3][1][0] << " " << (int)HashString("PORTRAIT\\UKHB") << endl;

		// Recalculate the seeds for the updated chars:
		// seeds[size - 1][2][2] = seeds[all chars in str exept the last][(normal string, string with '\')][(seed1, seed2)]
		// str = KI]F3WD,L
		// if i = 1  =>  ch_i = 'I'
		// Thus, seeds[i][0][0] = seed1 for char (i - 1), ie 'K'

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

		if(a <= 0)
        {
            //cout << a << " " << str << endl;
            a = 1;	// The first value shouldn't be changed.
        }

		int chi, offset;
		unsigned long seed2, tmp;


        for( ; a < size - 2; a++)   // if size=6, then this is 0 - 3
        {
            chi = str[a - 1];
            offset = chi + 0x100;

            seed2 = seeds[a - 1][0][1];
            seeds[a][0][0] = dwCryptTable[offset] ^ (seeds[a - 1][0][0] + seed2);
            seeds[a][0][1] = chi + seeds[a][0][0] + seed2 + (seed2 << 5) + 3;
        }
        // TODO: My gut feeling tells me that we update the char with / waay too often

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
        chi = str[a];
        offset = chi + 0x100;

        seed2 = seeds[a][0][1];
        a++;
        seeds[a][0][0] = dwCryptTable[offset] ^ (seeds[a - 1][0][0] + seed2);
        seeds[a][0][1] = chi + seeds[a][0][0] + seed2 + (seed2 << 5) + 3;
        seed2 = seeds[a - 1][1][1];
        seeds[a][1][0] = dwCryptTable[offset] ^ (seeds[a - 1][1][0] + seed2);
        seeds[a][1][1] = chi + seeds[a][1][0] + seed2 + (seed2 << 5) + 3;


/*
{
char temp[MAXARRSIZE];
int k = 0, l = 0;
while(PRE[k] != '\0')
	temp[l++] = PRE[k++];
k = 0;
while((k < size - 3) && (str[k] != '\0'))
	temp[l++] = str[k++];
temp[l++] = '\\';
while((k < size + 0) && (str[k] != '\0'))
	temp[l++] = str[k++];
temp[l] = '\0';
cout <<  " \"" << temp << "\" \"" <<  str << "\" " << hex<< (int)HashString(temp) << " " << (int)seeds[6][1][0] << endl;
//cout << hex << (int)HashString() << endl;
}
*/
	}
}


