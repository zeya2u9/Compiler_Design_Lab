#include<stdio.h>
#include<string.h>

int main()
{
        FILE *ptr;
        int i,j,k,m,n,len,a[10][10],temp,b[20];
        ptr=fopen("file.txt","r");
        i=0;
        j=0;
        while(!feof(ptr))
        {
                fscanf(ptr,"%d",&temp);
                a[i][j]=temp; //printf("temp=%d\n",temp);
                j++;
                if(j%4==0)
                {
                        i++;
                        j=0;
                }
        }
        m=i;n=j;
        /*for(i=0;i<m;i++)
        {
                for(j=0;j<n;j++)
                        printf("%d ",a[i][j]);
                printf("\n");
        }*/
        fclose(ptr);
        printf("\nInput the length of string\n");
        scanf("%d",&len);
        printf("Enter string:\n");
        for(i=0;i<len;i++)
                scanf("%d",&b[i]);
        j=0;
        for(i=0;i<len;i++)
        {
                        if(b[i]==0)
                        {
                                j++;
                                printf("State=%d\n",a[j][3]);
                                j=2*(a[j][3]-1);
                        }
                        else
                        {
                                printf("State=%d\n",a[j][3]);
			          j=2*(a[j][3]-1);
                        }

        }
        return 0;
}
