#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 200		//����洢�������ֵ

typedef struct node
{
	int timein = maxsize;//����ʱ��
	int no = -1;//ҳ������
	int nextuse = 0;
}job;
int queue[maxsize];
job memory[maxsize];

void FIFO(int mmax, int duilie)//�û�ʱ�û��Ƚ���
{
	int j = 0,flag=0,cout=0,time=0,tmp,tmptime;
	for(int j=0;j<duilie;j++) {
		flag = 0;
		time++;
		int mintimein = maxsize;
		for (int i = 0; i < mmax; i++) {
			if (queue[j] == memory[i].no) {//����ڴ����Ѿ�����
				flag = 1;
				break;
			}
			else {
				if (memory[i].no == -1) {//�����û��ռ�� 
					memory[i].no = queue[j];
					memory[i].timein = time;
					cout++;
					flag = 2;
					break;
				}
				else {
					if (memory[i].timein < mintimein) {//������Ƚ���
						mintimein = memory[i].timein;
						tmp = i;
					}
				}
			}
		}
		if (flag == 0) {
			memory[tmp].no = queue[j];
			memory[tmp].timein = time;
			cout++;
		}
		for (int z = 0; z < mmax; z++) {
			if (memory[z].no != -1) {
				printf("%d,", memory[z].no);
			}
			else {
				printf("-,");
			}
		}
		if (flag == 2)
			flag = 0;
		printf("%d", flag);
		if (j < duilie - 1)
			printf("/");
	}
	printf("\n");
	printf("%d\n", cout);
}
bool has(int tmp,int mmax) {//�����ڴ�����û�����ҳ��
	for (int n = 0; n < mmax; n++) {
		if (memory[n].no == tmp) {
			return true;
		}
	}
	return false;
}
void OPT(int mmax, int duilie)//�û�ʱ�û��Ƚ���
{
	int j = 0, flag = 0, cout = 0, time = 0, tmp, tmpi,tnext[maxsize];
	for (int j = 0; j<duilie; j++) {
		flag = 0;
		time++;
		for (int i = 0; i < mmax; i++) {
			if (queue[j] == memory[i].no) {//����ڴ����Ѿ�����
				flag = 1;
				break;
			}
			else {
				if (memory[i].no == -1) {//�����û��ռ�� 
					memory[i].no = queue[j];
					memory[i].timein = time;
					cout++;
					flag = 2;
					break;
				}
			}
		}
		if (flag == 0) {
			for (int x = 0; x < maxsize; x++) {
				tnext[x] = maxsize;
			}
			for (int p = time; p < duilie; p++) {
				for (int q = 0; q < mmax; q++) {
					if (memory[q].no == queue[p]) {//����ں�߶������ҵ����ڴ��е�ҳ�棬�Ǿͼ�¼��һ�ε�ʱ��
						if (p < tnext[memory[q].no]) {
							tnext[memory[q].no] = p;//tnext�м�¼��ҳ����һ��������õ�ʱ��
						}
					}
				}
			}

			int longnext = 0,tmpcout=0;
			for (int m = 0; m < maxsize; m++) {
				if (has(m,mmax)) {
					if (tnext[m] == maxsize) {
						tmpcout++;
					}
				}
				if (tnext[m] > longnext&&has(m,mmax)) {//�ҵ����������δ�õ��Ǹ�
					longnext = tnext[m];
					tmpi = m;//tmpi��¼��Ӧ��Ҫ�滻��ҳ���
				}
			}
			if (longnext == maxsize) {
			}
			for (int n = 0; n < mmax; n++) {
				if (memory[n].no == tmpi) {
					tmp = n;
					break;
				}
			}
			memory[tmp].no = queue[j];
			memory[tmp].timein = time;
			cout++;
		}
		for (int z = 0; z < mmax; z++) {
			if (memory[z].no != -1) {
				printf("%d,", memory[z].no);
			}
			else {
				printf("-,");
			}
		}
		if (flag == 2)
			flag = 0;
		printf("%d", flag);
		if (j < duilie - 1)
			printf("/");

	}
	printf("\n");
	printf("%d\n", cout);
}

int main() {
	memset(queue, -2, sizeof(queue));
	int n, i = 0,kuaishu;
	scanf("%d\n", &n);
	scanf("%d\n", &kuaishu);
	while (1) {
		scanf("%d", &queue[i++]);
		if (getchar() == '\n')
			break;
	}
	switch (n) {
	case 1:
		OPT(kuaishu, i);
		break;
	case 2:
		FIFO(kuaishu, i);
		break;
	case 3:

		break;
	default:
		break;
	}
	return 0;
}