Using these libraries:
stdio.h
memory.h
stdlib.h
limits.h
string.h
regex.h
openssl/sha.h (can install with: sudo apt-get install libssl-dev)

Compilation uses linked libraries 'ssl' and 'crypto'
Compile instructions: gcc WOMM.c -pedantic -Wall -Wextra -Werror -lssl -lcrypto