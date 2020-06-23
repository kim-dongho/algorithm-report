#include <iostream>
#include <cstring> // memset을 사용하기 위한 헤더파일 
#include <algorithm> // max를 사용하기 위한 헤더파일  
#include <utility> // pair를 사용하기 위한 헤더파일 
#include <vector> // vector를 사용하기 위한 헤더파일  
#define MAX 20 // K 배열값을 20으로 고정하기 위한 변수 MAX 

using namespace std;

int P[5] = {4,6,8,9,6}; // 이익 
int W[5] = {2,4,5,8,3}; // 무게 
int n = 5, m = 13; // 물건의 개수, 배낭의 무게 
int dynamic_f(int a,int b);
int K[MAX][MAX]; // 최대 효율을 뽑아내기 위해 사용할 2차원배열 K 

int dynamic_first()
{
	int i,w;
	
	for(w = 0; w <= m; w++) 
		K[0][w] = 0;
	for(i = 0; i <= n; i++) // 가로 또는 세로가 0인 곳을 다 0으로 채움 
		K[i][0] = 0;
	for(i = 1; i <= n; i++)
	{
		for(w = 1; w <= m; w++)
		{
			if(w < W[i-1]) // 현재 무게가 물건의 무게보다 작을 때 
				K[i][w] = K[i-1][w]; 
			else // 
				K[i][w] = max(K[i-1][w],(K[i-1][w-W[i-1]]+P[i-1]));
		}
	}
	
	for (int i = 0; i <= n; i++) { // 배열 값 출력 
		for (int j = 0; j <= m; j++)
			cout << K[i][j] << ' ';
		cout << endl;
	}
	
	return K[n][m]; // 최대 이익 리턴 
}

int dynamic_second()
{
	memset(K,0,sizeof(K)); // dynamic_first에서 사용했던 배열을 초기화 
	int i,w;
	
	for(w = 0; w <= m; w++)
		K[0][w] = 0;
	for(i = 0; i <= n; i++) // 가로 또는 세로가 0인 곳을 다 0으로 채움  
		K[i][0] = 0;
	
	dynamic_f(n,m);

	for (int i = 0; i <= n; i++) { // 출력  
		for (int j = 0; j <= m; j++)
			cout << K[i][j] << ' ';
		cout << endl;
	}
	
	return K[n][m];
}

int dynamic_f(int i, int w)
{
	if(i == 0) // 가로가 0 일 때 
	{
		if(W[i] <= w) // W[0]보다 w가 크거나 같을 때   
			return P[i-1]; // P[0]인 4를 리턴 
		else if(0 <= w) // 0 <= w < W[i] 이므로 0 삽입 
			return 0;
	}
	
	if(w < 0) // 세로의 범위를 벗어났을 때 
		return -P[i+1]; // -P[i+1]을 리턴하면 값이 0이 됨 

	return K[i][w] = max(dynamic_f(i-1, w), dynamic_f(i-1,w-W[i-1])+P[i-1]);
}

float dynamic_third()
{
	float P_f[6] = {4,6,8,9,6}; // 실수도 저장해야 하므로 무게와 이익을 float변수로 다시 설정 
	float W_f[6] = {2,4,5,8,3};

	vector <pair <float,float>> S; // 좌표 값을 넣기 위한 pair 자료형의 vector S 
	S.push_back({0,0}); // 첫 시작점인 0,0 삽입 
	
	for(int i = 0; i <= n; i++)
	{
		vector <pair <float,float>> Sp,tmp; // 값을 저장하기 위한 Sp tmp 벡터  
		
		for(int j = 0; j < S.size(); j++) // 평행이동 
			Sp.push_back({S[j].first + W_f[i], S[j].second + P_f[i]});
		
		int a,b; 
		
		for(a=0,b=0; a < S.size();) // 합치는 과정 
		{
			if(S[a].first >= Sp[b].first && S[a].second <= Sp[b].second)
				a++;
			else{
				tmp.push_back(S[a++]);
			}
		}
		
		while(a < S.size()) // S or Sp에 남은 값들을 tmp에 다 저장 
			tmp.push_back(S[a++]);
		while(b < Sp.size())
			tmp.push_back(Sp[b++]);

		S = tmp; // 임시로 저장해 놓은 값들을 S에 다시 복사 
						
		sort(S.begin(),S.end()); // 오름차순 정렬 
		
		cout << "I = " << i << endl;
		for(int k = 0; k < S.size(); k++){
			if(S[k].first == S[k+1].first && S[k].second == S[k+1].second)
				continue;
			cout << S[k].first << ' ' << S[k].second << endl;
		}
		cout << endl;
	}
	
	int check = S[0].second; // 최대 이익을 찾기 위한 check 변수 
	
	for(int i = 1; i < S.size(); i++) // 최대 이익을 저장하다 배낭의 무게보다 커질 경우 반복문 탈출  
	{
		if(S[i].first > m)
			break;
		if(check < S[i].second)
			check = S[i].second;
	}
	
	return check; // 최대 이익 리턴 
}
int main()
{
	cout << "동적 계획법 첫 번째 " << endl << endl;
	cout << "배낭 크기 = " << m << endl;
	cout << "최대 이익 = " << dynamic_first() << endl << endl;
	
	cout << "동적 계획법 두 번째 " << endl << endl;
	cout << "배낭 크기 = " << m << endl;
	cout << "최대 이익 = " << dynamic_second() << endl << endl;
	
	cout << "동적 계획법 세 번째 " << endl;
	cout << "배낭의 무게가 " << m << " 일때 최대 이익 = " << dynamic_third() << endl;
}
