#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct _Node{
	int l;
	int r;
	int sum;
}node;
//algorithm 2에서 필요하다

int size;
int *arr;
int sec_left;
int sec_right;

int first_algo(int *left, int *right);
int second_algo(int *left, int *right);
int third_algo(int *left, int *right);
int Max3(int a, int b, int c, int *index); 
node MaxSubSum(int Left, int Right);


int main(int argc, char* argv[])
{
	char *in_file_name;
	char *out_file_name;
	char order;
	int left, right;
	int max_sum=0;
	clock_t start, finish;

	in_file_name = (char *)malloc(100*sizeof(char));	//파일이름을 저장할 변수들을 동적할당한 뒤 strcpy를 이용하여 파일이름에 내용을 넣어준다.
	out_file_name = (char *)malloc(100*sizeof(char));
	strcpy(in_file_name,argv[1]);
	strcpy(out_file_name,"result_");
	strcpy(out_file_name+7, in_file_name);
	order = argv[2][0];

	FILE *ifp = fopen(in_file_name, "r");//input파일은 읽기전용으로 열고 output파일은 쓰기전용으로 열어준다.
	FILE *ofp = fopen(out_file_name, "w");


//	printf("%s %s %c\n", in_file_name, out_file_name, order);

	if(ifp == NULL)//input파일이 존재하지않거나 output파일이 제대로 만들어지지 않은 경우 에러 출력
	{
		printf("INPUT FILE ERROR\n");
		return 0;
	}
	if(ofp == NULL)
	{
		printf("OUTPUT FILE ERROR\n");
		return 0;
	}

//인풋 파일의내용을 받아와 변수 size와 배열 arr[]에 저장해 준다.
	fscanf(ifp, "%d", &size);

	arr = (int*)malloc(size*sizeof(int));
	for(int i=0; i<size; i++){
		fscanf(ifp, "%d",&arr[i]);
	}

	start= clock();

	//입력받은 algorithem isdex에 맞게 실행해준다.
	if(order=='1'){

		max_sum = first_algo(&left,&right);

	}

	else if(order=='2'){
	
		max_sum = second_algo(&left,&right);

	}

	else if(order=='3'){
		
		max_sum = third_algo(&left,&right);

	}

	else{
		printf("algorithem index error!\n");
	}

	finish = clock();

	fprintf(ofp, "%s\n", in_file_name);
	fprintf(ofp, "%c\n", order);
	fprintf(ofp, "%d\n", size);
	fprintf(ofp, "%d\n", left);
	fprintf(ofp, "%d\n", right);
	fprintf(ofp, "%d\n", max_sum);
	fprintf(ofp, "%lf\n", ((double)finish-(double)start)/1000);
	return 0;
}

int first_algo(int *left, int *right)
{
	int max, this, i, j;

	max=arr[0];
	*left = 0;
	*right = 0;
//max에 arr[0]를 넣어준 뒤 이중 for문을 이용하여 this에 배열의 합을 넣어주고
//max의 값과 비교하며 this가 더 큰경우 max에 this의 값을 넣어준 뒤 *left에는 i를 *right네는 j를 넣어준다.
//그런뒤max를 return해준다.
	for(i=0; i<size; i++){
		this=0;
		
		for(j=i; j<size;j++){
			this += arr[j];
			
			if(this>max){
				max = this;
				*left=i;
				*right=j;
			}
		}
	}
	return max;
}

int second_algo(int *left, int *right)
{
	node max = MaxSubSum(0, size-1);// node max를 선언하여 return값의 형이 node인 함수 MaxSubSum을 실행한다.

	*left= max.l;
	*right= max.r;
	return max.sum;

}

