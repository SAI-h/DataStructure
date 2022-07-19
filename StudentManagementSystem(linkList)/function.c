#include "info.h"

// 1.根据指定学生数目,逐个输入学生信息,初始化链表
bool initByInput(LinkList *linkList){
    printf("请输入需要录入的学生人数:");
    char num[MAX_SIZE];
    scanf("%s", num);
    flush();
    while(!isDigit(num)){
        printf("请输入一个合法的数:");
        scanf("%s", num);
        flush();
    }
    int n = getNum(num);
    for(int i = 0; i < n; i ++){
        Node* item = (Node*)malloc(sizeof (struct Node));
        if(item == NULL) return false;
        printf("请输入第%d名学生的学号:", i + 1);
        scanf("%s", item->data.no);
        flush();
        printf("请输入第%d名学生的姓名:", i + 1);
        scanf("%s", item->data.name);
        flush();
        printf("请输入第%d名学生的成绩:", i + 1);
        item->data.pirce = getLocORMark(1);
        item->nxt = *linkList;
        *linkList = item;
    }
    return true;
}

// 2.从指定文件输入学生信息初始化链表
bool initFromFile(LinkList *linkList){
    FILE* fp = fopen(FILE_PATH, "rt");
    if(fp == NULL) return false;
    while(!feof(fp)){ // 一直读到文件末尾
        Node* item = (Node*)malloc(sizeof (struct Node));
        fscanf(fp, "%s%s%d", item->data.no, item->data.name, &(item->data.pirce));
        item->nxt = *linkList;
        *linkList = item;
    }
    fclose(fp);
    return true;
}

// 3.逐个显示学生表中所有学生的信息
void showInfo(LinkList linkList, int idx){
    if(linkList == NULL){
        printf("\n暂无学生信息!\n\n");
        return;
    }
    while(linkList){
        printf("  %d号位置学生信息\n", idx ++);
        printf("学号\t姓名\t成绩\n");
        printf("%s\t%s\t%d\n", linkList->data.no, linkList->data.name, linkList->data.pirce);
        printf("--------------------\n");
        linkList = linkList->nxt;
    }
}

// 4.根据学生姓名查找,返回学生的学号和成绩,可能存在重名的情况
LinkList searchByName(char *name, LinkList linkList){
    LinkList stus = NULL;
    while(linkList){
        if(!strcmp(linkList->data.name, name)){
            Node* item = (Node*)malloc(sizeof (struct Node));
            strcpy(item->data.no, linkList->data.no);
            strcpy(item->data.name, linkList->data.name);
            item->data.pirce = linkList->data.pirce;
            item->nxt = stus;
            stus = item;
        }
        linkList = linkList->nxt;
    }
    return stus;
}

// 5.返回链表中指定位置下的学生信息
Node searchByLocation(int location, LinkList linkList){
    for(int i = 1; i < location && linkList != NULL; i ++) linkList = linkList->nxt;
    Node res;
    res.data.pirce = NOT_FOUND;
    if(linkList){
        strcpy(res.data.no, linkList->data.no);
        strcpy(res.data.name, linkList->data.name);
        res.data.pirce = linkList->data.pirce;
    }
    return res;
}

// 6.给定学生信息,在指定位置进行插入
bool insertStu(int location, Node *info, LinkList *linkList){
    LinkList tmp = *linkList;
    if(location == 1 || tmp == NULL){
        info->nxt = *linkList;
        *linkList = info;
    }else{
        for(int i = 1; i < location - 1 && tmp->nxt; i ++) tmp = tmp->nxt;
        info->nxt = tmp->nxt;
        tmp->nxt = info;
    }
    return true;
}

// 7.删除指定位置的学生信息
bool delStuByLocation(int location, LinkList *linkList){
    LinkList tmp = *linkList;
    if(tmp == NULL) return false;
    if(location == 1) *linkList = (*linkList)->nxt;
    else{
        for(int i = 1; i < location - 1 && tmp->nxt; i ++) tmp = tmp->nxt;
        if(!tmp->nxt) return false;
        Node* del = tmp->nxt;
        tmp->nxt = del->nxt;
        free(del); // 释放空间
    }
    return true;
}

// 8.删除学号重复的学生
bool delStuByNo(LinkList linkList){ // 暴力判重
    for(LinkList pre = linkList; pre; pre = pre->nxt)
        for(LinkList cur = pre; cur->nxt; )
            if(!strcmp(cur->nxt->data.no, pre->data.no)){
                Node* del = cur->nxt;
                cur->nxt = del->nxt;
                free(del);
            }else cur = cur->nxt;
    return true;
}

// 9.统计学生个数
int countNumOfStu(LinkList linkList){ // 暴力遍历
    int cnt = 0;
    while(linkList){
        cnt ++;
        linkList = linkList->nxt;
    }
    return cnt;
}

// 10.展示选择项
void showMenu(){
    printf("1.指定学生数目,输入学生信息\n");
    printf("2.从文件初始化学生信息\n");
    printf("3.逐个显示学生表中所有学生的信息\n");
    printf("4.根据学生姓名查找,得到学生基本信息\n");
    printf("5.返回指定位置下的学生信息\n");
    printf("6.在指定位置进行插入学生信息\n");
    printf("7.删除指定位置的学生信息\n");
    printf("8.删除学号重复的学生\n");
    printf("9.统计学生个数\n");
    printf("10.退出程序\n");
}

// 清空缓存区
void flush(){
    char ch;
    while((ch = getchar()) != '\n' && ch != EOF);
}

// 得到合法的序号选项:
int getChoice(){
    int choice = -1;
    char ch;
    printf("请选择你想要实现的功能(输入1~10之间的序号):");
    scanf("%d", &choice);
    // 清空输入缓存
    flush();
    while(choice < 1 || choice > 10){
        printf("请输入合法的序号值(1~10):");
        scanf("%d", &choice);
        flush();
    }
    return choice;
}

// 判断是否是一个合法的数
bool isDigit(char *num){
    for(int i = 0; num[i]; i ++)
        if(num[i] > '9' || num[i] < '0') return false;
    return true;
}

// 将数字字符转换为数字
int getNum(char *num){
    int res = 0;
    for(int i = 0; num[i]; i ++)
        res = 10 * res + (num[i] - '0');
    return res;
}

// 得到一个合法位置或成绩
int getLocORMark(int ch){
    char poi[MAX_SIZE];
    scanf("%s", poi);
    flush();
    char insert[2][MAX_SIZE] = {"位置", "成绩"};
    while(!isDigit(poi)){
        printf("请输入一个合法的%s:", insert[ch]);
        scanf("%s", poi);
        flush();
    }
    return getNum(poi);
}