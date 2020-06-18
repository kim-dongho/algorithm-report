#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#define MAX 20

using namespace std;

int P[5] = {4,6,8,9,6};
int W[5] = {2,4,5,8,3};
int n = 5, m = 13;
int dynamic_f(int a,int b);
int K[MAX][MAX];

int dynamic_first()
{
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
	memset(K,0,sizeof(K));
	int i,w;
	
	for(w = 0; w <= m; w++)
		K[0][w] = 0;
	for(i = 0; i <= n; i++)
		K[i][0] = 0;
	
	dynamic_f(n,m);

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++)
			cout << K[i][j] << ' ';
		cout << endl;
	}
	
	return K[n][m];
}

int dynamic_f(int i, int w)
{
	if(i == 1)
	{
		if(W[i] <= w){
			K[i][w] = P[0];
			return P[i];
		}
		else if(0 <= w)
			return 0;
	}
	
	if(w < 0)
		return -P[i+1];

	return K[i][w] = max(dynamic_f(i-1, w), dynamic_f(i-1,w-W[i-1])+P[i-1]);
}
int main()
{
	cout << "동적 계획법 첫 번째 " << endl << endl;
	cout << "배낭 크기 = " << m << endl;
	cout << "최대 이익 = " << dynamic_first() << endl << endl;
	
	cout << "동적 계획법 두 번째 " << endl << endl;
	cout << "배낭 크기 = " << m << endl;
	cout << "최대 이익 = " << dynamic_second() << endl << endl;
	
	/* cout << "동적 계획법 세 번째 " << endl;
	x = dynamic_third();
	cout << "배낭 크기 = " << m << endl;
	cout << "최대 이익 = " << x << endl; */
}