node MaxSubSum(int Left, int Right)
{
	node MaxLeftSum, MaxRightSum;
	int MaxLeftBorderSum, MaxRightBorderSum;
	int LeftBorderSum, RightBorderSum;
	int Center, i;
	int Bounder_left, Bounder_right;
	node max;
	int index;

//Left와Right가 같은 경우 max.l과 max.r모두에 Left의 값을 넣어주고
//max를 return한다
	if(Left == Right){
		max.l=max.r=Left;
		max.sum= arr[Left];

		return max;
	}

	Center = (Left+Right) /2;

	/*binary search를 하듯이Center에 Left와 Right를 2로 나눈 값을 넣어준 뒤 재귀함수를 이용한다.
	 
	 */
	MaxLeftSum = MaxSubSum(Left, Center);
	MaxRightSum = MaxSubSum(Center+1, Right);
	
	/*Center에서부터 Left까지 i를1씩 감소시키면서 
	  BounderSum이 MaxBounderSum보다 클 때에는그 값을 MaxBounderSum에 넣어주고
	Bounder_left에는 i의 값을 넣어준다 */
	
 
	MaxLeftBorderSum = arr[Center]; 
	LeftBorderSum = 0;
	Bounder_left=Center;
	for(i = Center; i>=Left; i--){
		LeftBorderSum += arr[i];
		if(LeftBorderSum> MaxLeftBorderSum){
			MaxLeftBorderSum = LeftBorderSum;
			Bounder_left=i;
		}
	}

	/*Centeri+1에서부터 Right까지 i를1씩 증가시키면서 
	  BounderSum이 MaxBounderSum보다 클 때에는그 값을 MaxBounderSum에 넣어주고
	Bounder_right에는 i의 값을 넣어준다 */
	
	MaxRightBorderSum = arr[Center+1];
	RightBorderSum = 0;
	if(Center+1<=Right)
		Bounder_right=Center+1;
	else
		Bounder_right=Center;
	for(i= Center+1; i<=Right; i++){
		RightBorderSum +=arr[i];
		if(RightBorderSum > MaxRightBorderSum){
			MaxRightBorderSum = RightBorderSum;
			Bounder_right=i;
		}
	}

/*Max3함수를 실행하여 세개의 값중 가장 큰 값을 return받고,
   	그게 몇번째 값인지 확인 해주는 index의 주소값을 같이 넘겨 그 값을 저장해 온다*/
	max.sum =  Max3(MaxLeftSum.sum, MaxRightSum.sum, MaxRightBorderSum + MaxLeftBorderSum, &index);

	/*저장한 index값에 따라 max의 값을 저장해 준뒤 max를 return한다.*/
	if(index==1){
		max=MaxLeftSum;

	}
	else if(index==2){
		max=MaxRightSum;
		
	}
		
	else if(index==3){
		max.l=Bounder_left;
		max.r=Bounder_right;
	}

	return max;
}


/*
   3개의 값중 최댓값을 찾고 그 값이 몇번째 값인지 알려주는 함수
 */
int Max3(int a, int b, int c, int *index)
{
	int max;
	if(a>=b){
		*index=1;
		max = a;
		if(a>=c){
			max = a;
			return max;
		}
		else{
			*index=3;
			max = c;
			return max;
		}
	}
	else{
		*index=2;
		max = b;
		if(b>=c){
			max = b;
			return max;
		}
		else{
			*index=3;
			max = c;
			return max;
		}
	}
}


int third_algo(int *left, int *right)
{
	int max=arr[0], this=0, j;
	int keep_left=0;

	/*
	 for문을 이용해 this에 arr[j]의 값을 더해주면서
	 arr[0]의 값을 가지고 있는 max의 값과비교하여
	 this의 값이 더 큰경우 max에 this의 값을, *right에 j의 값을, 
	 *left에 keep_left의 값을 넣어준다.

	 this가 0보다 작은 경우에는 this는 다시 0으로, keep_left에는 j+1을 넣어준다
	 그러나 이때 arr[j]가 arr[j]를 더하기 이전의 this값보다 크거나 같은 경우에는
	 *left와 *right에 j를 넣고 max에arr[j]의 값을 넣어준다.
	 */
	*left = *right = 0;
	for(j=0; j<size; j++){
		this += arr[j];

		if(this > max){
			max = this;
			*right= j;
			*left= keep_left;
/*			if(arr[j-1]==0&& arr[j]==0)
			{
				*right--;
				*left--;
			}*/
		}
		else if (this<0){
			
			if(arr[j]>=this-arr[j]){
				*left=*right=j;
				max=arr[j];
			}
			this = 0;
			keep_left = j+1;
		}
	}

	return max;
}
