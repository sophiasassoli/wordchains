README for wordchains.c

Sophia Sassoli
ssassoli3@gatech.edu

Compiler used: Xcode
Operating system used: macOS Catalina


PROJECT OVERVIEW

The objective of this project was to implement our learning of shortest path algorithms by solving a “word chain”, in which we progressively transform one specified word to another specified word of the same length through a series of steps where only one letter is 
changed at a time. In addition, each transformation must result in another word.

This process was viewed as a graph problem, in which each word is represented as a node, and an edge exists between two notes of exactly three of the letter of the corresponding words are the same, and in the same position. 

Then a graph algorithm was implemented to determine a shortest path through the graph from a specified source word to a specified destination word, and the path was printed.

The source and destination words are specified as two command-line arguments using integer indices corresponding to the word’s position in the file.

COMPILING & RUNNING THE PROGRAM

navigate to the directory that contains the file.
* make sure provided "wordchains.txt" file is in the same directory.

command to compile the program:
gcc -o wordchains wordchains.c

command to run the program:
./wordchains int1 int2

int1 and int2 should be two integers between 0 and 499 \n
int1 represents the source word, int2 represents the destination word
