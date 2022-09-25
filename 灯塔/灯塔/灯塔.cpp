#include <iostream>
using namespace std;

#define MAXSIZE 4000005
#define ll long long 

struct coordinate
{
	ll x;
	ll y;
}cod[MAXSIZE], x[MAXSIZE];
ll cnt;


// merge sort
template<typename T>
void merge(T* cod, T* dest, int lo, int mi, int hi)
{
	T* A = cod + lo;
	int lb = mi - lo;
	T* B = dest + lo;
	for (int i = 0; i < lb; i++) B[i] = A[i];
	int lc = hi - mi;
	T* C = cod + mi;
	for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
	{
		if ((k < lc) && ((j >= lb) || (C[k].x < B[j].x))) A[i++] = C[k++];
		if ((j < lb) && ((k >= lc) || (C[k].x >= B[j].x))) A[i++] = B[j++];
	}
}
template<typename T>
void mergeSort(T* cod, T* x, int lo, int hi)
{
	if (hi - lo < 2) return;
	int mi = (lo + hi) >> 1;
	mergeSort(cod, x, lo, mi);
	mergeSort(cod, x, mi, hi);
	merge(cod, x, lo, mi, hi);
}

//--------------------------------------------------------------------

// fing not inversion
template<typename T>
void invBetween(T* x, T* y, int lo, int mi, int hi)
{
	T* A = x + lo;
	int lb = mi - lo;
	T* B = y + lo;
	for (int i = 0; i < lb; i++) B[i] = A[i];
	int lc = hi - mi;
	T* C = x + mi;
	for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
	{
		if ((k < lc) && ((j >= lb) || (C[k].y < B[j].y))) A[i++] = C[k++];
		if ((j < lb) && (k >= lc || (C[k].y >= B[j].y)))
		{
			A[i++] = B[j++];
			if (k < lc) cnt += lc - k;
		}
	}
}
template<typename T>
void invInside(T* x, T* y, int lo, int hi)
{
	if (hi - lo < 2) return;
	int mi = (lo + hi) >> 1;
	invInside(x, y, lo, mi);
	invInside(x, y, mi, hi);
	invBetween(x, y, lo, mi, hi);
}

//----------------------------------------------------------------------------

int main()
{
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%lld %lld", &cod[i].x, &cod[i].y);
	}

	mergeSort(cod, x, 0, n);

	cnt = 0;
	invInside(cod, x, 0, n);

	cout << cnt << endl;

	//system("pause");
	return 0;
}