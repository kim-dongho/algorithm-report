#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void merge(int left,int mid,int right);

vector<long long> v_quick; // 퀵정렬을 위한 vector 
vector<long long> v_merge; // 합병정렬을 위한 vector 

void show_array(int n)
{
	for(int i = 0; i < n; i++)
		cout << v_quick[i] << ' ';
	cout << endl;
}
void insert_v(int n) // 벡터에 값을 넣어주는 함수 
{
	for(int i = 0; i < n; i++) // num의 크기만큼 반복 
	{
		v_quick.push_back(i); // v_quick 벡터에 i값 삽입 
		v_merge.push_back(i); // v_merge 벡터에 i값 삽입 
	}
}

void shuffle_num(int n) // 벡터에 들어간 값을 섞어주는 함수 
{
	srand((unsigned int)time(0)); // rand()를 돌리기 위해 설정 
	
	for(int i = 0; i < n; i++)
	{
		int x = rand() % (n-i) + i; // 임의의 값 설정 
		
		if(i != x){ // 벡터의 값이 다르다면 (v_quick 과 v_merge는 값이 같기 때문에 하나의 조건문으로 함) 
			swap(v_quick[i],v_quick[x]); // algorithm 헤더파일에 있는 swap 함수로 값을 바꿔줌 
			swap(v_merge[i],v_merge[x]); // algorithm 헤더파일에 있는 swap 함수로 값을 바꿔줌 
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
			
	int pivot = v_quick[(left+right)/2]; // 레코드의 가운데를 pivot으로 설정 
	int low = left; // 레코드의 맨 첫 값 
	int high = right; // 레코드의 맨 끝 값 
	
	while(low <= high) // Low랑 High랑 교차할때까지 
	{
		while(v_quick[low] < pivot) // pivot 값보다 v_quick[low]의 값이 클때 까지 
			low++;
		while(v_quick[high] > pivot) // pivot 값보다 v_quick[low]의 값이 작을때 까지 
			high--;
		
		if(low <= high)
		{
			swap(v_quick[low],v_quick[high]); // 값을 바꿈 
			low++,high--; // 다음으로 넘어 감 
		}
	}
	
	if(pivot-low <= num_1)
		insert_sort(num);
	else
		quick_sort(left,high,num,num_1); // pivot의 왼쪽 퀵정렬  
	
	if(high-pivot <= num_1)
		insert_sort(num);
	else
		quick_sort(low,right,num,num_1); // pivot의 오른쪽 퀵정렬 
}

void merge_sort(int left, int right) // 분할 
{
	if(left < right)
	{
		int mid = (left+right)/2; // 중간 값 설정 
		merge_sort(left,mid); // 왼쪽 분할 
		merge_sort(mid+1,right); // 오른쪽 분할 
		merge(left,mid,right); // 합병 
	}
}

void merge(int left,int mid,int right)
{
	int tmp[v_merge.size()]; // 값을 임시로 저장하기 위한 v_merge 크기의 배열 tmp 
	
	int i = left; // 왼쪽 인덱스 
	int j = mid+1; // 중간 인덱스 
	int k = left; // 오른쪽 인덱스 
	
	while(i <= mid && j <= right) //  왼쪽 배열이나 오른쪽 배열을 전부 돌때까지 반복 
	{
		if(v_merge[i] <= v_merge[j]) // 값을 비교하여 작은 값을 tmp 배열에 저장 
			tmp[k++] = v_merge[i++];
		else
			tmp[k++] = v_merge[j++];
	}
	
	if(i > mid) // 왼쪽 값들이나 오른쪽 값들 중 한 쪽이 다 비었을 경우 남은 값을 넣기위해 쓰는 조건문 
	{
		for(int l = j; l <= right; l++)
			tmp[k++] = v_merge[l];
	}
	else
	{
		for(int l = i; l <= mid; l++)
			tmp[k++] = v_merge[l];
	}
	
	for(int l = left; l <= right; l++) // tmp 배열에 있는 값들은 전부 v_merge로 복사 
		v_merge[l] = tmp[l];
}

int main()
{
	int num,num_1; // 배열의 크기를 정하는 num 변수 
	clock_t start1, end1, start2, end2; // quick or insert , merge 시간 계산을 위한 변수 
	cout << "입력 >> "; 
	cin >> num; // 배열의 크기값 입력받기
	cout << "임계값을 입력 >> ";
	cin >> num_1; 
	
	insert_v(num); // 벡터에 num의 크기만큼 값을 넣는 insert_v 함수 
	shuffle_num(num); // sort time check를 위한 shuffle을 하는 shuffle_num 함수 

	start1 = clock(); // 함수 실행시간 측정 시작
	quick_sort(0,num-1,num,num_1); // 퀵정렬 실행 
	end1 = clock(); // 함수 실행시간 측정 끝 
	printf("%f\n",(double)(end1-start1)/CLOCKS_PER_SEC);
	
	start2 = clock(); // 함수 실행시간 측정 시작
	merge_sort(0,num-1); // 합병정렬 실행 
	end2 = clock(); // 함수 실행시간 측정 끝
	printf("%f\n",(double)(end2-start2)/CLOCKS_PER_SEC);
	
}
