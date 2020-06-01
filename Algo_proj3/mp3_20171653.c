#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//필요한 헤더파일을 include

typedef struct _node{
	char symbol;
	int freq;
	struct _node *left;
    struct _node *right;
}node;
//사용할 구조체 선
void check_freq(void);
void construct_tree(void);
int find_minfreq(void);
void make_huf(void);
void make_huf_code(node *h, unsigned c, int l);

void decompressing(void);

void destroy_tree(node *h);

node *head[256];
node *huf_head;
node *root = NULL;
int huf_len[256];
unsigned huf[256];
char strcode[256][20];
char *keep;
int file_len;
int *frequency;
int num_head;
int num=0;
int ch =0;

FILE *ifp;
FILE *ofp;
//필요한 함수와 변수를 선언해준다.


int main(int argc, char* argv[])
{
	char *in_file_name;
	char *out_file_name;
	char *order;

	int rest;
	int in_file_name_len;
	int bi_code[14];
	
	in_file_name = (char *)malloc(100*sizeof(char));
	out_file_name = (char *)malloc(100*sizeof(char));
	order = (char *)malloc(2*sizeof(char));
	
	strcpy(in_file_name, argv[2]);

	order = argv[1];

	if(strcmp(order,"-c")==0)
	{
		in_file_name_len = strlen(in_file_name);
			
		ifp = fopen(in_file_name, "r");
		

		if(ifp == NULL){
			printf("INPUT FILE ERROR!!\n");
			return 0;
		}

		strcpy(out_file_name, in_file_name);
		strcpy(out_file_name+in_file_name_len, ".zz");
		ofp = fopen(out_file_name, "w");
//파일의 이름을 넣어 인풋파일은 r로 아웃풋 파일은 w로 열어주었다.
		if(ofp == NULL){
			printf("OUTPUT FILE ERROR!!\n");
			return 0;
		}
		keep = (char*)malloc(sizeof(char));
		fscanf(ifp, "%c", &keep[0]);
	
		int i=1;
		while(1){
			keep = (char*)realloc(keep,(i+1)*sizeof(char));
			if((fscanf(ifp, "%c",&keep[i]))==EOF)
				break;
			i++;
		}
		//배열을 동적할당으로 만들어 인풋파일의 내용을 읽어온다.
		file_len = i;
				
		frequency = (int*)calloc(256, sizeof(int));


		check_freq();
		construct_tree();
		make_huf();
//함수를 실행해 빈도수를 저장하고 그에 맞게 트리를 만든뒤 허프만 코드를 만들어준다.
		unsigned temp;

		fprintf(ofp, "%d ", num);

		for(i=0; i<256; i++)
		{
			if(huf_len[i]!=0){
				fprintf(ofp, "%d %d ",i,frequency[i]);
				
				}

		}//아웃풋파일에 기호와 빈도수를 출력해준다

		char *result=(char*)malloc(sizeof(char)*1);

		int m=0;
		for(i=0; i<file_len; i++){
			for(int j=0; j<256; j++){
				if((int)keep[i] == j)
				{
					temp = huf[j];
					for(int k =1; k<=huf_len[j]; k++){
						bi_code[huf_len[j]-k] = temp % 2;
						temp /=2;
					}
					for(int k=0; k<huf_len[j]; k++){
						result[m]=(char)(bi_code[k]+48);
						result=(char*)realloc(result,(m+2)*sizeof(char));
						m++;
					}	
				}
			}
		}
//인풋파일의 내용을 허프만코드로 배열에 저장해준다.
		int p_len = m/32;
		if ((m%32)!=0)
			p_len++;

		unsigned int *prin = (unsigned int*)calloc(p_len,sizeof(unsigned int));
		int len =m;
		i=0;
		int k=0;
		for(int j=0; j<len; j++){
			if(k==32){
				k=0;
				i++;
			}
			if(result[j]=='0'){
				prin[i]<<=1;
				k++;
			}
			else if(result[j]=='1'){
				prin[i]<<=1;
				prin[i]|=1;
				k++;
			}

		}
		prin[i]<<=32-(m%32);

		fprintf(ofp, "%d %d ", p_len, m%32);
		for(i=0; i<p_len;i++){
			fprintf(ofp, "%d ", prin[i]);
		}
//16비트씩 int변수에 넣어 아웃풋 파일에 출력해준다.

		fclose(ifp);
		fclose(ofp);
		destroy_tree(huf_head);
	}

	else if(strcmp(order, "-d")==0)
	{
		int len;
		in_file_name_len = strlen(in_file_name);
	
		
		ifp = fopen(in_file_name, "r");
		if(ifp == NULL){
			printf("INPUT FILE ERROR!!\n");
			return 0;
		}


		frequency = (int*)calloc(256, sizeof(int));
		
		strcpy(out_file_name, in_file_name);

		strcpy(out_file_name+in_file_name_len, ".yy");
		
		ofp = fopen(out_file_name, "w");
		
		
		if(ofp == NULL){
			printf("OUTPUT FILE ERROR!!\n");
			return 0;
		}

		for(int i=0; i<256; i++){
			huf_len[i] = huf[i] = 0;
		}

		int get;
		fscanf(ifp,"%d ",&num);
		for(int i=0; i<num; i++){
			fscanf(ifp, "%d", &get);
			fscanf(ifp, "%d ", &frequency[(int)get]);
		}

		fscanf(ifp, "%d %d ",&len, &rest);
		
		unsigned int *inpu = (unsigned int*)malloc(len*sizeof(unsigned int));
		for(int i=0; i<len; i++){
			fscanf(ifp, "%d", &inpu[i]);
		}
		//printf("%d %d %d %d\n", inpu[0], inpu[1], inpu[2], inpu[26]);
		fclose(ifp);
		
		ifp = fopen(in_file_name, "w");
		for(int i=0; i<len; i++){
			fprintf(ifp,"%d",inpu[i]);
		}

	
		keep = (char*)malloc(((len-1)*32+rest)*sizeof(char));
		int k=0;
		unsigned int t;
		for(int i=0;i<len-1; i++){
			for(int j=0; j<32; j++){
				t=inpu[i]%2;
				inpu[i]/=2;
				if(t==1){
					keep[(i+1)*32-j-1] = '1';
					k++;
				}
				else if(t==0){
					keep[(i+1)*32-j-1] = '0';
					k++;
				}
			}
		}
		
		if(rest>0){
			for(int i=0; i<32-rest; i++){
				inpu[len-1]/=2;
			}
			for(int i=rest; i>0; i--){
				t=inpu[len-1]%2;
				inpu[len-1]/=2;
				if(t==1){
					keep[k+i-1]='1';
				}
				else if(t==0){
					keep[k+i-1] = '0';
				}
			}
		}
		
		file_len = k+rest;

		construct_tree();

		decompressing();

		fclose(ifp);
		fclose(ofp);
		destroy_tree(huf_head);

	}

	else
	{
		printf("ERROR!!\n");
	}
}

