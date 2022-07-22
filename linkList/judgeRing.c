/*
21.单链表有环,是指单链表的最后一个结点指向了链表中的某个结点.试着编写算法判断单链表是否存在环.
*/

#include "relatedFun.c"

// 循环单链表的输出
void outputRLinkList(LinkList L, int length) {
    for(int i = 0; i < 2 * length; i ++) {
        printf("%d", L -> data);
        if(i != 2 * length - 1) printf("->");
        L = L -> next;
    }
    printf("...\n");
}

// 这里采取的方法是设置快慢指针:一个fast,每次移动两个单位;一个slow,每次移动一个单位
// 如果存在环,那么fast先进入环,slow后进入环;进入环后,两个指针在若干步后一定会相遇,以此来判定环是否存在
// 之后,再来看如何获取到环的入口点的位置
// 不妨设链表起始处到环的入口点的距离为a,环的入口点沿着环的方向到相遇点的距离为x,环长为r,相遇时fast绕过了n圈
// 相遇时经过的时间相同,fast的速度时slow的两倍,因此fast经过的路程是slow经过的路程的两倍
// Sfast = Sslow * 2; 而Sslow = a + x, Sfast = a + n * r + x
// 有2(a+x)=a+nr+x ==> a = nr - x;
// 相遇点的位置距离x的位置,当前这一圈还有r-x的路程,而后再经过(n-1)圈[长度为(n-1)r]恰好能停在环的起始位置处
// 即位于相遇点,步长为1的指针,在经历(nr-x)的时刻后会停在环的入口点
// 之前又说道a=nr-x,即链表起始处到环的入口点的距离也为nr-x,即位于链表起始处,步长为1的指针,在经历(nr-x)的时刻后同样会停在环的入口点
// 即让一个指针指向链表起始处,一个指针指向fast和slow的相遇点,当这两个指针相遇时所在位置一定时在环的入口点
// 这种方法时间复杂度是O(n),空间复杂度为O(1)
// 其实更容易想到的方法是冗余一个visited字段,每访问一个结点将visited标记为true,
// 若某一次访问发现当前结点的visited值为true,则说明这个结点在之前是被访问过的,那么链表就存在了环,而该点就是环的入口点
// 只不过其空间复杂度为O(n),属于空间换取时间的一种做法
LinkList judgeRing(LinkList L) {
    LNode *fast = L, *slow = L;
    while(fast && fast -> next) { // 注意这里的条件
        fast = fast -> next -> next;
        slow = slow -> next;
        if(fast == slow) break;
    }
    if(fast == NULL || fast -> next == NULL) return NULL; // 没有环,不要写成slow!=fast,若链表只有一项,其本身没有环,但是fast等于slow
    LNode *p = L, *q = fast;
    while(p != q) {
        p = p -> next;
        q = q -> next;
    }
    return p;
}

int main(void) {
    srand((size_t)time(NULL));
    int length = rand() % Maxsize + 1;
    LinkList L = createRandomLinkList(length, rand() % Maxsize, false);
    bool hasRing = rand() % 2;
    printf("The original LinkList is:\n");
    if(!hasRing) {
        output(L, false);
    }else { // 构造带环的链表,即尾结点随机指向单链表中的任意结点
        LNode *tail = L; // 获取尾指针
        while(tail -> next) tail = tail -> next;
        int location = rand() % length; // 链表中的location号元素被尾结点next指针指向
        LNode *op = L;
        while(location --) op = op -> next;
        tail -> next = op;
        // 因为存在环,所以输出长度等于无环时自身长两倍的元素,必定能出现循环节
        outputRLinkList(L, length);
    }
    LinkList cycle = judgeRing(L);
    if(cycle == NULL) {
        printf("There are no rings in linked lists(hasRing = %d)!\n", hasRing);
    }else{
        printf("There is a ring in linked lists(hasRing = %d)!\n", hasRing);
        printf("The circular section is:\n");
        output(cycle, false);
    }
    delLinkList(&L);
    return 0;
}