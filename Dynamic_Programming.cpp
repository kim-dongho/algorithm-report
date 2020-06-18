#include <iostream>
#include <cstring>
#include <algorithm>
#define MAX 15
using namespace std;

int P[5] = {4,6,8,9,6};
int W[5] = {2,4,5,8,3};
int n = 5, m = 13;

int dynamic_first()
{
	int K[MAX][MAX];
	memset(K,-1,sizeof(int));
	int i,w;
	
	for(w = 0; w <= m; w++)
		K[0][w] = 0;
	for(i = 0; i <= n; i++)
		K[i][0] = 0;
	for(i = 1; i <= n; i++)
	{
		for(w = 1; w <= m; w++)
		{
			if(w < W[i-1])
				K[i][w] = K[i-1][w];
			else
				K[i][w] = max(K[i-1][w],(K[i-1][w-W[i-1]]+P[i-1]));
		}
	}
	
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++)
			cout << K[i][j] << ' ';
		cout << endl;
	}
	
	return K[n][m];
}

int dynamic_second()
{
	int K[MAX][MAX];
	memset(K,-1,sizeof(K));
	int i,w;
	
	for(w = 0; w <= m; w++)
		K[0][w] = 0;
	for(i = 0; i <= n; i++)
		K[i][0] = 0;
	for(i = 1; i <= n; i++)
	{
		for(w = 1; w <= m; w++)
		{
			if(w < W[i-1] && K[i-1][w] >= 0)
				K[i][w] = K[i-1][w];
			
		}
	}
	
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++)
			cout << K[i][j] << ' ';
		cout << endl;
	}
	
	return K[n][m];
}

int main()
{
	cout << "동적 계획법 첫 번째 " << endl << endl;
	int x = dynamic_first();
	cout << "배낭 크기 = " << m << endl;
	cout << "최대 이익 = " << x << endl << endl;
	
	cout << "동적 계획법 두 번째 " << endl << endl;
	x = dynamic_second();
	cout << "배낭 크기 = " << m << endl;
	cout << "최대 이익 = " << x << endl << endl;
	
	/* cout << "동적 계획법 세 번째 " << endl;
	x = dynamic_third();
	cout << "배낭 크기 = " << m << endl;
	cout << "최대 이익 = " << x << endl; */
}
