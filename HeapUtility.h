#ifndef HEAP_UTILITY_H
#define HEAP_UTILITY_H

#include "PatientUtility.h"
#include <stdlib.h>
#include "File_Input_Utility.h"
#include <stdbool.h>

// constants

// data structures
typedef struct HeapStruct
   {
    PatientType *array;    

    int size, capacity;

    bool displayFlag;
   } HeapType;

typedef enum { CLEAR_PRIORITY_ENGINE = 101,
    GET_PRIORITY, INITIALIZE_PRIORITY_ENGINE, NON_VALID_PRIORITY } PriorityCode;

// function prototypes

/*
Name: accessPriority 
Process: static initial array pointer provided and set to NULL,
         and static initial size set to zero
         Priority Codes:
         INITIALIZE_PRIORITY_ENGINE - if array has not 
                                      been previously initialized,
                                      sets up priority generating system
                                      with possible values up 
                                      to twice as much as the given
                                      initial capacity provided,
                                      returns NON_VALID_PRIORITY
         GET_PRIORITY - generates a unique value between 1 and twice the
                        initial given capacity, returns value
         CLEAR_PRIORITY_ENGINE - if array has been initialized,
                                 deallocates dynamic memory created
                                 for the function operation,
                                 resets static array pointer to NULL,
                                 and size to zero,
                                 returns NON_VALID_PRIORITY
Function input/parameters: control code as specified (PriorityCode),
                           given initial capacity (int)
Function output/parameters: none
Function output/returned: value as specified (int)
Device input/---: none
Device output/---: none
Dependencies: rand, malloc w/sizeof, isInArray, free
*/
int accessPriority( PriorityCode code, int initialCapacity );

/*
Name: addHeapItem
Process: adds item to heap with unique priority,
         reports action, updates size,
         calls bubble up to reset heap
Function input/parameters: heap data (HeapType *), patient name (char *)
Function output/parameters: updated heap data (HeapType *)
Function output/returned: none
Device input/---: none
Device output/monitor: patient addition action displayed 
Dependencies: setPatientFromData, printf, accessPriority,
              bubbleUpArrayHeap (recursively)
*/
void addHeapItem( HeapType *heap, const char *nameSet );

/*
Name: clearHeap
Process: frees heap array, sets all other data members appropriately,
         clears priority generating function
Function input/parameters: heap data (HeapType *)
Function output/parameters: none
Function output/returned: pointer to cleared heap type (NULL)
Device input/---: none
Device output/---: none
Dependencies: free, accessPriority
*/
HeapType *clearHeap( HeapType *heap );

/*
Name: findHeapTreeHeight
Process: recursively calculates the height of the virtual tree used in the heap
Function input/parameters: number of items (int)
Function output/parameters: none
Function output/returned: height of virtual tree (int)
Device input/---: none
Device output/---: none
Dependencies: findHeapTreeHeight (recursively)
*/
int findHeapTreeHeight( int heapSize );

/*
Name: getDataFromFile
Process: initializes heap,
         uploads data from file with unknown number of data sets,
         if heap display flag set, 
         shows upload operation and sets heap display flag,
         returns true if data found and uploaded, false otherwise,
         priority is acquired and applied to each data item as it is input
Function input/parameters: file name (const char *),
                           initial capacity (int),
                           display flag (bool)
Function output/parameters: none
Function output/returned: pointer to newly created heap (HeapType *),
                          or NULL if upload failed
Device input/hard drive: data from HD
Device output/monitor: if display flag set, displays uploaded values
Dependencies: openInputFile, readStringToDelimiterFromFile, 
              readStringToLineEndFromFile, initializeHeap,
              checkForEndOfInputFile, readStringToLineEndFromFile, 
              addHeapItem, printf, closeInputFile
*/
HeapType *getDataFromFile( const char *fileName, 
                                            int initialCapacity, bool verbose );

/*
Name: initializeHeap
Process: initializes heap, creates heap array from given capacity,
         sets other heap members appropriately, 
         initializes the priority generating engine,
         display flag is initially set to false
Function input/parameters: initial capacity (int)
Function output/parameters: none
Function output/returned: pointer to created heap (HeapType *)
Device input/---: none
Device output/---: none
Dependencies: malloc, sizeof, accessPriority
*/
HeapType *initializeHeap( int initialCapacity );

/*
Name: isEmpty
Process: reports if heap is empty
Function input/parameters: heap data (const HeapType)
Function output/parameters: none
Function output/returned: Boolean result of test (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isEmpty( const HeapType heap );

/*
Name: privateBubbleUp
Process: recursively rebalances heap after new data is added for max heap,
         displays bubble up actions if heap display flag set
Function input/parameters: heap data (HeapType *), current index (int)
Function output/parameters: updated heap data (HeapType *)
Function output/returned: none
Device input/---: none
Device output/monitor: bubble up operations displayed as specified
Dependencies: setPatientFromStruct, comparePriority, getPatientInfo,
              bubbleUpArrayHeap (recursively), 
              other appropriate functions acceptable
Note: 1) Swapping operation may not exceed two lines
      2) Comparison process may not use array elements
*/
void privateBubbleUp( HeapType *heap, int currentIndex );

/*
Name: privateTrickleDown
Process: recursively rebalances heap after data removal from max heap
         displays trickle down actions to screen if display flag set
Function input/parameters: heap data (HeapType *), current index (int),
                           display flag (bool)
Function output/parameters: updated heap data (HeapType *)
Function output/returned: none
Device input/---: none
Device output/monitor: trickle down operations displayed as specified
Dependencies: setPatientFromStruct, copyPatient, comparePriorities, 
              getPatientInfo, printf, setPatientToString,
              trickleDownArrayHeap (recursively), others acceptable
Note: May not be more than two sets of swap actions, and, 
      May not be more than two recursion calls in code
      --- one to the left child
      --- one to the right child
comparePriorities calls may use array elements as needed
*/
void privateTrickleDown( HeapType *heap, int currentIndex );

/*
Name: removeItem
Process: removes item from heap, reports removal action, adjusts data, 
         displays removal action, updates size, calls trickle down to reset heap
Function input/parameters: heap data (HeapType *)
Function output/parameters: updated heap data (HeapType *),
                            patient data removed (PatientType *)
Function output/returned: none
Device input/---: none
Device output/monitor: removal action displayed as specified
Dependencies: setPatientFromStruct, getPatientInfo, printf,
              trickleDownArrayHeap, others acceptable
*/
void removeItem( PatientType *removed, HeapType *heap );

/*
Name: setDisplayFlag
Process: sets Boolean flag to drive bubble up, trickle down displays
Function input/parameters: heap data (HeapType *), flag (bool)
Function output/parameters: updated heap data (HeapType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void setDisplayFlag( HeapType *heap, bool flagSet );

/*
Name: showArray
Process: displays array as is, from lowest index to highest
Function input/parameters: heap data (HeapType)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: array displayed as specified
Dependencies: getPatientInfo, printf
*/
void showArray( HeapType heap );


#endif   // HEAP_UTILITY_H

