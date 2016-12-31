#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXJOB 200		//定义存储数据最大值
typedef struct node
{
	int start = 0;//起始地址
	int length = 0;		    //长度
	int tag = -1;		//标志被谁占用,若没有占用则设为-1
}job;

typedef struct wt
{
	int no;//序号
	int jcno;//进程号
	int pv = 0;//申请或释放操作
	int cout = 0;//容量
}wai;

job kj[MAXJOB];  //定义空闲区表
int kjk_num = 0;		//空闲区块数
int cout = 1;//输出做标记用
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

//首次适应
void earliest(int job_name, int job_length)
{
	int i, j;
	for (i = 0; i<kjk_num; i++) {				//顺序查找满足条件的空间
		if (kj[i].length >= job_length&&kj[i].tag == -1) {//用找到的第一个
			if (kj[i].length != job_length) {//用了以后有剩余
				kjk_num++;//多了一个空间块
				for (j = kjk_num; j > i + 1; j--) {
					kj[j] = kj[j - 1];//由于要分空间块，所以将所有空间块后移一个腾出空间
				}
				kj[i].tag = job_name;//记录下进程号
				kj[i + 1].length = kj[i].length - job_length;//初始化剩余空间的长度
				kj[i + 1].tag = -1;
				kj[i].length = job_length; //原空间块的大小就变成了用掉的大小
				kj[i + 1].start = kj[i].start + job_length;//初始化后一个的起点
			}
			else {//用了以后正好没有剩余
				kj[i].tag = job_name;//记录占用的进程号即可
			}
			break;
		}
	}
}

//最佳适应算法
void excellent(int job_name, int job_length)
{
	int i, j, minleave = 100000, mintag = -1,flag=0;
	for (i = 0; i<kjk_num; i++) {				//顺序查找满足条件且剩余空间最小的空间块
		if (kj[i].length >= job_length&&kj[i].tag == -1) {//找到符合条件的了，判断是否最小
			if (kj[i].length == job_length) {//用了以后正好没有剩余
				kj[i].tag = job_name;//记录占用的进程号即可
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
	}//跑完循环以后在最小的上分配空间

	if (flag) {
		kjk_num++;//多了一个空间块
		for (j = kjk_num; j > mintag + 1; j--) {
			kj[j] = kj[j - 1];//由于要分空间块，所以将所有空间块后移一个腾出空间
		}
		kj[mintag].tag = job_name;//记录下进程号
		kj[mintag + 1].length = kj[mintag].length - job_length;//初始化剩余空间的长度
		kj[mintag + 1].tag = -1;
		kj[mintag].length = job_length; //原空间块的大小就变成了用掉的大小
		kj[mintag + 1].start = kj[mintag].start + job_length;//初始化后一个的起点
	}
}

//最坏适应算法
void worst(int job_name, int job_length)
{
	int i, j, maxleave = -1, maxtag = -1,flag=0;
	for (i = 0; i<kjk_num; i++) {				//顺序查找满足条件且剩余空间最大的空间块
		if (kj[i].length >= job_length&&kj[i].tag == -1) {//找到符合条件的了，判断是否最大
			if (kj[i].length - job_length > maxleave) {
				maxleave = kj[i].length - job_length;
				maxtag = i;
				flag = 1;
			}
		}
	}//跑完循环以后分配空间
	if (flag) {
		for (j = kjk_num; j > maxtag + 1; j--) {
			kj[j] = kj[j - 1];//由于要分空间块，所以将所有空间块后移一个腾出空间
		}
		kj[maxtag].tag = job_name;//记录下进程号
		kj[maxtag + 1].length = kj[maxtag].length - job_length;//初始化剩余空间的长度
		kj[maxtag + 1].tag = -1;
		kj[maxtag].length = job_length; //原空间块的大小就变成了用掉的大小
		kj[maxtag + 1].start = kj[maxtag].start + job_length;//初始化后一个的起点
		kjk_num++;//多了一个空间块
	}
}

void connect(int a, int b) {//调用的时候必须a<b
	kj[a].length += kj[b].length;
	for (int i = b; i + 1 < kjk_num; i++) {
		kj[i] = kj[i + 1];
	}
	kjk_num--;
}

void free(int jcno,int room) {
	int flag = 0;
	for (int i = 0; i < kjk_num; i++) {
		if (kj[i].tag == jcno&&kj[i].length==room) {//找到该进程的占用块
			kj[i].tag = -1;//标记为空闲
			if (i - 1 >= 0 && kj[i - 1].tag == -1) {//如果可以和前一个连起来
				connect(i - 1, i);
				i--;
				flag = 1;//连接了，少了一个
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