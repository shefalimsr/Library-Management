#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

//defining the properties of the fields used in the program


#define IN 1
#define OUT 0


void Addbook();
void Searchbook();
void Displaybook();
void Author();
void Allcopies();
void Stock();
void Issue();
void Retrnbk();
void Addmembr();
void Exit();

char info[500];


struct book
{
  int bid;
  char bname[25] ;
  char author[25];
  int copies;
  char titles[500];
  int status;
};
struct member
{
  int mid;
  char mname[25] ;
  char department[25];
  int availibcard;
  int phno;

};


//initializing the files used in the program

FILE *librcd;
FILE *memrcd;
FILE *fp1;
FILE *fp2;
FILE *temp1;
FILE *temp2;
void main()
{
    int choice=0,i;

    printf("\n\t\tLIBRARY MANAGEMENT SYSTEM \n");
    do{
    printf("\n\t~~MENU~~\n 1. Add A New Book\n 2. Search a book \n 3. Display Complete Information of a Book \n 4. Display All Books of An Author\n 5. List Titles of a Book\n 6. List Count of Books (Issued & On Stock)\n 7. To Issue a Book \n 8. To return a Book \n 9. Exit the program\n\n\t Enter your choice \n");
    scanf("%i",&choice);


    switch (choice)
    {
        case 1: Addbook();
                break;
        case 2: Searchbook();
                break;
        case 3: Displaybook();
                break;
        case 4: Author();
                break;
        case 5: Allcopies();
                break;
        case 6: Stock();
                break;
        case 7: Issue();
                break;
        case 8: Retrnbk();
                break;
        case 9: Addmembr();
                break;
        case 10: Exit();
        default: printf(" ! Invalid Input...\n");
    }
}while(choice!=10);
}

void Addbook()
{
    int i;
    book.status=IN;
    librcd = fopen("librcd.txt","a+");
    printf("Enter The unique id of The Book :(Integer) \n");
        scanf("%d",&book.bid);
    printf("Enter The Name of The Book :\n");
        scanf("%s",book.bname);
    printf("Enter The Name of Author :\n");
        scanf("%s",book.author);
    printf("Enter The Number of The Book:(Integer)\n");
        scanf("%d",&book.copies);
    fprintf(librcd,"\n%d\t%s\t%s\t%d\t%d\t",book.bid,book.bname,book.author,book.status,book.copies);
    printf("Enter The Titles Of The Book : \n");
    for(i=0;i<book.copies;i++)
    {
        scanf("%s",book.titles);
        fprintf(librcd,"%s\t",book.titles);
    }
    fclose(librcd);
    printf(" A New Book has been Added Successfully...\n");

}

void Displaybook()
{
    librcd = fopen("librcd.txt","a+");
    printf("\nBook id\tName\tAuthor\tStatus\tNo.\tTitles\n",info);
    do
    {
        fgets(info,500,librcd);
        printf("%s\n",info);
    }while(!feof(librcd));
    fclose(librcd);
    memrcd = fopen("memrcd.txt","a+");
    printf("\nMid\tName\tDept\tPh.no\tAvailable cards\n");
    do
    {
        fgets(info,500,memrcd);
        printf("%s\n",info);
    }while(!feof(memrcd));
    fclose(memrcd);

}

void Searchbook()
{
    int i;
    char Target[25],stats[3];
    int Found=0;
    if((librcd=fopen("librcd.txt","r"))== NULL)
        printf(" The File is Empty...\n\n");
    else
    {
        printf("\nEnter The Name Of Book : ");
            scanf("%s",Target);
        while(!feof(librcd)&& Found==0)
        {
        fscanf(librcd,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.copies);
            if(strcmp(Target,book.bname)==0)
                Found=1;
            for(i=0;i<book.copies;i++)
                fscanf(librcd,"%s",book.titles);
        }
        if(Found)
        {
            if(book.status==IN)
                strcpy(stats,"IN");
            else
                strcpy(stats,"OUT");

            printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\n\n",book.bid,book.bname,book.author,stats);
        }
        else if(!Found)
            printf("! There is no such Entry...\n");
        fclose(librcd);
    }

}

