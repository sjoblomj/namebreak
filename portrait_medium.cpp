
#include "portrait_medium.h"
using namespace std;

/*
bool saveMatchMediumRange(int stringtype)
{
    char temp[MAXARRSIZE + 20];
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
        ss << " No hit!! Codename1: " << hex;
        ss << (unsigned int)HashString(temp);
        important = 1;
    }
    ss << " Codename2: ";

    string outputstr = ss.str();
    ss.str("");
    ss << hex << HashString_orig(temp, 2);
    for(int i = ss.str().length(); i < 16; i++)
        ss.str(" " + ss.str());
    print(outputstr + ss.str(), important);

    bool restart = false;
    if(networkmode)
        restart = network_hit(stringtype);

    if((unsigned int)HashString_orig(temp, 2) == CODENAME2)
    {
        print("\033[22;31m MATCH FOUND!!!!\n\n", 1);
        out << "  MATCH FOUND!!!!!!!!!!!!!\n\n";
        if(networkmode)
            network_match(stringtype);
    }
    out << endl;
    out.close();
    if(!networkmode) print("\n", 0);

    #ifdef VALIDATE
    if(strcmp(temp, ANSWER.c_str()) == 0)
        exit(0);
    if(strcmp(temp, ANSWER.c_str()) > 0 && strlen(temp) >= strlen(ANSWER.c_str()))
    {
        ss.str("");
        ss << "String not found! The right answer is \"" << ANSWER;
        ss << "\", but it hasn't been found. Last hit: \"" << temp;
        ss << "\".\n";
        print(ss.str(), 1);
        exit(1);
    }
    #endif


    // If we are to restart, then do a network handshake and
    // return true to indicate that we have a new range.
    if(networkmode && restart)
    {
        network_handshake(0);
        InitializeSeedsTable();
        return true;
    }
    return false;
}

*/




void runLoopMediumRange(int upperlimit)
{
    int ch, offset, i;
    unsigned long seed1, seed2;
    unsigned long seeda, seedb;
    InitializeSeedsTable();

    int oldsize = size;
    // getNextMediumRange will expand the size when needed.
LoopMedium:
    while(size < upperlimit && size == oldsize)
    {
        ch = str[size - 1];
        offset = 0x100 + ch;

        for(i = 1; i >= 0; i--)
        {
            seed2 = seeds[size - 1][i][1];
            seeda = dwCryptTable[offset] ^ (seeds[size - 1][i][0] + seed2); // Last letter
            seedb = ch + seeda + seed2 + (seed2 << 5) + 3;

            seeda = seeda + seedb;
            seedb = seedb + (seedb << 5);


            seed1 = 0xC680EC6C ^ seeda;                 // F
            seed2 = 73 + seed1 + seedb;

            seed1 = 0x6A227D2F ^ (seed1 + seed2);       // I
            seed2 = 76 + seed1 + seed2 + (seed2 << 5);

            seed1 = 0x31A5E829 ^ (seed1 + seed2);       // D
            seed2 = 71 + seed1 + seed2 + (seed2 << 5);

            seed1 = 0x7EB0DBE0 ^ (seed1 + seed2);       // 0
            seed2 = 51 + seed1 + seed2 + (seed2 << 5);

            seed1 = 0x7EB0DBE0 ^ (seed1 + seed2);       // 0
            seed2 = 51 + seed1 + seed2 + (seed2 << 5);

            seed1 = 0x7DFB8384 ^ (seed1 + seed2);       // .
            seed2 = 49 + seed1 + seed2 + (seed2 << 5);

            seed1 = 0xD3723E97 ^ (seed1 + seed2);       // S
            seed2 = 86 + seed1 + seed2 + (seed2 << 5);

            seed1 = 0xE4D00ED6 ^ (seed1 + seed2);       // M
            seed2 = 80 + seed1 + seed2 + (seed2 << 5);


            if(((unsigned int)(0x8DF65112 ^ (seed1 + seed2))) == CODENAME1)
                if(saveMatch(i, false))
                    // Would be nice with a 'continue', but that would
                    // continue the inner loop and we want to continue the outer.
                    goto LoopMedium;
        }

        seed1 = 0x2DEB6BC0 ^ seeda;                 // /
        seed2 = 95 + seed1 + seedb;

        seed1 = 0xC680EC6C ^ (seed1 + seed2);       // F
        seed2 = 73 + seed1 + seed2 + (seed2 << 5);

        seed1 = 0x6A227D2F ^ (seed1 + seed2);       // I
        seed2 = 76 + seed1 + seed2 + (seed2 << 5);

        seed1 = 0x31A5E829 ^ (seed1 + seed2);       // D
        seed2 = 71 + seed1 + seed2 + (seed2 << 5);

        seed1 = 0x7EB0DBE0 ^ (seed1 + seed2);       // 0
        seed2 = 51 + seed1 + seed2 + (seed2 << 5);

        seed1 = 0x7EB0DBE0 ^ (seed1 + seed2);       // 0
        seed2 = 51 + seed1 + seed2 + (seed2 << 5);

        seed1 = 0x7DFB8384 ^ (seed1 + seed2);       // .
        seed2 = 49 + seed1 + seed2 + (seed2 << 5);

        seed1 = 0xD3723E97 ^ (seed1 + seed2);       // S
        seed2 = 86 + seed1 + seed2 + (seed2 << 5);

        seed1 = 0xE4D00ED6 ^ (seed1 + seed2);       // M
        seed2 = 80 + seed1 + seed2 + (seed2 << 5);

        if(((unsigned int)(0x8DF65112 ^ (seed1 + seed2))) == CODENAME1)
            if(saveMatch(2, false))
                continue;

        getNextMediumRange();
    }
}



void getNextMediumRange()
{
    // str is for example "KHADNCR"
    // Increment the string
    char ch = getNextChar(str[size - 1]);
    str[size - 1] = ch;             // Increment the last char

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
//      for(i = lastincrementedindex; i < size; i++)
        for(int x = 0; x < size; x++)
        {
            if(str[x] < LASTWORD[x])
                break;
            if(str[x] > LASTWORD[x])    // Expand word
            {
                if(networkmode)
                {
                    network_handshake(1);  // Get new range from network
                    InitializeSeedsTable();
                    return;
                }
                else
                {
                    size++;
                    stringstream ss;
                    ss << "String about to get expanded! Was: \"";
                    ss << str << "\" ";
                    for(x = 0; x < size; x++)
                        str[x] = FIRSTWORD[x];
                    str[x] = '\0';
                    InitializeSeedsTable();
                    a = 0;

                    ss << "New size: " << size << ". Now: \"";
                    ss << str << "\""  << endl;
                    print(ss.str(), 0);
                    break;
                }
            }
        }


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
            a = 1;  // The first value shouldn't be changed.
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
    }
}
