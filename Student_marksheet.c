//BLOCKCHAIN ENGINEER TEST

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>


//defining main functions 
void main_menu();
void add();
FILE*del();
void update();
void display();

//defining supporting functions
int check(int x);
//defining structure
struct Student
{
	char name[30];
	int rollno;
	int english;
	int math;
	int science;
	int total_marks;
}st;
//global declaration
FILE*fp;
//driver code
int main()
{
	if((fp=fopen("student.txt","rb+"))==NULL)
	{
		if ((fp=fopen("student.txt","wb+"))==NULL)
		{
			printf("cant open file");
			return 0;
		}
	}
    printf("\n\t\tProject submission by :Ritika Rao");
	main_menu();
	return 1;
}
//main menu
void main_menu()
{   //main_menu display to direct to function implementation
    int option;
    do
	{
		printf("\n\nPlease Choose your choice \n 1.Add\t2.View\t3.Delete\t4.Update\t5.Exit\n");
        scanf("%d",&option);
				
		switch(option)
		{
			case 1: add();
           			break;
			case 2: display();
					break;
			case 3: del();
					break;
			case 4: update();
					break;
			default: printf("\nYou have pressed a wrong key");
					exit(0);
		}

	}while(option!='5');
}
//function to check if marks added are invalid
int check(int i)
{
    //marks entered can't be greater than 100 or less than 0 
    if(i>100||i<0)
    {
        return 1;        
    }
    else
    {
        return 0;
    }
    
}
//adding new record
void add()
{   
    //open a file to record all data
    fp=fopen("student.dat","ab");
    int e=0,m=0,s=0,roll=0,total=0; //temporary variables
    //taking details 
	printf("Please Enter The New Details of student \n");
    printf("\nEnter The roll number of student ");
    scanf("%d",&roll);
    //checking if roll number already exits 
    if(st.rollno==roll){
        printf("\nStudent record already exists.Try modify the record? ");
        main_menu();
    }
    else
    {
        st.rollno=roll;
        fflush(stdin);
        printf("\nEnter The Name of student ");
        gets(st.name);
        //checking validity of marks entered on every step 
        printf("\nEnter The marks in science out of 100: ");
        scanf("%d",&s);
        if(check(s)==0){
            st.science=s;
            total+=s;
        }
        else
        {
            printf("OOPS!!Invalid input.");
            main_menu();
        }

        printf("\nEnter The marks in maths out of 100 : ");
        scanf("%d",&m);
        if(check(m)==0){
            st.math=m;
            total+=m;
            }
        else
        {
            printf("OOPS!!Invalid input.");
            main_menu();
        }

        printf("\nEnter The marks in english out of 100 : ");
        scanf("%d",&e);
        if(check(e)==0){
            st.english=e;
            total+=e;
            
        }
        else
        {
            printf("OOPS!!Invalid input.");
            main_menu();
        }

        st.total_marks=total;
        printf("%d",st.total_marks);

        fwrite(&st,sizeof(st),1,fp);
        fclose(fp);

        printf("\nStudent Record Has Been Created \n");
        printf("\n===============================\n");
         
    }
  
}
FILE*del(){
	int no;
    FILE *ft;

    printf("\n\tDelete Record");
    printf("\nPlease Enter The roll number of student You Want To Delete");
    scanf("%d",&no);
    fp=fopen("student.dat","rb");
    //opening a temporary file
    ft=fopen("Temp.dat","wb");
    rewind(fp);
    //searching for record
    while((fread(&st,sizeof(st),1,fp))>0)
    {
       if(st.rollno!=no)
       {
      fwrite(&st,sizeof(st),1,ft);
       }
    }
    fclose(ft);
    fclose(fp);
    //replacing original file with new file 
    remove("student.dat");
    rename("Temp.dat","student.dat");
    printf("\n\n\tRecord Deleted ..");
    printf("\n===============================\n");
    return fp;
}
void update()
{
	int no=0,found=0;
    printf("\n\tUPDATE RECORD\n");
    //taking roll number of student we want to update details for
    printf("\nPlease Enter The roll number of student");
    scanf("%d",&no);
    fp=fopen("student.dat","rb+");
    rewind(fp);
    //searching for roll number
    while((fread(&st,sizeof(st),1,fp))==1)
	{
	    if(st.rollno==no)
	        {
                found=1;
                //updating details
				fflush(stdin);
                printf("\n\nEnter The Name of student ");
                gets(st.name);
                printf("\nEnter The marks in maths out of 100 : ");
                scanf("%d",&st.math);
                printf("\nEnter The marks in english out of 100 : ");
                scanf("%d",&st.english);
                printf("\nEnter The marks in science out of 100 : ");
                scanf("%d",&st.science);
                st.total_marks=(st.math+st.english+st.science);
               
                fseek(fp,-(long)sizeof(st),1);
                fwrite(&st,sizeof(st),1,fp);
                fclose(fp);
	        }
	}
    //there is a chance user gives wrong roll number
    if(found==1)
        printf("\nRecord Updated");
    else 
        printf("\nRecord Not found"); 
    printf("\n===============================\n");

}

