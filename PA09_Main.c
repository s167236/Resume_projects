// header files
#include <time.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include "HeapUtility.h"

// constants
const int DEFAULT_CAPACITY = 100;

int main( int argc, char *argv[] )
   {
    HeapType *heap = NULL;
    PatientType removedPatient;
    int treeHeight;
    char response; 
    bool verboseFlag = true;

    // title
    printf( "\nPatient Queue/Heap Test\n" );
    printf( "=======================\n" );

    // initialize random generator
    srand( time( NULL ) );

    // Upload data
    heap = getDataFromFile( "inData.txt", DEFAULT_CAPACITY, verboseFlag );

    treeHeight = findHeapTreeHeight( heap->size );

    printf( "       Current Tree Size: %2d\n\n", heap->size );
    printf( "     Current Tree Height: %2d\n\n", treeHeight );

    printf( "     Press any letter to remove items: " );
    scanf( "%c", &response );

    // remove patients
    while( !isEmpty( *heap ) )
       {
        removeItem( &removedPatient, heap );
       }

    // end program

       // clear heap
       heap = clearHeap( heap );

       // display end program
       printf( "\nEnd Program\n" );
 
       // return success
       return 0;

   }

