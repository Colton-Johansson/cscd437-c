Team: Worked on my machine...
Colton Johansson
Joe Carlson
Brandtly Strobeck

Using these libraries:
stdio.h
memory.h
stdlib.h
limits.h
string.h
regex.h
openssl/sha.h (can install with: sudo apt-get install libssl-dev)

Input files must be put in the folder: input_files, which resides in the same directory as the C executable.

Programmed in: Ubuntu 18.04.1 LTS
OpenSSL Version: OpenSSL 1.1.0g
gcc Version: 7.3.0

Compilation uses linked libraries 'ssl' and 'crypto'
Compile instructions: gcc -pedantic -Wall -Wextra -Werror WOMM.c -lssl -lcrypto
Run: ./a.out