void Author()
{
    int i;
    char Target[500];
    int Found=0;
    if((librcd=fopen("librcd.txt","r"))==NULL)
    printf("The file is empty... \n\n");
    else
    {
        printf("\nEnter The Name Of Author : ");
            scanf("%s",Target);
        printf("\nBooks:");
        while(!feof(librcd))
        {
            fscanf(librcd,"%d %s %s %d %d",&book.bid,book.bname,book.author,&book.status,&book.copies);
            if(strcmp(Target,book.author)==0)
            {
                Found=1;
                printf("\n\t%s",book.bname);
            }
            for(i=0;i<book.copies;i++)
                fscanf(librcd,"%s",book.titles);
        }
        if(!Found)
            printf(" ! There is no such Entry...\n");
        fclose(librcd);
    }

}
void Allcopies()
{
    int i;
    char Target[500];
    int Found=0;
    if((librcd=fopen("librcd.txt","r"))==NULL)
        printf("The file is empty...\n\n");
    else
    {
        printf("\nEnter The Book Name :");
        scanf("%s",Target);
        while(!feof(librcd)&& Found==0)
        {
            fscanf(librcd,"%d %s %s %d %d",&book.bid,book.bname,book.author,&book.status,&book.copies);
            if(strcmp(Target,book.bname)==0)
                {
                    Found=1;
                    break;
                }
            for(i=0;i<book.copies;i++)
                fscanf(librcd,"%s",book.titles);
        }
        if(Found)
        {
            //printf("The Name of book is:               %s\n",book.bname);
            printf("\nThe Titles:\n");
            for(i=0;i<book.copies;i++)
            {
                fscanf(librcd,"%s",book.titles);
                    printf("%d.%s......\n",i+1,book.titles);
            }
        }
        else if(!Found)
            printf(" ! There is no such Entry...\n");
        fclose(librcd);
    }

}
void Stock()
{
    int i,issuecount=0,stockcount=0;
    int Found=0;
    if((librcd=fopen("librcd.txt","r"))==NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        while(!feof(librcd))
        {
            fscanf(librcd,"%d %s %s %d %d",&book.bid,book.bname,book.author,&book.status,&book.copies);
            if(book.status==IN)
            {
                stockcount++;
            }
            else
            {
                issuecount++;
            }
            for(i=0;i<book.copies;i++)
                fscanf(librcd,"%s",book.titles);
        }
        fclose(librcd);
    printf("\nCount of issued Books:%d\nCount of Books in Stock:%d\n",issuecount,stockcount-1);
    }

}
void Addmembr()
{
    int i;

    memrcd = fopen("memrcd.txt","a+");
    printf("Enter The userid of the Member(Integer) :\n");
        scanf("%d",&member.mid);
    printf("Enter The Name of the Member :\n");
        scanf("%s",member.mname);
    printf("Enter The Department\n");
        scanf("%s",member.department);

    printf("Enter The phone number of the member:\n");
        scanf("%d",&member.phno);
    member.availibcard=5;
    fprintf(memrcd,"\n%d\t%s\t%s\t%d\t%d\t",member.mid,member.mname,member.department,member.phno,    member.availibcard);
    fclose(memrcd);
    printf("\n (' ') Added  A New member Successfully...\n");


}
void Issue()
{
    int mid,i,Found1=0,Found2=0;
    char issubookname[20];
    printf("\nEnter The user id of the Member : \n");
        scanf("%d",&mid);
    if((memrcd=fopen("memrcd.txt","r"))==NULL)
        printf("The file is empty...\n\n");
    else
    {
        while(!feof(memrcd)&& Found1==0)
        {
            fscanf(memrcd,"%d %s %s %d %d ",&member.mid,member.mname,member.department,&member.phno,&member.availibcard);
            if(mid==member.mid)
            {
                Found1=1;
            }
        }
        if(Found1)
        {
            if(member.availibcard<1)
            {
                printf("Library card not available...\n");
            }
            else
            {    printf("\nEnter The Name of book :");
                scanf("%s",issubookname);
                if((librcd=fopen("librcd.txt","r"))==NULL)
                    printf("The file is empty...\n\n");
                else
                {
                    while(!feof(librcd)&& Found2==0)
                    {
                        fscanf(librcd,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.copies);
                        if(strcmp(issubookname,book.bname)==0)
                            Found2=1;
                        for(i=0;i<book.copies;i++)
                            fscanf(librcd,"%s",book.titles);
                    }
                    if(Found2)
                    {
                        if(book.status==0)
                        {
                            printf("Book already issued...\n");
                        }
                        else
                        {

                            fp2=fopen("fp2.txt","w");
                            if((temp2=fopen("memrcd.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp2))
                                {
                                    fscanf(temp2,"%d %s %s %d %d ",&member.mid,member.mname,member.department,&member.phno,&member.availibcard);


                                    if(mid==member.mid)
                                    {
                                        member.availibcard--;
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",member.mid,member.mname,member.department,member.phno,    member.availibcard);
                                    }
                                    else{
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",member.mid,member.mname,member.department,member.phno,member.availibcard);}
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);


                            fp1=fopen("fp1.txt","w");
                            if((temp1=fopen("librcd.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                      fscanf(temp1,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.copies);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(issubookname,book.bname)!=0)
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d    \t",book.bid,book.bname,book.author,book.status,book.copies);
                                    }
                                    else
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d\t",book.bid,book.bname,book.author,0,book.copies);
                                    }
                                    for(i=0;i<book.copies;i++)
                                    {
                                        fscanf(temp1,"%s",book.titles);
                                        fprintf(fp1,"%s\t",book.titles);
                                    }
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(librcd);
                            fclose(memrcd);
                            remove("librcd.txt");
                            rename("fp1.txt","librcd.txt");
                            remove("memrcd.txt");
                            rename("fp2.txt","memrcd.txt");
                            printf("Book Successfully issued...\n");
                        }
                    }
                    else if(!Found2)
                        printf("There is no such Book...\n");

                }
            }
        }
        else if(!Found1)
            printf("Invalid User id...\n");


    }

}
void Retrnbk()
{
int mid,i,Found1=0,Found2=0,flag=0;char retbookname[20];
    temp1=librcd;
    temp2=memrcd;
   printf("\nEnter The user id of the Member :\n");
        scanf("%d",&mid);
    if((memrcd=fopen("memrcd.txt","r"))==NULL)
        printf("The file is empty...\n\n");
    else
    {
        while(!feof(memrcd)&& Found1==0)
        {
            fscanf(memrcd,"%d %s %s %d %d ",&member.mid,member.mname,member.department,&member.phno,&member.availibcard);
            if(mid==member.mid)
            {
                Found1=1;
            }
        }
        if(Found1)
        {
            if(member.availibcard>=5)
            {
                printf("Error...\n");
            }
            else
            {    printf("\nEnter The Name of book :");
                scanf("%s",retbookname);
                if((librcd=fopen("librcd.txt","r"))==NULL)
                    printf("The file is empty ...\n\n");
                else
                {
                    while(!feof(librcd)&& Found2==0)
                    {
                        fscanf(librcd,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.copies);
                        if(strcmp(retbookname,book.bname)==0)
                        Found2=1;
                        for(i=0;i<book.copies;i++)
                            fscanf(librcd,"%s",book.titles);
                    }
                    if(Found2)
                    {
                        if(book.status==1)
                        {
                            printf("Error...Book already in stock\n");
                        }
                        else
                        {

                            fp2=fopen("fp2.txt","w");
                            if((temp2=fopen("memrcd.txt","a+"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp2))
                                {
                                    fscanf(temp2,"%d %s %s %d %d ",&member.mid,member.mname,member.department,&member.phno,&member.availibcard);


                                    if(mid==member.mid)
                                    {
                                        member.availibcard++;
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",member.mid,member.mname,member.department,member.phno,    member.availibcard);
                                    }
                                    else
                                    {
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",member.mid,member.mname,member.department,member.phno,member.availibcard);
                                    }
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);


                            fp1=fopen("fp1.txt","w");
                            if((temp1=fopen("librcd.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                      fscanf(temp1,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.copies);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(retbookname,book.bname)!=0)
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d    \t",book.bid,book.bname,book.author,book.status,book.copies);
                                    }
                                    else
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d\t",book.bid,book.bname,book.author,1,book.copies);
                                    }
                                    for(i=0;i<book.copies;i++)
                                    {
                                        fscanf(temp1,"%s",book.titles);
                                        fprintf(fp1,"%s\t",book.titles);
                                    }
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(librcd);
                            fclose(memrcd);
                            printf("('') Book Successfully Returned...\n");
                            remove("librcd.txt");
                            rename("fp1.txt","librcd.txt");
                            remove("memrcd.txt");
                            rename("fp2.txt","memrcd.txt");

                        }
                    }
                    else if(!Found2)
                        printf("! There is no such Book...\n");

                }
            }
        }
        else if(!Found1)
            printf("! Invalid User id...\n");


    }

}
void Exit()
{
  exit(0);
}
