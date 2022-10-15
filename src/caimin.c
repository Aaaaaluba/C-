/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-09-17 11:44:46
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-09-17 11:51:55
 * @FilePath: \人工智能物联网\C语言\项目\src\caimin.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include"caimin.h"
#include"caipiao.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

extern cm* cmhead;//彩民链表头指针
extern cm* cmend;//彩民链表尾指针
extern int cpnum;//已发行彩票数量
extern int cmnum;//彩民数量
extern caipiao* cphead;
extern caipiao* cpend;
extern cmgmcp* cmgmcphead = NULL;//彩民购买彩票头指针
extern cmgmcp* cmgmcpend = NULL;//彩民购买彩票尾指针

void caiminzhucedenglu(int* cmnum) {//彩民注册登陆界面
	int a;
	do {
		printf("\n\n");
		printf("--------------------------彩民登录注册菜单--------------------------\n");
		printf("请选择你的操作：\n");
		printf("1.登录\t2.注册\t3.返回上一级\n");
		scanf("%d", &a);
		switch (a) {
		case 1:
			//登录
			denglu();
			break;
		case 2:
			//注册
			zhuce(cmnum);
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
void caimincaidan() {//彩民登录后的操作菜单
	printf("\n\n");
	printf("----------------------------彩民操作菜单----------------------------\n");
	printf("1.查看个人信息\t2.修改密码\t3.账户充值\t4.下注\t5.注销\n");
	printf("6.查看历史记录\t7.返回上一级\n");
	printf("--------------------------------------------------------------------\n");
	printf("\n\n");
}
void denglu() {//彩民登录界面
	char name[100];
	char password[100];
	int i = 0;
	int a;
	int b;
	cm* t = cmhead;
	if (t == NULL) {//没彩民的时候
		printf("系统内暂无彩民！\n");
		return;
	}
	do {
		printf("请输入彩民用户名：");
		scanf("%s", name);
		getchar();
		printf("请输入彩民密码：");
		scanf("%s", password);
		getchar();
		t = cmhead;
		//判断彩民用户名密码，错误三次自动退出程序
		for (int j = 0; j < cmnum; j++, t = t->next) {
			if (strcmp(name, (t->name)) == 0 && strcmp(password, (t->password)) == 0) {
				do {
					caimincaidan();
					printf("请输入您的操作：");
					scanf("%d", &a);
					switch (a) {
					case 1:
						//查看个人信息
						caiminchakangerenxinxi(t);
						break;
					case 2:
						//修改密码
						caiminxiugaimima(t);
						break;
					case 3:
						//账户充值
						caiminzhanghuchongzhi(t);
						break;
					case 4:
						//下注
						caiminxiazhu(t);
						break;
					case 5:
						//注销
						b = caiminzhuxiao(t);
						if (b == 0) {
							return;
						}
						break;
					case 6:
						//查看历史记录
						chakanlishijilu(t);
						break;
					case 7:
						//返回上一级
						return;
					default:
						printf("您的输入有误，请重新输入！\n");
						a = 1;
					}
				} while (a);
				return;
			}
		}
		printf("您输入的账号或密码有误，请重新输入！\n");
		i++;
	} while (i < 3);
	if (i = 3) {
		printf("输入三次错误，强制退出程序，拜拜！\n");
		exit(0);
	}
}
void zhuce(int* cmnum) {//新用户注册界面
	char a[100];
	int b;
	do {
		cm* new = malloc(sizeof(cm));
		cm* t = cmhead;
		printf("请输入您的用户名：");
		scanf("%s", new->name);
		printf("请输入您的密码：");
		scanf("%s", new->password);
		printf("请再次确认您的密码：");
		scanf("%s", a);
		new->next = NULL;
		new->money = 0.0;
		if (cmhead == NULL) {//没有如果用户注册过
			if (strcmp(a, new->password) == 0) {//判断二次输入密码是否正确
				printf("注册成功！\n");
				cmhead = new;
				cmend = new;
				*cmnum = *cmnum + 1;
				return;
			}
			else {
				printf("两次输入的密码不一致，请重新输入！\n");
				b = -1;
				continue;
			}
		}
		//新用户注册
		for (int i = 0; i < *cmnum; i++) {
			if (strcmp(new->name, t->name) == 0) {
				printf("该用户名已被注册过，请重新输入！\n");
				b = -1;
				return;
			}
			t = t->next;
		}
		if (strcmp(a, new->password) == 0) {//判断二次输入密码是否正确
			printf("注册成功！\n");
			cmend->next = new;
			cmend = new;
			*cmnum = *cmnum + 1;
			return;
		}
		else {
			printf("两次输入的密码不一致，请重新输入！\n");
			b = -1;
		}
	} while (b = -1);
}
void caiminchakangerenxinxi(cm* t) {
	printf("彩民账号：%s\n", t->name);
	printf("彩民密码：%s\n", t->password);
	printf("彩民余额：%.2f\n", t->money);
}
void caiminxiugaimima(cm* t) {//彩民修改密码
	char pw1[100];
	char pw2[100];
	char pw3[100];
	int a = -1;
	do {
		printf("请输入您的原密码：");
		scanf("%s", pw1);
		getchar();
		if (strcmp(pw1, t->password) != 0) {
			printf("原密码有误，请重新输入！\n");
			continue;
		}
		printf("请输入您的新密码：");
		scanf("%s", pw2);
		getchar();
		printf("请再次输入您的新密码：");
		scanf("%s", pw3);
		getchar();
		if (strcmp(pw2, pw3) != 0) {
			printf("两次新密码不一致，请重新输入！\n");
			continue;
		}
		strcpy(t->password, pw3);
		printf("修改密码成功！\n");
		break;
	} while (a = -1);
}
void caiminzhanghuchongzhi(cm* t) {//彩民账户充值
	int a = 0;
	int b = 0;
	int c = 0;
	do {
		printf("您当前账户余额为：%.2f\n", t->money);
		printf("是否进行充值？\n");
		printf("1.是\t2.否\n");
		scanf("%d", &a);
		if (a == 1) {
			printf("输入您要充值的金额：");
			scanf("%d", &b);
			t->money = t->money + b * 1.0;
			printf("充值完成！\n");
			break;
		}
		else if (a = 2) {
			return;
		}
		else {
			printf("您的输入有误，请重新输入！\n");
			c = -1;
		}
	} while (c = -1);

}
void caiminxiazhu(cm* t) {//彩民下注
	int a;
	do {
		printf("\n\n");
		printf("------------------彩民下注页面------------------\n");
		printf("1.自选号码\t2.机选号码\t3.返回上一级\n");
		printf("请输入您的选择：");
		scanf("%d", &a);
		switch (a) {
		case 1:
			//自选号码
			zixuanhaoma(t);
			break;
		case 2:
			//机选号码
			jixuanhaoma(t);
			break;
		case 3:
			//返回上一级
			return;
		default:
			printf("输入有误，请重新输入！\n");
			break;
		}
	} while (1);
}
void zixuanhaoma(cm* t) {//自选号码进行下注（对机选加注也需在这里进行选号码）
	cmgmcp* new = malloc(sizeof(cmgmcp));
	int a;
	cmgmcp* temp = cmgmcphead;
	int b;
	int c;
	if (cpend == NULL) {//系统内没有彩票的时候
		printf("暂无新彩票发行！\n");
		return;
	}
	if (cpend->kaijiangzhuangtai == 1) {//上一期彩票开奖，暂未发布新彩票时
		printf("暂无新彩票发行！\n");
		return;
	}
	//正常下注
	printf("发布期号：%d\n", cpend->NO);
	new->NO = cpend->NO;
	printf("本期售价为：%.2f\n", cpend->price);
	printf("请输入您的自选号：");
	for (int i = 0; i < 7; i++) {
		scanf("%d", &(new->xuanzehaoma[i]));
	}
	for (temp = cmgmcphead; temp != NULL; temp = temp->next) {//加注
		if (memcmp(temp->xuanzehaoma, new->xuanzehaoma, 7) == 0) {
			if (temp->num == 5) {
				printf("已达到最大购买上限！\n");
				return;
			}
			printf("您购买过这张彩票了！\n");
			printf("是否进行加注？\n");
			printf("1.加注\t2.不加注\n");
			scanf("%d", &b);
			if (b == 1) {
				do {
					do {
						printf("输入您要加注的数量（您已下注过%d注，不可超过5注）：", temp->num);
						scanf("%d", &c);
						if (temp->num + c > 5) {
							printf("本张彩票购买已超过5注！\n");
						}
					} while (temp->num + c > 5);
					if (t->money >= c * cpend->price * 1.0) {
						t->money = t->money - c * cpend->price * 1.0;
						temp->num = temp->num + c;
						cpend->jiangjin = cpend->jiangjin * 1.0 + c * cpend->price * 1.0;
						cpend->shouchuzongshu = cpend->shouchuzongshu + c;
						cpend->zhuangjiajine = cpend->zhuangjiajine * 1.0 + c * cpend->price * 1.0;
						printf("加注成功！\n");
						return;
					}
					else {
						printf("余额不足！请重新下注！\n");
					}
				} while (t->money < c * cpend->price * 1.0);
			}
			return;
		}
	}
	//正常下注
	strcpy(new->name, t->name);
	printf("购买者姓名：%s\n", new->name);
	if (cmgmcpend == NULL) {
		new->ID = 10001;
	}
	else {
		new->ID = cmgmcpend->ID + 1;
	}
	printf("本张彩票的ID是：%d\n", new->ID);
	do {
		do {
			printf("购买注数：");
			scanf("%d", &a);
			if (a > 5) {
				printf("不可以下注超过5注！请重新选择！\n");
			}
		} while (a > 5);
		if (t->money < (cpend->price) * a * 1.0) {
			printf("余额不足！请重新下注！\n");
		}
		if (a == 0) {
			printf("您没有进行下注！\n");
			return;
		}
	} while (t->money < (cpend->price) * a * 1.0);
	new->num = a;
	new->next = NULL;
	if (cmgmcphead == NULL) {//彩民购买彩票头结点
		cmgmcphead = new;
		cmgmcpend = new;
		(t->money) = (t->money) - (cpend->price) * (new->num) * 1.0;
		cpend->jiangjin = cpend->jiangjin * 1.0 + (new->num) * cpend->price * 1.0;
		cpend->shouchuzongshu = cpend->shouchuzongshu + (new->num);
		cpend->zhuangjiajine = cpend->zhuangjiajine * 1.0 + (new->num) * cpend->price * 1.0;
		printf("下注成功！\n");
		return;
	}
	cmgmcpend->next = new;
	cmgmcpend = new;
	(t->money) = (t->money) - (cpend->price) * (new->num) * 1.0;
	cpend->jiangjin = cpend->jiangjin * 1.0 + (new->num) * cpend->price * 1.0;
	cpend->shouchuzongshu = cpend->shouchuzongshu + (new->num);
	cpend->zhuangjiajine = cpend->zhuangjiajine * 1.0 + (new->num) * cpend->price * 1.0;
	printf("下注成功！\n");
}
void jixuanhaoma(cm* t) {
	cmgmcp* new = malloc(sizeof(cmgmcp));
	int a;
	cmgmcp* temp = cmgmcphead;
	int b;
	if (cpend == NULL) {
		printf("暂无新彩票发行！\n");
		return;
	}
	if (cpend->kaijiangzhuangtai == 1) {
		printf("暂无新彩票发行！\n");
		return;
	}
	printf("发布期号：%d\n", cpend->NO);
	new->NO = cpend->NO;
	printf("本期售价为：%.2f\n", cpend->price);

	printf("机选号分别是：");
	for (int i = 0; i < 6; i++) {
		b = rand() % 32 + 1;
		new->xuanzehaoma[i] = b;
		printf("%d ", new->xuanzehaoma[i]);
	}
	b = rand() % 16 + 1;
	(new->xuanzehaoma[6]) = b;
	printf("%d\n", new->xuanzehaoma[6]);
	strcpy(new->name, t->name);
	printf("购买者姓名：%s\n", new->name);
	if (cmgmcpend == NULL) {
		new->ID = 10001;
	}
	else {
		new->ID = cmgmcpend->ID + 1;
	}
	printf("本张彩票的ID是：%d\n", new->ID);
	do {
		do {
			printf("购买注数：");
			scanf("%d", &a);
			if (a > 5) {
				printf("不可以下注超过5注！请重新选择！\n");
			}
		} while (a > 5);
		if (t->money < (cpend->price) * a * 1.0) {
			printf("余额不足！请重新下注！\n");
		}
		if (a == 0) {
			printf("您没有进行下注！\n");
			return;
		}
	} while (t->money < (cpend->price) * a * 1.0);
	new->num = a;
	new->next = NULL;
	if (cmgmcphead == NULL) {//彩民购买彩票头结点
		cmgmcphead = new;
		cmgmcpend = new;
		(t->money) = (t->money) - (cpend->price) * (new->num) * 1.0;
		cpend->jiangjin = cpend->jiangjin * 1.0 + (new->num) * cpend->price * 1.0;
		cpend->shouchuzongshu = cpend->shouchuzongshu + (new->num);
		cpend->zhuangjiajine = cpend->zhuangjiajine * 1.0 + (new->num) * cpend->price * 1.0;
		printf("下注成功！\n");
		return;
	}
	cmgmcpend->next = new;
	cmgmcpend = new;
	(t->money) = (t->money) - (cpend->price) * (new->num) * 1.0;
	cpend->jiangjin = cpend->jiangjin * 1.0 + (new->num) * cpend->price * 1.0;
	cpend->shouchuzongshu = cpend->shouchuzongshu + (new->num);
	cpend->zhuangjiajine = cpend->zhuangjiajine * 1.0 + (new->num) * cpend->price * 1.0;
	printf("下注成功！\n");
}
int caiminzhuxiao(cm* t) {
	cm* p = cmhead;
	cmgmcp* pp = cmgmcphead;
	char choice;
	getchar();
	printf("是否注销账号（注销后所有数据清空）？\n输入（Y/N）：");
	scanf("%c", &choice);
	getchar();
	if (choice == 'Y' || choice == 'y') {
		cm* q = p;
		cmgmcp* qq = pp;
		for (int i = 0; i < cmnum; i++) {//删除彩民结构体结点
			if (strcmp(t->name, p->name) == 0) {
				if (p == cmhead) {
					cmhead = cmhead->next;
					cmnum = cmnum - 1;
				}
				else {
					q->next = p->next;
					cmnum = cmnum - 1;
				}
				break;
			}
			else {
				q = p;
				p = p->next;
			}
		}
		//删除彩民购买彩票结构体结点

		if (pp != NULL) {
			for (; pp != NULL; qq = pp, pp = pp->next) {
				if (strcmp(t->name, pp->name) == 0) {
					if (pp == cmgmcphead) {
						cmgmcphead = cmgmcphead->next;
					}
					else {
						qq->next = pp->next;
					}
				}
			}
		}

		printf("注销成功！\n");
		return 0;
	}
	else {
		printf("谢天谢地你没删！\n");
		return 1;
	}
}
void chakanlishijilu(cm* t) {
	printf("\n\n");
	cmgmcp* p = cmgmcphead;
	int a = 0;

	if (p == NULL) {
		printf("您暂未购买过彩票！\n");
		return;
	}
	for (; p != NULL; p = p->next) {//所有彩民购买过的彩票
		if (strcmp(t->name, p->name) == 0) {//找到该账户购买的所有彩票
			printf("\n发布期号：%d\n", p->NO);
			printf("本张彩票ID：%d\n", p->ID);
			printf("本张彩票选择的号码是：");
			for (int i = 0; i < 7; i++) {
				printf("%d ", p->xuanzehaoma[i]);
			}
			printf("\n");
			printf("购买者账号：%s\n", p->name);
			printf("本期彩票中奖号码：");
			for (caipiao* t = cphead; t != NULL; t = t->next) {//发布过的所有彩票
				if (t->NO == p->NO) {//找到跟该账户购买过的彩票同期发行的期号
					if (t->kaijiangzhuangtai == 1) {//判断是否开奖
						for (int i = 0; i < 7; i++) {
							printf("%d ", p->zhongjianghaoma[i]);
						}
						printf("\n");
						printf("奖项等级：%s！\n", p->jiangxiangdengji);
						printf("已购买注数：%d\n", p->num);
						printf("中奖金额为：%.2f\n", p->zhongjiangprice);
					}
					else {
						printf("暂未开奖！\n");
					}
				}
			}
			a++;
		}
	}
	if (a == 0) {
		printf("您暂未购买过彩票！\n");
	}
}