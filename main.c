#include <stdio.h>
#include <stdlib.h>

//Create structures
struct patient {
    char *name;
    long int id;
    float bloodPressure;
    struct patient *nextPatient;
};

//Renaming the struct and struct pointer
typedef struct patient Patient;
typedef struct patient* patientPtr;

//Prototypes
patientPtr push(patientPtr topPtr,char* name,float bloodPressure);
patientPtr pop(patientPtr head);
void stack();
void printStack(patientPtr currentPtr);
patientPtr stackNode(patientPtr stackPtr);
void top(patientPtr head);
int isEmpty(patientPtr ptr);

int main() {

    int dataStructure;

    printf("Choose a data structure");

    while(dataStructure != 5) {
        printf("\n1- Stack\n2- Que\n3- Trees\n4- Hash tables\n5- Exit\nPlease Select an option: ");
        scanf("%d",&dataStructure);

        switch (dataStructure) {
            case 1: puts("Stacks");
                    stack();
                break;
            case 2: puts("Ques");
                    break;
            case 3: puts("Trees");
                    break;
            case 4: puts("Hash Tables");
                    break;
            case 5: puts("Exit");
                    exit(0);
            default: puts("Invalid Choice");
                     break;
        }
    }

    return 0;
}

void stack() {
    int option;
    patientPtr stackPointer = NULL;

    while(option != 5) {
        printf("\n1- push to the stack\n2- pop from the stack\n3- print stack\n4- top\n5- Exit Stack data structure\nSelect an option: ");
        scanf("%d",&option);
        switch (option) {
            case 1: puts("push\n");
                    stackPointer = stackNode(stackPointer);
                    break;
            case 2: puts("pop\n");
                    if(!isEmpty(stackPointer)) {
                        stackPointer = pop(stackPointer);
                    }
                    break;
            case 3: puts("print\n");
                    printStack(stackPointer);
                    break;
            case 4: puts("top");
                    top(stackPointer);
                    break;
            case 5: puts("exit");
                    option = 5;
                    break;
            default: puts("Invalid Choice");
                    break;
        }
    }



}

patientPtr stackNode(patientPtr stackPtr) {
    char *name = (char*)malloc(100 * sizeof(char));
    float bloodPressure;

    printf("Enter patient name: ");
    scanf("%s",name);

    printf("Enter blood pressure: ");
    scanf("%f",&bloodPressure);

    stackPtr = push(stackPtr,name,bloodPressure);

    return stackPtr;
}


patientPtr push(patientPtr topPtr,char* name,float bloodPressure) {
    static int id = 0;

    //Allocate a space on the heap for the struct
    patientPtr newPtr = (patientPtr) malloc(sizeof(Patient));

    if (newPtr != NULL) {
        newPtr->name = name;
        newPtr->bloodPressure = bloodPressure;
        newPtr->id = id++;
        newPtr->nextPatient = topPtr;
        topPtr = newPtr;
    } else {
        printf("Can't allocate memory for %s %f. Memory Full\n",name,bloodPressure);
    }

    return topPtr;
}


patientPtr pop(patientPtr topPtr) {


//    char* name = topPtr->name;
//    printf("You sure you want to remove patient %s? click 'Y' yes or 'N' for no: ",name);
//    char c ;
//    scanf("%c",&c);

        patientPtr tempPtr;
        tempPtr = topPtr;
        topPtr = topPtr->nextPatient;
        free(tempPtr);

    return topPtr;
}



void printStack(patientPtr currentPtr){

    if(currentPtr == NULL) {
        printf("Stack is empty, nothing to print\n");
    } else {
        printf("The stack is\n\n------> ");

        while(currentPtr != NULL) {
            printf("|---------------------\n        |ID: %15ld\n        |Name:%15s\n        |Blood pressure:"
                   " %9f\n        |__________________________\n        ",currentPtr->id,currentPtr->name,currentPtr->bloodPressure);
            currentPtr = currentPtr->nextPatient;

        }
    }
}

int isEmpty(patientPtr ptr){
    if(ptr == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void top(patientPtr head) {
    if(head == NULL) {
        printf("Stack is empty, nothing to print\n");
    } else {
        printf("The stack is\n\n------> ");
            printf("|---------------------\n        |ID: %15ld\n        |Name:%15s\n        |Blood pressure:"
                   " %9f\n        |__________________________\n        ",head->id,head->name,head->bloodPressure);
    }
}