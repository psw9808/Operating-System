////////////////////////////////////////////////////////////////////////
//  Recusive.c
//  This program is designed to show memory layout by repeatedly calling
//  a subroutine and allocating stack data on each call.
//  This uses up lots of stack until eventually no more stack space can
//  be allocated and the program crashes.
//  This stack data is being touched simply because return addresses
//  are being pushed.
//
//  Compile with  gcc recursive.c -o rc.
//  This SHOULD work with 32 or 48 bit logical addresses
////////////////////////////////////////////////////////////////////////
#include  <stdio.h>
#include  <string.h>

#define   ONE_MEG              1048576

//  Prototypes
void     RecursiveRoutine( int );
char     *commas(unsigned long amount);

//  This is a global so the subroutine can see it.
unsigned long    FirstStackLocation;

int    main( int argc, char  *argv[] )
{
    int    TopOfStack;
    int    Counter = 0;

    FirstStackLocation = (unsigned long)(&TopOfStack);
    printf("First location on stack: %s\n", 
            commas( (unsigned long)FirstStackLocation  ) );
    RecursiveRoutine( 0 );
}

///////////////////////////////////////////////////////////////////////////
//  This routine is called recursively.  It does no real work but adds
//  a variable to the stack which uses up space on the stack.
//  It's expected that the program will crash when memory is exhausted.
///////////////////////////////////////////////////////////////////////////
#define    STACK_ALLOC    ONE_MEG/1
void  RecursiveRoutine( int RecursiveDepth )
{
    char    Temp[ STACK_ALLOC ];
    char    StringTop[32];
    char    StringBottom[32];
	char stringmalloc[32];
		
	long       *MemoryPtr;

	MemoryPtr = ( long * ) malloc( ONE_MEG );

		if ( MemoryPtr == 0 ) {
            printf( "The program is ending because we could allocate no more memory.\n");
	   		printf( "Total megabytes allocated = %d\n", RecursiveDepth);
            exit(0);
        }

		if ( ( RecursiveDepth % 1 ) == 0 )    // Print out status every so often
		{
			strcpy(stringmalloc, commas((unsigned long)&(MemoryPtr)));
			printf( "We have allocated %d Megabytes   %s \n", RecursiveDepth ,stringmalloc );
			
		}
    strcpy( StringTop,  commas( (unsigned long)(FirstStackLocation) ) );
    strcpy( StringBottom, commas( (unsigned long)&(Temp[STACK_ALLOC]) ) );
    printf("Iteration = %3d:  Stack Top/Bottom/Bytes: %s  %s  %d\n", 
             RecursiveDepth, StringTop, StringBottom,
             FirstStackLocation - (unsigned long)&(Temp[STACK_ALLOC])  );
    RecursiveDepth++;
    RecursiveRoutine( RecursiveDepth );
}

///////////////////////////////////////////////////////////////////////////
//  The following routines are for formatting only and aren't needed for
//  an understanding of the memory manipulations done above.
///////////////////////////////////////////////////////////////////////////
#define BASE 16
#define GROUP 4
// This routine converts an unsigned integer into a string with commas.
// You may need to adjust the base and the number of digits between
// commas as given by BASE and GROUP.
// Need space to hold the digits of an unsigned int,
// intervening commas and a null byte. It depends on
// BASE and GROUP above (but logarithmically, not
// as a constant. so we must define it manually here)
///////////////////////////////////////////////////////////////////////////
#define MAXTEXT 25 

int prepend(char *, unsigned, char *);
int preprintf(char *, unsigned, char *, ...);

char *commas(unsigned long amount)
    {
    short i;
    short offset = MAXTEXT-1;   /* where the string "starts"  */
    short place;                /* the power of BASE for      */
                                /* current digit              */
    static char text[MAXTEXT];

    for ( i = 0; i < MAXTEXT; i++ )
        text[i] = '\0';
					     
   /* Push digits right-to-left with commas */
   for (place = 0; amount > 0; ++place)
      {
      if (place % GROUP == 0 && place > 0)
         offset = prepend(text,offset,",");
      offset = preprintf(text,offset,"%X",amount % BASE);
      amount /= BASE;
    }
    return (offset >= 0) ? text + offset : NULL;
}
    /* preprint.c: Functions to prepend strings */
    
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
    
int prepend(char *buf, unsigned offset, char *new_str)
    {
    int new_len = strlen(new_str);
    int new_start = offset - new_len;
    /* Push a string onto the front of another */
    if (new_start >= 0)
        memcpy(buf+new_start,new_str,new_len);
    
    /* Return new start position (negative if underflowed) */
    return new_start;
}
    
int preprintf(char *buf, unsigned offset, char *format, ...)
    {
    int pos = offset;
    char *temp = malloc(BUFSIZ);
    
    /* Format, then push */
    if (temp)
        {
        va_list args;
        
        va_start(args,format);
        vsprintf(temp,format,args);
        pos = prepend(buf,offset,temp);
        va_end(args);
        free(temp);
    }
    return pos;
}

