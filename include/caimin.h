/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-09-17 11:44:46
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-09-17 11:49:54
 * @FilePath: \人工智能物联网\C语言\项目\include\caimin.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
struct Caimin {
	char name[100];//彩民账号（全局唯一）
	char password[100];//彩民密码
	float money;//彩民账户余额
	struct Caimin* next;
};
typedef struct Caimin cm;
void caimincaidan();
void caiminzhucedenglu(int*);
void denglu();
void zhuce(int*);
void caiminchakangerenxinxi(cm*);
void caiminxiugaimima(cm*);
void caiminzhanghuchongzhi(cm*);
void caiminxiazhu(cm*);
void zixuanhaoma(cm*);
void jixuanhaoma(cm*);
int caiminzhuxiao(cm*);
void chakanlishijilu(cm*);