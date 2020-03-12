#ifndef GRAPHS_H
#define GRAPHS_H
#include <vector>
#include <stack>
#include <queue>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
namespace graphs{

/**
 * @brief The DenseGraph class 稠密图
 */
class DenseGraph
{
private:
    int n, m; // 节点个数和边界数
    bool directed; // 有向图
    vector<vector<bool>> g; //邻接矩阵表示 0 0 0 0 0 对角线几乎都是 0

public:
    DenseGraph(int n, bool directed):n(n), directed(directed){
        m = 0;
        for(int i=0; i<n; i++){
            g.push_back(vector<bool>(n, false));
        }
    }

    ~DenseGraph(){
        //TODO
    }

    // 顶点个数
    int V(){
        return n;
    }

    // 边的个数
    int E(){
        return m;
    }

    void addEdge(int v, int w){
        assert(v>=0 && v<=n);
        assert(w>=0 && w<=n);

        if(haseEdge(v, w))
            return;

        g[v][w] = true;
        if(!directed)
            g[w][v] = true;

        m++;
    }


    bool haseEdge(int v, int w){
        assert(v>=0 && v<=n);
        assert(w>=0 && w<=n);
        return g[v][w];
    }

    void show(){
        for(int v=0; v<n; v++){
            for(int i=0; i<n; i++){
                cout << " " << g[v][i];
            }
            cout << endl;

        }
    }
    /**
     * @brief The Iterator class 迭代器输出邻近点
     */
    class Iterator
    {
    private:
        int index;
        DenseGraph& G;
        int v;
    public:
        Iterator(DenseGraph& g, int v): G(g), v(v){
            assert( v >= 0 && v < G.V() );
            index = -1;
        }


        int begin(){
            index = -1;
            return next();
        }

        int next(){
            for(index += 1; index < G.V(); index++){
                if(G.g[v][index])
                    return index;
            }

            return -1;
        }

        bool end(){
            return index >= G.V();
        }

    };

}; // DenseGraph


/**
 * @brief The SparseGraph class 稀疏图
 */
class SparseGraph
{
private:
    int n, m;
    bool directed;
    vector<vector<int>> g;  // 邻接链表表示

public:
    SparseGraph(int n, bool directed):n(n), directed(directed){
        m = 0;
        for(int i=0; i<n; i++){
            g.push_back(vector<int>());
        }
    }

    ~SparseGraph(){}

    int V(){
        return n;
    }

    int E(){
        return m;
    }

    void addEdge(int v, int w){
        assert(v>=0 && v<=n);
        assert(w>=0 && w<=n);
        if(hasEdge(v, w))
            return;
        g[v].push_back(w);
        if(v!=w && !directed)
            g[w].push_back(v);
    }


    //
    bool hasEdge(int v, int w){
        assert(v>=0 && v<=n);
        assert(w>=0 && w<=n);

        for(int i=0; i<g[v].size(); i++){
            if(g[v][i] == w)
                return true;
        }

        return false;
    }

    void show(){
        for(int v=0; v<n; v++){
            cout << "vertex: " << v;
            for(int i=0; i<g[v].size(); i++){
                cout << " " << g[v][i];
            }
            cout << endl;

        }
    }

    /**
     * @brief The Iterator class 迭代器输出邻近点
     */
    class Iterator
    {
    private:
        int index;
        SparseGraph& G;
        int v;
    public:
        Iterator(SparseGraph& g, int v): G(g), v(v){
            index = -1;
        }


        int begin(){
            index = -1;
            return next();
        }

        int next(){
            index += 1;
            if(index < G.g[v].size()){
                return G.g[v][index];
            }

            return -1;

        }

        bool end(){
            return index >= G.g[v].size();
        }

    };

}; // SparseGraph



/**
 * @brief The Component class 计算图的连通分量
 * 设置为模板类型，
 */
template <typename Graph>
class Component{

private:
    Graph& G;
    int count;
    vector<bool> visited;  // 表示是否访问过
    vector<int> idx;  // 是否都属于同一个Component

