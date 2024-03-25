/* Name: Wong Syn Yee Student ID: 20409327 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structure to store visitor information
struct visitData{
    char *SrNo;
    char *ticketNo;
    char *Name;
    char *ID;
    };

//structure to store data
struct ticket{
    struct visitData visitor;
    struct ticket *nextPtr;
}*head=NULL;

//function to update ticket.txt file
void ticketfile(struct ticket *head)
{
    //create pointer for ticket file
    FILE *filePtr=NULL;
    //pointer points to the first element in linked list
    struct ticket *temp = head;
    //i=counter to calculate the number of visitors
    int i=0;
    while(temp!=NULL){
        temp = temp->nextPtr;
        i++;
    }
    //write ticket file
    temp=head;
    if((filePtr=fopen("Tickets.txt","w"))==NULL)
    {
        puts(" File could not be opened");
    }
    else
    {
        //write total number of visitor before displaying the list
        fprintf(filePtr," Total visitors: %d\n",i);
        while(head!=NULL)
        {
            //display the list of visitors
            fprintf(filePtr," %02d",head->visitor.SrNo);
            fprintf(filePtr," %s",head->visitor.ticketNo);
            fprintf(filePtr," %s",head->visitor.Name);
            fprintf(filePtr," %s\n",head->visitor.ID);
            head=head->nextPtr;
        }
    }
    //close the file
    fclose(filePtr);
}

//create variables and pointer for serial number as global variable
int ticketsrno;
char *tempsrno;
//function to add visitor into the linked list
void addvisitor(struct ticket **head, int VisitorType, char *Name, char *ID)
{
    //create pointer and allocate memory
    struct ticket *newvisitor=(struct ticket*)malloc(sizeof(struct ticket));
    struct ticket *ptr=*head;

    //increase the serial number for new input
    tempsrno++;

    //do formatting for the id
    //select depends on the visitor whether is local or international
    char *tempid;
    tempid=(char*)malloc(20);
    if(VisitorType==1)
    {
        //local visitor, put IC infront
        strcpy(tempid,"IC");
        strcat(tempid,ID);
    }
    if(VisitorType==2)
    {
        //international visitor, put PASS in front
        strcpy(tempid,"PASS");
        strcat(tempid,ID);
    }

    //do formatting for the ticket
    char *tempname;
    tempname=(char*)malloc(30);
    strcpy(tempname,Name);

    char *tempticket;
    tempticket=(char*)malloc(30);

    //this is for calculating the first 6 character of the name
    char *first6letter;
    first6letter=(char*)malloc(30);

    //calculate string length of the name
    int strlength=strlen(tempname);
    //if name is more than or equal to 6 character
    if(strlength>5)
    {
        //just copy the name
        strcpy(first6letter,tempname);
    }

    //if name is less than 6 character
    //put white spaces in front of the name
    if(strlength<6)
    {
        int a,b;
        for(a=0; a<=5-strlength; a++)
        {
            first6letter[a]=' ';
        }
        for(b=0; b<=5-strlength; a++, b++)
        {
            first6letter[a]=tempname[b];
        }
    }

    //convert the first 6 character to integer
    int ticketnumber[30];
    int c=0;
    while(c<=5)
    {
        int a=*first6letter;
        ticketnumber[c]=a;
        first6letter++;
        c++;
    }

    //insert the serial number at the end of the ticket number
    //increase the serial number for each new visitor
    ticketsrno++;
    //if the number contain 2 digit then just add the number at the end of the ticket number
    if(ticketsrno>9)
    {
        ticketnumber[c]=ticketsrno;
    }
    //if the number is only one digit then add zero before adding the number at the end of the ticket number
    if(ticketsrno>=0 && ticketsrno<10)
    {
        ticketnumber[c]=0;
        c++;
        ticketnumber[c]=ticketsrno;
    }

    //change the type of ticket from integer to character
    char ticketinchar[50]={0};
    int d;
    while(d<=c)
    {
        sprintf(&ticketinchar[strlen(ticketinchar)],"%d",ticketnumber[d]);
        d++;
    }

    //copy the ticket in char into temp ticket
    strcpy(tempticket,ticketinchar);

    //do formatting for the name to replace space with underscore
    //memory allocation already done in previous step
    int i=0;
    //replace space with underscore symbol
    while(i<strlength)
    {
        if(tempname[i]==' ')
        {
            tempname[i]='_';
        }
        i++;
    }

    //add the formated data into linked list
    newvisitor->visitor.SrNo=tempsrno;
    newvisitor->visitor.ticketNo=tempticket;
    newvisitor->visitor.Name=tempname;
    newvisitor->visitor.ID=tempid;
    newvisitor->nextPtr=NULL;

    if(*head==NULL)
    {
        //if the list is empty then new visitor will become the head
        *head=newvisitor;
    }
    else{
        //if list is not empty then insert new visitor at the end of list
        ptr=*head;
        while(ptr->nextPtr!=NULL)
        {
            ptr=ptr->nextPtr;
        }
        ptr->nextPtr=newvisitor;
    }

    //show and tell that the data is recorded
    puts("");
    printf(" %02d",newvisitor->visitor.SrNo);
    printf(" %s",newvisitor->visitor.ticketNo);
    printf(" %s",newvisitor->visitor.Name);
    printf(" %s",newvisitor->visitor.ID);
    puts("");
    printf("\n The information of the visitor %s is recorded.\n",newvisitor->visitor.Name);
    printf("\n----------------------------------------------------------------------\n");
    //update the ticket file
    ticketfile(*head);

    //create pointer for the outputfile
    FILE *outputfPtr=NULL;
    outputfPtr=fopen("output.txt","a");
        if(outputfPtr==NULL)
        {
            printf("File could not be opened\n");
        }
        else
        {
            //update command in the output file
            fprintf(outputfPtr,"\n The information of the visitor %s is recorded.\n",newvisitor->visitor.Name);
        }
    //close the output file
    fclose(outputfPtr);
    return;
}

//function to search the visitor information by ticket number
void searchbyticket(struct ticket *head, char *searchticketnumber)
{
    //create pointer for the outputfile
    FILE *outputfPtr=NULL;
    outputfPtr=fopen("output.txt","a");
    struct ticket * tempsearch = head;
    int datanum=0;
    while(tempsearch!=NULL)
    {
        //determine if the ticket number entered is in the linked list
        int success= strcmp(tempsearch->visitor.ticketNo,searchticketnumber);

        //if the ticket number is in the list then display the visitor information on the screen
        if(success== 0)
        {
            printf("\n The following record of the visitor is found:\n");
            printf(" %02d",tempsearch->visitor.SrNo);
            printf(" %s",tempsearch->visitor.ticketNo);
            printf(" %s",tempsearch->visitor.Name);
            printf(" %s",tempsearch->visitor.ID);
            puts("");
            //also update the output file
            fprintf(outputfPtr,"\n The following record of the visitor is found:\n");
            fprintf(outputfPtr," %02d",tempsearch->visitor.SrNo);
            fprintf(outputfPtr," %s",tempsearch->visitor.ticketNo);
            fprintf(outputfPtr," %s",tempsearch->visitor.Name);
            fprintf(outputfPtr," %s\n",tempsearch->visitor.ID);
            datanum++;
        }
        tempsearch=tempsearch->nextPtr;
    }
    //if none of the ticket number matched then display message of not found
    if(datanum==0)
    {
        printf("\n The visitor of ticket number %s is not found\n",searchticketnumber);
        //also update the output file
        fprintf(outputfPtr,"\n The visitor of ticket number %s is not found\n",searchticketnumber);
    }
    printf("\n----------------------------------------------------------------------\n");
    //close the output file
    fclose(outputfPtr);
}

//function to search the visitor information by name
void searchbyname(struct ticket *head, char *searchname)
{
    //create pointer for output file
    FILE *outputfPtr=NULL;
    outputfPtr=fopen("output.txt","a");
    struct ticket *tempsearch1 = head;
    struct ticket *tempsearch2 = head;

    //convert space character into underscore
    int strlength=strlen(searchname);
    int i=0;
    while(i<strlength)
    {
        if(searchname[i]==' ')
        {
            searchname[i]='_';
        }
        i++;
    }

    int datanum=0;
    while(tempsearch1!=NULL)
    {
        //compare the name entered and the name stored in the list
        int success= strcasecmp(tempsearch1->visitor.Name,searchname);

        //if the result matched then increase the visitor count to be displayed
        if(success == 0)
        {
            datanum++;
        }
        tempsearch1=tempsearch1->nextPtr;
    }

    //if visitor count not zero then display the message of the visitor is found
    if(datanum!=0)
    {
        printf("\n The following record of the visitor is found:\n");
        fprintf(outputfPtr,"\n The following record of the visitor is found:\n");
    }

    while(tempsearch2!=NULL)
    {
        //compare the name entered and the name stored in the list
        int success= strcasecmp(tempsearch2->visitor.Name,searchname);

        //if the result matched
        if(success == 0)
        {
            //display all the visitor with that name
            printf(" %02d",tempsearch2->visitor.SrNo);
            printf(" %s",tempsearch2->visitor.ticketNo);
            printf(" %s",tempsearch2->visitor.Name);
            printf(" %s",tempsearch2->visitor.ID);
            puts("");
            //and also update the output file
            fprintf(outputfPtr," %02d",tempsearch2->visitor.SrNo);
            fprintf(outputfPtr," %s",tempsearch2->visitor.ticketNo);
            fprintf(outputfPtr," %s",tempsearch2->visitor.Name);
            fprintf(outputfPtr," %s\n",tempsearch2->visitor.ID);
        }
        tempsearch2=tempsearch2->nextPtr;
    }

    //if no name is matched then display the message of visitor not found
    if(datanum==0)
    {
        printf(" The visitor of name %s is not found\n",searchname);
        //and also update the output file
        fprintf(outputfPtr,"\n The visitor of name %s is not found\n",searchname);
    }
    printf("\n----------------------------------------------------------------------\n");
    //close the output file
    fclose(outputfPtr);
}

//function to search the visitor information by id number
void searchbyid(struct ticket *head, char *searchid)
{
    //create pointer foe output file
    FILE *outputfPtr=NULL;
    outputfPtr=fopen("output.txt","a");
    struct ticket * tempsearch2 = head;
    int datanum=0;
    while(tempsearch2!=NULL)
    {
        //determine if the id number entered by the user is matched with the id in the linked list
        int success= strcasecmp(tempsearch2->visitor.ID,searchid);

        //if the id number is matched
        if(success==0)
        {
            //display the id number on screen
            printf("\n The following record of the visitor is found:\n");
            printf(" %02d",tempsearch2->visitor.SrNo);
            printf(" %s",tempsearch2->visitor.ticketNo);
            printf(" %s",tempsearch2->visitor.Name);
            printf(" %s",tempsearch2->visitor.ID);
            puts("");
            //and also update the output file
            fprintf(outputfPtr,"\n The following record of the visitor is found:\n");
            fprintf(outputfPtr," %02d",tempsearch2->visitor.SrNo);
            fprintf(outputfPtr," %s",tempsearch2->visitor.ticketNo);
            fprintf(outputfPtr," %s",tempsearch2->visitor.Name);
            fprintf(outputfPtr," %s\n",tempsearch2->visitor.ID);
            //update the visitor count
            datanum++;
        }
        tempsearch2=tempsearch2->nextPtr;
    }
    //if no id number is matched
    if(datanum==0)
    {
        //display the message of not found
        printf(" The visitor of ID %s is not found\n",searchid);
        //and also update the output file
        fprintf(outputfPtr,"\n The visitor of ID %s is not found\n",searchid);
    }
    printf("\n----------------------------------------------------------------------\n");
    //close the output file
    fclose(outputfPtr);
}

//function to determine the search type based on user choice
void search(int SearchType)
{
    char searchticketnumber[30];
    char searchname[30];
    char searchid[20];
    switch(SearchType)
    {
        //search by ticket number
        case 1:
                puts("");
                //prompt user for ticket number
                printf(" Ticket Number: ");
                scanf("%s",searchticketnumber);
                puts("");
                searchbyticket(head,searchticketnumber);
                break;

        //search by name
        case 2:
                puts("");
                //prompt user for name
                printf(" Name: ");
                scanf("%*c");
                scanf("%[^\n]",searchname);
                puts("");
                searchbyname(head,searchname);
                break;

        //search by id number
        case 3:
                puts("");
                //prompt user for id number
                printf(" Follow the example below to search the visitor.\n");
                printf(" For international visitor: PASSXXXXXXX\n");
                printf(" For local visitor: ICXXXXXXX\n");
                puts("");
                printf(" ID: ");
                scanf("%*c");
                scanf("%[^\n]",searchid);
                puts("");
                searchbyid(head,searchid);
                break;
    }
}

//function to delete the visitor information by ticket number
void deletebyticketnumber(char *deleteticketnumber)
{
    //create pointer for output file
    FILE *outputfPtr=NULL;
    outputfPtr=fopen("output.txt","a");
    struct ticket *temp1 = head;
    struct ticket *temp2 = head;
    while(temp1!=NULL)
    {
        //determine if ticket number entered matched with the ticket number in linked list
        int success=strcmp(temp1->visitor.ticketNo,deleteticketnumber);
        if(success==0)
        {
            if(temp1==temp2){
                //if the ticket number to delete in first node
                head = head->nextPtr;
                free(temp1);
            }
            else{
                //temp 1 is the node we need to delete
                //temp 2 is the node previous to temp 1
                temp2->nextPtr = temp1->nextPtr;
                free(temp1);
            }

            //display the delete message
            printf(" The visitor with Ticket No: %s, information is deleted.\n",deleteticketnumber);
            printf("\n----------------------------------------------------------------------\n");

            if(outputfPtr==NULL)
            {
                printf("File could not be opened\n");
            }
            else
            {
                //update the output file
                fprintf(outputfPtr,"\n The visitor with Ticket No.: %s, information is deleted.\n",deleteticketnumber);
            }
            //close the output file
            fclose(outputfPtr);

            //update the ticket file
            ticketfile(head);
            return;
        }
        temp2 = temp1;
        temp1 = temp1->nextPtr;
    }
    //if nothing is matched then display the message of not found
    printf(" Visitor with ticket number %s is not found !!!\n", deleteticketnumber);
    //and update the output file
    fprintf(outputfPtr,"\n Visitor with ticket number %s is not found !!!\n", deleteticketnumber);
    printf("\n----------------------------------------------------------------------\n");
    //close the output file
    fclose(outputfPtr);

}

//function to delete the visitor information by id number
void deletebyid(char *deleteid)
{
    //create pointer for the output file
    FILE *outputfPtr=NULL;
    outputfPtr=fopen("output.txt","a");
    struct ticket *temp1 = head;
    struct ticket *temp2 = head;

    while(temp1!=NULL)
    {
        //determine if id numeber entered matched with the id number in linked list
        int success=strcasecmp(temp1->visitor.ID,deleteid);
        if(success==0)
        {
            if(temp1==temp2){
                //if the record to delete is in first node
                head = head->nextPtr;
                free(temp1);
            }
            else{
                //temp 1 is the node we need to delete
                //temp 2 is the node previous to temp 1
                temp2->nextPtr = temp1->nextPtr;
                free(temp1);
            }

            //display the message of visitor been deleted
            printf(" The visitor with ID: %s, information is deleted.\n",temp1->visitor.ID);
            printf("\n----------------------------------------------------------------------\n");
            //update the ticket file
            ticketfile(head);

            if(outputfPtr==NULL)
                {
                    printf("File could not be opened\n");
                }
                else
                {
                    //update the output file
                    fprintf(outputfPtr,"\n The visitor with ID: %s, information is deleted.\n",temp1->visitor.ID);
                }
            //close the output file
            fclose(outputfPtr);
            return;

        }
        temp2 = temp1;
        temp1 = temp1->nextPtr;
    }
    //if id is not matched then display message of not found
    printf(" Visitor with ID %s is not found !!!\n", deleteid);
    //also update the output file
    fprintf(outputfPtr,"\n Visitor with ID %s is not found !!!\n", deleteid);
    printf("\n----------------------------------------------------------------------\n");
    //close the output file
    fclose(outputfPtr);
}

//function to delete the visitor information by name
void deletebyname(char *deletename)
{
    //create pointer to the output file
    FILE *outputfPtr=NULL;
    outputfPtr=fopen("output.txt","a");
    struct ticket *temp1 = head;
    struct ticket *temp2 = head;
    struct ticket *tempfind = head;
    struct ticket *tempfind2 = head;
    char dltid[20];

    //convert space character into underscore
    int strlength=strlen(deletename);
    int i=0;
    while(i<strlength)
    {
        if(deletename[i]==' ')
        {
            deletename[i]='_';
        }
        i++;
    }

    int datanum=0;
    while(tempfind!=NULL)
    {
        //determine if any of the names matched
        int success= strcasecmp(tempfind->visitor.Name,deletename);

        if(success == 0)
        {
            //if the mane matched then update the visitor count
            datanum++;
        }
        tempfind=tempfind->nextPtr;
    }

    //if more than one name is matched then we have to delete by id
    if(datanum>1)
    {
        //display the message that visitor is same, prompt for input for id
        printf("\n The following visitors have same names, Please enter the ID to deleted:\n");
        //also update the output file
        fprintf(outputfPtr,"\n The following visitors have same names, Please enter the ID to deleted:\n");
        while(tempfind2!=NULL){
        int success= strcasecmp(tempfind2->visitor.Name,deletename);

        if(success == 0)
        {
            //to print the names that are same
            printf(" %02d",tempfind2->visitor.SrNo);
            printf(" %s",tempfind2->visitor.ticketNo);
            printf(" %s",tempfind2->visitor.Name);
            printf(" %s",tempfind2->visitor.ID);
            puts("");
            //also update the output file
            fprintf(outputfPtr," %02d",tempfind2->visitor.SrNo);
            fprintf(outputfPtr," %s",tempfind2->visitor.ticketNo);
            fprintf(outputfPtr," %s",tempfind2->visitor.Name);
            fprintf(outputfPtr," %s\n",tempfind2->visitor.ID);
        }
        //to next node
        tempfind2=tempfind2->nextPtr;
    }
        //prompt for id input from user
        puts("");
        printf(" Follow the example below to delete the visitor.\n");
        printf(" For international visitor: PASSXXXXXXX\n");
        printf(" For local visitor: ICXXXXXXX\n");
        puts("");
        printf(" ID: ");
        scanf("%*c");
        scanf("%[^\n]",dltid);
        //go to the function of delete by id
        deletebyid(dltid);
    }
    //if the name entered does not appear more than once
    else
    {
        while(temp1!=NULL)
        {
            //determine which name is matched
            int success=strcasecmp(temp1->visitor.Name,deletename);
            if(success==0)
            {
                if(temp1==temp2){
                    //if the information to delete is the first node
                    head = head->nextPtr;
                    free(temp1);
                }
                else{
                    //temp 1 is the node we need to delete
                    //temp 2 is the node previous to temp 1
                    temp2->nextPtr = temp1->nextPtr;
                    free(temp1);
                }

                puts("");
                //display the message that the visitor is being deleted
                printf(" The visitor: %s information is deleted.\n", temp1->visitor.Name);
                //also update the output file
                fprintf(outputfPtr,"\n The visitor: %s information is deleted.\n", temp1->visitor.Name);
                printf("\n----------------------------------------------------------------------\n");
                //update the ticket file
                ticketfile(head);
                //close the output file
                fclose(outputfPtr);
                return;

            }
            temp2 = temp1;
            temp1 = temp1->nextPtr;
        }
        //if the visitor name is not matched then display the message of not found
        printf(" Visitor with name %s is not found !!!\n", deletename);
        //also update the output file
        fprintf(outputfPtr,"\n Visitor with name %s is not found !!!\n", deletename);
        printf("\n----------------------------------------------------------------------\n");
        }
        //close the output file
    fclose(outputfPtr);
}

//function to sort the list based on alphabetical order
void sortlinklist()
{
    //create pointer for output file
    FILE *outputfPtr=NULL;
    outputfPtr=fopen("output.txt","a");
    struct ticket *temp = head;

    //calculate the number of node in the linked list
    int c = 1;
    while(temp->nextPtr != NULL)
    {
        temp = temp->nextPtr;
        c++;
    }
    temp = head;

    //loop until all node being compared
    for(int i=0;i<c;i++)
    {
        temp = head;
        while(temp->nextPtr != NULL)
        {
            //if the name in node is greater than the name in the next node
            if(strcmp(temp->visitor.Name,temp->nextPtr->visitor.Name) > 0)
            {
                //swap the position for all visitor information
                char *x;

                x=temp->visitor.Name;
                temp->visitor.Name=temp->nextPtr->visitor.Name;
                temp->nextPtr->visitor.Name=x;


                x=temp->visitor.SrNo;
                temp->visitor.SrNo=temp->nextPtr->visitor.SrNo;
                temp->nextPtr->visitor.SrNo=x;


                x=temp->visitor.ID;
                temp->visitor.ID=temp->nextPtr->visitor.ID;
                temp->nextPtr->visitor.ID=x;


                x=temp->visitor.ticketNo;
                temp->visitor.ticketNo=temp->nextPtr->visitor.ticketNo;
                temp->nextPtr->visitor.ticketNo=x;

            }
            //to next node
            temp = temp->nextPtr;
        }
    }
    temp = head;
    //display the sorted linked list
    while(temp != NULL)
    {
        printf(" %02d",temp->visitor.SrNo);
        printf(" %s",temp->visitor.ticketNo);
        printf(" %s",temp->visitor.Name);
        printf(" %s",temp->visitor.ID);
        puts("");
        //also update the output file
        fprintf(outputfPtr,"\n %02d",temp->visitor.SrNo);
        fprintf(outputfPtr," %s",temp->visitor.ticketNo);
        fprintf(outputfPtr," %s",temp->visitor.Name);
        fprintf(outputfPtr," %s",temp->visitor.ID);
        temp = temp->nextPtr;
    }
    printf("\n----------------------------------------------------------------------\n");
    fprintf(outputfPtr,"\n");
    fclose(outputfPtr);
}

//function to sort the linked list back to ascending order based on serial number
void sortback()
{
    struct ticket *temp = head;

    //calculate the number of node in the linked list
    int c = 1;
    while(temp->nextPtr != NULL)
    {
        temp = temp->nextPtr;
        c++;
    }
    temp = head;

    //loop until all node being compared
    for(int i=0;i<c;i++)
    {
        temp = head;
        while(temp->nextPtr != NULL)
        {
            //if the serial number in node is greater than the serial number in the next node
            if(temp->visitor.SrNo > temp->nextPtr->visitor.SrNo)
            {
                //swap the position for all visitor information
                char *x;

                x=temp->visitor.Name;
                temp->visitor.Name=temp->nextPtr->visitor.Name;
                temp->nextPtr->visitor.Name=x;


                x=temp->visitor.SrNo;
                temp->visitor.SrNo=temp->nextPtr->visitor.SrNo;
                temp->nextPtr->visitor.SrNo=x;


                x=temp->visitor.ID;
                temp->visitor.ID=temp->nextPtr->visitor.ID;
                temp->nextPtr->visitor.ID=x;


                x=temp->visitor.ticketNo;
                temp->visitor.ticketNo=temp->nextPtr->visitor.ticketNo;
                temp->nextPtr->visitor.ticketNo=x;

            }
            //to next node
            temp = temp->nextPtr;
        }
    }
}

//function to display all visitor data
void display()
{
    FILE *outputfPtr=NULL;
    outputfPtr=fopen("output.txt","a");
    struct ticket *temp;
    temp=head;
    int i=0;
    //to calculate how many visitors are there in the linked list
    while(temp!=NULL){
        temp = temp->nextPtr;
        i++;
    }
    temp=head;
    puts("");
    //display the total number of visitor and update output file
    printf(" Total visitors:%d\n",i);
    fprintf(outputfPtr,"\n Total visitors:%d\n",i);
    puts("");
    //display the list of visitors
    while(temp!=NULL){
        printf(" %02d",temp->visitor.SrNo);
        printf(" %s",temp->visitor.ticketNo);
        printf(" %s",temp->visitor.Name);
        printf(" %s",temp->visitor.ID);
        //also update output file
        fprintf(outputfPtr," %02d",temp->visitor.SrNo);
        fprintf(outputfPtr," %s",temp->visitor.ticketNo);
        fprintf(outputfPtr," %s",temp->visitor.Name);
        fprintf(outputfPtr," %s\n",temp->visitor.ID);
        puts("");
        //to next node
        temp = temp->nextPtr;
    }
    printf("\n----------------------------------------------------------------------\n");
    //close output file
    fclose(outputfPtr);
}


//main function of the program
int main(void)
{
    //change the color of the screen
    system("color f1");
    //declare variables to be used
    char Name[30], ID[20];
    char dltticketnumber[30];
    char dltid[20];
    char dltname[30];
    int VisitorType;
    int SearchType;
    int MyChoice,sort;
    struct ticket *temp;

    //instruction to be displayed
    printf("----------------------------------------------------------------------");
    printf("\n Welcome to Theme Park! Select number to perform different function.");
    printf("\n 1.Add a new visitor information.");
    printf("\n 2.Search visitor information based on Ticket No, Name, or ID.");
    printf("\n 3.Delete the visitor information based on ticket number.");
    printf("\n 4.Delete the visitor information based on full name.");
    printf("\n 5.Delete the visitor information based on ID.");
    printf("\n 6.Display Total No of tickets sold.");
    printf("\n 7.Exit.");
    printf("\n----------------------------------------------------------------------\n");

    //loop to prompt user to choose the function
    while(1)
    {
        //prompt for input
        printf(" Enter your choice: ");
        scanf("%d",&MyChoice);
        //switch based on choice
        switch(MyChoice)
        {
            case 1:
                //calculate the current number of visitor
                temp=head;
                int i=0;
                while(temp!=NULL)
                {
                    temp = temp->nextPtr;
                    i++;
                }
                //if the visitor reach 40 people
                temp=head;
                if(i>39)
                {
                    //stop adding visitor
                    printf("Visitor limit of 40 reached!\n");
                    printf("You cannot add visitor anymore!\n");
                    printf("\n----------------------------------------------------------------------\n");
                }
                else
                {
                    //prompt for name
                    puts("");
                    printf(" Name: ");
                    scanf("%*c");
                    scanf("%[^\n]",Name);
                    //prompt for id
                    puts("");
                    printf(" ID: ");
                    scanf("%s",ID);
                    //prompt for nationality
                    puts("");
                    printf(" Please enter the number based on the visitor's nationality.\n");
                    printf(" 1 for local visitor.\n");
                    printf(" 2 for international visitor.\n");
                    printf(" Nationality: ");
                    scanf("%d",&VisitorType);
                    //go to function to add visitor into the linked list
                    addvisitor(&head,VisitorType,Name,ID);
                }
                break;

            case 2:
                //prompt for choice to search visitor based on their choice
                puts("");
                printf(" 1.Search visitor information by Ticket Number.\n");
                printf(" 2.Search visitor information by Name.\n");
                printf(" 3.Search visitor information by ID.\n");
                puts("");
                printf(" Choice: ");
                scanf("%d",&SearchType);
                //go to function
                search(SearchType);
                break;

            case 3:
                //prompt for ticket number
                puts("");
                printf(" Ticket Number: ");
                scanf("%*c");
                scanf("%[^\n]",dltticketnumber);
                //go to function to delete by ticket number
                deletebyticketnumber(dltticketnumber);
                break;

            case 4:
                //prompt for name
                puts("");
                printf(" Name: ");
                scanf("%*c");
                scanf("%[^\n]",dltname);
                //go to function to delete by name
                deletebyname(dltname);
                break;

            case 5:
                //prompt for id
                puts("");
                printf(" Follow the example below to delete the visitor.\n");
                printf(" For international visitor: PASSXXXXXXX\n");
                printf(" For local visitor: ICXXXXXXX\n");
                printf(" ID: ");
                scanf("%*c");
                scanf("%[^\n]",dltid);
                //go to function to delete by id
                deletebyid(dltid);
                break;

            case 6:
                //ask user whether to view based on alphabetical order
                printf(" Do you want to view the list based on alphabetical order?\n");
                printf(" 1. Yes\n 2. No\n\n");
                puts("");
                printf(" My choice:");
                scanf("%d",&sort);
                puts("");
                if (sort==1)
                {
                    //go to function to sort based on alphabetical order
                    sortlinklist();
                    //sort the linked list back after displaying
                    sortback();
                }
                else if (sort==2)
                {
                    //display the visitor information
                    display();
                }
                break;

            case 7:
                //exit program
                exit(0);
                break;
        }
    }
}
