#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int max=0;
int prime=0;
int arraySize=0;
int size=0;
int *bloomArray;
struct Data
{
    int key;
    int value;
};
struct HashTable
{
    int flag;
    //flag=0;data not present
    //flag=1;data present
    //flag=2;data that was present was deleted
    struct Data *item;
};
struct HashTable *array;
int hash1(int key)
{
    int h1;
    h1=key%size;
    return h1;
};
int hash2(int key)
{
    int h2;
    h2=prime-(key%size);
    return abs(h2);
};
int primeDeterminationForSize(int max)
{
    int i,j;
    for(i=max;;i++)
    {
        for(j=2;j<=i;j++)
        {
            if(i%j==0)
            {
                break;
            }
        }
        if(i==j)
            return i;
    }
};
//Array initialization
void initializeArray()
{
    int i=0;
    bloomArray=malloc(sizeof(int));
    for(i=0;i<size;i++)
    {
        array[i].flag=0;
        array[i].item=NULL;
        bloomArray[i]=0;
    }
}
//Inserting the value
void insert()
{
    //printf("Entered insert");
    if(arraySize==max)
    {
        printf("Hash Table is full. Insertion cannot be performed!");
    }
    else
    {
        //printf("Entered else");
        struct Data *newdata=(struct Data*)malloc(sizeof(struct Data));
        printf("Enter the key and its value:");
        scanf("%d%d",&newdata->key,&newdata->value);
        printf("\n%d,%d\n",newdata->key,newdata->value);
        int h1=hash1(newdata->key);
        int h2=hash2(newdata->key);
        bloomArray[h1]=1;
        bloomArray[h2]=1;
        int index=h1;
        int j=1;
        //printf("Hash1=%d\nHash2=%d\n",h1,h2);
        while(array[index].flag==1)
        {
            //printf("\nEntered loop flag 1");
            if(array[index].item->key==newdata->key)
            {
                int yesNo;
                printf("The given key matches the previously inserted key. Do you want to update?(press 1 for yes)\t");
                scanf("%d",&yesNo);
                if(yesNo==1)
                    array[h1].item->value=newdata->value;
            }
            else
            {
                index=(h1+j*h2)%max;
                j++;
            }
        }
    //  printf("\nEntered else loop");
        array[index].flag=1;
        array[index].item=newdata;
        arraySize++;
    //  printf("Index:%d\nKey:%d\nValue:%d\n",index,array[index].item->key,array[index].item->value);
    }
};
void deletion()
{
    int delkey,h1,h2,j=1;
    printf("Enter Key to be deleted:");
    scanf("%d",&delkey);
    if(arraySize==0)
        printf("No item present for deletion!");
    else
    {
        h1=hash1(delkey);
        int index=h1;
        h2=hash2(delkey);
        bloomArray[h1]=0;
        bloomArray[h2]=0;
        while(array[index].flag==1)
        {
            if(array[index].item->key==delkey)
            {
                //printf("Entered del loop");
                array[index].item=NULL;
                array[index].flag=2;
                break;
            }
            else
            {
                index=(h1+j*h2)%size;
                j++;
            }
        }
        arraySize--;
    }
}
void printValue(int size)
{
    int i=0;
    printf("\nPrinting the HashTable array:\nKey\tValue\tIndex\n");
    for(i=0;i<size;i++)
    {
        if(array[i].flag==0||array[i].flag==2)
            continue;
        else
            printf("%d\t%d\t%d\n",array[i].item->key,array[i].item->value,i);
    }
};
void bloomSearch()
{
    if(arraySize==0)
        printf("Array is empty!");
    else
    {
        int h1,h2,j=1,searchkey,flag;
        //char flag;
        printf("Enter key to be searched:");
        scanf("%d",&searchkey);
        h1=hash1(searchkey);
        h2=hash2(searchkey);
        if(bloomArray[h1]==1&&bloomArray[h2]==1)
        {
            printf("\nThe %d maybe present",searchkey);
            printf("\nDo you want to do a deep search(1/0)?\t");
            scanf("%d",&flag);
            //if(flag=='y'||flag=='Y')
            if(flag==1)
            {
                int index=hash1(searchkey);
                while(array[index].flag==1)
                {
                    if(array[index].item->key==searchkey)
                    {
                        //printf("Entered search loop");
                        printf("\nThe key %d is found at %d\n",searchkey,index);
                        break;
                    }
                    else
                    {
                        index=(h1+j*h2)%size;
                        j++;
                    }
                }
            }
            else
            {
                 printf("\n%d is not present",searchkey);
                 return;
            }
        }
        else
            printf("\n%d is not present",searchkey);
    }
}
void sizeDisplay()
{
    printf("The maximum size of the Hash Table :    %d\nThe number of elements present :   %d",size,arraySize);
}
int main()
{
    printf("Enter the maximum number of values to be hashed:");
    scanf("%d",&max);
    printf("Enter the prime for second hashing:");
    scanf("%d",&prime);
    size=primeDeterminationForSize(max);
    //printf("max=%d\nprime=%d\nsize=%d",max,prime,size);
    array=(struct HashTable*)malloc(size*sizeof(struct HashTable));
    initializeArray();
    int choice=1;
    printf("\nEnter your choice:\n\t1.Insert a value\n\t2.Print the value array\n\t3.Delete a value\n\t4.Display the array size\n\t5.Search using bloom filter\n Enter Choice:");
    scanf("%d",&choice);
    while (choice!=0)
    {
        switch(choice)
        {
        case 1:
            {
                insert();
                break;
            }
        case 2:
            {
                printValue(size);
                break;
            }
        case 3:
            {
                deletion();
                break;
            }
        case 4:
            {
                sizeDisplay();
                break;
            }
        case 5:
            {
                bloomSearch();
                break;
            }
        default:
            printf("Enter correct choice!");
        }
        printf("\nEnter your choice:\n\t1.Insert a value\n\t2.Print the value array\n\t3.Delete a value\n\t4.Display the array size\n\t5.Search using bloom filter\n Enter Choice:");
        scanf("%d",&choice);
    }
    return 0;
}
