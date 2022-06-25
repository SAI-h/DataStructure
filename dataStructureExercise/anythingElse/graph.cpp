#include <iostream>
#include <cstring>
#include <map>
#include <queue>

using namespace std;

const int N = 10010, M = 1000010;
// 10000 * 10000 / 2 * 10000 = 10 ^ 12 / 2
typedef long long ll;
typedef pair<int, int> PII;
int h[N], e[M], ne[M], idx;
ll w[M];
map<PII, int> dr;
int n, m;

priority_queue<PII, vector<PII>, greater<PII> > q;
ll dist[N];
bool st[N];
int cost[N];

int add(int a, int b, int c){
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int main(void){
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for(int i = 0; i < m; i ++){
        int op, a, b, w;
        scanf("%d%d%d%d", &op, &a, &b, &w);
        if(!op)
            dr[{b, a}] = 1;
        add(a, b, w), add(b, a, w);
    }

    for(int i = 2; i <= n; i ++) dist[i] = 1e12;
    q.push({0, 1});
    memset(cost, 0x3f, sizeof cost);
    cost[1] = 0;
    while(q.size()){
        PII t = q.top();
        q.pop();

        int ver = t.second;

        if(ver == n){
            printf("%lld %d\n", dist[n], cost[n]);
            break;
        }

        if(st[ver]) continue;

        long long distance = t.first;
        for(int i = h[ver]; i != -1; i = ne[i]){
            int j = e[i];
            if(dist[j] > distance + w[i]){
                dist[j] = distance + w[i];
                if(dr[{ver, j}])
                    cost[j] = cost[ver] + 1;
                else
                    cost[j] = cost[ver];
                q.push({dist[j], j});
            }
        }
    }

    return 0;
}