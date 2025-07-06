#include <iostream>
#include <vector>

using namespace std;

class disjointSet{
    private:
    vector<int> parent, size, rank;
    public:
    disjointSet(int n){
        parent.resize(n + 1);
        size.resize(n + 1);
        rank.resize(n + 1, 0);
        for(int i = 0; i <= n; i++){
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUltiParent(int node){
        if(node == parent[node]) return node;
        return parent[node] = findUltiParent(parent[node]);
    }

    void unionByRank(int u, int v) {
            int up_u = findUltiParent(u);
            int up_v = findUltiParent(v);
            if (up_u == up_v)
                return;

            if (rank[up_u] > rank[up_v]) {
                parent[up_v] = up_u;
            } else if (rank[up_v] > rank[up_u]) {
                parent[up_u] = up_v;
            } else {
                parent[up_v] = up_u;
                rank[up_u]++;
            }
        }

        void unionBySize(int u, int v) {
            int up_u = findUltiParent(u);
            int up_v = findUltiParent(v);
            if (up_u == up_v)
                return;

            if (size[up_u] > size[up_v]) {
                parent[up_v] = up_u;
                size[up_u] += size[up_v];
            } else {
                parent[up_u] = up_v;
                size[up_v] += size[up_u];
            }
        }
};

int main(){
    disjointSet ds(7);
    ds.unionBySize(1,2);
    // ds.unionBySize(2,3);
    ds.unionBySize(4,5);
    ds.unionBySize(6,7);
    ds.unionBySize(5,6);

    ds.unionBySize(3,7);
    if(ds.findUltiParent(2) == ds.findUltiParent(3)){
        cout << "same\n";
    }else cout << "not same\n";
    
}