    // 深度优先遍历
    void dfs(int v){

        visited[v] = true; // 被访问过
        idx[v] = count;
        // 遍历的临界点
        typename Graph::Iterator it(G, v);

        for(int i = it.begin(); !it.end(); i = it.next()){
            if(!visited[i])
                dfs(i);
        }
    }


public:
    Component(Graph& g): G(g){
        count = 0;

        for(int i=0; i<G.V(); i++)
        {
            visited.push_back(false);
            idx.push_back(-1);
        }
        // 对比每个没有访问过的节点进行遍历
        for( int i = 0 ; i < G.V() ; i ++ )
            if( !visited[i] ){
                dfs(i);
                count += 1; // 容易写到if 之外
            }

    }


    int size(){
        return count;
    }


    bool connected(int v, int w){
        assert(v>=0 && v<= G.V());
        assert(w>=0 && w<= G.V());
        assert(idx[v]!=-1 && idx[w]!=-1);
        return idx[v]==idx[w];
    }

};


/**
 * @brief The ReadGraph class
 * 读取数据
 */
template <typename Graph>
class ReadGraph{
private:
    string line;
public:
    ReadGraph(Graph& g, std::string filename){

        ifstream inf(filename);
        if(inf.is_open()){
            while (getline(inf, line)) {
                stringstream ss(line);
                int a, b;
                ss >> a >> b;
                g.addEdge(a, b);
            }
        }

    }
};


template<typename Graph>
class Path
{

private:
    Graph& G;
    vector<bool> visited;
    vector<int> from;
    int s;
    void dfs(int v){

        visited[v] = true;
        typename Graph::Iterator it(G, v);
        for(int i=it.begin(); !it.end(); i=it.next()){
            if(!visited[i]){
                from[i] = v;
                cout << i << " -> " << v << endl;
                dfs(i);
            }
        }

    }

public:
    Path(Graph& g, int s):G(g),s(s)
    {
        for(int i=0; i<G.V(); i++){
            visited.push_back(false);
            from.push_back(-1);
        }

        for(int v=0; v<G.V(); v++){
            if(!visited[v])
                dfs(v);
        }
    }


    bool hasPath(int v){
        assert(v>=0 && v<=G.V());
        return visited[v];
    }

    void path(int v, vector<int> &vec){
        stack<int> s;

        int p = v;
        while (p!=-1) {
            s.push(p);
            p = from[p];
        }
        vec.clear();

        while (!s.empty()) {
            vec.push_back(s.top());
            s.pop();
        }
    }

    void showPath(int v){
        vector<int> vec;
        path(v, vec);

        for(int i=0; i< vec.size(); i++){
            cout  << vec[i];
            if(i == vec.size() - 1)
                cout << endl;
            else
                cout << " -> ";
        }
    }

};

/**
 * @brief The BFSPath class
 * 广度优先遍历
 */
template <typename Graph>
class BFSPath{

private:
    Graph& G;
    vector<bool> visited;
    vector<int> from;
    int s;


public:
    BFSPath(Graph& g, int s): G(g), s(s){
        for(int i=0; i<G.V(); i++){
            visited.push_back(false);
            from.push_back(-1);
        }

        // 广度优先遍历
        queue<int> q;
        q.push(s);
        visited[s] = true;

        while (!q.empty()) {
            // 从队列中取出第一元素
            int v = q.front();
            q.pop();

            typename Graph::Iterator it(G, v);
            for(int i=it.begin(); !it.end(); i=it.next()){
                if(!visited[i]){
                    visited[i] = true;
                    q.push(i);
                    from[i] = v;
                }
            }
        }


    }


    void hasPath(int v){
        assert((v>=0 && v<= G.V()));
        return visited[v];
    }

    void path(int v, vector<int>& vec){

        stack<int> s;

        int p = v;
        while (p != -1) { // 最后一个为-1
            s.push(p);
            p = from[p];
        }

        vec.clear();

        while (!s.empty()) {
            vec.push_back(s.top());
            s.pop();
        }
    }

    void showPath(int v){
        vector<int> vec;
        path(v, vec);

        for (int i=0; i<vec.size(); i++){
            cout  << vec[i];
            if(i == vec.size() - 1)
                cout << endl;
            else
                cout << " -> ";
        }
        cout<< endl;
    }

};
}  // name space graph

#endif // GRAPHS_H
