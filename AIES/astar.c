#include <stdio.h>

void printmat(int a[],int x,int y)
{
	for(int i=0;i<x;i++)
	{
		for(int j=0;j<y;j++)
		{
			if(a[i*y + j] == 0) { printf("  "); continue;}
			printf("%d ", a[i*y + j]);
		}
		printf("\n");
	}
}

int hamming(int a[], int x, int y)
{
	int h=0;

	for(int i=0;i<x;i++)
	{
		for(int j=0;j<y;j++)
		{
			if(a[i*y + j] == 0) continue;
			if(a[i*y + j] != i*y+j+1) h++;
		}
	}
	return h;
}

int manhattan(int a[], int b[], int x, int y)
{
	int m=0;

	for(int i=0;i<x;i++)
	{
		for(int j=0;j<y;j++)
		{
			if(a[i*y + j] == 0) continue;
			if(a[i*y + j] != b[i*y + j])
			{
				for(int k=0;k<x;k++)
				{
					for(int l=0;l<y;l++)
					{
						if(a[i*y + j] == b[k*y + l])
						{
							int y1 = l-j;
							if(y1 < 0) y1 *= -1;
							m += y1;
							int x1 = k - i;
							if(x1 < 0) x1 *= -1;
							m += x1;
						}
					}
				}
			}
		}
	}

	return m;
}


int main()
{
	int s[9] ,g[9] = {0},x=3,y=3;

	for(int i=0;i<8;i++)
		g[i] = i+1;

	while(1)
	{
		int f=0;
		for(int i=0;i<3;i++)
		{
			printf("Enter elements of row %d: ", i+1);
			scanf("%d%d%d", &s[i*3], &s[i*3 + 1], &s[i*3 + 2]);
		}

		for(int i=0;i<9;i++)
		{
			if(s[i] < 0 || s[i] > 8)
			{
				printf("Invalid Input Try again\n");
				f=1;
			}
		}
		if(f) continue;
		break;
	}
	printmat(s, x, y);
	printf("\nHamming Distance: %d\n", hamming(s, x, y));
	printf("\n");
	printmat(s, x, y);
	printf("Manhattan Distance: %d\n", manhattan(s, g, x, y));
	printmat(g, x, y);
	printf("\nHamming Distance: %d", hamming(g, x, y));

	return 0;
}
