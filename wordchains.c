# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define infinity 9999          // value if path does not exist
# define MAX 500        
# define TEMP 0                 // temporary value for function implementation
# define PERM 1                 // temporary value for function implementation
# define NIL -1                 // temporary value for function implementation

int n = 500;                    // num vertices
int prev[MAX];                  // array to store previous node
int pathlength[MAX];            // array to store path length between nodes
int status[MAX];                // array to store whether a word has been visited for path algorithm
int adjmatrix[MAX][MAX];        // graph representation of words
char words[500][6];             // array to store words from file


/* function to check if an edge exists between two words, 
   i.e. if two words have exactly 3 letters in common 
   returns edge value (0 or 1) for adjacency matrix */
int check_edge(char word1[], char word2[]) {
    int sameletters = 0;
    for (int i = 0; i < 4; i++) {
        if (word1[i] == word2[i]) {
            sameletters += 1;
        } 
    }

    if (sameletters == 3) {
        return 1;
    } else {
        return 0;
    }
}

/* function to find path between source word and destination word;
   outputs shortest distance and path taken */
void findpath(int source, int v) {
    int i, u;
    int path[MAX];              // stores the shortest path found (each node that is visited)
    int shortestdist = 0;       // computes the length of the shortest path
    int count = 0;              // number of nodes visited in the path

    /* loop to store the path into an array */
    while(v != source) {
        count++;
        path[count] = v;
        u = prev[v];
        shortestdist += adjmatrix[u][v];
        v = u;
    }
    count++;
    path[count] = source;

    /* output to tell user path and length of path */
    printf("Shortest path is: ");
    for(i = count; i >= 1; i--) {
        printf("%s ", words[path[i]]);
    }
    printf("\nShortest distance is: %d\n", shortestdist);
}


/* used for intermittent steps in path algorithm;
   returns temporary nodes representing the minimum value of the path length;
   returns NIL if there are no temporary vertices left to visit or if path length is infinity */
int min_temp() {
    int i;
    int min = infinity;
    int k = NIL;
    for(i = 0; i < n; i++) {
        if(status[i] == TEMP && pathlength[i] < min) {
            min = pathlength[i];
            k = i;
        }
    }
    return k;
}


/* implements dijkstra's algorithm to compute shortest path between nodes */
void pathalgorithm(int source) {
    int i, current;

    /* temporary values for nodes to keep track during algorithm computation */
    for(i = 0; i < n; i++) {
        prev[i] = NIL;
        pathlength[i] = infinity;
        status[i] = TEMP;
    }
    pathlength[source] = 0;             // path length of source vertex = 0

    while(1) {
        current = min_temp();           // finds temp node with shortest path length

        if(current == NIL) {
            return;
        }

        status[current] = PERM;         // node has been visited

        /* checks for adjacent nodes that have not been visited;
           updates path and path length, moves to next node to check */
        for(i = 0; i < n; i++) {
            if(adjmatrix[current][i] != 0 && status[i] == TEMP) {
                if(pathlength[current] + adjmatrix[current][i] < pathlength[i]) {
                    prev[i] = current;
                    pathlength[i] = pathlength[current] + adjmatrix[current][i];
                }
            }
        }
    }
}




int main(int argc, char *argv[]) {
    
    FILE *txtfile;
    txtfile = fopen("wordlist.txt", "r");

    char tempword[6];

    /* read in words from file, store into an array */
    int i = 0;
    while (i < 500) {
        fscanf(txtfile, "%s", tempword); 
        strcpy(words[i], tempword);
        i++;
    }

    fclose(txtfile);

    /* initialize values for adjency matrix --> create edges */
    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            adjmatrix[i][j] = check_edge(words[i], words[j]);
        }
    }

    /* create variables to hold command line arguments; source node and destination node */
    int s = atoi(argv[1]);
    int d = atoi(argv[2]);

    /* finds shortest path from source node */
    pathalgorithm(s);
    
    /* checks values of nodes and returns appropriate message or information */
    int c = 1;
    while(c == 1) {
        if(d < 0 || d >= n) {
            printf("Please try again. The destination word does not exist.\n");
            c = 0;
        } else if(d == s) {
            printf("The source and destination words are the same.\n");
            c = 0;
        } else if(pathlength[d] == infinity) {
            printf("There is no path that exists from source word to destination word.\n");
            c = 0;
        } else {
            findpath(s, d);
            c = 0;
        }
    }


    return 0;
}