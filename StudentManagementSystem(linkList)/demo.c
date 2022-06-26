#include "function.c"

int main(void){
    LinkList p = NULL;
    int choice = -1;
    do{
        showMenu();
        choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                if(initByInput(&p)) 
                    printf("\n恭喜！录入成功!\n\n");
                else
                    printf("\n抱歉!录入失败,请重试!\n\n");
                break;
            }
            case 2:
            {
                if(initFromFile(&p))
                    printf("\n恭喜！录入成功！\n\n");
                else
                    printf("\n抱歉！录入失败,请重试!\n\n");
                break;
            }
            case 3:
            {
                showInfo(p, START_LOC);
                break;
            }
            case 4:
            {
                char name[MAX_SIZE];
                printf("请输入你想要查询的学生姓名:");
                scanf("%s", name);
                flush();
                LinkList stus = searchByName(name, p);
                if(stus == NULL)
                    printf("\n没有名为%s的学生的信息！\n\n", name);
                else{
                    printf("以下为名为%s的学生的信息详情:\n", name);
                    showInfo(stus, START_LOC);
                    free(stus);
                }
                break;
            }
            case 5:
            {
                printf("请输入你想要查询的学生信息的指定位置:");
                int loc = getLocORMark(0);
                Node info = searchByLocation(loc, p);
                if(info.data.pirce == NOT_FOUND)
                    printf("\n抱歉！未能找到该位置的学生信息！\n\n");
                else{
                    (&info)->nxt = NULL;
                    showInfo(&info, loc);
                }
                break;
            }
            case 6:
            {
                Node* stu = (Node*)malloc(sizeof (struct Node));
                printf("请输入你要加入学生的位置:");
                int loc = getLocORMark(0);
                printf("请输入学生的学号:");
                scanf("%s", stu->data.no);
                printf("请输入学生的姓名:");
                scanf("%s", stu->data.name);
                printf("请输入学生的成绩:");
                stu->data.pirce = getLocORMark(1);
                stu->nxt = NULL;
                if(insertStu(loc, stu, &p))
                    printf("\n插入成功！\n\n");
                break;
            }
            case 7:
            {
                printf("请输入你想删除的学生位置:");
                int loc = getLocORMark(0);
                if(delStuByLocation(loc, &p))
                    printf("\n删除成功！\n\n");
                else
                    printf("\n删除失败！请检查学生信息表单是否为空,或删除的位置过大！\n\n");
                break;
            }
            case 8:
            {
                if(delStuByNo(p))
                    printf("\n学号去重成功！\n\n");
                break;
            }
            case 9:
            {
                printf("\n当前学生人数为:%d\n\n", countNumOfStu(p));
                break;
            }
        }
    }while(choice != 10);
    free(p);
    return 0;
}