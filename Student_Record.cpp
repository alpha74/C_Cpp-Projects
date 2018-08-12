#include<stdio.h>
#include<conio.h>
#include<string.h>
#define s_string 50
#define max_rec 10
struct library_rec
{
	char name_book[s_string];
	char author_name[s_string];
	int year_publication;
	int num_avail_copies;
};


   
   void self(struct library_rec records[],int lo,int mid, int hi);
   void sort(struct library_rec records[],int lo,int hi);
   void swap(struct library_rec records1,struct library_rec records2);
   void contin_self(struct library_rec records[]);
   void display(struct library_rec records[]);
   void set(struct library_rec records[]);
   void list_insert(struct library_rec records[],int num);
   void delete_rec(struct library_rec records[]);
   int getNumRec(struct library_rec records[]);
   int isEmpty(struct library_rec records[]);
   int isFull(struct library_rec records[]);
   void topAuthor(struct library_rec records[]);
   void sort(struct library_record[]);
   void popularAuthor(struct library_rec records[]);
   void KthPopular(struct library_rec records[],int k);
   //void list_unique(struct library_rec records[]);
   void union_list(struct library_rec list1[],struct library_rec list2[],struct library_rec list3[],int n1,int n2);
   void intersection(struct library_rec list1[],struct library_rec list2[],struct library_rec list3[],int n1,int n2);
   void difference(struct library_rec list1[],struct library_rec list2[],struct library_rec list3[], int n1,int n2);
   void symmetric_difference(struct library_rec list1[],struct library_rec list2[],struct library_rec list3[],int n1,int n2);

