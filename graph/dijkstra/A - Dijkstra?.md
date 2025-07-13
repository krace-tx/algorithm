## A - Dijkstra?

**Problem Description**
You are given a weighted undirected graph. The vertices are enumerated from `1` to `n`. Your task is to find the shortest path between vertex `1` and vertex `n`.

## Input

The first line contains two integers `n` and `m` (`2` ≤ `n` ≤ `10^5`, `0` ≤ `m` ≤ `10^5`), where `n` is the number of vertices and `m` is the number of edges. Following `m` lines contain one edge each in form `a_i`, `b_i` and `w_i` (`1` ≤ `a_i`, `b_i` ≤ `n`, `1` ≤ `w_i` ≤ `10^6`), where `a_i`, `b_i` are edge endpoints and `w_i` is the length of the edge.

It is possible that the graph has loops and multiple edges between pair of vertices.

## Output

Write the only integer `-1` in case of no path. Write the shortest path in opposite case. If there are many solutions, print any of them.

## Examples

### Example 1
**Input:**
```
5 6
1 2 2
2 5 5
2 3 4
1 4 1
4 3 3
3 5 1

```
**Output:**
```
1 4 3 5 
```


### Example 2
**Input:**
```
5 6
1 2 2
2 5 5
2 3 4
1 4 1
4 3 3
3 5 1
```
**Output:**
```
1 4 3 5 
```


## ideas
1. 问题分析
我们需要在一个加权无向图中找到从顶点 1 到顶点 n 的最短路径。图的顶点数为 n，边数为 m，且可能存在自环和重边。如果不存在路径，则输出 -1。

2. 具体实现步骤
图的存储：使用邻接表（vector<pii> adj[N]）存储图结构，每个节点保存其相邻节点及边的权重。

优先队列优化：使用最小堆（priority_queue）快速获取当前距离起点最近的节点，确保算法的高效性（时间复杂度为 O((V + E) log V)）。

距离数组：dist[N] 记录从起点到每个节点的当前最短距离，初始时设为无穷大（INF），起点的距离设为 0。

父节点数组：parent[N] 记录每个节点在最短路径上的前驱节点，用于最后回溯路径。

3. 路径回溯
从终点 n 开始，通过 parent 数组逆向追踪到起点 1，得到路径的逆序。

最后将路径反转，得到从 1 到 n 的正确顺序。


## solve
```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>

const int INF = 1e18;
const int N = 1e5 + 5;

vector<pii> adj[N];
vector<int> dist(N, INF);
vector<int> parent(N, -1);

void dijkstra(int start, int n) {
    dist[start] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int current_dist = pq.top().first;
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

vector<int> f(int start, int end) {
    vector<int> path;
    for (int v = end; v != start; v = parent[v]) {
        if (v == -1) return vector<int>(); 
        path.push_back(v);
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

void code() {
    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i <= n; i++) {
        adj[i].clear();
        dist[i] = INF;
        parent[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dijkstra(1, n);

    if (dist[n] == INF) {
        cout << -1 << endl;
        return;
    }

    vector<int> path = f(1, n);
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    while(t--) code();
    return 0;
}
```
