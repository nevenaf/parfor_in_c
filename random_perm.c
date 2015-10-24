/*
    ** Template parfor loop **
    
    Example: make an array of random permutations
    
    Compilation: gcc -std=c99 -o random_perm random_perm.c
    
    Run: ./run

*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/wait.h>

#define parentRead 0
#define childWrite 1


// Returns a random integer i <= uniform(i,m) <= m 
unsigned uniform(unsigned i,unsigned m)
{
    return (unsigned)(rand()%(m+1-i)+i);
} 

// Returns a random permutation of symbols from 0 to n-1
void random_permutation(int n, int* perm)
{    
    int i,j;
    for(i=0; i<n; i++) perm[i]=i;
    
    for(i=0; i<n; i++)
    {
        j = uniform(0,i);
        perm[i] = perm[j];
        perm[j] = i;
    }
}

// Makes an array of pop random permutations of length n
void make_random_population(int pop, int n, int* population)
{
    int p;
    int* filedesc = malloc(sizeof(int)*2*pop);
    int* pids = malloc(sizeof(int)*pop);
    int child_pid;
    int len;
    for (p=0; p<pop; p++)
    {
        if(pipe(filedesc+2*p) < 0)
        {
            perror("Failed to allocate pipe for child ");
            exit(EXIT_FAILURE);
        }
        child_pid = fork();
        if(child_pid < 0)
        {
            perror("Failed to fork a child ");
            exit(EXIT_FAILURE);
        }
        else if(child_pid==0)
        {
            
            srand(time('\0')*(p+1)); // seed each child with a different rand. num. gen.
            close(filedesc[2*p+parentRead]); // close parent's read pipe
            random_permutation(n, population+p*n); // make random array
            if(write(filedesc[2*p+childWrite], population+p*n, sizeof(int)*n)<0)
            {
                perror("Chiled failed to write result in the pipe");
                exit(EXIT_FAILURE);
            }
            close(filedesc[2*p+childWrite]); // close childs write pipe
            _exit(1); // terminate only this thread
        }
        else // this is parent
        {
            close(filedesc[2*p+childWrite]); // close child's write pipe
            pids[p] = child_pid; // save child's pid
        }
        
    }
    
    for(p = 0; p<pop; p++)  
    {
        //while(0<waitpid(pids[p],NULL,0)); // we are waiting for a child to send a result, so no explcit waiting function is needed
        
        len = read(filedesc[2*p+parentRead], population+n*p, sizeof(int)*n); // get answer from the child
        if(len < 0)
        {
            perror("Parent failed to read random object from the pipe");
            exit(EXIT_FAILURE);
        }
        else if(len ==0 )
        {
            printf("Parent got EOF instead of random object in the pipe \n");
            exit(EXIT_FAILURE);
        }
        
        close(filedesc[2*p+parentRead]); // close parent's read pipe
    }
    free(filedesc);
    free(pids);
}

// Prints an integer array of length n
void print_int_array(int n, int* array)
{
    for(int i=0; i<n-1; i++) printf("%d, ", array[i]);
    printf("%d \n", array[n-1]);
}

int main(int argc, char **argv)
{
    int n = 10;
    int pop = 8;
    
    int* population = malloc(sizeof(int)*n*pop);
    
    make_random_population(pop, n, population);
    for(int p=0; p<pop; p++)
    {
        printf("permutation %d: ", p);
        print_int_array(n, population+p*n);
    }    
    
    free(population);
    return 1;
    
}