int main()
{
	int num1,num2,k,entry,year_publish,num_copies;
	char book_name[s_string],author_name[s_string],option;
	
	struct library_rec records[max_rec],list1[max_rec],list2[max_rec],list3[max_rec];
	
   set(records);
   set(list1);
   set(list2);
   set(list3);
	

   
  	  printf("\n1.Insert\n2.Delete\n3.Display\n4.Get Number of Records\n 5. isEmpty\n6. isFull\n 7. Topmost Book Author\n8.Most Popular Author\n 9. Kth Popular Book \n10. List Unique\n ");
      printf("11. Union\n  12.Intersection\n 13. Difference \n14. Symmetric Difference \n");
      
      while(option!='N')
      {
      		printf("\nenter ur choice : ");
      		scanf("%d",&entry);
			switch(entry)
      	{
        	case 1:
         		printf("enter num of records you want to insert : ");
				scanf("%d",&num1);
				list_insert(records,num1);
                sort(records,0,getNumRec(records)-1);
                break;
                
       	 	case 2:
                printf("\n Enter the details of Record to be deleted ");
                printf("\n Enter the author name: ");
                scanf("%s",author_name);
                printf("\n Enter the book name: ");
                scanf("%s",book_name);
                delete_rec(records);
                
                sort(records,0,getNumRec(records)-1);
                
                break;
        	case 3: display(records);
                break;
        	case 4: 
                printf("\n The number of active records are : %d ",getNumRec(records));
                break;
        	case 5:
               if(isEmpty(records)==0)
               {
                 printf("\n The records are EMPTY");
               }
               else
               {
                 printf("\n The records are NOT EMPTY");
               }
               break;
        	case 6:
               if(isFull(records)==1)
               {
                 printf("\n The records are FULL");
               }
               else
               {
                 printf("\n The records are NOT FULL");
               }
               break;
        	case 7:
		
			    topAuthor(records);       
			   
               break;
               
        	case 8:
               popularAuthor(records);
    		   break;
        	case 9:
			 printf("\n Enter the value of k: ");
             scanf("%d",&k);
             KthPopular(records,k);
             break;

        /*case 10:
				unique(records);
                break;
                */
                
        	case 11:
				 printf("enter num : ");
				 scanf("%d",&num1);	
				 list_insert(list1,num1);
				 printf("enter num : ");
				 scanf("%d",&num2);
        		 list_insert(list2,num2);
                 union_list(list1,list2,list3,num1,num2);
                 printf("\n The union of the list is :");

                 display(list3);
                 break;
                 
        	case 12: printf("enter num : ");
				 scanf("%d",&num1);	
				 list_insert(list1,num1);
				 printf("enter num : ");
				 scanf("%d",&num2);
        		 list_insert(list2,num2);
                 intersection(list1,list2,list3,num1,num2);
                 printf("\n The intersection of the list is :");

                 display(list3);
                 
                 break;
                 
        	case 13:
        		 printf("enter num : ");
				 scanf("%d",&num1);	
				 list_insert(list1,num1);
				 printf("enter num : ");
				 scanf("%d",&num2);
        		 list_insert(list2,num2);
                 difference(list1,list2,list3,num1,num2);
                 printf("\n The difference of the list is :");

                 display(list3);
                 break;
                 
        	case 14: printf("enter num : ");
				 scanf("%d",&num1);	
				 list_insert(list1,num1);
				 printf("enter num : ");
				 scanf("%d",&num2);
        		 list_insert(list2,num2);
                 symmetric_difference(list1,list2,list3,num1,num2);
                 printf("\n The difference of the list is :");

                 display(list3);
                 break;
                
        	default:break;
      }
      
      printf("\ndo you want to continue(Y/N) : ");
      fflush(stdin);
      scanf("%c",&option);
      
  }
      
}

 
void self(struct library_rec records[],int lo,int mid, int hi)
{
	int i,j,k;
	i=lo;
	j=mid+1;
	k=lo;
	struct library_rec temp[max_rec];
	while(i<=mid && j<=hi)
	{
		if(strcmp(records[i].author_name,records[j].author_name)<0)
		{
		      strcpy(temp[k].name_book,records[i].name_book);
		      strcpy(temp[k].author_name,records[i].author_name);		     
			  temp[k].year_publication=records[i].year_publication;
		      temp[k].num_avail_copies=records[i].num_avail_copies;
		      k++;
		      i++;
		}
		
		else
		{
			  strcpy(temp[k].name_book,records[j].name_book);
		      strcpy(temp[k].author_name,records[j].author_name);
		      temp[k].year_publication=records[j].year_publication;
		      temp[k].num_avail_copies=records[j].num_avail_copies;
		      k++;
		      j++;
		}
	}
	
	if(i<=mid)
	{
		while(i<=mid)
		{
			  strcpy(temp[k].name_book,records[i].name_book);
		      strcpy(temp[k].author_name,records[i].author_name);
		      temp[k].year_publication=records[i].year_publication;
		      temp[k].num_avail_copies=records[i].num_avail_copies;
		      k++;
		      i++;
		}
	}
	else
	{
		while(j<=hi)
		{
			  strcpy(temp[k].name_book,records[j].name_book);
		      strcpy(temp[k].author_name,records[j].author_name);
		      temp[k].year_publication=records[j].year_publication;
		      temp[k].num_avail_copies=records[j].num_avail_copies;
		      k++;
		      j++;
		}
	}
	
	for(i=0;i<=hi;i++)
	{
		strcpy(records[i].name_book,temp[i].name_book);
		strcpy(records[i].author_name,temp[i].author_name);
		records[i].year_publication = temp[i].year_publication;
		records[i].num_avail_copies = temp[i].num_avail_copies;
	}
}

void sort(struct library_rec records[],int lo,int hi)
{
	int mid;
	int i;
	mid=(lo+hi)/2;
	if(lo<hi)
	{
		sort(records,lo,mid);
		sort(records,mid+1,hi);
		
		self(records,lo,mid,hi);
	}
	
	contin_self(records);
}

void swap(struct library_rec records1,struct library_rec records2)
{
	struct library_rec temp;
				strcpy(temp.name_book,records1.name_book);
				strcpy(temp.author_name,records1.author_name);
				temp.year_publication=records1.year_publication;
				temp.num_avail_copies=records1.num_avail_copies ;
				
				strcpy(records1.name_book,records2.name_book);
				strcpy(records1.author_name,records2.author_name);
				records1.year_publication=records2.year_publication;
				records1.num_avail_copies=records2.num_avail_copies ;
				
				strcpy(records2.name_book,temp.name_book);
				strcpy(records2.author_name,temp.author_name);
				records2.year_publication=temp.year_publication;
				records2.num_avail_copies=temp.num_avail_copies ;
				
}
void contin_self(struct library_rec records[])
{
	int i;
	struct library_rec temp;
	
		strcpy(temp.name_book,records[0].name_book);
		strcpy(temp.author_name,records[0].author_name);
		temp.year_publication=records[0].year_publication;
		temp.num_avail_copies=records[0].num_avail_copies ;
	for(i=1;i<max_rec;i++)
	{
		if(strcmp(records[i].author_name,temp.author_name)==0)
		{
			if(strcmp(records[i].name_book,temp.name_book)<0)
			{
				swap(records[i],temp);
				
				strcpy(temp.name_book,records[i].name_book);
				strcpy(temp.author_name,records[i].author_name);
				temp.year_publication=records[i].year_publication;
				temp.num_avail_copies=records[i].num_avail_copies ;
				
			}
		}
	}
}


