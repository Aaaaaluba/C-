/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-09-17 11:44:46
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-09-17 11:53:10
 * @FilePath: \人工智能物联网\C语言\项目\src\my.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include<stdio.h>
#include<stdlib.h>
#include"my.h"
#include"caipiao.h"
#include"caimin.h"

extern cm* cmhead;//彩民链表头指针
extern cm* cmend;//彩民链表尾指针
extern caipiao* cphead;
extern caipiao* cpend;
extern cmgmcp* cmgmcphead;//彩民购买彩票头指针
extern cmgmcp* cmgmcpend;//彩民购买彩票尾指针
extern int cpnum;
extern int cmnum;

void zhucaidan() {
	printf("\n\n");
	printf("------------------------------主菜单------------------------------\n");
	printf("1.服务器（管理员登录）\t2.客户端（彩民）登录\t3.第三方（公证员）登录\n");
	printf("4.退出程序\n");
	printf("------------------------------------------------------------------\n");
	printf("\n\n");
}

void read() {//读取历史文件

	int len1;
	caipiao* t1;

	int len2;
	cm* t2;



	FILE* fp1 = fopen("./bat/guanliyuan.bat", "rb");
	if (fp1 != NULL) {
		t1 = malloc(sizeof(caipiao));
		len1 = fread(t1, sizeof(caipiao), 1, fp1);
		while (len1 != 0) {
			t1->next = NULL;
			if (cphead == NULL) {
				cphead = t1;
				cpend = t1;
				cpnum += 1;
			}
			else {
				cpnum += 1;
				cpend->next = t1;
				cpend = t1;
			}
			t1 = malloc(sizeof(caipiao));
			len1 = fread(t1, sizeof(caipiao), 1, fp1);
		}
		fclose(fp1);
	}


	FILE* fp2 = fopen("./bat/caimin.bat", "rb");
	if (fp2 != NULL) {
		t2 = malloc(sizeof(cm));
		len2 = fread(t2, sizeof(cm), 1, fp2);
		while (len2 != 0) {
			t2->next = NULL;
			if (cmhead == NULL) {
				cmhead = t2;
				cmend = t2;
				cmnum += 1;
			}
			else {
				cmnum += 1;
				cmend->next = t2;
				cmend = t2;
			}
			t2 = malloc(sizeof(cm));
			len2 = fread(t2, sizeof(cm), 1, fp2);
		}
		fclose(fp2);
	}



	int len3;
	cmgmcp* t3;
	FILE* fp3 = fopen("./bat/caimingoumaicaipiao.bat", "rb");
	if (fp3 != NULL) {
		t3 = malloc(sizeof(cmgmcp));
		len3 = fread(t3, sizeof(cmgmcp), 1, fp3);
		while (len3 != 0) {
			t3->next = NULL;
			if (cmgmcphead == NULL) {
				cmgmcphead = t3;
				cmgmcpend = t3;
			}
			else {
				cmgmcpend->next = t3;
				cmgmcpend = t3;
			}
			t3 = malloc(sizeof(cmgmcp));
			len3 = fread(t3, sizeof(cmgmcp), 1, fp3);
		}
		fclose(fp3);
	}



}