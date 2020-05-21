#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
using namespace std;

void merge(int left,int mid,int right);

vector<int> v_quick;
vector<int> v_merge;

void insert_v(int n)
{
	for(int i = 0; i < n; i++)
	{
		v_quick.push_back(i);
		v_merge.push_back(i);
	}
}

void shuffle_num(int n)
{
	srand((unsigned int)time(0));
	
	for(int i = 0; i < n; i++)
	{
		int x = rand() % n; 
		int y = rand() % n;
		
		if(v_quick[x] != v_quick[y]){
			swap(v_quick[x],v_quick[y]);
			swap(v_merge[x],v_merge[y]);
		}
	}
}

void show_array(int n)
{
	for(int i = 0; i < n; i++)
		cout << v_quick[i] << ' ';
	cout << endl;
	for(int i = 0; i < n; i++)
		cout << v_merge[i] << ' ';
	cout << endl;
}

void quick_sort(int left,int right)
{
	if(left >= right)
		return;
		
	int pivot = v_quick[(left+right)/2];
	int low = left;
	int high = right;
			
	while(low <= high)
	{
		while(v_quick[low] < pivot) 
			low++;
		while(v_quick[high] > pivot)
			high--;
		
		if(low <= high)
		{
			swap(v_quick[low],v_quick[high]);
			low++,high--;
		}
	}
	
	quick_sort(left,high);
	quick_sort(low, right);
	
}

void merge_sort(int left, int right)
{
	if(left < right)
	{
		int mid = (left+right)/2;
		merge_sort(left,mid);
		merge_sort(mid+1,right);
		merge(left,mid,right);
	}
}

void merge(int left,int mid,int right)
{
	int tmp[v_merge.size()];
	
	int i = left;
	int j = mid+1;
	int k = left;
	
	while(i <= mid && j <= right)
	{
		if(v_merge[i] <= v_merge[j])
			tmp[k++] = v_merge[i++];
		else
			tmp[k++] = v_merge[j++];
	}
	
	if(i > mid)
	{
		for(int l = j; l <= right; l++)
			tmp[k++] = v_merge[l];
	}
	else
	{
		for(int l = i; l <= mid; l++)
			tmp[k++] = v_merge[l];
	}
	
	for(int l = left; l <= right; l++)
		v_merge[l] = tmp[l];
}

int main()
{
	int num;
	clock_t start1, end1, start2, end2;
	cout << "х╫╪Ж ют╥б >> ";
	cin >> num;
	
	insert_v(num);
	shuffle_num(num);
	
	start1 = clock();
	quick_sort(0,num-1);
	end1 = clock();
	
	printf("%f\n",(double)(end1-start1)/CLOCKS_PER_SEC);
	
	start2 = clock();
	merge_sort(0,num-1);
	end2 = clock();
	printf("%f\n",(double)(end2-start2)/CLOCKS_PER_SEC);
}
