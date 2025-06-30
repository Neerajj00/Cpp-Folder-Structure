#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;
typedef pair<int, int> P;

class Solution
{
private:
    vector<vector<P>> make(vector<vector<int>> &edges, int n)
    {
        vector<vector<P>> adj(n + 1);
        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }
        return adj;
    }

public:
    vector<int> shortestPath(int n, int m, vector<vector<int>> &edges)
    {
        vector<vector<P>> adj = make(edges, n);

        priority_queue<P, vector<P>, greater<P>> pq;
        vector<int> dist(n + 1, INT_MAX);
        vector<int> parent(n + 1, -1);

        dist[1] = 0;
        parent[1] = 1;
        pq.push({0, 1});

        while (!pq.empty())
        {
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            for (auto it : adj[node])
            {
                int newDist = d + it.second;
                int newNode = it.first;

                if (dist[newNode] > newDist)
                {
                    dist[newNode] = newDist;
                    pq.push({newDist, newNode});
                    parent[newNode] = node;
                }
            }
        }

        if (dist[n] == INT_MAX)
            return {-1};
        vector<int> ans;
        int node = n;

        while (parent[node] != node)
        {
            ans.push_back(node);
            node = parent[node];
        }
        ans.push_back(1);

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

// ---------- DRIVER CODE ----------
int main()
{
    // Sample input: n = 5 nodes, m = 6 edges
    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges(m, vector<int>(3));
    for (int i = 0; i < m; ++i)
    {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    Solution sol;
    vector<int> result = sol.shortestPath(n, m, edges);

    if (result.size() == 1 && result[0] == -1)
    {
        cout << "-1\n";
    }
    else
    {
        for (int node : result)
        {
            cout << node << " ";
        }
        cout << "\n";
    }

    return 0;
}