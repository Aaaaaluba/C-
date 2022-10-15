/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-09-17 11:44:46
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-09-17 11:50:24
 * @FilePath: \人工智能物联网\C语言\项目\include\caipiao.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
struct Caipiao {//管理员彩票信息
	int NO;//发布期号
	float price;//彩票单价
	int kaijiangzhuangtai;//开奖状态：1 开奖  0 没开奖
	int zhongjianghaoma[7];//中奖号码（中奖数字共有7个）
	int shouchuzongshu;//本期售出总数
	float jiangjin;//本期奖池总额
	float zhuangjiajine;//庄家钱包金额
	struct Caipiao* next;
};
struct Caimingoumaicaipiao {//彩民购买彩票信息
	int NO;//发布期号
	int ID;//每张彩票唯一标识ID
	int zhongjianghaoma[7];//中奖号码（中奖数字共有7个）
	int xuanzehaoma[7];//买彩票时选的号码（数字共有7个）
	char name[100];//购买者账号
	int num;//已购买的注数（单张彩票不能超过5注）
	float zhongjiangprice;//中奖金额
	char jiangxiangdengji[100];//获得几等奖
	struct Caimingoumaicaipiao* next;
};
typedef struct Caipiao caipiao;
typedef struct Caimingoumaicaipiao cmgmcp;

void shuru(caipiao*);//管理员发行彩票输入内容
void chakancaipiao(int*);//公证员查看彩票信息内容