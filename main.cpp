#include <libgen.h> //for basename
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>

#include "defs.h"

using namespace std; 

int f_flags;
string progname;

void usage(ostream &fpo, int status) {
    fpo << "\
usage: " << progname << " [options] [FILE...]\n\
\n\
Options:\n\
  -d  show me some debugging messages\n\
  -v  be verbose\n\
  -q  be quiet\n\
  -h  print this friendly message\n\
";
    exit(status);
}

void setprogname(char* str) {
    progname = string(basename(str));
}

void errmsg(const char* str) {
    string message = progname + ": " + string(str);
    perror(message.c_str());
}

int main(int argc, char *argv[]) {
    int opt = 0;
    f_flags = 0;
    extern int optind;

    setprogname(argv[0]);
    
    while ((opt = getopt(argc, argv, "dqvh")) != -1) {
        switch (opt) {
        case 'd':
            f_flags |= F_DEBUG;
            break;
        case 'v':
            f_flags |= F_VERBOSE;
            break;
        case 'q':
            f_flags |= F_QUIET;
            break;
        case 'h':
            usage(cout, 0);
        default: /* '?' */
            fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    argc -= optind;
    argv += optind;

    
    if (argc == 0) {
        if (DEBUG)
            cerr << "no file arguments, reading from standard in" << endl;
        // do something with std::cin?
    }

    // do something with each file given as argument
    for(; argc > 0; argc -= 1, argv +=1) {
        if (DEBUG)
            fprintf(stderr, "file argument: %s\n", *argv);
        ifstream ifs(*argv, ifstream::in);
        if (!ifs.good()) {
            errmsg(*argv);
            //can we continue on an error, or should be break out of
            //the loop?
        } else {
            // Do something with ifs
            // and don't forget to close it!
            ifs.close();
        }
    } 

    exit(EXIT_SUCCESS);
}
