#include <iostream>
#include <vector> // vector�� Ȱ���ϱ����� ������� 
#include <algorithm> // sort�� Ȱ���ϱ����� ������� 
#include <cstring> // memset�� Ȱ���ϱ����� ������� 
using namespace std;

int arr[9]; // ������ ������ �����ϱ� ���� �迭 arr
vector <int> cnt; // �ر���Ģ�� Ȱ���ϱ� ���� vector cnt 

bool comp(vector<int> a,vector<int> b) // ���Ϳ��� ��밪�� ���� �������� �����ϱ� ���� comp �Լ� 
{
	return a.at(2) < b.at(2); // at(2)�� ������ ���Ͽ� a�� ������ true ����(�������� ����) 
}
void init_set() // ������ ���� �ʱ�ȭ�����ִ� �Լ� 
{
	memset(arr,-1,sizeof(arr)); // �迭�� ��� ���Ұ��� -1�� �ٲ� 
}
int find(int a) // �� ������ ��Ʈ������� Ȯ���ϱ� ���� �Լ� find  
{
	if(arr[a] <= -1){ // arr[a]���� ��Ʈ����� �� 
		for(int i = 0; i < cnt.size(); i++) // ��Ʈ��尡 �ƴ� �������� ����Ǿ��ִ� vector�� ũ�⸸ŭ �ݺ� 
			cnt[i] = a; // ��Ʈ��尡 �ƴ� �������� ��� ��Ʈ����� ������ �ٲ� 
		return a; // ���� a�� ��Ʈ��� �̱� ������ a�� ���� 
	}
	else{ // arr[a]���� ��Ʈ��尡 �ƴ� �� 
		cnt.push_back(a); // ���� a�� vector cnt�� push_back(����) 
		return find(arr[a]); // ��Ʈ��带 ã�ư��� ���� ����Լ� find(arr[a]) 
	}
	
}
void union_t(int a,int b) // ���� a�� ���� b�� �պ������� �Լ� union_t 
{
	if(arr[a] < arr[b]){ // arr[a]�� ���� ���� ���
		arr[a] += arr[b]; // arr[b]�� ���� arr[a]�� ���� 
		arr[b] = a; // arr[b]�� ���� �� ���� �θ����� a�� ���� �ȴ�. 
	}
	else{ // �� ���� ���ų� arr[a]�� �� Ŭ�� 
		arr[b] += arr[a]; // arr[a]�� ���� arr[b]�� ���� 
		arr[a] = b; // arr[a]�� ���� �� ���� �θ����� b���� �ȴ�. 
	}
}
int main()
{
	vector<vector <int> > v; // ���� �ΰ��� ��밪�� �����ϱ� ���� int�� ���ߺ��� 
	
	v.push_back({0,1,4}); // ������ ���� 
	v.push_back({0,7,8});
	v.push_back({1,2,8});
	v.push_back({1,7,11});
	v.push_back({2,3,7});
	v.push_back({2,5,4});
	v.push_back({2,8,2});
	v.push_back({3,4,9});
	v.push_back({3,5,14});
	v.push_back({4,5,10});
	v.push_back({5,6,2});
	v.push_back({6,7,1});
	v.push_back({6,8,6});
	v.push_back({7,8,7}); // ������ ���� 
	
	sort(v.begin(),v.end(),comp); // �� ������ ��밪�� ���Ͽ� ������������ �������ִ� �Լ�(Quick Sort)
	
	init_set(); // �迭 �ʱ�ȭ 
	
	int sum = 0; // �ּ� ������ ���ϱ� ���� ���� sum 
	int length = v.size(); // ���ߺ��� v�� ũ�⸦ �����ϱ����� ���� length 
	
	for(int i = 0; i < length; i++) // ��� ������ ���ϱ����� ���ߺ��� v�� ���̸�ŭ �ݺ� 
	{
		int x = find(v[i][0]); // ���� v[i]�� [0]��° ��, ù��° �������� ���Ͽ� ���� x�� ����  
		int y = find(v[i][1]); // ���� v[i]�� [1]��° ��, �ι�° �������� ���Ͽ� ���� y�� ���� 
		
		if(x != y) // x,y�� ���� �ʴٴ� ���� �� ������ ���� ������ �ȵ��ִ� ��� 
		{
			union_t(x,y); // x,y�� �պ��� 
			sum += v[i][2]; // �պ��� ���� ������ ����� ���� sum�� ���� 
		}
	}
	cout << sum; // �ּҺ��Ʈ���� ���� ��� 
}
