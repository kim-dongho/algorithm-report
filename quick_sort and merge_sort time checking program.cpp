#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void merge(int left,int mid,int right);

vector<long long> v_quick; // �������� ���� vector 
vector<long long> v_merge; // �պ������� ���� vector 

void show_array(int n)
{
	for(int i = 0; i < n; i++)
		cout << v_quick[i] << ' ';
	cout << endl;
}
void insert_v(int n) // ���Ϳ� ���� �־��ִ� �Լ� 
{
	for(int i = 0; i < n; i++) // num�� ũ�⸸ŭ �ݺ� 
	{
		v_quick.push_back(i); // v_quick ���Ϳ� i�� ���� 
		v_merge.push_back(i); // v_merge ���Ϳ� i�� ���� 
	}
}

void shuffle_num(int n) // ���Ϳ� �� ���� �����ִ� �Լ� 
{
	srand((unsigned int)time(0)); // rand()�� ������ ���� ���� 
	
	for(int i = 0; i < n; i++)
	{
		int x = rand() % (n-i) + i; // ������ �� ���� 
		
		if(i != x){ // ������ ���� �ٸ��ٸ� (v_quick �� v_merge�� ���� ���� ������ �ϳ��� ���ǹ����� ��) 
			swap(v_quick[i],v_quick[x]); // algorithm ������Ͽ� �ִ� swap �Լ��� ���� �ٲ��� 
			swap(v_merge[i],v_merge[x]); // algorithm ������Ͽ� �ִ� swap �Լ��� ���� �ٲ��� 
		}
	}
}

void insert_sort(int num)
{
	int j;
	for(int i = 0; i < num; i++)
	{
		j = i;
		while(v_quick[j] > v_quick[j+1]){
			swap(v_quick[j],v_quick[j+1]);
			j--;
		}
	}
}

void quick_sort(int left,int right,int num,int num_1)
{
	if(left >= right) // 
		return;
			
	int pivot = v_quick[(left+right)/2]; // ���ڵ��� ����� pivot���� ���� 
	int low = left; // ���ڵ��� �� ù �� 
	int high = right; // ���ڵ��� �� �� �� 
	
	while(low <= high) // Low�� High�� �����Ҷ����� 
	{
		while(v_quick[low] < pivot) // pivot ������ v_quick[low]�� ���� Ŭ�� ���� 
			low++;
		while(v_quick[high] > pivot) // pivot ������ v_quick[low]�� ���� ������ ���� 
			high--;
		
		if(low <= high)
		{
			swap(v_quick[low],v_quick[high]); // ���� �ٲ� 
			low++,high--; // �������� �Ѿ� �� 
		}
	}
	
	if(pivot-low <= num_1)
		insert_sort(num);
	else
		quick_sort(left,high,num,num_1); // pivot�� ���� ������  
	
	if(high-pivot <= num_1)
		insert_sort(num);
	else
		quick_sort(low,right,num,num_1); // pivot�� ������ ������ 
}

void merge_sort(int left, int right) // ���� 
{
	if(left < right)
	{
		int mid = (left+right)/2; // �߰� �� ���� 
		merge_sort(left,mid); // ���� ���� 
		merge_sort(mid+1,right); // ������ ���� 
		merge(left,mid,right); // �պ� 
	}
}

void merge(int left,int mid,int right)
{
	int tmp[v_merge.size()]; // ���� �ӽ÷� �����ϱ� ���� v_merge ũ���� �迭 tmp 
	
	int i = left; // ���� �ε��� 
	int j = mid+1; // �߰� �ε��� 
	int k = left; // ������ �ε��� 
	
	while(i <= mid && j <= right) //  ���� �迭�̳� ������ �迭�� ���� �������� �ݺ� 
	{
		if(v_merge[i] <= v_merge[j]) // ���� ���Ͽ� ���� ���� tmp �迭�� ���� 
			tmp[k++] = v_merge[i++];
		else
			tmp[k++] = v_merge[j++];
	}
	
	if(i > mid) // ���� �����̳� ������ ���� �� �� ���� �� ����� ��� ���� ���� �ֱ����� ���� ���ǹ� 
	{
		for(int l = j; l <= right; l++)
			tmp[k++] = v_merge[l];
	}
	else
	{
		for(int l = i; l <= mid; l++)
			tmp[k++] = v_merge[l];
	}
	
	for(int l = left; l <= right; l++) // tmp �迭�� �ִ� ������ ���� v_merge�� ���� 
		v_merge[l] = tmp[l];
}

int main()
{
	int num,num_1; // �迭�� ũ�⸦ ���ϴ� num ���� 
	clock_t start1, end1, start2, end2; // quick or insert , merge �ð� ����� ���� ���� 
	cout << "�Է� >> "; 
	cin >> num; // �迭�� ũ�Ⱚ �Է¹ޱ�
	cout << "�Ӱ谪�� �Է� >> ";
	cin >> num_1; 
	
	insert_v(num); // ���Ϳ� num�� ũ�⸸ŭ ���� �ִ� insert_v �Լ� 
	shuffle_num(num); // sort time check�� ���� shuffle�� �ϴ� shuffle_num �Լ� 

	start1 = clock(); // �Լ� ����ð� ���� ����
	quick_sort(0,num-1,num,num_1); // ������ ���� 
	end1 = clock(); // �Լ� ����ð� ���� �� 
	printf("%f\n",(double)(end1-start1)/CLOCKS_PER_SEC);
	
	start2 = clock(); // �Լ� ����ð� ���� ����
	merge_sort(0,num-1); // �պ����� ���� 
	end2 = clock(); // �Լ� ����ð� ���� ��
	printf("%f\n",(double)(end2-start2)/CLOCKS_PER_SEC);
	
}
