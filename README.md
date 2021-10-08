# 2018-2 Algorithm Projects
CSE3081-01
<br/>

## Project1
#### Project Goal
The goal of this MP is to understand how different algorithms perform differently while producing the same result for the same problem.
<br/>

## Project2
#### Project Goal
selection sort, quick sort, merge sort, 직접 구현한 가장 빠른 sorting 알고리즘의 구현 및 속도 비교.
<br/>

## Project3
구조체와 링크드 리스트를 사용하여 빈도수에 따라 트리구조를 만들어 허프만 알고리즘을 구현. 즉 빈도수가 클수록 작은 길이의 비트로 표현될 수 있도록 구현한 프로젝트.  

 -c (compress하는 경우) : malloc realloc등의 동적 할당을 이용해 배열을 만들어 원래 내용을 저장하고 그 각각의 문자의 빈도수를 구해 그 빈도수에 맞게 트리구조를 만들어주고 왼쪽 노드를 따라 갈 때에는 0을, 오른쪽 노드를 따라 갈 때에는 1을 뒤에 넣어 주며 허프만 알고리즘을 만족하도록 구현하였다. 그리고 for 문을 이용해 처음 들어왔던 문자와 비교하여 그 문자에 해당하는 허프만 코드를 비트 단위로 int 자료형을 가진 배열에 32비트씩 저장하여 그 결과물을 다시 .zz파일에 출력해 주었다.

-d (decompress하는 경우) : int형 배열에 파일의 내용을 받아오고, 다시 트리구조를 만들어 그 트리를 따라 내려가면서 트리의 끝에 도착할 때마다 해당하는 문자를 출력하여 원래 파일과 동일하게 만들어 다시 .zz.yy파일에 출력해 주었다.

<br/><br/>
#### Development Environment
Linux Machine
