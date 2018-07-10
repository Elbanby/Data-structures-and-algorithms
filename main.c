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
void stack();
patientPtr stackNode(patientPtr stackPtr);
patientPtr push(patientPtr topPtr,char* name,float bloodPressure);
patientPtr pop(patientPtr);

void printStack(patientPtr currentPtr);
void top(patientPtr head);

void queue();
void enqueue(patientPtr *headPtr, patientPtr *tailPtr, char* name,float bloodPressure);
void dequeue(patientPtr *head, patientPtr *tail);
void printQueue( patientPtr currentPtr );
void front(patientPtr head);
void end(patientPtr tail);

int isEmpty(patientPtr ptr);
float getBloodPressure ();
char* getName ();

int main() {

    int dataStructure = 0;

    printf("Choose a data structure");

    while(dataStructure != 5) {
        printf("\n1- Stack\n2- Que\n3- Trees\n4- Hash tables\n5- Exit\nPlease Select an option: ");
        scanf("%d",&dataStructure);

        switch (dataStructure) {
            case 1: puts("Stacks");
                stack();
                break;
            case 2: puts("Queues");
                queue();
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

char* getName (){
    char *name = (char*)malloc(100 * sizeof(char));
    printf("Enter patient name: ");
    scanf("%s",name);
    return name;
}

float getBloodPressure () {
    float bloodPressure;
    printf("Enter blood pressure: ");
    scanf("%f",&bloodPressure);

    return bloodPressure;
}

int isEmpty(patientPtr ptr){
    return (ptr == NULL);
}

void stack() {
    int option = 0;
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
    stackPtr = push(stackPtr,getName(),getBloodPressure());
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

/* check validation
 * //    char* name = topPtr->name;
//    printf("You sure you want to remove patient %s? click 'Y' yes or 'N' for no: ",name);
//    char c ;
//    scanf("%c",&c);

 * */
patientPtr pop(patientPtr topPtr) {

    patientPtr tempPtr;
    tempPtr = topPtr;
    topPtr = topPtr->nextPatient;
    free(tempPtr);

    return topPtr;
}



void printStack(patientPtr currentPtr){
    if(isEmpty(currentPtr)) {
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



void top(patientPtr head) {
    if(head == NULL) {
        printf("Stack is empty, nothing to print\n");
    } else {
        printf("The stack is\n\n------> ");
        printf("|---------------------\n        |ID: %15ld\n        |Name:%15s\n        |Blood pressure:"
               " %9f\n        |__________________________\n        ",head->id,head->name,head->bloodPressure);
    }
}

//--------------------Queues----------------------------------

void queue() {
    patientPtr head = NULL;
    patientPtr tail = NULL;

    int choice = 0;

    while (choice != 6) {
        printf("1- Add to queue\n2- Remove item from que\n3- print queue\n4- Front\n5- End\n6- Exit\nPlease enter choice:");
        scanf("%d",&choice);
        puts("");

        switch (choice) {
            case 1: printf("Add to queue\n");
                    enqueue(&head,&tail,getName(),getBloodPressure());
                    break;
            case 2: dequeue(&head,&tail);
                    break;
            case 3: printQueue(head);
                    break;
            case 4: front(head);
                    break;
            case 5: end(tail);
                    break;
            case 6: choice = 6;
                    break;
            default: printf("Invalid option\n");
                     break;
        }
    }
}

void enqueue(patientPtr *headPtr, patientPtr *tailPtr, char* name,float bloodPressure) {
     static int id = 0;

     patientPtr newPatient = (patientPtr)malloc(sizeof(struct patient));

     if (newPatient != NULL) {

         newPatient->name = name;
         newPatient->bloodPressure = bloodPressure;
         newPatient->nextPatient = NULL;
         newPatient->id = id++;

          //If the que is empty
          if (isEmpty(*headPtr)) {
              *headPtr = newPatient;
           } else {
             (*tailPtr)->nextPatient = newPatient;
           }

            //This will insure that we are always pointing to the last element of the queue
            *tailPtr = newPatient;

      } else {
              printf("Cant allocate memory space. Memory full %s %f" ,name, bloodPressure );
      }
}

void dequeue(patientPtr *head, patientPtr *tail) {

    if (isEmpty(*head)) {
        printf("Queue is empty");
    } else {
        patientPtr tempPtr = *head;

        char* patientName = (*head)->name;

        printf("Deleting Patient: %s\n", patientName);
        *head = (*head)->nextPatient;

        if (isEmpty(*head) ) {
           *tail = NULL;
        }

        free(tempPtr);
    }
}


void printQueue( patientPtr currentPtr ) {

    if (isEmpty(currentPtr)) {
        puts( "\n Queue is empty.\n" );
    }
    else {
        puts( "your queue has:" );

        while ( currentPtr != NULL ) {
            printf("[Name: %s Blood pressure:%f Id: %ld] --->", currentPtr->name, currentPtr->bloodPressure,currentPtr->id );

            currentPtr = currentPtr->nextPatient;
        }
        puts( "NULL\n" );
    }
}

void front(patientPtr head) {
     if (isEmpty(head)) {
        printf("Queue is empty");
     } else {
         printf("[Name: %s Blood pressure:%f Id: %ld] --->", head->name, head->bloodPressure,head->id );
     }
}


void end(patientPtr tail) {
    if (isEmpty(tail)) {
        printf("Queue is empty");
    } else {
        printf("[Name: %s Blood pressure:%f Id: %ld] --->", tail->name, tail->bloodPressure,tail->id );
    }
}
