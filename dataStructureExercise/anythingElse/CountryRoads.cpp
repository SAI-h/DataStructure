#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 510, M = 2 * 16010;
int h[N], e[M], ne[M], w[M], idx;
int n, m, ans[N], maxv[N];
// maxv[j]: 存储0-j的最大路径长度
bool st[N];
queue<int> q;

void add(int a, int b, int c){
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u, int fa){
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(j == fa) continue;
        // din[j] -= 2;
        ans[j] = min(ans[j], max(maxv[u], w[i]));
        maxv[j] = max(maxv[j], w[i]);
        dfs(j, u);
    }
}

int main(void){
    int T;
    scanf("%d", &T);

    for(int k = 1; k <= T; k ++){
        memset(h, -1, sizeof h);
        idx = 0;
        memset(st, false, sizeof st);
        memset(ans, 0x3f, sizeof ans);
        memset(maxv, 0, sizeof maxv);


        scanf("%d%d", &n, &m);
        while(m --){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c), add(b, a, c);
        }

        int tt;
        scanf("%d", &tt);

        dfs(tt, -1);
    
        printf("Case %d:\n", k);
        for(int i = 0; i < n; i ++) 
            if(ans[i] == 0x3f3f3f3f) printf("Impossible\n");
            else printf("%d\n", ans[i]);
    }

    return 0;
}

// #include <iostream>
// #include <cstring>
// #include <queue>

// using namespace std;

// const int N = 510, M = 2 * 16010;
// int h[N], e[M], ne[M], w[M], idx;
// int n, m, ans[N], maxv[N];
// // maxv[j]: 存储0-j的最大路径长度
// bool st[N];
// queue<int> q;
// bool gg[N][N];

// void add(int a, int b, int c){
//     e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
// }

// int main(void){
//     int T;
//     scanf("%d", &T);

//     for(int k = 1; k <= T; k ++){
//         memset(h, -1, sizeof h);
//         idx = 0;
//         memset(st, false, sizeof st);
//         memset(ans, 0x3f, sizeof ans);
//         memset(maxv, 0, sizeof maxv);


//         scanf("%d%d", &n, &m);
//         while(m --){
//             int a, b, c;
//             scanf("%d%d%d", &a, &b, &c);
//             add(a, b, c), add(b, a, c);
//         }

//         int tt;
//         scanf("%d", &tt);
//         q.push(tt);
//         ans[tt] = 0;
//         while(q.size()){
//             int t = q.front();
//             q.pop();

//             for(int i = h[t]; i != -1; i = ne[i]){
//                 int j = e[i];
//                 if(gg[j][t]) continue;
//                 cout << t << ' ' << j << endl;
//                 gg[t][j] = true;
//                 ans[j] = min(ans[j], max(maxv[t], w[i]));
//                 maxv[j] = max(maxv[j], w[i]);
//                 cout << j << ' ' << ans[j] << endl;
//                 cout << endl;
//                 if(!st[j]){
//                     st[j] = true;
//                     q.push(j);
//                 }
//             }
//         }
        
//         cout << endl;
    
//         // printf("Case %d:\n", k);
//         // for(int i = 0; i < n; i ++) 
//         //     if(ans[i] == 0x3f3f3f3f) printf("Impossible\n");
//         //     else printf("%d\n", ans[i]);
//     }

//     return 0;
// }