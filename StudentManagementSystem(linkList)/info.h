#define bool int
#define true 1
#define false 0
#define MAX_SIZE 1024
#define FILE_PATH "studentsInfo.txt"
#define NOT_FOUND -1
#define START_LOC 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生信息的定义
typedef struct
{
    char no[MAX_SIZE];    // 学号
    char name[MAX_SIZE]; // 姓名
    int pirce;     // 成绩
}Stu;

// 链表结点
typedef struct Node
{
    Stu data;
    struct Node *nxt; 
}Node, *LinkList;

// 1.根据指定学生数目,逐个输入学生信息,初始化链表
bool initByInput(LinkList *linkList);
// 2.从指定文件输入学生信息初始化链表
bool initFromFile(LinkList *linkList);
// 3.逐个显示学生表中所有学生的信息
void showInfo(LinkList linkList, int idx);
// 4.根据学生姓名查找,返回学生的学号和成绩,可能存在重名的情况
LinkList searchByName(char *name, LinkList linkList);
// 5.返回链表中指定位置下的学生信息
Node searchByLocation(int location, LinkList linkList);
// 6.给定学生信息,在指定位置进行插入
bool insertStu(int location, Node *info, LinkList *linkList);
// 7.删除指定位置的学生信息
bool delStuByLocation(int location, LinkList *linkList);
// 8.删除学号重复的学生
bool delStuByNo(LinkList linkList);
// 9.统计学生个数
int countNumOfStu(LinkList linkList);
// 10.展示选择项
void showMenu();

// 清空缓存区
void flush();
// 得到合法的序号选项:
int getChoice();
// 判断是否是一个合法的数
bool isDigit(char *num);
// 将数字字符转换为数字
int getNum(char *num);
// 得到一个合法位置或成绩
int getLocORMark(int ch);