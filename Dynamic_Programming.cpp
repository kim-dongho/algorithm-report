#include <iostream>
#include <cstring> // memset�� ����ϱ� ���� ������� 
#include <algorithm> // max�� ����ϱ� ���� �������  
#include <utility> // pair�� ����ϱ� ���� ������� 
#include <vector> // vector�� ����ϱ� ���� �������  
#define MAX 20 // K �迭���� 20���� �����ϱ� ���� ���� MAX 

using namespace std;

int P[5] = {4,6,8,9,6}; // ���� 
int W[5] = {2,4,5,8,3}; // ���� 
int n = 5, m = 13; // ������ ����, �賶�� ���� 
int dynamic_f(int a,int b);
int K[MAX][MAX]; // �ִ� ȿ���� �̾Ƴ��� ���� ����� 2�����迭 K 

int dynamic_first()
{
	int i,w;
	
	for(w = 0; w <= m; w++) 
		K[0][w] = 0;
	for(i = 0; i <= n; i++) // ���� �Ǵ� ���ΰ� 0�� ���� �� 0���� ä�� 
		K[i][0] = 0;
	for(i = 1; i <= n; i++)
	{
		for(w = 1; w <= m; w++)
		{
			if(w < W[i-1]) // ���� ���԰� ������ ���Ժ��� ���� �� 
				K[i][w] = K[i-1][w]; 
			else // 
				K[i][w] = max(K[i-1][w],(K[i-1][w-W[i-1]]+P[i-1]));
		}
	}
	
	for (int i = 0; i <= n; i++) { // �迭 �� ��� 
		for (int j = 0; j <= m; j++)
			cout << K[i][j] << ' ';
		cout << endl;
	}
	
	return K[n][m]; // �ִ� ���� ���� 
}

int dynamic_second()
{
	memset(K,0,sizeof(K)); // dynamic_first���� ����ߴ� �迭�� �ʱ�ȭ 
	int i,w;
	
	for(w = 0; w <= m; w++)
		K[0][w] = 0;
	for(i = 0; i <= n; i++) // ���� �Ǵ� ���ΰ� 0�� ���� �� 0���� ä��  
		K[i][0] = 0;
	
	dynamic_f(n,m);

	for (int i = 0; i <= n; i++) { // ���  
		for (int j = 0; j <= m; j++)
			cout << K[i][j] << ' ';
		cout << endl;
	}
	
	return K[n][m];
}

int dynamic_f(int i, int w)
{
	if(i == 0) // ���ΰ� 0 �� �� 
	{
		if(W[i] <= w) // W[0]���� w�� ũ�ų� ���� ��   
			return P[i-1]; // P[0]�� 4�� ���� 
		else if(0 <= w) // 0 <= w < W[i] �̹Ƿ� 0 ���� 
			return 0;
	}
	
	if(w < 0) // ������ ������ ����� �� 
		return -P[i+1]; // -P[i+1]�� �����ϸ� ���� 0�� �� 

	return K[i][w] = max(dynamic_f(i-1, w), dynamic_f(i-1,w-W[i-1])+P[i-1]);
}

float dynamic_third()
{
	float P_f[6] = {4,6,8,9,6}; // �Ǽ��� �����ؾ� �ϹǷ� ���Կ� ������ float������ �ٽ� ���� 
	float W_f[6] = {2,4,5,8,3};

	vector <pair <float,float>> S; // ��ǥ ���� �ֱ� ���� pair �ڷ����� vector S 
	S.push_back({0,0}); // ù �������� 0,0 ���� 
	
	for(int i = 0; i <= n; i++)
	{
		vector <pair <float,float>> Sp,tmp; // ���� �����ϱ� ���� Sp tmp ����  
		
		for(int j = 0; j < S.size(); j++) // �����̵� 
			Sp.push_back({S[j].first + W_f[i], S[j].second + P_f[i]});
		
		int a,b; 
		
		for(a=0,b=0; a < S.size();) // ��ġ�� ���� 
		{
			if(S[a].first >= Sp[b].first && S[a].second <= Sp[b].second)
				a++;
			else{
				tmp.push_back(S[a++]);
			}
		}
		
		while(a < S.size()) // S or Sp�� ���� ������ tmp�� �� ���� 
			tmp.push_back(S[a++]);
		while(b < Sp.size())
			tmp.push_back(Sp[b++]);

		S = tmp; // �ӽ÷� ������ ���� ������ S�� �ٽ� ���� 
						
		sort(S.begin(),S.end()); // �������� ���� 
		
		cout << "I = " << i << endl;
		for(int k = 0; k < S.size(); k++){
			if(S[k].first == S[k+1].first && S[k].second == S[k+1].second)
				continue;
			cout << S[k].first << ' ' << S[k].second << endl;
		}
		cout << endl;
	}
	
	int check = S[0].second; // �ִ� ������ ã�� ���� check ���� 
	
	for(int i = 1; i < S.size(); i++) // �ִ� ������ �����ϴ� �賶�� ���Ժ��� Ŀ�� ��� �ݺ��� Ż��  
	{
		if(S[i].first > m)
			break;
		if(check < S[i].second)
			check = S[i].second;
	}
	
	return check; // �ִ� ���� ���� 
}
int main()
{
	cout << "���� ��ȹ�� ù ��° " << endl << endl;
	cout << "�賶 ũ�� = " << m << endl;
	cout << "�ִ� ���� = " << dynamic_first() << endl << endl;
	
	cout << "���� ��ȹ�� �� ��° " << endl << endl;
	cout << "�賶 ũ�� = " << m << endl;
	cout << "�ִ� ���� = " << dynamic_second() << endl << endl;
	
	cout << "���� ��ȹ�� �� ��° " << endl;
	cout << "�賶�� ���԰� " << m << " �϶� �ִ� ���� = " << dynamic_third() << endl;
}
