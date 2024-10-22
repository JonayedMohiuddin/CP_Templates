#include<bits/stdc++.h>
using namespace std;

// DFS

int n;                   // number of vertices
vector<vector<int>> adj; // graph represented as an adjacency list
vector<int> color;
vector<int> time_in, time_out;
int dfs_timer = 0;

void dfs(int v)
{
    time_in[v] = dfs_timer++;
    color[v] = 1;
    for (int u : adj[v])
        if (color[u] == 0)
            dfs(u);
    color[v] = 2;
    time_out[v] = dfs_timer++;
}

// BFS

vector<vector<int>> adj; // adjacency list representation
int n;                   // number of nodes
int s;                   // source vertex

queue<int> q;
vector<bool> used(n);
vector<int> d(n), p(n);

q.push(s);
used[s] = true;
p[s] = -1;
while (!q.empty())
{
    int v = q.front();
    q.pop();
    for (int u : adj[v])
    {
        if (!used[u])
        {
            used[u] = true;
            q.push(u);
            d[u] = d[v] + 1;
            p[u] = v;
        }
    }
}

if (!used[u]) {
    cout << "No path!";
} else {
    vector<int> path;
    for (int v = u; v != -1; v = p[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    cout << "Path: ";
    for (int v : path)
        cout << v << " ";
}

