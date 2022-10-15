/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-09-17 11:44:46
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-09-17 11:52:44
 * @FilePath: \人工智能物联网\C语言\项目\src\guanliyuan.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"guanliyuan.h"
#include"caipiao.h"
#include"caimin.h"

extern caipiao* cphead = NULL;//彩票链表头指针
extern caipiao* cpend = NULL;//彩票链表尾指针
extern cm* cmhead = NULL;//彩民链表头指针
extern cm* cmend = NULL;//彩民链表尾指针
extern int cpnum = 0;//已发行彩票数量
extern int cmnum = 0;//彩民数量
extern cmgmcp* cmgmcphead;

void guanliyuandenglu(int* cpnum) {
	char name[100];
	char password[100];
	int i = 0;
	int a;
	do {
		printf("请输入管理员用户名：");
		scanf("%s", name);
		getchar();
		printf("请输入管理员密码：");
		scanf("%s", password);
		getchar();
		//管理员账号密码判断，正确则执行下一步，错误则重新输入，三次以后自动退出程序
		if (strcmp(name, "admin") == 0 && strcmp(password, "admin") == 0) {
			do {
				guanliyuancaidan();
				printf("请输入您的操作：");
				scanf("%d", &a);
				switch (a) {
				case 1:
					//发行彩票
					faxingcaipiao(cpnum);
					break;
				case 2:
					//查询彩民信息
					chaxuncaiminxinxi();
					break;
				case 3:
					//排序
					paixu();
					break;
				case 4:
					//保存
					save();
					break;
				case 5:
					chakancaipiao(cpnum);
					break;
				case 6:
					//返回上一级
					return;
				default:
					printf("您的输入有误，请重新输入！\n");
					a = 1;
				}
			} while (a);
		}
		else {
			printf("您输入的账号或密码有误，请重新输入！\n");
			i++;
		}
	} while (i < 3);
	if (i >= 3) {
		printf("输入三次错误，强制退出程序，拜拜！\n");
		exit(0);
	}
}
void guanliyuancaidan() {
	//管理员登陆成功后的操作菜单
	printf("\n\n");
	printf("------------------------------------管理员菜单------------------------------------\n");
	printf("1.发行彩票\t2.查询彩民信息\t3.排序\t4.保存\t5.查看彩票\t6.返回上一级\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("\n\n");
}
void faxingcaipiao(int* cpnum) {
	caipiao* new = malloc(sizeof(caipiao));//创建一个新的结点
	if (*cpnum == 0) {//还没有发布过彩票
		shuru(new);
		new->zhuangjiajine = 1000000.0f;
		cphead = new;
		cpend = new;
		*cpnum = *cpnum + 1;
		printf("发布成功！\n");
	}
	else {//已经发过彩票
		//还没开奖
		if (cpend->kaijiangzhuangtai == 0) {
			printf("上期彩票尚未开奖，不可以增加彩票发行！\n");
		}
		//已经开奖
		else {
			shuru(new);
			new->zhuangjiajine = cpend->zhuangjiajine * 1.0;
			for (caipiao* t = cphead; t != NULL; t = t->next) {
				if (new->NO == t->NO) {
					printf("该期彩票已被发布过，请重新输入！\n");
					return;
				}
			}
			*cpnum = *cpnum + 1;
			cpend->next = new;
			cpend = new;
			printf("发布成功！\n");
		}
	}
}
void chaxuncaiminxinxi() {
	int a;
	do {
		printf("\n\n");
		printf("--------------------------查询彩民信息菜单--------------------------\n");
		printf("1.根据彩民账号查询\t2.根据彩民账户余额区间查询\t3.返回上一级\n");
		scanf("%d", &a);
		switch (a) {
		case 1:
			//根据彩民账号查询
			caiminzhanghaochaxun();
			break;
		case 2:
			//根据彩民账户余额区间查询
			caiminyuechaxun();
			break;
		case 3:
			//返回上一级
			return;
		default:
			//输入错误
			printf("您的输入有误，请重新输入！\n");
			a = 1;
		}
	} while (a);
}
void caiminzhanghaochaxun() {//彩民账号查询
	cm* t = cmhead;
	char a[100];

	printf("请输入您要查询的彩民账号：");
	scanf("%s", a);
	getchar();
	for (int i = 0; i < cmnum; i++, t = t->next) {
		if (strcmp(a, t->name) == 0) {
			printf("彩民账号：%s\n", t->name);
			printf("彩民密码：%s\n", t->password);
			printf("彩民余额：%.2f\n", t->money);
			return;
		}
	}
	printf("没有您查询的这个人！\n");
}
void caiminyuechaxun() {//彩民余额范围查询
	cm* t = cmhead;
	int a, b;
	int c = 0;
	int i = 0;
	printf("请输入您要查询的彩民余额区间：");
	scanf("%d %d", &a, &b);
	for (; i < cmnum; i++, t = t->next) {
		if (t->money >= a && t->money <= b) {
			printf("彩民账号：%s\n", t->name);
			printf("彩民密码：%s\n", t->password);
			printf("彩民余额：%.2f\n", t->money);
			printf("\n");
			c++;
		}
	}
	if (c == 0) {
		printf("没有这个范围内的账号！\n");
	}
}
void paixu()




{//对彩民进行排序
	cm* p = cmhead;//指向指针
	cm* x = cmhead;//指向指针的前一个指针

	for (int i = 0; i < (cmnum - 1); i++) {//冒泡排序
		p = cmhead;
		x = cmhead;
		for (int j = 0; j < (cmnum - 1 - i); j++) {
			if ((p->money) > (p->next->money)) {
				if (p == cmhead) {//如果是头结点
					cmhead = p->next;
					p->next = p->next->next;
					x = cmhead;
					x->next = p;
				}
				else {
					cm* t = p->next;
					p->next = t->next;
					t->next = p;
					x->next = t;
					x = t;
				}
			}
			else {
				x = p;
				p = p->next;
			}
		}
	}
	cm* q = cmhead;
	if (q == NULL) {
		printf("当前没有用户注册\n");
		return;
	}
	printf("彩民账号\t彩民密码\t彩民余额\n");
	for (int i = 0; i < cmnum; i++) {//输出
		printf("%s\t\t%s\t\t%.2f\n", q->name, q->password, q->money);
		q = q->next;
	}
}
void save() {//保存到文件中
	FILE* fp1 = fopen("./bat/guanliyuan.bat", "wb");
	caipiao* t = cphead;
	FILE* fp2 = fopen("./bat/caimin.bat", "wb");
	cm* p = cmhead;
	FILE* fp3 = fopen("./bat/caimingoumaicaipiao.bat", "wb");
	cmgmcp* q = cmgmcphead;
	while (t != NULL) {
		fwrite(t, sizeof(caipiao), 1, fp1);
		t = t->next;
	}
	while (p != NULL) {
		fwrite(p, sizeof(cm), 1, fp2);
		p = p->next;
	}
	while (q != NULL) {
		fwrite(q, sizeof(cmgmcp), 1, fp3);
		q = q->next;
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	printf("保存成功！\n");
}