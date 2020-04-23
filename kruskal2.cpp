#include <iostream>
#include <vector> // vector를 활용하기위한 헤더파일 
#include <algorithm> // sort를 활용하기위한 헤더파일 
#include <cstring> // memset을 활용하기위한 헤더파일 
using namespace std;

int arr[9]; // 정점의 값들을 저장하기 위한 배열 arr
vector <int> cnt; // 붕괴법칙을 활용하기 위한 vector cnt 

bool comp(vector<int> a,vector<int> b) // 벡터에서 비용값을 토대로 오름차순 정렬하기 위한 comp 함수 
{
	return a.at(2) < b.at(2); // at(2)의 값으로 비교하여 a가 작으면 true 리턴(오름차순 정렬) 
}
void init_set() // 정점의 값을 초기화시켜주는 함수 
{
	memset(arr,-1,sizeof(arr)); // 배열의 모든 원소값을 -1로 바꿈 
}
int find(int a) // 이 정점이 루트노드인지 확인하기 위한 함수 find  
{
	if(arr[a] <= -1){ // arr[a]값이 루트노드일 때 
		for(int i = 0; i < cnt.size(); i++) // 루트노드가 아닌 정점들이 저장되어있는 vector의 크기만큼 반복 
			cnt[i] = a; // 루트노드가 아닌 정점들을 모두 루트노드의 값으로 바꿈
		cnt.clear(); // 중복된 값이 누적되지 않게 vector cnt를 초기화  
		return a; // 정점 a는 루트노드 이기 때문에 a를 리턴 
	}
	else{ // arr[a]값이 루트노드가 아닐 때 
		cnt.push_back(a); // 정점 a를 vector cnt에 push_back(저장) 
		return find(arr[a]); // 루트노드를 찾아가기 위한 재귀함수 find(arr[a]) 
	}
	
}
void union_t(int a,int b) // 정점 a와 정점 b의 합병을위한 함수 union_t 
{
	if(arr[a] < arr[b]){ // arr[a]의 값이 작을 경우
		arr[a] += arr[b]; // arr[b]의 값을 arr[a]에 저장 
		arr[b] = a; // arr[b]의 값은 그 값의 부모노드인 a의 값이 된다. 
	}
	else{ // 두 값이 같거나 arr[a]가 더 클때 
		arr[b] += arr[a]; // arr[a]의 값을 arr[b]에 저장 
		arr[a] = b; // arr[a]의 값은 그 값의 부모노드인 b값이 된다. 
	}
}
int main()
{
	vector<vector <int> > v; // 정점 두개와 비용값을 저장하기 위한 int형 이중벡터 	
	int n = 9; // 정점의 개수를 저장하기 위한 int형 변수 n 
	int save[n][n] = {  {0,4,0,0,0,0,0,8,0}, 
						{4,0,8,0,0,0,0,11,0},
						{0,8,0,7,0,4,0,0,2},
						{0,0,7,0,9,14,0,0,0},
						{0,0,0,9,0,10,0,0,0},
						{0,0,4,14,10,0,2,0,0},
						{0,0,0,0,0,2,0,1,6},
						{8,11,0,0,0,0,1,0,7},
						{0,0,2,0,0,0,6,7,0} }; // 비용인접행렬로 만들기 위한 int형 이차원배열 save  
						
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++) // 이차원 배열을 돌리기 위한 이중 반복문 
		{
			if(i == j || save[i][j] == 0) // 본인이 본인을 가리킬때 비용이 있는 것이 없으므로 i == j일때 continue, 그리고 값이 없을 때도 continue 
				continue;

			v.push_back({ i, j, save[i][j] }); // 정점 두개와 그 정점간의 비용을 이차원 벡터 v에 저장 
			save[i][j] = 0; // 비용을 0으로 만들어 중복 방지 
			save[j][i] = 0; // [i][j]와 [j][i]는 값이 같으므로 같이 0으로 만들어 중복 방지  
		}
	 }
	sort(v.begin(),v.end(),comp); // 각 벡터의 비용값을 비교하여 오름차순으로 정렬해주는 함수(Quick Sort)
	
	init_set(); // 배열 초기화 
	
	int sum = 0; // 최소 비용들을 더하기 위한 변수 sum 
	int length = v.size(); // 이중벡터 v의 크기를 저장하기위한 변수 length 
	
	for(int i = 0; i < length; i++) // 모든 간선을 비교하기위해 이중벡터 v의 길이만큼 반복 
	{ 
		if(find(v[i][0]) != find(v[i][1])) // 정점두개의 값이 같지 않다는 것은 두 정점이 서로 연결이 안되있는 경우 
		{
			union_t(find(v[i][0]),find(v[i][1])); // 정점 두개를 합병함 
			sum += v[i][2]; // 합병된 정점 사이의 비용을 변수 sum에 저장 
		}
	}
	cout << sum; // 최소비용트리의 값을 출력 
}
