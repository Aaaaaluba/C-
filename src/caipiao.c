/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-09-17 11:44:46
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-09-17 11:52:10
 * @FilePath: \人工智能物联网\C语言\项目\src\caipiao.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include"caipiao.h"
#include<stdio.h>
#include<string.h>

extern caipiao* cphead;
extern caipiao* cpend;

void shuru(caipiao* new) {//发行彩票输入内容
	printf("发布期号：\n");
	scanf("%d", &(new->NO));
	printf("彩票单价：\n");
	scanf("%f", &(new->price));
	new->kaijiangzhuangtai = 0;
	new->shouchuzongshu = 0;
	new->jiangjin = 0.0f;
	new->next = NULL;
}
void chakancaipiao(int* cpnum) {//查看彩票信息
	caipiao* t = cphead;
	if (t == NULL) {
		printf("当前没有彩票发行！\n");
		return;
	}
	for (int i = 0; i < *cpnum; i++) {
		printf("发布期号：%d\n", t->NO);
		printf("彩票单价：%.2f\n", t->price);
		if (t->kaijiangzhuangtai == 0) {
			printf("开奖状态：未开奖！\n");
			printf("中奖号码：暂无中奖号产生！\n");
		}
		else {
			printf("开奖状态：已开奖！\n");
			printf("中奖号码：");
			for (int i = 0; i < 7; i++) {
				printf("%d ", t->zhongjianghaoma[i]);
			}
			printf("\n");
		}
		printf("本期售出总数：%d\n", t->shouchuzongshu);
		printf("本期奖池总额：%.2f\n", t->jiangjin);
		printf("庄家剩余金额：%.2f\n", t->zhuangjiajine);
		printf("\n");
		t = t->next;
	}
}