#define MAX_SIZE 1024
#define bool int
#define true 1
#define false 0
#define ASCII_RANGE 128
#define FILE_PATH "article.txt"
#define CODE_FILE_PATH "afterCode.txt"
#define DECODE_FILE_PATH "afterDecode.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 哈夫曼树结构
typedef struct HfNode
{
    char letter;
    int weight;
    struct HfNode *left;
    struct HfNode *right;
}HfNode, *HfTree;

// 定义小根堆
typedef struct Heap
{
    HfNode *item; // 存储堆元素的数组
    int sz; // 堆当前元素的个数
    int capacity; // 堆的最大容量
}Heap;

// 建立空的小根堆
Heap* buildEmptyHeap(int cap);
// 下沉堆数组中的loc号元素
void down(Heap *heap, int loc);
// 上升堆数组中的loc号元素
void up(Heap *heap, int loc);
// 判断堆是否为空
bool isEmpty(Heap *heap);
// 删除堆顶元素,并返回
HfNode* delItem(Heap *heap);
// 在堆中插入新元素
bool insertItem(Heap *heap, HfNode *item);
// 交换两个元素
void swap(HfNode *a, HfNode *b);
// 阅读文本,统计单词数目
int* readArticle(char *fileName);
// 根据字符及其频率创建堆
Heap* buildHeap(int *record);
// 建立哈夫曼树
HfTree buildHfTree(Heap *heap);
// 通过哈夫曼树形成各字符与之对应的编码
void translate(HfTree hf, char *code);
// 生成编码后的文件
void proBin(char *inputFile, char *outputFile);
// 生成译码后的文件
void decoding(char *inputFile, char *outputFile, HfTree hf);
// 释放空间
void free_hf(HfTree hf);