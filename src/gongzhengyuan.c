/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-09-17 11:44:46
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-09-17 11:54:10
 * @FilePath: \人工智能物联网\C语言\项目\src\gongzhengyuan.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include"gongzhengyuan.h"
#include"caipiao.h"
#include"caimin.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

extern caipiao* cphead;
extern caipiao* cpend;
extern cmgmcp* cmgmcpend;
extern cmgmcp* cmgmcphead;
extern cm* cmhead;


void gongzhengyuandenglu(int* cpnum) {//公证员登陆界面
	char name[100];
	char password[100];
	int a;
	int i = 0;
	do {
		printf("请输入公证员用户名：");
		scanf("%s", name);
		getchar();
		printf("请输入公证员密码：");
		scanf("%s", password);
		getchar();
		//公证员登录账号密码判断，错误三次自动退出程序
		if (strcmp(name, "eee") == 0 && strcmp(password, "123") == 0) {
			do {
				gongzhengyuancaidan();
				printf("请输入你的选择：");
				scanf("%d", &a);
				getchar();
				switch (a) {
				case 1:
					//开奖
					kaijiang();
					break;
				case 2:
					//查看彩票信息
					chakancaipiao(cpnum);
					break;
				case 3:
					//返回上一级
					return;
				default:
					printf("您的输入有误，请重新输入！\n");
					a = 1;
				}
			} while (a);
			return;
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
void gongzhengyuancaidan() {//公证员操作菜单
	printf("\n\n");
	printf("----------------------------公证员菜单----------------------------\n");
	printf("1.开奖\t2.查看彩票信息\t3.返回上一级\n");
	printf("-------------------------------------------------------------------\n");
	printf("\n\n");
}
void kaijiang() {//公证员开奖操作
	caipiao* t = cphead;//指向指针
	cmgmcp* p = cmgmcphead;
	char a;
	int b[7];//中奖数字
	if (t == NULL) {
		printf("当前没有彩票发行！\n");
		return;
	}
	else if (cpend->kaijiangzhuangtai == 1) {
		printf("当前没有彩票发行！\n");
		return;
	}
	printf("当前尚未开奖彩票信息如下：\n");
	printf("发布期号：%d\n", cpend->NO);
	printf("彩票单价：%.2f\n", cpend->price);
	if (cpend->kaijiangzhuangtai == 0) {
		printf("开奖状态：未开奖！\n");
	}
	else {
		printf("开奖状态：已开奖！\n");
	}
	printf("本期售出总数：%d\n", cpend->shouchuzongshu);
	printf("本期奖池总额：%.2f\n", cpend->jiangjin);
	printf("是否进行开奖？（Y/N）\n");
	scanf("%c", &a);
	getchar();
	if (a == 'Y' || a == 'y') {//判断是否需要开奖
		cpend->kaijiangzhuangtai = 1;
		for (int i = 0; i < 6; i++) {
			b[i] = rand() % 32 + 1;
			cpend->zhongjianghaoma[i] = b[i];
		}
		b[6] = rand() % 16 + 1;
		cpend->zhongjianghaoma[6] = b[6];

		if (p != NULL) {
			for (; p != NULL; p = p->next) {
				if (p->NO == cpend->NO) {
					for (int i = 0; i < 7; i++) {
						p->zhongjianghaoma[i] = b[i];
					}
				}
			}
		}
		zhongjiang(b);
		printf("开奖成功！\n");
		return;
	}
	else {
		printf("拜拜！\n");
	}
}
void zhongjiang(int b[]) {//中奖算法：前6个数字为红球，取值范围1-33，第7个数字是蓝球，取值范围1-16
	cmgmcp* t = cmgmcphead;
	int c[7];//彩民购买彩票中选中的数字
	int d[7];//开奖中奖数字
	int red = 0;//红球相同数字的个数
	int blue = 0;//蓝球相同数字的个数
	char a[100];//中奖的彩民账号
	for (; t != NULL; t = t->next) {//开奖
		red = 0;
		blue = 0;
		for (int i = 0; i < 7; i++) {
			c[i] = t->xuanzehaoma[i];
			d[i] = b[i];
		}
		if (t->NO == cpend->NO) {
			for (int i = 0; i < 6; i++) {//c
				for (int j = 0; j < 6; j++) {//d
					if (c[i] == d[j]) {
						d[j] = 0;
						red++;
						break;
					}
				}
			}
			if (c[6] == d[6]) {
				blue++;
			}
			if (blue == 1) {//给钱
				switch (red) {//蓝球一个，红球数量不同奖项不同
				case 6:
					strcpy(t->jiangxiangdengji, "一等奖");
					t->zhongjiangprice = cpend->jiangjin * t->num * 0.5;
					strcpy(a, t->name);
					for (cm* p = cmhead; p != NULL; p = p->next) {
						if (strcmp(p->name, a) == 0) {
							p->money = p->money + t->zhongjiangprice * 1.0;
						}
					}
					cpend->zhuangjiajine = cpend->zhuangjiajine * 1.0 - t->zhongjiangprice * 1.0;
					break;
				case 5:
					strcpy(t->jiangxiangdengji, "三等奖");
					t->zhongjiangprice = cpend->jiangjin * t->num * 0.1;
					strcpy(a, t->name);
					for (cm* p = cmhead; p != NULL; p = p->next) {
						if (strcmp(p->name, a) == 0) {
							p->money = p->money + t->zhongjiangprice * 1.0;
						}
					}
					cpend->zhuangjiajine = cpend->zhuangjiajine * 1.0 - t->zhongjiangprice * 1.0;
					break;
				case 4:
					strcpy(t->jiangxiangdengji, "四等奖");
					t->zhongjiangprice = cpend->jiangjin * t->num * 0.08;
					strcpy(a, t->name);
					for (cm* p = cmhead; p != NULL; p = p->next) {
						if (strcmp(p->name, a) == 0) {
							p->money = p->money + t->zhongjiangprice * 1.0;
						}
					}
					cpend->zhuangjiajine = cpend->zhuangjiajine * 1.0 - t->zhongjiangprice * 1.0;
					break;
				case 3:
					strcpy(t->jiangxiangdengji, "五等奖");
					t->zhongjiangprice = cpend->jiangjin * t->num * 0.05;
					strcpy(a, t->name);
					for (cm* p = cmhead; p != NULL; p = p->next) {
						if (strcmp(p->name, a) == 0) {
							p->money = p->money + t->zhongjiangprice * 1.0;
						}
					}
					cpend->zhuangjiajine = cpend->zhuangjiajine * 1.0 - t->zhongjiangprice * 1.0;
					break;
				default://2 1 0
					strcpy(t->jiangxiangdengji, "六等奖");
					t->zhongjiangprice = cpend->jiangjin * t->num * 0.02;
					strcpy(a, t->name);
					for (cm* p = cmhead; p != NULL; p = p->next) {
						if (strcmp(p->name, a) == 0) {
							p->money = p->money + t->zhongjiangprice * 1.0;
						}
					}
					cpend->zhuangjiajine = cpend->zhuangjiajine * 1.0 - t->zhongjiangprice * 1.0;
					break;
				}
			}
			else {//蓝球数量为0，红球数量不同奖项不同
				switch (red) {
				case 6:
					strcpy(t->jiangxiangdengji, "二等奖");
					t->zhongjiangprice = cpend->jiangjin * t->num * 0.25;
					strcpy(a, t->name);
					for (cm* p = cmhead; p != NULL; p = p->next) {
						if (strcmp(p->name, a) == 0) {
							p->money = p->money + t->zhongjiangprice * 1.0;
						}
					}
					cpend->zhuangjiajine = cpend->zhuangjiajine * 1.0 - t->zhongjiangprice * 1.0;
					break;
				case 5:
					strcpy(t->jiangxiangdengji, "四等奖");
					t->zhongjiangprice = cpend->jiangjin * t->num * 0.08;
					strcpy(a, t->name);
					for (cm* p = cmhead; p != NULL; p = p->next) {
						if (strcmp(p->name, a) == 0) {
							p->money = p->money + t->zhongjiangprice * 1.0;
						}
					}
					cpend->zhuangjiajine = cpend->zhuangjiajine * 1.0 - t->zhongjiangprice * 1.0;
					break;
				case 4:
					strcpy(t->jiangxiangdengji, "五等奖");
					t->zhongjiangprice = cpend->jiangjin * t->num * 0.05;
					strcpy(a, t->name);
					for (cm* p = cmhead; p != NULL; p = p->next) {
						if (strcmp(p->name, a) == 0) {
							p->money = p->money + t->zhongjiangprice * 1.0;
						}
					}
					cpend->zhuangjiajine = cpend->zhuangjiajine * 1.0 - t->zhongjiangprice * 1.0;
					break;
				default:
					strcpy(t->jiangxiangdengji, "对不起，您暂未获奖！");
					t->zhongjiangprice = cpend->jiangjin * t->num * 0.0;
					strcpy(a, t->name);
					for (cm* p = cmhead; p != NULL; p = p->next) {
						if (strcmp(p->name, a) == 0) {
							p->money = p->money + t->zhongjiangprice * 1.0;
						}
					}
					break;
				}
			}
		}
	}
}