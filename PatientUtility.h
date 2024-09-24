#ifndef PATIENT_UTILITY_H
#define PATIENT_UTILITY_H

// header files
#include <time.h>
#include <stdio.h>
#include "GeneralUtility.h"
#include "StandardConstants.h"

// constants

// data structure
typedef struct PatientStruct
   {
    char patientName[ STD_STR_LEN ];

    int priority;
   } PatientType;

// prototypes

/*
Name: comparePriorities
Process: compares priority of two patients in heap,
         if first patient has higher priority than second patient, 
         returns positive value, 
         if first patient has lower priority than second patient,
         returns negative value, otherwise returns zero
Function input/parameters: two patients (const PatientType)
Function output/parameters: none
Function output/returned: integer result as specified (int)
Device input/---: none
Device output/---: none
Dependencies: none
*/
int comparePriorities( const PatientType onePatient, 
                                               const PatientType otherPatient );
/*
Name: copyPatient
Process: copies patient data from source to destination
Function input/parameters: source patient data (const PatientType)
Function output/parameters: pointer to updated destination data (PatientType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: privateCopyString
*/
void copyPatient( PatientType *destPatient, const PatientType sourcePatient );

/*
Name: setPatientToString
Process: sets patient data into a string
Function input/parameters: patient type data (const PatientType)
Function output/parameters: updated patient data as string (char *) 
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: sprintf
*/
void setPatientToString( char *patientStr, const PatientType patientNode );

/*
Name: setPatientFromData
Process: sets patient data into a patient data node
Function input/parameters: patient name (const char *), patient priority (int)
Function output/parameters: updated patient data (PatientType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: privateCopyString
*/
void setPatientFromData( PatientType *patientNode, 
                                         const char *nameSet, int prioritySet );

/*
Name: setPatientFromStruct
Process: sets patient data from source struct into destination struct
Function input/parameters: patient type data as struct (const PatientType)
Function output/parameters: updated patient data as struct (PatientType *) 
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: setPatientFromData
*/
void setPatientFromStruct( PatientType *patientNode, const PatientType source );


#endif   // PATIENT_UTILITY_H