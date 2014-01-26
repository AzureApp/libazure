//
//  new_main.cpp
//  azured
//
//  Created by Callum Taylor on 04/01/2014.
//
//

#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

#define kRED  "\033[1;31m"
#define kGRN  "\033[1;32m"
#define kYEL  "\033[1;33m"
#define kBLU  "\033[1;34m"
#define kMAG  "\033[1;35m"
#define kCYN  "\033[1;36m"

#define kCLR "\033[1;0m"

#define AZGreet \
"\
++++++++++++++++++++++\n\
++Azure Alpha (v0.5)++\n\
++[--help for usage]++\n\
++++++++++++++++++++++\n"

int main(int argc, char **argv)
{
    if(argc > 1)
        if(!strcmp(argv[1], "--help"))
        {
            //PrintHelp
        }
        else if(!strcmp(argv[1], "-list-processes"))
        {
            //print all running processes
        }
        else if(!strcmp(argv[1], "-attach"))
        {
            //attach to argv[2]
        }
        else if(!strcmp(argv[1], "-debug"))
        {
            //debug mode on
        }
        else
        {
            //print help
        }
    cout << kBLU << AZGreet << kCLR;
    //run menu
    return 0;
}