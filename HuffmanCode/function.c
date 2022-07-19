#include "info.h"

extern char HfCode[ASCII_RANGE][MAX_SIZE];

// 建立空的小根堆
Heap* buildEmptyHeap(int cap){
    Heap *heap = (Heap*)malloc(sizeof (struct Heap));
    heap->item = (HfNode*)malloc((cap + 1) * sizeof(struct HfNode));
    heap->sz = 0;
    heap->capacity = cap;
    return heap;
}

// 下沉堆数组中的loc号元素
void down(Heap *heap, int loc){
    int t = loc;
    if(loc * 2 <= heap->sz && heap->item[loc * 2].weight < heap->item[t].weight) t = loc * 2;
    if(loc * 2 + 1 <= heap->sz && heap->item[loc * 2 + 1].weight < heap->item[t].weight) t = loc * 2 + 1;
    if(t != loc){
        swap(&(heap->item[loc]), &(heap->item[t]));
        down(heap, t);
    }
}

// 上升堆数组中的loc号元素
void up(Heap *heap, int loc){
    while(loc / 2 && heap->item[loc / 2].weight > heap->item[loc].weight){
        swap(&(heap->item[loc]), &(heap->item[loc / 2]));
        loc /= 2;
    }
}

// 判断堆是否为空
bool isEmpty(Heap *heap){
    return heap->sz == 0;
}

// 删除堆顶元素,并返回
HfNode* delItem(Heap *heap){
    HfNode *res = (HfNode*)malloc(sizeof (struct HfNode));
    *res = heap->item[1];
    heap->item[1] = heap->item[heap->sz];
    heap->sz --;
    down(heap, 1);
    return res;
}

// 在堆中插入新元素
bool insertItem(Heap *heap, HfNode *item){
    if(heap->sz == heap->capacity) return false;
    heap->sz ++;
    heap->item[heap->sz] = *item;
    up(heap, heap->sz);
    return true;
}

// 交换两个元素
void swap(HfNode *a, HfNode *b){
    HfNode tmp = *a;
    *a = *b;
    *b = tmp;
}

// 阅读文本,统计单词数目
int* readArticle(char *fileName){
    int *record = (int *)malloc(ASCII_RANGE * sizeof(int));
    for(int i = 0; i < ASCII_RANGE; i ++) record[i] = 0;
    FILE* fp = fopen(fileName, "rt");
    while(!feof(fp)){
        char ch = fgetc(fp);
        record[ch] ++;
    }
    fclose(fp);
    return record;
}

// 根据字符及其频率创建堆
Heap* buildHeap(int *record){
    Heap *heap = buildEmptyHeap(MAX_SIZE);
    for(int i = 0; i < ASCII_RANGE; i ++)
        if(record[i]){
            HfNode *tmp = (HfNode*)malloc(sizeof (struct HfNode));
            tmp->letter = i;
            tmp->weight = record[i];
            tmp->left = tmp->right = NULL;
            insertItem(heap, tmp);
        }
    return heap;
}

// 建立哈夫曼树
HfTree buildHfTree(Heap *heap){
    int sz = heap->sz;
    // 共sz个元素,每次循环减少一个(-2+1)元素,sz-1次循环后只剩下一个元素
    for(int i = 0; i < sz - 1; i ++){
        HfNode *t = (HfNode *)malloc(sizeof (struct HfNode));
        t->left = delItem(heap);
        t->right = delItem(heap);
        t->weight = t->left->weight + t->right->weight;
        insertItem(heap, t);
    }
    return delItem(heap);
}

// 通过哈夫曼树形成各字符与之对应的编码
void translate(HfTree hf, char *code){
    if(hf->left == NULL && hf->right == NULL){
        strcpy(HfCode[hf->letter], code);
        return;
    }
    int len = strlen(code);
    if(hf->left){
        code[len] = '0';
        code[len + 1] = '\0';
        translate(hf->left, code);
        code[len] = '\0';
    }
    if(hf->right){
        code[len] = '1';
        code[len + 1] = '\0';
        translate(hf->right, code);
        code[len] = '\0';
    }
}

// 生成编码后的文件
void proBin(char *inputFile, char *outputFile){
    FILE* fin = fopen(inputFile, "rt");
    FILE* fout = fopen(outputFile, "w");
    while(!feof(fin)){
        char ch = fgetc(fin);
        fprintf(fout, "%s", HfCode[ch]);
    }
    fclose(fin);
    fclose(fout);
}

// 生成译码后的文件
void decoding(char *inputFile, char *outputFile, HfTree hf){
    /*
    FILE* fin = fopen(inputFile, "rt");
    FILE* fout = fopen(outputFile, "w");
    char con[MAX_SIZE] = "";
    int len = 0;
    while(!feof(fin)){
        char ch = fgetc(fin);
        con[len] = ch;
        con[len + 1] = '\0';
        bool flag = false;
        for(int i = 0; i < ASCII_RANGE; i ++)
            if(!strcmp(con, HfCode[i])){
                fprintf(fout, "%c", i);
                len = 0;
                flag = true;
                break;
            }
        if(!flag) len ++;
    }
    fclose(fin);
    fclose(fout);
    */
    // 用现有的哈夫曼树能更加高效地实现译码功能
    HfTree head = hf;
    FILE* fin = fopen(inputFile, "rt");
    FILE* fout = fopen(outputFile, "w");
    while(!feof(fin)){
        char ch = fgetc(fin);
        if(ch == '0')
            head = head->left;
        else
            head = head->right;
        if(head->left == NULL && head->right == NULL){
            fprintf(fout, "%c", head->letter);
            head = hf;
        }
    }
    fclose(fin);
    fclose(fout);
}

// 释放空间
void free_hf(HfTree hf){
    if(hf->left) free_hf(hf->left);
    if(hf->right) free_hf(hf->right);
    free(hf);
}