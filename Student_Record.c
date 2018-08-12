#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME 50
#define MAX_CODE 10
#define MAX_RECORDS 200
#define MAX_SUBJECTS 5

/*------------------------------------------Global Declaration of all the functions and structures----------------------------------------*/




struct student_record_tag
{
	int roll_no;
	char student_name[MAX_NAME];
	char subject_code[MAX_CODE];
	int marks;
} ;
void initialize(struct student_record_tag student_record[], int size);
void insert(struct student_record_tag student_record[], int size, char n[], int r, char code[], int m);
void delete(struct student_record_tag student_record[], int size, int r, char code[]);
void getNumRecords(struct student_record_tag student_record[], int size);
void isEmpty(struct student_record_tag student_record[], int size);
void getMaxMarks(struct student_record_tag student_record[], int size, char code[]);
void isFull(struct student_record_tag student_record[], int size);
void Find_topper(struct student_record_tag student_record[], int size);
void Find_failures(struct student_record_tag student_record[], int size, int k, int p);
void list_unique(struct student_record_tag student_record[], int size);
void list_union(struct student_record_tag list1[], struct student_record_tag list2[],struct student_record_tag list3[], int size_l1, int size_l2);
void list_intersection(struct student_record_tag list1[], struct student_record_tag list2[], int size_l1, int size_l2);
void list_difference(struct student_record_tag list1[], struct student_record_tag list2[],struct student_record_tag list3[], int size_l1, int size_l2);
void list_symmetric_difference(struct student_record_tag list1[], struct student_record_tag list2[], int size_l1, int size_l2);
void Find_Kth_popular_subject(struct student_record_tag student_record[],int ks, int size);
void list_sort(struct student_record_tag student_record[], int size);


/*------------------------------------------//Global Declaration of all the functions and structures-------------------------------------*/

struct student_record_tag student_record[MAX_RECORDS], list1[MAX_RECORDS], list2[MAX_RECORDS], list3[MAX_RECORDS],temp1[MAX_RECORDS],temp2[MAX_RECORDS];


	
/*-------------------------------------------------MAIN FUNCTION STARTS HERE----------------------------------------------------------*/