void display(struct library_rec records[])
{
	int i=0;
	for(;i<=max_rec;i++)
	{		
		printf("\n%s",records[i].name_book);
		printf("\n%s",records[i].author_name);
		printf("\n%d",records[i].year_publication);
		printf("\n%d",records[i].num_avail_copies);
	}
}



void set(struct library_rec records[])
{
	int i=0;
	for(;i<max_rec;i++)
	{
		strcpy(records[i].name_book,"");
		strcpy(records[i].author_name,"");
		records[i].year_publication = 0;
		records[i].num_avail_copies = 0;
	}
}


void list_insert(struct library_rec list[], int num)
{
       int i;
       
       for(i=0;i<num;i++)
       {
		if(strcmp(list[i].name_book,"\0")==0) //since there can't exist a record without a book name
		{
			fflush(stdin);
			printf("\nenter book name : ");
			gets(list[i].name_book);
			fflush(stdin);
			printf("\nenter name of author : ");
			gets(list[i].author_name);
			printf("\nenter the year of publication : ");
			scanf("%d",&list[i].year_publication);
			printf("\nenter number of available copies : ");
			scanf("%d",&list[i].num_avail_copies);
		}
		
	}
}

void delete_rec(struct library_rec records[])
{
	int i=0,found=0;
	printf("you are in the delete menu\n");
	char book[50],author[50];
	printf("enter book name and author which has to be deleted : ");
	fflush(stdin);
	scanf("%s %s",book,author);
	
	while(i<max_rec && found==0)
	{
		if(strcmp(records[i].name_book,book)==0 && strcmp(records[i].author_name,author)==0)
		{
			strcpy(records[i].name_book,"");
			strcpy(records[i].author_name,"");
			records[i].num_avail_copies=0;
			records[i].year_publication=0;
			found=1;	
		}
		i++;
	}
	
	if(found)
	printf("successfully deleted\n");
	
	else
	printf("record not found to be deleted\n");

}


int getNumRec(struct library_rec records[])
{
	int i=0,last=0,count=0;
	while(last==0 && i<=max_rec)
	{
		if(records[i].num_avail_copies==0)
		last=1;

		else
		count++;
		
		i++;
	}
	
	return(count);
}



int isEmpty(struct library_rec records[])
{
	int i=0,found=1;
	while(i<max_rec && found==1)
	{
		if(strcmp(records[i].author_name,"")!=0)
		found=0;
		
		else
		found=1;
		
		i++;
	}
	
	return(!found);
}

int isFull(struct library_rec records[])
{
	int i=0,found=1;
	while(i<max_rec && found==1)
	{
		if(strcmp(records[i].author_name,"")==0)
		found=0;
		
		i++;
	}
	
	return(found);
}

void topAuthor(struct library_rec records[])
{
	char name[30];
	int index,i=1;
	int flag=0;
	printf("enter the book name : ");
	fflush(stdin);
	scanf("%s",name);
	
	index=records[0].num_avail_copies;
	while(i<max_rec)			// finding the max of the num_avail_copies
	{
		if(strcmp(records[i].name_book,name)==0)
		{
			if(index < records[i].num_avail_copies)
			index = records[i].num_avail_copies;
			
			i++;		
		}
	}
	
	while(i<max_rec && flag==1)
	{
		if(index==records[i].num_avail_copies)			//comparing index with the existing records to find the top author 
		{
			printf("the top author : %s\n",records[i].author_name);
			flag=1;	
		}	
		
		i++;
	}	
	
	
}

void popularAuthor(struct library_rec records[])
{
	int index=0,sum=0,i=0,n;
    char a_name[50],p_author[50];
    n=getNumRec(records);
    strcpy(a_name,records[0].author_name);
    while(i<n)
    {
       if(strcmp(records[i].author_name,a_name)==0)
       {
         sum+=records[i].num_avail_copies;		// calculating the number of copies in the name of a particular author 
         if(sum>index)
         {
           index=sum;
           strcpy(p_author,records[i].author_name);
         }
       }
       else
       {
         strcpy(a_name,records[i].author_name);
         sum=records[i].num_avail_copies;
       }
       i++;
    }	
    
    printf("popular author is : %s\n",p_author);
}

