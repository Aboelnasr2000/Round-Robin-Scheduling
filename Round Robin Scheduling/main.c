#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 */

typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;
/*
 *
 */
typedef struct Node
{
    Process data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
    Node *front ;
    Node *rear  ;
    /* TODO: ADD YOUR CODE HERE */
} Queue;
/*
 *
 */
Queue* init()
{
    Queue *q =malloc(sizeof(Queue));
    q->front=q->rear=NULL;
    return q;
    /* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
int isEmpty(Queue *q)
{
    if(q->front==NULL)
        return 1;
    /* TODO: ADD YOUR CODE HERE */
    return 0;
}
/*
 *
 */
Process dequeue(Queue *q)
{
    Process x;
    if(q->front)
    {
        Node *temp =q->front;
        x =temp->data;
        q->front=q->front->next;
        free(temp);
        if(q->front==NULL)
            q->rear=NULL;
        return x;
    }
    return x ;
    /* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
Node *newNode(Process x)
{
    Node *a = malloc(sizeof(Queue));
    a->data=x;
    a->next=NULL;
    return a;
}


void enqueue(Queue *q, Process val)
{
    Node *n=newNode(val);
    if(q->front==NULL)
        q->front=q->rear=n;
    else
    {
        q->rear->next=n;
        q->rear=n;
    }
    /* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
void destroy(Queue *q)
{
    while (isEmpty(q))
    {
        dequeue(q);
    }
    /* TODO: ADD YOUR CODE HERE */
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    Queue *q = init();
    Process arr[100]= {};
    int count=0;
    int i ;
    int j ;
    FILE *fp;
    fp=fopen(filename,"r");
    int quantumTime;
    char garbage[10];
    fscanf(fp,"%s %s %s %s %d",garbage,garbage,garbage,garbage,&quantumTime);
    if (fp !=NULL)
        while (!feof(fp))
        {
            arr[count].name=malloc(4);
            fscanf(fp,"%s ",arr[count].name);
            fscanf(fp,"%d ",&(arr[count].starting_time));
            fscanf(fp,"%d\n",&(arr[count].remaining_time));
            count ++;
        }

    for (i=0 ; i<quantumTime ; i++)
    {
        for (j=0 ; j<count ;  j++)
        {
            if(arr[j].starting_time == i)
            {
                enqueue(q,arr[j]);
            }
        }
        if(!isEmpty(q))
        {
            Process nasr;
            nasr=dequeue(q);
            printf("%s (%d-->%d)",nasr.name,i,i+1);
            (nasr.remaining_time)--;
            if(nasr.remaining_time!=0)
                enqueue(q,nasr);
            if(nasr.remaining_time==0)
                printf(" %s aborts",nasr.name);
            printf("\n");
        }
        else{
            printf("Idle (%d--%d)\n",i,i+1);
        }
    }
    printf("Stop\n");
}


int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}
