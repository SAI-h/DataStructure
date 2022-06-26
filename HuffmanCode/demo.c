#include "function.c"

// 存储各字符与其对应的编码(前缀码)
char HfCode[ASCII_RANGE][MAX_SIZE];

int main(void){
    int *record = readArticle(FILE_PATH);
    Heap *heap = buildHeap(record);
    HfTree hf = buildHfTree(heap);
    char str[MAX_SIZE] = "";
    translate(hf, str);
    proBin(FILE_PATH, CODE_FILE_PATH);
    decoding(CODE_FILE_PATH, DECODE_FILE_PATH, hf);
    free(record);
    free(heap);
    free_hf(hf);
    return 0;
}