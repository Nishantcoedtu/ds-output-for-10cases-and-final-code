#include <stdio.h>
#include <stdlib.h>
int a, i;
struct node                           //structure to create nodes for stack
{
    int val;
    struct node *next;
} * top, *ptr, *newptr, *temp;
struct node *create_ptr(int a)       //Function to create new node
{
    newptr = (struct node *)malloc(sizeof(struct node));
    newptr->val = a;
    newptr->next = NULL;
    return newptr;
}
void push(int val)                   //push function
{
    ptr = create_ptr(val);
    if (top == NULL)
        top = ptr;
    else
    {
        ptr->next = top;
        top = ptr;
    }
}
void pop()                            //pop function
{
    if (top == NULL)
        printf("\n!!!!!!!UNDERFLOW!!!!!!!\n");
    else
    {
        temp = top;
        top = top->next;
        free(temp);
    }
}

// using commandline arguments
int main(int argc,char *argv[])
{
    int count, line = 0, flag = 0, i, j;
    char str[100], ch;
    FILE *fp;
//argc should be equal to 2 ,first is application name and second is file name whose indentation is to be checked
    if(argc!=2)
    {
    	printf("\nInvalid argument");
    	exit(1);
	}
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("File not found");
        exit(1);
    }
    while (fgets(str, sizeof(str), fp))
    {
        count = 0;

        printf("%s", str);
        if (flag == 0)
        {
            line++;
            for (i = 0; i < sizeof(str); i++)
            {
                if (str[i]== ' ')
                    count++;
                else if(str[i]=='\t')
                count+=8;
                else
                    break;
            }
            if ((top != NULL) && (count < top->val))
            {
                pop();
                if(top==NULL)
                {
                	flag=1;
				}
                else if (count == top->val)
                    continue;
                else
                    flag = 1;
            }
            else if ((top == NULL) || (count > top->val))
            {
                push(count);
            }
        }
    }
    
    if (flag == 0)
    {
        printf("\nThis file is properly indented\n");
    }
    else
        printf("\nError at line %d , NOT properly indented\n", line);
    fclose(fp);
}