int main()
{
	int option,i,no_stu,size,k,p,size_l1, size_l2,size_l3,ch;size_l3=size_l1+size_l2; int kth;
	char name[MAX_NAME],choice='y'; 
	int rollno; 
	char sub_code[MAX_CODE]; 
	int marksi;
	
 	printf("STUDENT RECORD\n");
 	printf("Roll_no and Subject_code are the keys for this record\n");
 	printf("Enter the number of student in your class\n");
 	scanf("%d",&no_stu);
 	size=no_stu;size_l1=no_stu;size_l2=no_stu;
 	initialize(student_record,MAX_RECORDS);
 	initialize(list1,MAX_RECORDS);
 	initialize(list2,MAX_RECORDS);
 	initialize(list3,MAX_RECORDS);
 	initialize(temp1,MAX_RECORDS);
 	initialize(temp2,MAX_RECORDS);
 	printf("Enter the entries into the student record\n");
 	for(i=0;i<no_stu;i++)
 	{
                printf("Enter Roll No. of Student\n");
		scanf("%d",&student_record[i].roll_no);
                printf("Enter Student name\n");
		scanf("%s",student_record[i].student_name);
                printf("Enter Subject Code\n");
		scanf("%s",student_record[i].subject_code);
                printf("Enter Marks Obtained\n");
		scanf("%d",&student_record[i].marks);
 	}
 	list_sort(student_record, size);
   	
   	while(choice!='n' || choice!='N')
   	{
   		printf("Plz Select the Action you want to perform on the record amongst these\n");
      		printf("\n1.Insert or update\n");
      		printf("\n2.Delete\n");
     		printf("\n3.Get No. of Records\n");
      		printf("\n4.Isempty or not\n");
      		printf("\n5.Isfull or not\n");
      		printf("\n6.Get max marks in particular subject\n");
      		printf("\n7.Find_topper\n");
      		printf("\n8.Find_kth_popular_subject\n");
      		printf("\n9.Find_failures\n");
      		printf("\n10.list_unique\n");
      		printf("\n11.list_union\n");
      		printf("\n12.list_intersection\n");
      		printf("\n13.list_difference\n");
      		printf("\n14.list_symmetric_difference\n\n");
      		printf("\nEnter your choice\n");
      		scanf("%d",&option);
	
		switch(option)
      		{
    			case 1:
       			printf("Enter all the following details of the student you want to add into the record\n");
       			printf("Enter Roll No. of Student\n");
			scanf("%d",&rollno);
                	printf("Enter Student name\n");
			scanf("%s",name);
               		printf("Enter Subject Code\n");
			scanf("%s",sub_code);
                	printf("Enter Marks Obtained\n");
			scanf("%d",&marksi);
        		insert(student_record, MAX_RECORDS, name, rollno, sub_code, marksi);
        		list_sort(student_record,size);
         		break;
        		
	  		case 2:
        		printf("Enter all the following details of the student you want to delete from the record\n");
       			printf("Enter Roll No. of Student\n");
			scanf("%d",&rollno);
                	printf("Enter Subject Code\n");
			scanf("%s",sub_code);
         		delete(student_record, size, rollno, sub_code);
         		list_sort(student_record, size);
         		break;
         		
         		case 3:
         		getNumRecords(student_record, size);
         		list_sort(student_record, size);
         		break;
         		
         		case 4:
         		isEmpty(student_record, size);
         		list_sort(student_record, size);
         		break;
	 		
	 		case 5:
         		isFull(student_record,size);
         		list_sort(student_record, size);
         		break;
         		
         		case 6:
         		getMaxMarks(student_record, size, sub_code);
         		list_sort(student_record, size);
         		break;
         		
         		case 7:
         		Find_topper(student_record, size);
         		list_sort(student_record, size);
         		break;
         		
        		case 8:
         		printf("Plz enter the value of k\n");
         		scanf("%d",&kth);
         		Find_Kth_popular_subject(student_record,kth,size);
         		list_sort(student_record, size);
         		break;
         		
         		case 9:
         		printf("Plz enter the cutoff marks\n");
         		scanf("%d",&p);
         		printf("Plz enter the minimum no. of subjects the student needs to pass\n");
         		scanf("%d",&k);
         		Find_failures(student_record, size, k, p);
         		list_sort(student_record, size);
         		break;
         		
	      		case 10:
         		list_unique(student_record, size);
         		list_sort(student_record, size);
         		break;
         		
            		case 11:
            		printf("Plz enter list1\n");
            		for(i=0;i<size_l1;i++)
 			{
                		printf("Enter Roll No. of Student\n");
				scanf("%d",&list1[i].roll_no);
                		printf("Enter Student name\n");
				scanf("%s",list1[i].student_name);
                		printf("Enter Subject Code\n");
				scanf("%s",list1[i].subject_code);
                		printf("Enter Marks Obtained\n");
				scanf("%d",&list1[i].marks);
 			}
 			printf("\n\nPlz enter list2\n");
 			for(i=0;i<size_l2;i++)
 			{
                		printf("Enter Roll No. of Student\n");
				scanf("%d",&list2[i].roll_no);
                		printf("Enter Student name\n");
				scanf("%s",list2[i].student_name);
                		printf("Enter Subject Code\n");
				scanf("%s",list2[i].subject_code);
                		printf("Enter Marks Obtained\n");
				scanf("%d",&list2[i].marks);
 			}
         		list_union(list1, list2,list3, size_l1, size_l2);
         		list_sort(list1, size_l1);
         		list_sort(list2, size_l2);
         		list_sort(list3, size_l3);
         		break;
         		
         		case 12:
         		printf("\n\nPlz enter list1\n");
            		for(i=0;i<size_l1;i++)
 			{
                		printf("Enter Roll No. of Student\n");
				scanf("%d",&list1[i].roll_no);
                		printf("Enter Student name\n");
				scanf("%s",list1[i].student_name);
                		printf("Enter Subject Code\n");
				scanf("%s",list1[i].subject_code);
                		printf("Enter Marks Obtained\n");
				scanf("%d",&list1[i].marks);
 			}
 			printf("\n\nPlz enter list2\n");
 			for(i=0;i<size_l2;i++)
 			{
                		printf("Enter Roll No. of Student\n");
				scanf("%d",&list2[i].roll_no);
                		printf("Enter Student name\n");
				scanf("%s",list2[i].student_name);
                		printf("Enter Subject Code\n");
				scanf("%s",list2[i].subject_code);
                		printf("Enter Marks Obtained\n");
				scanf("%d",&list2[i].marks);
 			}
         		list_intersection(list1, list2, size_l1, size_l2);
         		list_sort(list1, size_l1);
         		list_sort(list2, size_l2);
         		list_sort(list3, size_l3);
         		break;
         		
        		case 13:
        		printf("\n\nPlz enter list1\n");
            		for(i=0;i<size_l1;i++)
 			{
                		printf("Enter Roll No. of Student\n");
				scanf("%d",&list1[i].roll_no);
                		printf("Enter Student name\n");
				scanf("%s",list1[i].student_name);
                		printf("Enter Subject Code\n");
				scanf("%s",list1[i].subject_code);
                		printf("Enter Marks Obtained\n");
				scanf("%d",&list1[i].marks);
 			}
 			printf("\n\nPlz enter list2\n");
 			for(i=0;i<size_l2;i++)
 			{
                		printf("Enter Roll No. of Student\n");
				scanf("%d",&list2[i].roll_no);
                		printf("Enter Student name\n");
				scanf("%s",list2[i].student_name);
                		printf("Enter Subject Code\n");
				scanf("%s",list2[i].subject_code);
                		printf("Enter Marks Obtained\n");
				scanf("%d",&list2[i].marks);
 			}
         		list_difference(list1, list2, list3, size_l1, size_l2);
         		list_sort(list1, size_l1);
         		list_sort(list2, size_l2);
         		list_sort(list3, size_l3);
         		break;
         		
         		case 14:
         		printf("\n\nPlz enter list1\n");
            		for(i=0;i<size_l1;i++)
 			{
                		printf("Enter Roll No. of Student\n");
				scanf("%d",&list1[i].roll_no);
                		printf("Enter Student name\n");
				scanf("%s",list1[i].student_name);
                		printf("Enter Subject Code\n");
				scanf("%s",list1[i].subject_code);
                		printf("Enter Marks Obtained\n");
				scanf("%d",&list1[i].marks);
 			}
 			printf("\n\nPlz enter list2\n");
 			for(i=0;i<size_l2;i++)
 			{
                		printf("Enter Roll No. of Student\n");
				scanf("%d",&list2[i].roll_no);
                		printf("Enter Student name\n");
				scanf("%s",list2[i].student_name);
                		printf("Enter Subject Code\n");
				scanf("%s",list2[i].subject_code);
                		printf("Enter Marks Obtained\n");
				scanf("%d",&list2[i].marks);
 			}
         		list_symmetric_difference(list1, list2,size_l1,size_l2);
         		list_sort(list1, size_l1);
         		list_sort(list2, size_l2);
         		list_sort(list3, size_l3);
         		break;
         	
         		default:break;
         	}
         	
         	printf("\nDo you want to continue(y/n)?\n");
         	fflush(stdin);
         	scanf("%c",&choice);	
         }
return 0;
}


