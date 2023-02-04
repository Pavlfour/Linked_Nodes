#include <stdio.h>
#include <stdlib.h>

struct node{
    int phone;
    int insideCounter; //This is used to count the same values
    int currentHour; //This for printing usage
    struct node *ptr;
};

int main()
{
    struct node *head=NULL;
    struct node *assist=NULL;
    struct node *assistCounter=NULL;

    int tempor;
    int counter=0;
    char check=1;
    int userInput;

    while(check){
        printf("Give me a positive integral between 1-10000\n");
        scanf("%d",&userInput);
        if((userInput>=1) && (userInput<=10000))
        {
            counter+=1;
            if(!head) //initialize the first node
            {
                head = (struct node *)malloc(sizeof(struct node));
                if(!head){printf("Error allocating memory");exit(1);}
                head->phone=userInput;
                head->insideCounter=1;
                head->currentHour=0;
                head->ptr=NULL;
            }
            else
            {
                    assist=head;
                    while((assist->ptr)!=NULL)
                        assist=assist->ptr;
                    assist->ptr=(struct node *)malloc(sizeof(struct node));
                    if((!assist->ptr)){printf("Error allocating memory");exit(1);}
                    assist->ptr->phone=userInput;
                    assist->ptr->insideCounter=1;
                    assist->ptr->currentHour=0;
                    assist->ptr->ptr=NULL;
            }
        }
        else
        {
            if(!head)
            {
                printf("No Call was made!");
                exit(1);
            }
            else {check=0;} //exiting the loop if out of boundaries
        }
    }

    //sorting the nodes in increasing order
    assist=head;
    assistCounter=assist;
    for(int i=0;i<counter-1;i++)
    {
        for(int j=0;j<counter-i-1;j++)
        {
            assistCounter=assistCounter->ptr;
            if((assist->phone)>(assistCounter->phone))
            {
                tempor = assist->phone;
                assist->phone=assistCounter->phone;
                assistCounter->phone=tempor;
            }
        }
        assist=assist->ptr;
        assistCounter=assist;
    }

    //changing values in phone variables in each node
    for(int i=0;i<counter;i++)
    {
        assist=head;
        for(int j=0;j<counter-i-1;j++)
        {
            assist=assist->ptr;
        }
        assist->phone=(assist->phone)/60; //Basically we are converting them into minutes
        if((assist->phone)>=60) //and this here into hours,currentHour is set to 1 also
        {
            assist->phone=(assist->phone)/60;
            assist->currentHour=1;
        }
    }

    //counting the same phone values in different nodes and use the insideCounter variable
    assist=head;
    assistCounter=assist;
    for(int i=0;i<counter-1;i++)
    {
        for(int j=0;j<counter-i-1;j++)
        {
            assistCounter=assistCounter->ptr;
            if((assist->phone)==(assistCounter->phone) && (assistCounter->insideCounter)!=0 && (assistCounter->currentHour)==0)  //for minutes
            {
                (assist->insideCounter)+=1;
                assistCounter->insideCounter=0;
            }
            if((assist->phone)==(assistCounter->phone) && (assistCounter->insideCounter)!=0 && (assist->currentHour)==1 && (assistCounter->currentHour)==1)  //for hours
            {
                (assist->insideCounter)+=1;
                assistCounter->insideCounter=0;
            }
        }
        assist=assist->ptr;
        assistCounter=assist;
    }

    //final print
    printf("Total phonecalls were %d\n",counter);
    assist=head;
    for(int i=0;i<counter;i++)
    {
       if((assist->insideCounter!=0) && (assist->currentHour==0))
       {
           printf("The phonecalls that lasted between %d and <%d minutes are: %d\n",assist->phone,(assist->phone)+1,assist->insideCounter);
       }
       if((assist->insideCounter!=0) && (assist->currentHour==1))
            printf("The phonecalls that lasted between %d and <%d hours are: %d\n",(assist->phone),(assist->phone)+1,assist->insideCounter);

       assist=assist->ptr;
    }

    //free nodes
    for(int i=0;i<counter;i++)
    {
        assist=head;
        for(int j=0;j<counter-i-1;j++)
            assist=assist->ptr;
        free(assist);
    }
    return 0;
}
