#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 200		//定义存储数据最大值

int wait[maxsize];
int cmp(const void *a, const void *b){
	return *(int *)a - *(int *)b; 
}
void FCFS(int first, int final)//置换时置换先进的
{
	printf("%d,", first); int tmp = first, cout = 0;
	for (int i = 0; i < final; i++) {
		printf("%d", wait[i]);
		cout += abs(wait[i] - tmp);
		tmp = wait[i];
		if (i < final - 1) {
			printf(",");
		}
		else {
			printf("\n");
		}
	}
	printf("%d\n", cout);
}

int SSTF(int first, int final) {
	int ans = 0;
	int now = 0, next, min;
	int have[maxsize];
	memset(have, 0, sizeof(have));
	have[0] = 1;
	printf("%d", first);
	for (int i = final; i >= 0; i--) {
		wait[i + 1] = wait[i];
	}
	wait[0] = first;
	for (int i = 2; i<final + 2; i++) {
		min = 999999;
		next = 0;
		for (int j = 0; j < final + 1; j++) {
			if (have[j] == 1) continue;//如果已经跑过了
			if (min>abs(wait[j] - wait[now])) {//如果没跑过而且是最小值
				min = abs(wait[j] - wait[now]);
				next = j;
			}
		}
		have[next] = 1;
		ans += abs(wait[now] - wait[next]);
		printf(",%d", wait[next]);
		now = next;
	}
	printf("\n%d\n", ans);
	return 0;
}


int SCAN(int first, int final, int dir) {
	printf("%d", first);
	for (int i = final; i >= 0; i--) {
		wait[i + 1] = wait[i];
	}
	wait[0] = first;
	qsort(wait, final + 1, sizeof(wait[0]), cmp);
	int cout = 0;
	int have[maxsize];
	memset(have, 0, sizeof(have));
	int z;//用于找到first在哪里
	for (z = 0; z < final + 1; z++) {
		if (wait[z] == first)
			break;
	}
	have[z] = 1; int i = 0, last = first;
	for (int j = z; j <= final + 1 && j >= 0; j += dir) {//从z开始按照指定的方向跑
		if (j == final + 1)dir = -1;//考虑两种特殊情况
		if (j == 0)dir = 1;
		if (have[j] == 1 || wait[j] == -1) continue;//如果已经跑过了
		i++;
		have[j] = 1;
		printf(",%d", wait[j]);
		cout += abs(wait[j] - last);
		last = wait[j];
		if (i == final)
			break;
	}
	printf("\n%d\n", cout);
	return 0;
}

int CSCAN(int first, int final, int dir) {
	printf("%d", first);
	for (int i = final; i >= 0; i--) {
		wait[i + 1] = wait[i];
	}
	wait[0] = first;
	qsort(wait, final + 1, sizeof(wait[0]), cmp);
	int cout = 0;
	int have[maxsize];
	memset(have, 0, sizeof(have));
	int z;//用于找到first在哪里
	for (z = 0; z < final + 1; z++) {
		if (wait[z] == first)
			break;
	}
	have[z] = 1; int i = 0, last = first;
	for (int j = z;; j += dir) {//从z开始按照指定的方向跑
		if (wait[j] == -1)j=0;//考虑两种特殊情况
		if (j == -1)j=final;
		if (have[j] == 1) continue;//如果已经跑过了
		i++;
		have[j] = 1;
		printf(",%d", wait[j]);
		cout += abs(wait[j] - last);
		last = wait[j];
		if (i == final) {
			break;
		}
	}
	printf("\n%d\n", cout);
	return 0;
}

int main() {
	memset(wait, -1, sizeof(wait));
	int n, i = 0, first, direction;
	scanf("%d\n", &n);
	scanf("%d\n", &first);
	scanf("%d\n", &direction);
	if (direction == 0)
		direction = -1;
	while (~scanf("%d,", &wait[i])) {
		i++;
	}
	switch (n) {
	case 1:
		FCFS(first, i);
		break;
	case 2:
		SSTF(first, i);
		break;
	case 3:
		SCAN(first, i, direction);
		break;
	case 4:
		CSCAN(first, i, direction);
		break;
	default:
		break;
	}
	return 0;
}