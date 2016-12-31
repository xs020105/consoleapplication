#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXJOB 200		//����洢�������ֵ
typedef struct node
{
	int start = 0;//��ʼ��ַ
	int length = 0;		    //����
	int tag = -1;		//��־��˭ռ��,��û��ռ������Ϊ-1
}job;

typedef struct wt
{
	int no;//���
	int jcno;//���̺�
	int pv = 0;//������ͷŲ���
	int cout = 0;//����
}wai;

job kj[MAXJOB];  //�����������
int kjk_num = 0;		//����������
int cout = 1;//����������
wai wait;

void view()
{
	int i, tmp;
	printf("%d/", cout++);
	for (i = 0; i<kjk_num; i++) {
		tmp = kj[i].tag;
		if (kj[i].tag == -1) {
			tmp = 0;
			printf("%d-%d.%d", kj[i].start, kj[i].start + kj[i].length - 1, tmp);
		}
		else {
			printf("%d-%d.1.%d", kj[i].start, kj[i].start + kj[i].length - 1, tmp);
		}
		if (i != kjk_num - 1)
			printf("/");
	}
	printf("\n");
}

//�״���Ӧ
void earliest(int job_name, int job_length)
{
	int i, j;
	for (i = 0; i<kjk_num; i++) {				//˳��������������Ŀռ�
		if (kj[i].length >= job_length&&kj[i].tag == -1) {//���ҵ��ĵ�һ��
			if (kj[i].length != job_length) {//�����Ժ���ʣ��
				kjk_num++;//����һ���ռ��
				for (j = kjk_num; j > i + 1; j--) {
					kj[j] = kj[j - 1];//����Ҫ�ֿռ�飬���Խ����пռ�����һ���ڳ��ռ�
				}
				kj[i].tag = job_name;//��¼�½��̺�
				kj[i + 1].length = kj[i].length - job_length;//��ʼ��ʣ��ռ�ĳ���
				kj[i + 1].tag = -1;
				kj[i].length = job_length; //ԭ�ռ��Ĵ�С�ͱ�����õ��Ĵ�С
				kj[i + 1].start = kj[i].start + job_length;//��ʼ����һ�������
			}
			else {//�����Ժ�����û��ʣ��
				kj[i].tag = job_name;//��¼ռ�õĽ��̺ż���
			}
			break;
		}
	}
}

//�����Ӧ�㷨
void excellent(int job_name, int job_length)
{
	int i, j, minleave = 100000, mintag = -1,flag=0;
	for (i = 0; i<kjk_num; i++) {				//˳���������������ʣ��ռ���С�Ŀռ��
		if (kj[i].length >= job_length&&kj[i].tag == -1) {//�ҵ������������ˣ��ж��Ƿ���С
			if (kj[i].length == job_length) {//�����Ժ�����û��ʣ��
				kj[i].tag = job_name;//��¼ռ�õĽ��̺ż���
				return;
			}
			else {
				if (kj[i].length - job_length < minleave) {
					minleave = kj[i].length - job_length;
					mintag = i;
					flag = 1;
				}
			}

		}
	}//����ѭ���Ժ�����С���Ϸ���ռ�

	if (flag) {
		kjk_num++;//����һ���ռ��
		for (j = kjk_num; j > mintag + 1; j--) {
			kj[j] = kj[j - 1];//����Ҫ�ֿռ�飬���Խ����пռ�����һ���ڳ��ռ�
		}
		kj[mintag].tag = job_name;//��¼�½��̺�
		kj[mintag + 1].length = kj[mintag].length - job_length;//��ʼ��ʣ��ռ�ĳ���
		kj[mintag + 1].tag = -1;
		kj[mintag].length = job_length; //ԭ�ռ��Ĵ�С�ͱ�����õ��Ĵ�С
		kj[mintag + 1].start = kj[mintag].start + job_length;//��ʼ����һ�������
	}
}

//���Ӧ�㷨
void worst(int job_name, int job_length)
{
	int i, j, maxleave = -1, maxtag = -1,flag=0;
	for (i = 0; i<kjk_num; i++) {				//˳���������������ʣ��ռ����Ŀռ��
		if (kj[i].length >= job_length&&kj[i].tag == -1) {//�ҵ������������ˣ��ж��Ƿ����
			if (kj[i].length - job_length > maxleave) {
				maxleave = kj[i].length - job_length;
				maxtag = i;
				flag = 1;
			}
		}
	}//����ѭ���Ժ����ռ�
	if (flag) {
		for (j = kjk_num; j > maxtag + 1; j--) {
			kj[j] = kj[j - 1];//����Ҫ�ֿռ�飬���Խ����пռ�����һ���ڳ��ռ�
		}
		kj[maxtag].tag = job_name;//��¼�½��̺�
		kj[maxtag + 1].length = kj[maxtag].length - job_length;//��ʼ��ʣ��ռ�ĳ���
		kj[maxtag + 1].tag = -1;
		kj[maxtag].length = job_length; //ԭ�ռ��Ĵ�С�ͱ�����õ��Ĵ�С
		kj[maxtag + 1].start = kj[maxtag].start + job_length;//��ʼ����һ�������
		kjk_num++;//����һ���ռ��
	}
}

void connect(int a, int b) {//���õ�ʱ�����a<b
	kj[a].length += kj[b].length;
	for (int i = b; i + 1 < kjk_num; i++) {
		kj[i] = kj[i + 1];
	}
	kjk_num--;
}

void free(int jcno,int room) {
	int flag = 0;
	for (int i = 0; i < kjk_num; i++) {
		if (kj[i].tag == jcno&&kj[i].length==room) {//�ҵ��ý��̵�ռ�ÿ�
			kj[i].tag = -1;//���Ϊ����
			if (i - 1 >= 0 && kj[i - 1].tag == -1) {//������Ժ�ǰһ��������
				connect(i - 1, i);
				i--;
				flag = 1;//�����ˣ�����һ��
			}
			if (flag == 1) {
				if (i + 1 <= kjk_num&&kj[i + 1].tag == -1) {
					connect(i, i + 1);
				}
			}
			else {
				if (i + 1 <= kjk_num&&kj[i + 1].tag == -1) {
					connect(i, i + 1);
				}
			}
			break;
		}
	}
}

int main() {
	int n, i = 0;
	scanf("%d\n", &n);
	scanf("%d\n", &kj[i].length);
	kjk_num++;
	while (~scanf("%d/%d/%d/%d", &wait.no, &wait.jcno, &wait.pv, &wait.cout)) {
		getchar();
		switch (n) {
		case 1:
			if (wait.pv == 1)
				earliest(wait.jcno, wait.cout);
			if (wait.pv == 2)
				free(wait.jcno, wait.cout);
			view();
			break;
		case 2:
			if (wait.pv == 1)
				excellent(wait.jcno, wait.cout);
			if (wait.pv == 2)
				free(wait.jcno, wait.cout);
			view();
			break;
		case 3:
			if (wait.pv == 1)
				worst(wait.jcno, wait.cout);
			if (wait.pv == 2)
				free(wait.jcno, wait.cout);
			view();
			break;
		default:
			break;
		}
	}
	return 0;
}