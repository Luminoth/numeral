/*
==========
Copyright 2002 Shane Lillie

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
==========
*/


#include <cstdlib>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

#include <errno.h>

extern int errno;


int main(int argc, char* argv[])
{
    // build the numeral map
    map<char, int> numerals;
    numerals['I'] = 1;
    numerals['V'] = 5;
    numerals['X'] = 10;
    numerals['L'] = 50;
    numerals['C'] = 100;
    numerals['D'] = 500;
    numerals['M'] = 1000;

    ifstream f("roman.dat");
    if(!f) {
        cerr << "Error opening file - " << strerror(errno) << endl;
        return 1;
    }

    string line;
    while(!f.eof()) {
        getline(f, line);
        if(line.empty())
            continue;

        char p = 0,  c = 0;
        int ip = 0, ic = 0;
        long value = 0;
        bool valid = true;
        for(unsigned int i=0; i<line.length(); i++) {
            c = toupper(line[i]);
            if(isspace(c))
                continue;

            // get the number value
            ic = numerals[c];
            if(0 == ic) {
                cerr << "Invalid character: " << c << " in " << line << endl;
                valid = false;
                break;
            }

            // base case, add the number to our total value
            if(p == 0)
                value += ic;
            else {
                // get the parents value
                ip = numerals[p];

                // if the parents value is less than the current value, we need to subtract the value itself
                if(ip < ic)
                    value -= (ip<<1);    // we subtract twice because we added it once already

                // add the number to our total value
                value += ic;
            }

            // update the parent
            p = c;
        }
        if(valid)
            cout << line << " = " << value << endl;
    }
    f.close();
    return 0;
}