// function to display records 
void display()
{
	char ch;
    printf("\n\tDISPLAY RECORDS !!!");
    fp=fopen("student.dat","rb");
    printf("\nDo you want to enter query?(Y/N)");
    scanf("%s",&ch);
    printf("%s",&ch);
    //if no query is given we display all records
    if (ch=='N'||ch=='n')
    {
        while((fread(&st,sizeof(st),1,fp))>0)
        {
        printf("\n\nRoll Number of Student : %d",st.rollno);
        printf("\nName of Student : %s",st.name);
        printf("\nMarks in Maths : %d",st.math);
        printf("\nMarks in English : %d",st.english);
        printf("\nMarks in Science : %d",st.science);
        printf("\nTotal Marks of student is  : %d\n",st.total_marks);
        printf("\n===============================\n");
        
        }
        
    }

    //query implementation
    else if(ch=='Y'||ch=='y')
    {
        int flag=0;
        int option=0;
        
        printf("Choose which you want to search?\n1.Name\t2.Roll Number\t3.Science\t4.Maths\t5.English\t6.Total Marks");
        scanf("%d",&option);
        switch (option)
        {
            //when user wants to search using name
            case 1: 
            {
                char name[20];
                printf("\nEnter name you want to search: ");
                scanf("%s",&name);
                while((fread(&st,sizeof(st),1,fp))>0)
                {
                    if((strcmp(name, st.name))==0)
                    {
                        printf("===============================\n");
                        printf("\nRoll number of student : %d",st.rollno);
                        printf("\nName of student : %s",st.name);
                        printf("\nMarks in Maths : %d",st.math);
                        printf("\nMarks in English : %d",st.english);
                        printf("\nMarks in Science : %d",st.science);
                        printf("\nTotal Marks of student is  : %d",st.total_marks);
                        
                    flag=1;
                    }
                }
                
            }
                break;

            case 2:
            {
                //when user wants to search using roll no.
                int n=0;
                printf("\nEnter Roll Number you want to search:");
                scanf("%d",&n);
                while((fread(&st,sizeof(st),1,fp))>0)
                {
                    if(st.rollno==n)
                    {
                        printf("===============================\n");
                        printf("\nRoll number of student : %d",st.rollno);
                        printf("\nName of student : %s",st.name);
                        printf("\nMarks in Maths : %d",st.math);
                        printf("\nMarks in English : %d",st.english);
                        printf("\nMarks in Science : %d",st.science);
                        printf("\nTotal Marks of student is  : %d",st.total_marks);
                        
                    flag=1;
                    }
                }
                
            }    
                break;

            case 3:
            {
                //when user wants to search using science marks
                int n=0;
                printf("\nEnter science marks you want to search:");
                scanf("%d",&n);
                while((fread(&st,sizeof(st),1,fp))>0)
                {
                    if(st.science==n)
                    {
                        printf("===============================\n");
                        printf("\nRoll number of student : %d",st.rollno);
                        printf("\nName of student : %s",st.name);
                        printf("\nMarks in Maths : %d",st.math);
                        printf("\nMarks in English : %d",st.english);
                        printf("\nMarks in Science : %d",st.science);
                        printf("\nTotal Marks of student is  : %d",st.total_marks);
                        
                    flag=1;
                    }
                }
                
            }    
                break;
            
            case 4:
            {
                //when user wants to search using maths marks
                int n=0;
                printf("\nEnter Maths marks you want to search:");
                scanf("%d",&n);
                while((fread(&st,sizeof(st),1,fp))>0)
                {
                    if(st.math==n)
                    {
                        printf("===============================\n");
                        printf("\nRoll number of student : %d",st.rollno);
                        printf("\nName of student : %s",st.name);
                        printf("\nMarks in Maths : %d",st.math);
                        printf("\nMarks in English : %d",st.english);
                        printf("\nMarks in Science : %d",st.science);
                        printf("\nTotal Marks of student is  : %d",st.total_marks);
                        
                    flag=1;
                    }
                }
                
            }    
                break;
            
            case 5:
            {
                //when user wants to search using english marks
                int n=0;
                printf("\nEnter English you want to search:");
                scanf("%d",&n);
                while((fread(&st,sizeof(st),1,fp))>0)
                {
                    if(st.english==n)
                    {
                        printf("===============================\n");
                        printf("\nRoll number of student : %d",st.rollno);
                        printf("\nName of student : %s",st.name);
                        printf("\nMarks in Maths : %d",st.math);
                        printf("\nMarks in English : %d",st.english);
                        printf("\nMarks in Science : %d",st.science);
                        printf("\nTotal Marks of student is  : %d",st.total_marks);
                        
                    flag=1;
                    }
                }
                
            }    
                break;
            
            case 6:
            {
                //when user wants to search using total marks
                int n=0;
                printf("\nEnter Total Marks you want to search:");
                scanf("%d",&n);
                while((fread(&st,sizeof(st),1,fp))>0)
                {
                    if(st.total_marks==n)
                    {
                        printf("===============================\n");
                        printf("\nRoll number of student : %d",st.rollno);
                        printf("\nName of student : %s",st.name);
                        printf("\nMarks in Maths : %d",st.math);
                        printf("\nMarks in English : %d",st.english);
                        printf("\nMarks in Science : %d",st.science);
                        printf("\nTotal Marks of student is  : %d",st.total_marks);
                        
                    flag=1;
                    }
                }
                
            }    
                break;
        
        default:
        {
            if(flag==0)
                printf("\n\nRecord not exist");
            printf("\n===============================\n");
        }
            break;
        }
 
    }

    else
    {
        printf("\nInvalid input");
        printf("\n===============================\n");
    }
    fclose(fp);
     
}