/*----------------------------------------------------//MAIN FUNCTION ENDS HERE-----------------------------------------------------------*/


//INITIALIZE FUNCTION//
/*----------------------------------------------------------------------------------------------------------------------------------------*/

void initialize(struct student_record_tag s[], int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		s[i].student_name[0]='\0';
		s[i].roll_no=0;
		s[i].marks=-1;
		s[i].subject_code[0]='\0';
		
	}
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/


//1.INSERT FUNCTION IN STRUCTURE RECORD//
void insert(struct student_record_tag student_record[], int size, char n[], int r, char code[], int m)
{
	int i,j,found;int free_index;
	i=0;found=0;
	
	while(i<size && found==0)
	{
		if((student_record[i].roll_no==r) && (strcmp(student_record[i].subject_code,code))==0)
		{
			found=1;
		}
		else
		{
			i++;
		}
	}
	if(found==1)
	{
		strcpy(student_record[i].student_name, n);
		student_record[i].marks=m;
		printf("Record Successfullly Inserted\n");
	}
	else
	{
		free_index==-1;
		i=0;
		while(i<20 && free_index == -1)
		{
			if(student_record[i].roll_no == 0)
			{
				free_index=1;
			}
			else
			{
				i++;
			}
		}
	}
	if(free_index== -1)
	{
		printf("Array Full\n");
	}
	else
	{
		strcpy(student_record[i].student_name, n);
		student_record[i].roll_no=r;
		strcpy(student_record[i].subject_code,code);
		student_record[free_index].marks=m;
		printf("Record Successfullly Inserted\n");
	}
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

//2.DELETE FUNCTION STARTS HERE//

/*----------------------------------------------------------------------------------------------------------------------------------------*/
void delete(struct student_record_tag student_record[], int size, int r, char code[])
{
	int i,j,found;
	i=0;found=0;
	
	while(i<size && found==0)
	{
		if((student_record[i].roll_no==r) && (strcmp(student_record[i].subject_code,code))==0)
		{
			found=1;
		}
		else
		{
			i++;
		}
	}
	if(found==1)
	{
	        student_record[i].student_name[0]='\0';
		student_record[i].roll_no=0;
		student_record[i].marks=-1;
		student_record[i].subject_code[0]='\0';
		printf("Record DELETED\n");
	}
	else
	{
		printf("FAILURE\n");
	}	
}
/*----------------------------------------------------------------------------------------------------------------------------------------*/


//3.getNumRecords starts here//

void getNumRecords(struct student_record_tag student_record[], int size)
{
	int i=0,count=0,flag=0;
	while(i<size && flag==0)
	{
		if(student_record[i].roll_no != 0 && student_record[i].subject_code != '\0')
		{
			count++;
		}
		else{flag=1;}
		i++;
	}
	printf("The total number of records currently filled in this record are %d \n",count);
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

//4.isEmpty function starts here//

void isEmpty(struct student_record_tag student_record[], int size)
{
	int i=0,count=0, flag=0;
	while(i<size && flag==0)
	{
		if(student_record[i].roll_no != 0 && student_record[i].subject_code != '\0')
		{
			count++;
		}
		else{flag=1;}
		i++;
	}
	if(count==0)
	{
		printf("RECORD is EMPTY\n");	
	}
	else
	{
		printf("RECORD is NOT EMPTY\n");
	}
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

//5.isFull function starts here//

void isFull(struct student_record_tag student_record[], int size)
{
	int i=0,count=0, flag=0;
	while(i<size && flag==0)
	{
		if(student_record[i].roll_no != 0 && student_record[i].subject_code != '\0')
		{
			count++;
		}
		else{flag=1;}
		i++;
	}
	if(count==size)
	{
		printf("FULL\n");	
	}
	else
	{
		printf("NOT FULL\n");
	}
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

//6.getMaxMarks function starts here//

void getMaxMarks(struct student_record_tag student_record[], int size, char subject_code[])
{
	struct maxrecords
	{
   		int rollnum;
   		char subject[MAX_CODE];
   		char name[MAX_NAME];
	};
	struct maxrecords rec;
  	int i,max=0,j=-1;
  	char sub[MAX_CODE];
  	printf("Enter the subject code for whose u want Max Marks\n");
 	scanf("%s",sub);
  	while(i<size)
  	{
    		if(strcmp(student_record[i].subject_code,sub)==0)
    		{
     			if(student_record[i].marks>max)
     			{
      				max=student_record[i].marks;
      				j=i;
     			}
     			else
     			{
      				i++;
     			}
    		}
    		else
    		{
     			i++;
    		}
   	}
   	rec.rollnum=student_record[j].roll_no;
   	strcpy(rec.subject,student_record[j].subject_code);
   	strcpy(rec.name,student_record[j].student_name);
   	printf("The max marks obtained in %s subject are %d and are obtained by %s.\n",rec.subject, max, rec.name);
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/



//7.Find_topper function starts here//

void Find_topper(struct student_record_tag student_record[], int size)
{
	int i,j,total,k,max=0;
  	char name[MAX_NAME];int rollnum;
  	for(i=0;i<size;i++)
  	{
    		total=0;
     		for(j=0;j<size;j++)
     		{
       			if(student_record[j].roll_no==student_record[i].roll_no)
       			{
        			total=total+student_record[j].marks;
       			}
     			if(total>max)
           		{
              			max=total;
              			k=j;
           		}
       		}
    	}
   rollnum=student_record[k].roll_no;
   strcpy(name,student_record[k].student_name);
   printf("Topper is: Roll no. %d and Name is  %s\n\n",rollnum, name);
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/


//8.Find_Kth_popular_subject function starts here//

void Find_Kth_popular_subject(struct student_record_tag student_record[],int ks, int size)
{
	int i,j,l=0,div=0,sorted=0,temp; char code[MAX_CODE];
	struct popular_subject_tag
	{
		char subject_code[MAX_CODE];
		int avg_marks;
	}pop_subject[MAX_SUBJECTS];
	for(i=0;i<size;i++)
	{
		pop_subject[i].subject_code[0]='\0';
		pop_subject[i].avg_marks= 0;	
	}
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if(strcmp(student_record[i].subject_code,student_record[j].subject_code)==0)
			{
				pop_subject[l].avg_marks+=student_record[j].marks;
				strcpy(pop_subject[l].subject_code,student_record[i].subject_code);
				div++;
			}
		}
		pop_subject[l].avg_marks=pop_subject[l].avg_marks/div;
		l++;
	}
	for(i=0;i<size-1 && sorted==0; i++)
	{
		sorted=1;
		for(j=0;j<size-i-1;j++)
		{
			if(pop_subject[j].avg_marks>pop_subject[j+1].avg_marks)
			{
				temp=pop_subject[j].avg_marks;
				pop_subject[j].avg_marks=pop_subject[j+1].avg_marks;
				pop_subject[j+1].avg_marks=temp;
				strcpy(code,pop_subject[j].subject_code);
				strcpy(pop_subject[j].subject_code,pop_subject[j+1].subject_code);
				strcpy(pop_subject[j+1].subject_code,code);
				sorted=0;
			}
		}
	}
	printf("Kth popular subject is: %s\n",pop_subject[ks-1].subject_code);
}


/*----------------------------------------------------------------------------------------------------------------------------------------*/

//9.Find_failures function starts here//

void Find_failures(struct student_record_tag student_record[], int size, int k, int p)
{
	struct failures
	{
		int rollno;
		int count;
		char stu_name[MAX_NAME];
	}failures[MAX_RECORDS];
	
	int i=0,count=0,j,l=0,m,flag=0;
	for(l=0;l<size;l++)
	{
		failures[l].count=0;
		failures[l].rollno=0;
		failures[l].stu_name[0]='\0';
	}l=0;
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if(student_record[j].roll_no == student_record[i].roll_no)
			{
				if(student_record[j].marks < p)
				{
					failures[l].count+=1;
					failures[l].rollno=student_record[j].roll_no;
					strcpy(failures[l].stu_name,student_record[j].student_name);
				}
			}
		}
		l++;		
	 }
	 for(i=0;i<l;i++)
	 {
	 	if(failures[i].count >= k)
	 	{
	 		printf("\nStudent with Roll No. %d named %s has failed\n",failures[i].rollno, failures[i].stu_name);
	 		flag=1;
	 	}
	 }
	 if(flag==0)
	 {
	 	printf("\nAll the students have passed\n");
	 }
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/

//10.list_unique function starts here//

void list_unique(struct student_record_tag student_record[],int size)
{

     	int i,j,sta_code=0;
     	for(i=0;i<size;i++)
     	{
      		for(j=i+1;j<size;j++)
      		{
       			if(student_record[j].roll_no==student_record[i].roll_no && strcmp(student_record[j].subject_code,student_record    [i].subject_code)==0)
       			{
         			student_record[j].student_name[0]='\0';
          			student_record[j].roll_no=0;
           			student_record[j].subject_code[0]='\0';
            			student_record[j].marks=-1;
            			sta_code=1;
       			}
      		}
      		
     	}
     	if(sta_code==1)
      	printf("Duplicate Entries removed\n");
      	else
      	printf("No Duplicate Entries found\n");  
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/




//11.list_union function starts here//

void list_union(struct student_record_tag list1[], struct student_record_tag list2[], struct student_record_tag list3[], int size_l1, int size_l2)
{
	int i,j,k=0,l,size_l3;
	size_l3=size_l1+size_l2;
	for(i=0;i<size_l1;i++)
	{
			strcpy(list3[i].student_name,list1[i].student_name);
          		list3[i].roll_no=list1[i].roll_no;
           		strcpy(list3[i].subject_code,list1[i].subject_code);
            		list3[i].marks=list1[i].marks;
	}
	for(j=i+1;j<size_l3;j++)
	{
			strcpy(list3[j].student_name,list2[k].student_name);
          		list3[j].roll_no=list2[k].roll_no;
           		strcpy(list3[j].subject_code,list2[k].subject_code);
            		list3[j].marks=list2[k].marks;
            		k++;
	}
	list_unique(list3, size_l3);
	printf("\nUnion of list 1 and list 2\n");
	printf("List3 is\n");
	for(l=0;l<size_l3;l++)
 	{
                printf("%d\n", list3[l].roll_no);
		printf("%s\n", list3[l].student_name);
		printf("%s\n", list3[l].subject_code);
		printf("%d\n", list3[l].marks);
	}

}
 


/*----------------------------------------------------------------------------------------------------------------------------------------*/


//12.list_intersection function starts here//

void list_intersection(struct student_record_tag list1[], struct student_record_tag list2[], int size_l1, int size_l2)
{
	int i,j,k=0,l,size_l3;int flag;
	size_l3=size_l1+size_l2;
	if(size_l1>size_l2)
	{
     		for(i=0;i<size_l1;i++)
     		{flag=0;
      			for(j=0;j<size_l2 &&flag==0;j++)
      			{
       				if(list2[j].roll_no==list1[i].roll_no && strcmp(list2[j].subject_code, list1[i].subject_code)==0)
       				{
         				strcpy(list3[k].student_name, list1[i].student_name);
          				list3[k].roll_no=list1[i].roll_no;
           				strcpy(list3[k].subject_code, list1[i].subject_code);
            				list3[k].marks=list1[i].marks;
            				flag=1;k++;
       				}
      			}
      		}
      	}
      	else
      	{
      		for(i=0;i<size_l2;i++)
     		{flag=0;
      			for(j=0;j<size_l1 &&flag==0;j++)
      			{
       				if(list1[j].roll_no==list2[i].roll_no && strcmp(list1[j].subject_code, list2[i].subject_code)==0)
       				{
         				strcpy(list3[k].student_name, list2[i].student_name);
          				list3[k].roll_no=list2[i].roll_no;
           				strcpy(list3[k].subject_code, list2[i].subject_code);
            				list3[k].marks=list2[i].marks;
            				flag=1;k++;
       				}
      			}
      	}
      		
     	}
	printf("\nIntersection of list 1 and list 2\n");
	printf("List3 is\n");
	for(l=0;l<k;l++)
 		{
                	printf("%d\n", list3[l].roll_no);
			printf("%s\n", list3[l].student_name);
			printf("%s\n", list3[l].subject_code);
			printf("%d\n", list3[l].marks);
		}

}


/*----------------------------------------------------------------------------------------------------------------------------------------*/


//13.list_difference function starts here//

void list_difference(struct student_record_tag list1[], struct student_record_tag list2[],struct student_record_tag list3[], int size_l1, int size_l2)
{
	int i=0,count=0,j,k=0;int found=0,l;
	for(i=0;i<size_l1;i++)
     	{
       		found=0;
       		for(j=0; j<size_l2 && found==0;j++)			 
       		{
         		if(list1[i].roll_no==list2[j].roll_no &&(strcmp(list1[i].subject_code, list2[j].subject_code)==0))
         		{		
         			found=1;
         		}
		}
       		if(found==0)
       		{
         		list3[k]=list1[i];
         		k++;
       		}
       }
       printf("\nDiffernce of list 1 and list 2\n");
       printf("List3 is\n");
	for(l=0;l<k;l++)
 		{
                	printf("%d\n", list3[l].roll_no);
			printf("%s\n", list3[l].student_name);
			printf("%s\n", list3[l].subject_code);
			printf("%d\n", list3[l].marks);
		}
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/



//14.list_symmetric_difference function starts here//

void list_symmetric_difference(struct student_record_tag list1[], struct student_record_tag list2[], int size_l1, int size_l2)
{
	int l;int size_l3=size_l1+size_l2;
	struct student_record_tag ;
	list_difference(list1,list2,temp1,size_l1,size_l2);
	list_difference(list2,list1,temp2,size_l1,size_l2);
	list_union(temp1,temp2,list3,size_l1,size_l2);
	printf("\nSymmetric Differnce of list 1 and list 2\n");
       	printf("List3 is\n");
	for(l=0;l<size_l3;l++)
 		{
                	printf("%d\n", list3[l].roll_no);
			printf("%s\n", list3[l].student_name);
			printf("%s\n", list3[l].subject_code);
			printf("%d\n", list3[l].marks);
		}
}

/*----------------------------------------------------------------------------------------------------------------------------------------*/






/*----------------------------------------------------------------------------------------------------------------------------------------*/


//list_sort function starts here//
void list_sort(struct student_record_tag student_record[], int size)
{
	int i,j,temp,sorted=0;char name[MAX_NAME],code[MAX_CODE];
	for(i=0;i<size-1 && sorted==0; i++)
	{
		sorted=1;
		for(j=0;j<size-i-1;j++)
		{
			if(student_record[j].roll_no>student_record[j+1].roll_no)
			{
				temp=student_record[j].roll_no;
				student_record[j].roll_no=student_record[j+1].roll_no;
				student_record[j+1].roll_no=temp;
				strcpy(name,student_record[j].student_name);
				strcpy(student_record[j].student_name,student_record[j+1].student_name);
				strcpy(student_record[j+1].student_name,name);
				temp=student_record[j].marks;
				student_record[j].marks=student_record[j+1].marks;
				student_record[j+1].marks=temp;
				strcpy(code,student_record[j].subject_code);
				strcpy(student_record[j].subject_code,student_record[j+1].subject_code);
				strcpy(student_record[j+1].subject_code,code);
				sorted=0;
			}
		}
	}
}





/*------------------------------------------------------****************************------------------------------------------------------*/



