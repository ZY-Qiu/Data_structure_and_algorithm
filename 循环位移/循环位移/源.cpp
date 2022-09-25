#include <iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

#define MAXSIZE 100001

char* A = new char[MAXSIZE * 2];
char* B = new char[MAXSIZE];


int* buildnext(char P[], int m)
{
	int j = 0;
	int* N = new int[m];
	int t = N[0] = -1;
	while (j < m - 1)
	{
		if (t < 0 || P[j] == P[t])
		{
			N[++j] = ++t;
		}
		else
		{
			t = N[t];
		}
	}
	return N;
}

bool KMP(char T[], char P[], int n, int m)
{
	int i = 0, j = 0;
	int* next = buildnext(P, m);

	while (i < n && j < m)
	{
		if (j < 0 || T[i] == P[j])
		{
			i++, j++;
		}
		else
		{
			j = next[j];
		}
	}
	if (i - j > n - m) return false;
	else return true;
}

int main()
{
	while (scanf("%s%s", A, B) != EOF)
	//while (scanf_s("%s%s", A, MAXSIZE, B, MAXSIZE) != EOF)
	{
		int n = strlen(A), m = strlen(B);
		if (n != m) printf("NO\n");
		else
		{
			for (int i = 0; i < n; i++)
			{
				A[n + i] = A[i];
			}
			if (KMP(A, B, n * 2, m)) printf("YES\n");
			else printf("NO\n");
		}
	}

	return 0;
}