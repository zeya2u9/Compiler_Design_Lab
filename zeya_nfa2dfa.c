#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char a[10][2][10],final,new_st[10][10];
int n_st=0,m=0;

void print(int m,int n,int o)
{
	int i,j,k;
	for(i=0;i<m;i++)
	{
		for(j=0;j<=n;j++)
		{
			for(k=0;k<o;k++)
				printf("%c,",a[i][j][k]);
			printf(" ");
		}
		printf("\n");
	}
}
int main()
{
	FILE *ptr;
	int i=0,j=0,k=0,max_j=0,n,o,flag=0;
	int row=0,count=0,col;
	char temp;
	clrscr();
	//INITIALLY a[][][]={n}
	for(i=0;i<10;i++)
		for(j=0;j<2;j++)
			for(k=0;k<10;k++)
				a[i][j][k]='n';
	//print(10,2,10);
	i=0;j=0;k=0;
	ptr=fopen("filee.txt","r");
	while(!feof(ptr))
	{
		fscanf(ptr,"%c",&temp);
		printf("read_i=%c",temp);
		if(temp==' ')
		{	j++;  k=0;		}
		else if(temp==',')
			k++;
		else if(temp=='l')
		{
			printf("Here in lll\n");
			if(max_j<j)
				max_j=j;
			i++;
			j=0;
			k=0;
		}
		else if(temp=='#')
		{
			fscanf(ptr,"%c",&temp);
			final=temp;
			break;
		}
		else if((temp>=48 && temp<=57) || temp=='n')
				 a[i][j][k]=temp;
	}
	fclose(ptr);
	m=i;
	n=max_j;
	o=i;
	printf("m=%d n=%d o=%d\n",m,n,o);
	print(m,n,o);
	getch();
	row=0;
	count=0;
	///CALLING NFA PROCEDURE
	while(1)
	{
		///checking for new state, row is set
		for(j=0;j<2;j++)
		{
			count=0;
			col=j;
			for(k=0;k<o;k++)
				if(a[row][j][k]!='n')
					count++;
			if(count>1)
			{
				if(form(row,col,count)==0)
				{
					if((row==m-1) && j==1)
					{
						flag=1;
						print(m,2,m);
						exit(0);
					}
				}
			}
		}
		if(flag==1)
			break;
		printf("Keeping track of row-%d in main \n",row);
		getch();
		if((row==m-1) && j==2)
		{
			print(m,2-1,m);
			exit(0);
		}
		row++;
	}
	return 0;
}
int redund_check(int pp,int kk,int rrow_no,int rr_no,int coll)
{
	int i;
	for(i=0;i<pp;i++)
	{
		if(a[rrow_no][coll][i]==a[rr_no][coll][kk])
			return 1;
	}
	return 0;
}
void add_transition(int row_no)
{
	int r_no,k,q=0,p=0,i;
	for(i=0;i<strlen(new_st[n_st-1]);i++)
	{
		r_no=new_st[n_st-1][i]-48;      ////TAKING LAST ADDED STATE OF NEW STATE
		k=0;
		while(a[r_no][0][k]!='n') /////COPYING COLUMN NO 0
		{
			////Check if it is already present
			if(redund_check(p,k,row_no,r_no,0)==0)
			{
				a[row_no][0][p]=a[r_no][0][k];
				p++;
			}
			k++;
		}
		printf("After copying col 0 of row no-%d p=%d \n",r_no,p);
		getch();
		k=0;
		while(a[r_no][1][k]!='n') /////COPYING COLUMN NO 1
		{
			if(redund_check(q,k,row_no,r_no,1)==0)
			{
				a[row_no][1][q]=a[r_no][1][k];
				q++;
			}
			k++;
		}
		printf("After copying col 1 of row no-%d q=%d \n",r_no,q);
		getch();
	}
	printf("New transition  added for new state with q=%d\n",q);
}
int check(char state[])
{
	int i;
	for(i=0;i<n_st;i++)
	{
		if(strcmp(state,new_st[i])==0)
			return 0;
	}
	return 1;
}
int form(int r,int c,int co)
{
	int t=0;
	char temp[10];
	while(a[r][c][t]!='n')
	{
		temp[t]=a[r][c][t];
		t++;
	}
	temp[t]='\0';
	//strcat(new_st[n_st++],temp);
	getch();

	printf("New state=%s\n",temp);
	if(check(temp)==1)
	{
		strcpy(new_st[n_st++],temp);
		printf("successfully added new state\n");
		m++;
		printf("new m=%d\n",m);
		getch();
		add_transition(m-1);
		return 1;
	}
	else
		printf("Already present\n");
	getch();
	return 0;
}
