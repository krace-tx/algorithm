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