void KthPopular(struct library_rec records[],int k)
{
	int n,i=0,j,t,flag=0,sorted=0;
	n=getNumRec(records);
	int a[n];
	for(i=0;i<n;i++)
	{
		a[i]=records[i].num_avail_copies;
	}
	
	for(i=0;i<n-1 && sorted==0;i++)
	{
		sorted=1;
		for(j=i;j<n-1-i;j++)					// bubble sorting the num_avail_copies values in the temp array
		{
			if(a[j]>a[j+1])
			{
				t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
				
				sorted=0;
			}
		}
	}
	
	for(i=0;i<n && flag==0;i++)
	{
		if(a[n-k]==records[i].num_avail_copies)
		flag=1;
	}
	
	if(flag)
	printf("%s\n",records[i].name_book);
}


void union_list(struct library_rec list1[],struct library_rec list2[],struct library_rec list3[],int n1, int n2) //merging function
  {
    int i,j,k;
    i=0;
    j=0;
    k=0;
    while((i<n1)&&(j<n2))
    {
      if(strcmp(list1[i].author_name,list2[j].author_name)<0)
      {
        list3[k++]=list1[i++];
      }
      else if(strcmp(list1[i].author_name,list2[j].author_name)>0)
      {
        list3[k++]=list2[j++];
      }
      else
      {
        if(strcmp(list1[i].name_book,list2[j].name_book)<0)
        {
          list3[k++]=list1[i++];
        }
        else if(strcmp(list1[i].name_book,list2[j].name_book)>0)
        {
          list3[k++]=list2[j++];
        }
        else
        {
          if(list1[i].year_publication>list2[j].year_publication)
          {
            list3[k++]=list1[i++];
            j++;
          }
          else
          {
            list3[k++]=list2[j++];
            i++;
          }
        }
      }
    }
    if(i<n1)
    {
      while(i<n1)
      {
        list3[k++]=list1[i++];
      }
    }
    else if(j<n2)
    {
      while(j<n1)
      {
        list3[k++]=list2[j++];
      }
    }
    
  }


  void intersection(struct library_rec list1[],struct library_rec list2[],struct library_rec list3[],int n1, int n2)
  {
    int i,j,k;
    i=0;
    j=0;
    k=0;
    while((i<n1)&&(j<n2))					// modification of union 
      if(strcmp(list1[i].author_name,list2[j].author_name)<0)
      {
        i++;
      }
      else if(strcmp(list1[i].author_name,list2[j].author_name)>0)
      {
        j++;
      }
      else
      {
        if(strcmp(list1[i].name_book,list2[j].name_book)<0)
        {
          i++;
        }
        else if(strcmp(list1[i].name_book,list2[j].name_book)>0)
        {
          j++;
        }
        else
        {
          if(list1[i].num_avail_copies<list2[j].num_avail_copies)
          {
            list3[k++]=list1[i++];
            j++;
          }
          else if(list1[i].num_avail_copies>list2[j].num_avail_copies)
          {
            list3[k++]=list2[j++];
            i++;
          }
          else
          {
          	list3[k++]=list2[j++];
            	i++;
          }
        }
      }
      
      
}
  

   void difference(struct library_rec list1[],struct library_rec list2[],struct library_rec list3[],int n1,int n2)
   {
     int i,j,k,found=0;
     i=0;j=0;k=0;
     for(i=0;i<n1;i++)
     {
       found=0;
       for(j=0;(j<n2)&&(found==0);j++)			 
       {
         if((strcmp(list1[i].author_name,list2[j].author_name)==0)&&(strcmp(list1[i].name_book,list2[j].name_book)==0))		// finding the common terms and not considering them.
         found=1;

       }
       if(found==0)
       {
         list3[k]=list1[i];		// placing the different terms in the list 3
         k++;
       }

     }
   }

   void symmetric_difference(struct library_rec list1[],struct library_rec list2[],struct library_rec list3[],int n1,int n2)
   {

     struct library_rec temp1[max_rec],temp2[max_rec];
     set(temp1);
     set(temp2);

     difference(list1,list2,temp1,n1,n2);		/*
     														since symmetric difference is commutative in nature
     											*/
     difference(list2,list1,temp2,n1,n2);		
     union_list(temp1,temp2,list3,n1,n2);		// merging the temporary records into one
     
   }