void check_freq(void)//빈도를 세는 함수
{
	int i;
	int charToInt;
	for(i =0; i<file_len; i++){
		charToInt =(int) keep[i];
		frequency[charToInt]++;
	}
}
void construct_tree(void)//트리를 만드는 함수
{
	int i, min;
	node *h, *h1, *h2;

	num_head = 0;
	for(i = 0; i<256; i++)
	{
		if(frequency[i] != 0)
		{
			if((h = (node *)malloc(sizeof(node)))==NULL)
			{
				printf("ERROR!\n");
				exit(1);
			}
			h->freq = frequency[i];
			h->symbol = (char)i;
			h->left = h->right = NULL;
			head[num_head] = h;
			num_head++;
		}
	}

	while(num_head>1)
	{
		min = find_minfreq();
		h1 = head[min];
		num_head--;
		head[min] = head[num_head];
		min = find_minfreq();
		h2 = head[min];

		if((h = (node *)malloc(sizeof(node)))==NULL)
		{
			printf("ERROR!\n");
			exit(1);
		}

		h->freq = h1->freq + h2->freq;
		h->symbol = 0;
		h->left = h1;
		h->right = h2;
		head[min] = h;

	}

	huf_head = head[0];
}

int find_minfreq(void)//빈도수가 가장작은 값을 찾는 함수
{
	int index, i;
	index = 0;
	for(i=1; i<num_head; i++)
	{
		if(head[i]->freq < head[index]->freq)
			index = i;
	}
	return index;
}

void make_huf(void)//허프만 코드를 만들기 위한 진입함수
{
	int i;
	for(i=0; i<256; i++)
	{
		huf[i] = huf_len[i]=0;
	}
	make_huf_code(huf_head, 0u, 0);

}

void make_huf_code(node *h, unsigned c, int l)//각 문자에 해당하는 허프만 코드를 만드는 함수
{
	if(h->left != NULL || h->right != NULL)
	{
		c <<= 1;
		l++;
		make_huf_code(h->left, c, l);
		c |= 1u;
		make_huf_code(h->right, c, l);
		c >>=1;
		l--;
	}

	else
	{
		huf[h->symbol] = c;
		huf_len[h->symbol] = l;
		if(l!=0)
			num++;
	}
}

	
void decompressing(void)//허프만 코드를 다시 원래 기호로 만들어주는 함
{
	node *curr;
	//node *temp;
	node *before=huf_head;
	
	curr = (node *)malloc(sizeof(node));
	curr = huf_head;
	for(int i=0; i<file_len; i++)
	{
		if(keep[i] == '0'){
			if(curr->left!=NULL){
				curr = curr->left;
			}

			else{
				fprintf(ofp,"%c", curr->symbol);
				curr = huf_head->left;
			}
		}


		else if(keep[i] == '1'){
			if(curr->right!=NULL){
				curr = curr->right;
			}

			else{
				
				fprintf(ofp,"%c", curr->symbol);
				curr = huf_head->right;
			}
		}
	}
	fprintf(ofp, "%c", curr->symbol);
}
void destroy_tree(node * h)//만든 트리를 없애주는 함수
{
	if(h!=NULL)
	{
		destroy_tree(h->left);
		destroy_tree(h->right);
		free(h);
	}
}

