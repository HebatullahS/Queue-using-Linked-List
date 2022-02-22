#include <stdio.h>
#include <stdlib.h>
#define Type Process

typedef struct Node Node;

typedef struct{
char Name[20];
int arrival_time;
int burst_time;
}Process;

struct Node{
Type Value;
struct Node* next;
};

typedef struct{
Node* Head;
Node* Tail;
}Queue;

Node* newNode(Type Value)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->Value = Value;
    n->next = NULL;
    return n;
}

void initialize(Queue *s)
{
    s->Head =s->Tail = NULL;

}

int isEmpty(Queue* s)
{
    if((s->Head==NULL)&&(s->Tail==NULL))
        return 1;

    return 0;
}

void enqueue(Queue *s, Type Value)
{
    Node* n = newNode(Value);

    if(isEmpty(s))
    {
        s->Head = n;
        s->Tail = n;
        return;
    }

    s->Tail->next = n;
    s->Tail = n;
}

Node* dequeue(Queue *s)
{
    if(isEmpty(s))
        return NULL;

    Node* n = s->Head;
    s->Head = s->Head->next;

    if(s->Head==NULL)
        s->Tail=NULL;

    return n;
}

Process* readOperations(int* Watch, int* NumberOfOperations)
{
    Process* Operations = (Process*)malloc(sizeof(Process)*70);

    FILE* f = fopen("DS.txt", "r");
    if(f!=NULL){
        char residue[50];
        fscanf(f, "%[^=]=%d\n", residue, &*Watch);
        int i=0;
        while(!feof(f))
        {
            fscanf(f, "%s %d %d\n", Operations[i].Name, &Operations[i].arrival_time, &Operations[i].burst_time);
            *NumberOfOperations = *NumberOfOperations +1;
            i++;
        }
    }
    else
        printf("\Oops ! Error :((");
    return Operations;
}

void RoundRobinScheduling()
{
    Queue RoundRobin;
    initialize(&RoundRobin);
    int n=0;
    int x = 0;
    Process* Operations = readOperations(&x, &n);

    int i=0;
    int j=0;

    for(j=0; j<n; j++)
    {
        if(Operations[j].arrival_time==0)
            enqueue(&RoundRobin, Operations[j]);
    }

    for(i=0; i<x; i++)
    {
        if(isEmpty(&RoundRobin))
        {
            printf("idle (%d-->%d)", i, i+1);
            for(j=0; j<n; j++)
            {
                if(Operations[j].arrival_time==i+1)
                    enqueue(&RoundRobin, Operations[j]);
            }
        }
        else
        {
            Process t = dequeue(&RoundRobin)->Value;
            printf("%s   (%d-->%d)", t.Name, i, i+1);
            t.burst_time--;
            for(j=0; j<n; j++)
            {
                if(Operations[j].arrival_time==i+1)
                    enqueue(&RoundRobin, Operations[j]);
            }

            if(t.burst_time==0)
                printf(" %s aborts", t.Name);
            else
                enqueue(&RoundRobin, t);
        }
        printf("\n");
    }
    printf("stop");
}

int main()
{
    RoundRobinScheduling();
    return 0;
}
