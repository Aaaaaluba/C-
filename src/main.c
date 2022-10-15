/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-09-17 11:44:46
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-09-17 11:52:56
 * @FilePath: \人工智能物联网\C语言\项目\src\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include<stdio.h>
#include"my.h"
#include"guanliyuan.h"
#include"caimin.h"
#include"gongzhengyuan.h"
#include"caipiao.h"

extern int cpnum;//已发行彩票数量
extern int cmnum;//彩民数量

void main() {
	int a = -1;
	read();
	do {
		zhucaidan();
		printf("请输入你的选择：");
		scanf("%d", &a);
		switch (a) {
		case 1:
			//服务器（管理员登录）
			guanliyuandenglu(&cpnum);
			continue;
		case 2:
			//客户端（彩民）
			caiminzhucedenglu(&cmnum);
			continue;
		case 3:
			//第三方（公证员）登录
			gongzhengyuandenglu(&cpnum);
			continue;
		case 4:
			//退出程序
			printf("退出程序，欢迎下次光临！\n");
			return;
		default:
			printf("您的输入有误，请重新输入！\n");
			continue;
		}
	} while (1);
}