#include "HeapUtility.h"
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
Dependencies: getRandBetween, malloc w/sizeof, privateIsInArray, free
*/
int accessPriority( PriorityCode code, int initialCapacity )
{
      static int *array = NULL;
      static int size = 0;
      int randNum;
      int returnVal = NON_VALID_PRIORITY;

      if(code == INITIALIZE_PRIORITY_ENGINE)
      {
            //create array using 2 times initialCapacity
            if(array == NULL)
            {
                  array = malloc(initialCapacity * 2 * sizeof(PatientType));
                  size = 0;
                  
            }
      }
      else if(code == GET_PRIORITY)
      {
            //check for valid array
            if(array != NULL)
            {
                  //start loop
                  do
                  {
                        randNum = privateGetRandBetween(1, (initialCapacity * 2));
                  } 
                  while (privateIsInArray(array, randNum, initialCapacity));
                  

                  //set value into array
                  array[size] = randNum;

                  //increment size
                  size = size + 1;

                  //set returnVal to return value
                  returnVal = randNum;
            }


      }
      else if( code == CLEAR_PRIORITY_ENGINE)
      {
            if(array != NULL)
            {
                  //deallocate array
                  free(array);

                  //set array to NULL
                  array = NULL;
                  
                  //set size to 0
                  size = 0;


            }
      }

      return returnVal;
}

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
void addHeapItem( HeapType *heap, const char *nameSet )
{
      if(heap->size < heap->capacity)
      {
            setPatientFromData(&heap->array[heap->size], nameSet,
                                           heap->array[heap->size].priority);
            accessPriority(heap->array[heap->size].priority, heap->capacity);
            heap->size = heap->size + 1;
            privateBubbleUp(heap, heap->size);
      }

}

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
HeapType *clearHeap( HeapType *heap )
{
      if(heap != NULL)
      {
            free(heap->array);
            heap->size = 0;
            heap->capacity = 0;
            heap->displayFlag = false;
            free(heap);
            
      }
      return NULL;
}

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
int findHeapTreeHeight( int heapSize )
{

      if(heapSize > 1)
      {
            return findHeapTreeHeight(heapSize / 2) + 1;
      }

      return 0;

}

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
                                            int initialCapacity, bool verbose )
{
    HeapType *getHeap = NULL;
    char patientStr[STD_STR_LEN];
    char garbage[STD_STR_LEN];
    int count = 0;


    if(openInputFile(fileName)) 
    {
      if(verbose == true)
      {
            printf("\nBegin Loading Data From File . . .\n");
      }
      getHeap = initializeHeap(initialCapacity);

      readStringToDelimiterFromFile(SEMICOLON, patientStr);
      while (!checkForEndOfInputFile()) 
      {
            readStringToLineEndFromFile(garbage);
            addHeapItem(getHeap, patientStr);
            count = count + 1;
            if(verbose == true)
            {
                  printf("%5d) Patient Name: %s", count, patientStr);
            }
            readStringToDelimiterFromFile(SEMICOLON, patientStr);
            
      }
    }

    closeInputFile();
    printf("                                  . . . End Loading Data From File\n\n");
    
    return getHeap;
}


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
HeapType *initializeHeap( int initialCapacity )
{
      HeapType *newHeap = (HeapType *)malloc(sizeof(HeapType));

      newHeap->capacity = initialCapacity;

      newHeap->array = (PatientType *)malloc(initialCapacity * sizeof(PatientType));

      newHeap->size = 0;

      newHeap->displayFlag = false;

      accessPriority(INITIALIZE_PRIORITY_ENGINE ,initialCapacity);

      return newHeap;
}

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
bool isEmpty( const HeapType heap )
{
      return heap == NULL;
}

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
void privateBubbleUp( HeapType *heap, int currentIndex )
{
      int parentIndex = (currentIndex - 1)/2;
      PatientType parent;
      PatientType child;
      /* char childDisp[MAX_STR_LEN];
      char parentDisp[MAX_STR_LEN];*/

      if(currentIndex > 0)
      {
            setPatientFromStruct(&child, heap->array[currentIndex]);
            setPatientFromStruct(&parent, heap->array[parentIndex]);
            if(comparePriorities(child, parent) > 0)
            {
                  /*if(heap->displayFlag == true)
                  {
                        setPatientToString(childDisp, 
                                                     heap->array[currentIndex]);
                        setPatientToString(parentDisp, 
                                                     heap->array[parentIndex]);
                        printf("   - Bubble up:\n");
                        printf("     - Swapping parent: %s\n", parentDisp); 
                        printf("   with child: %s\n", childDisp);
                  }*/
                  copyPatient(heap->array[parentIndex], child);
                  copyPatient(heap->array[currentIndex], parent);
                  privateBubbleUp(heap, parentIndex);
            }
      }
}

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
void privateTrickleDown( HeapType *heap, int currentIndex )
{
      int leftChildIndex = currentIndex * 2 + 1;
      int rightChildIndex = currentIndex * 2 + 2;
      PatientType *leftChild;
      PatientType *parent;
      PatientType *rightChild;
      /*char childDisp[MAX_STR_LEN];
      char parentDisp[MAX_STR_LEN];*/

      setPatientFromStruct(parent, heap->array[currentIndex]);

      // check for left child available
      if(leftChildIndex < heap->size)
      {
            // check for right child exists
            // and right child > left child
            // and right child > parent
            if(rightChildIndex < heap->size && 
                   comparePriorities(heap->array[currentIndex],
                              heap->array[rightChildIndex]) < 0 && 
                              comparePriorities(heap->array[rightChildIndex]
                                           , heap->array[leftChildIndex]) > 0)
            {
                  /*if(heap->displayFlag == true)
                  {
                   setPatientToString(childDisp, heap->array[rightChildIndex]);
                   setPatientToString(parentDisp, heap->array[currentIndex]);
                   printf("   - Trickle down swap:\n");
                   printf("     - moving down parent: %s\n", parentDisp);
                   printf("      - moving up Right child:%s\n", childDisp);
                  }*/
                  setPatientFromStruct(rightChild,
                                                 heap->array[rightChildIndex]);
                  // swap right/parent
                  copyPatient(&heap->array[currentIndex], *rightChild);
                  copyPatient(&heap->array[rightChildIndex], *parent);
                  // recurse to the right
                  privateTrickleDown(heap, rightChildIndex);
            }
      }
      // otherwise, check if left child greater than parent
      else if(comparePriorities(heap->array[leftChildIndex],
                                                heap->array[currentIndex]) > 0)
      {
            /*if(heap->displayFlag == true)
            {
             setPatientToString(childDisp, heap->array[rightChildIndex]);
             setPatientToString(parentDisp, heap->array[currentIndex]);
             printf("   - Trickle down swap:\n");
             printf("     - moving down parent: %s\n", parentDisp);
             printf("      - moving up Left child:%s\n", childDisp);
            }*/
            setPatientFromStruct(leftChild, heap->array[leftChildIndex]);
            // swap left/parent
            copyPatient(&heap->array[currentIndex], *leftChild);
            copyPatient(&heap->array[leftChildIndex], *parent);

            // recurse to the left 
            privateTrickleDown(heap, leftChildIndex); 
      }
      // end of check for left child

}

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
void removeItem( PatientType *removed, HeapType *heap )
{
      char removeChar[MAX_STR_LEN];
      //check for not empty
      if(heap != NULL)
      {
            setPatientToString(removeChar, heap->array[0]);
            printf("Removing patient: %s\n", removeChar);
            //remove item at index 0
            setPatientFromStruct(removed, heap->array[0]);
            //set item at index 0 to item at index size - 1
            setPatientFromStruct(&heap->array[0], heap->array[heap->size - 1]);
            //decrement the size
            heap->size = heap->size - 1;
            //call trickleDown
            privateTrickleDown(heap, 0);
      }
      //assume empty
      //set return value to empty
      

}

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
void setDisplayFlag( HeapType *heap, bool flagSet )
{
      heap->displayFlag = flagSet;
}

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
void showArray( HeapType heap )
{
      int index;
      char patientStr[STD_STR_LEN];

      for(index = 0; index < heap.size - 1; index ++)
      {
            setPatientToString(patientStr, heap.array[index]);

            printf("%s\n", patientStr);
      }

}