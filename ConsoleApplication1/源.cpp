#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 200		//定义存储数据最大值

typedef struct node
{
	int timein = maxsize;//进入时间
	int no = -1;//页面序列
	int nextuse = 0;
}job;
int queue[maxsize];
job memory[maxsize];

void FIFO(int mmax, int duilie)//置换时置换先进的
{
	int j = 0, flag = 0, cout = 0, time = 0, tmp, tmptime;
	for (int j = 0; j<duilie; j++) {
		flag = 0;
		time++;
		int mintimein = maxsize;
		for (int i = 0; i < mmax; i++) {
			if (queue[j] == memory[i].no) {//如果内存中已经有了
				flag = 1;
				break;
			}
			else {
				if (memory[i].no == -1) {//如果还没有占用 
					memory[i].no = queue[j];
					memory[i].timein = time;
					cout++;
					flag = 2;
					break;
				}
				else {
					if (memory[i].timein < mintimein) {//如果是先进的
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

bool has(int tmp,int mmax) {//看看内存中有没有这个页面
	for (int n = 0; n < mmax; n++) {
		if (memory[n].no == tmp) {
			return true;
		}
	}
	return false;
}
void OPT(int mmax, int duilie)//置换时置换先进的
{
	int j = 0, flag = 0, cout = 0, time = 0, tmp, tmpi,tnext[maxsize];
	for (int j = 0; j<duilie; j++) {
		flag = 0;
		time++;
		for (int i = 0; i < mmax; i++) {
			if (queue[j] == memory[i].no) {//如果内存中已经有了
				flag = 1;
				break;
			}
			else {
				if (memory[i].no == -1) {//如果还没有占用 
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
					if (memory[q].no == queue[p]) {//如果在后边队列中找到了内存中的页面，那就记录下一次的时间
						if (p < tnext[memory[q].no]) {
							tnext[memory[q].no] = p;//tnext中记录了页面下一次最近调用的时间
						}
					}
				}
			}

			int longnext = 0,tmpcout=0,tmpno[maxsize];
			for (int m = 0; m < maxsize; m++) {
				if (tnext[m] == maxsize&&has(m, mmax)) {//找到内存中有多少是接下去不再运行的
						tmpno[tmpcout++]=m;//记录下页面号
				}
				if (tnext[m] > longnext&&has(m,mmax)) {//找到队列里最久未用的那个
					longnext = tnext[m];
					tmpi = m;//tmpi记录了应该要替换的页面号
				}
			}
			for (int n = 0; n < mmax; n++) {
				if (memory[n].no == tmpi) {//通过页面号找到他在内存中的位置
					tmp = n;
					break;
				}
			}
			int min = 0x7f,tmpx=0,s=0;
			if (tmpcout >= 1) {//如果至少有两个是队列里不再出现的，那么就要fifo了
				for (int r = 0; r < tmpcout; r++) {
					for (s = 0; s < mmax; s++) {
						if (tmpno[r] == memory[s].no) {//通过页面号找到下标
							break;
						}
					}
					if (memory[s].timein < min) {
						min = memory[s].timein;
						tmpx = s;
					}
				}
				tmp = tmpx;
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

void LRU(int mmax, int duilie) {
	int j = 0, flag = 0, cout = 0, time = 0, tmp, tmptime;
	for (int j = 0; j<duilie; j++) {
		flag = 0;
		time++;
		int mintimein = maxsize;
		for (int i = 0; i < mmax; i++) {
			if (queue[j] == memory[i].no) {//如果内存中已经有了
				int temp = memory[i].no,r;
				for (r = i; memory[r + 1].no!=-1; r++) {//将后面的向前推
					memory[r].no = memory[r + 1].no;
				}
				memory[r].no = temp;
				flag = 1;
				break;
			}
			else {
				if (memory[i].no == -1) {//如果还没有占用 
					memory[i].no = queue[j];
					memory[i].timein = time;
					cout++;
					flag = 2;
					break;
				}
			}
		}

		if (flag == 0) {//如果找遍内存都还没有
			for (int r = 0; r < mmax-1; r++) {
				memory[r].no = memory[r + 1].no;
			}
			memory[mmax-1].no = queue[j];//就把第一个替换掉，新加的放在最后一个
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
		LRU(kuaishu, i);
		break;
	default:
		break;
	}
	return 0;
}