#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//필요한 헤더파일 include해준다
void selection_sort(int *A, int n);

void quick_sort(int *A, int left, int right);
int partition(int *A, int left, int right);

void merge_sort(int *A, int left, int right);
void merge(int *A, int left, int middle, int right);

void fastest_sort(int *A, int left, int right);
void swap(int *A, int a, int b);
void three_sort(int *A, int left, int middle, int right);

int size;

//필요한 함수들과 전역변수 선언

int main (int argc, char* argv[])
{
	char *in_file_name;
	char *out_file_name;
	char order;
	int *arr;

	clock_t start, finish;//필요한 지역변수들 선언

	in_file_name = (char *)malloc(100*sizeof(char));
	out_file_name = (char *)malloc(100*sizeof(char));

	order = argv[2][0];
	strcpy(in_file_name, argv[1]);
	strcpy(out_file_name,"result_");
	out_file_name[7]= order;
	strcpy(out_file_name+8, "_");
	strcpy(out_file_name+9, in_file_name);	
//파일이름을 저장할 포인터 변수를 동적할당한 뒤 strcpy를 이용해 변수에 파일이름을 넣어준다.

	FILE *ifp = fopen(in_file_name, "r");
	FILE *ofp = fopen(out_file_name, "w");
//input file은 읽기전용으로, result file은 쓰기전용으로 열어준다.

//	printf("%s %s %c\n", in_file_name, out_file_name, order);

	if(ifp == NULL){
		printf("INPUT FILE ERROR\n");
		return 0;
	}

	if(ofp == NULL){
		printf("OUTPUT FILE ERROR\n");
		return 0;
	}
//input file이 존재하지 않거나 result file이 만들어 지지 않은 경우 에러를 출력한다.

	fscanf(ifp, "%d", &size);

	arr = (int*)malloc(size* sizeof(int));
	for(int i=0; i<size; i++){
		fscanf(ifp, "%d", &arr[i]);
	}
//input file의 내용을 입력받아 변수 size에 저장한뒤, 그 크기에 맞게 동적할당하여 arr배열을 만들어준뒤 나머지 내용을  배열에 저장해둔다
	start = clock();

	if(order == '1'){
		selection_sort(arr, size);
	}
	else if(order == '2'){
		quick_sort(arr, 0, size-1);
	}
	else if(order == '3'){
		merge_sort(arr, 0, size-1);
	}
	else if(order == '4'){
		fastest_sort(arr, 0, size-1);
	}
	else{
		printf("algorithm index error!\n");
	}
// 입력받은 알고리즘 인덱스에 맞는 소트를 실행해주고 존재하지않는 인덱스가 들어올 경우 에러를 출력해 준다.

	finish = clock();

	fprintf(ofp, "%s\n", in_file_name);
	fprintf(ofp, "%c\n", order);
	fprintf(ofp, "%d\n", size);
	fprintf(ofp, "%lf\n", ((double)finish - (double)start)/1000);
	
	for(int i=0; i<size; i++){
		fprintf(ofp, "%d ", arr[i]);
	}
	
	fprintf(ofp, "\n");
//result 파일에 내용을 출력해준다.
	return 0;
}

void selection_sort(int *A, int n)
{

	int i, j, cur;
	for(i=0; i<n-1; i++){
		cur = i;
		for(j = i + 1; j < n; j++){
			if(A[j] < A[cur])
				cur = j;
		}
		swap(A, i, cur);
//i+1번째 배열부터 뒤로 쭉 배열을 비교해 그중 가장 작은 원소를 i번째에 넣어주는 정렬 방법
	}

}

void quick_sort(int *A, int left, int right)
{

	int pivot;

	if(right - left > 0){
		pivot = partition(A, left, right);//피벗을 선택한다.

		quick_sort(A, left, pivot-1);//재귀호출을 하여 반복
		quick_sort(A, pivot+1, right);
	}
}

int partition(int *A, int left, int right)
{
//이 함수에서 pivot을 선택해주고 함수를 다 실행하고 나면 pivot보다 작은 값은 pivot의 왼쪽에, 큰값은 오른 쪽에 있게된다.
	int i, pivot, temp;

	pivot = left;
	for(i=left; i<right; i++){
		if(A[i] < A[right]){
			swap(A, i, pivot);
			pivot++;
		}
	}

	swap(A, right, pivot);

	return pivot;
//이 때 선택되는 피벗은 원래 배열의 가장 오른쪽에 있던 값이다.
}
	
void swap(int *A, int a, int b)
{
	int temp;
	temp = A[a];
	A[a] = A[b];
	A[b] = temp;
//두 원소를 서로 바꿔주는 함수
}


void merge_sort(int *A, int left, int right)
{

	int middle;
	
	if(left < right){
		middle = (left + right)/2;

		merge_sort(A, left, middle);
		merge_sort(A, middle+1, right);
		//배열을 절반씩 나눠서 재귀호출을 하여 left와 right가 같아질 째 까지 쪼개준다

		merge(A, left, middle, right);//함수를 실행하여 나눴던 부분들을 다시 합쳐준다.
		
	}
}

void merge(int *A, int left, int middle, int right)
{
//나눴던걸 다시 합쳐주는 함수
	int i_left, i_right, i, m;
	int *tempArray;

	tempArray = (int*)malloc(size*sizeof(int));

	i_left = left;
	i_right = middle+1;
	i = left;

	while((i_left<=middle) && (i_right<= right)){
		if(A[i_left] < A[i_right]){
			tempArray[i++] = A[i_left++];
		}
		else{
			tempArray[i++] = A[i_right++];
		}
	}
// i_left가 middle보다 작거나 같고, i_right가 right보다 작거나 같은 동안 A[i_left]와 A[i_right]를 비교하여 작은것을 tempArray에 넣어준다.
	
	while(i_left <=  middle){
		tempArray[i++] = A[i_left++];
	}
	while(i_right <= right){
		tempArray[i++] = A[i_right++];	
	}
//맨 위의 while문을 끝내면i_right~right 사이의 원소들이 tempArray에 아직 옮겨지지 않았거나, i_left~middle 사이의 원소들이 옮겨지지 않았을 수 있기 때문에 위의 for문을 또 실행해 준다.

	for(m = left; m<=right; m++){
		A[m] = tempArray[m];
	}
//tempArray의 저장된 원소들을 그대로 A에 넣어준다.

}
	
void fastest_sort(int *A, int left, int right)
{

	int i, j, pivot, middle = left + ((right - left)/2);

	three_sort(A, left, middle, right);//맨 왼쪽, 가운데, 맨 오른쪽값을 sort해주는 함수

	if(right - left + 1 > 3){//원소가 3개 이하일 때는 위의 소트만으로 해결 가능하므로 3개보다 클 때만 실행
		pivot = A[middle];//위에서 정렬한 값중 중간값을 피벗으로

//피벗을 선택하는 과정 이후에는 퀵소트와 같다.
		swap(A, middle, right - 1);
		i = left;
		j = right - 1;

		while(1){
			while(A[++i] < pivot && i < right);
			while(A[--j] > pivot && left < j);

			if(i >= j)
				break;
			swap(A, i, j);
		}
		swap(A, i, right - 1);
		fastest_sort(A, left, i-1);
		fastest_sort(A, i+1, right);
	}
	
}

void three_sort(int *A, int left, int middle, int right)
{
//3개를 소트해주는 함수
	if(A[left] > A[middle])
		swap(A, left, middle);

	if(A[middle] > A[right])
		swap(A, middle, right);

	if(A[left] > A[middle])
		swap(A, left, middle);
}

