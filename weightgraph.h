#ifndef WEIGHTGRAPH_H
#define WEIGHTGRAPH_H
// 有权重的图，重点讨论有权重的无向图
// 图是由节点和边组成，边的值可以记录它们之间的权重
#include <cassert>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include <maxheap.h>

namespace WeightGraph {

using namespace std;
template <typename Weight>
/**
 * @brief The Edge class 边
 */
class Edge
{
private:
    int a, b;
    Weight w;

public:
    Edge(int a, int b, Weight w):
        a(a), b(b), w(w){

    }

    Edge(){}

    Weight wt(){
        return w;
    }

    int v0(){
        return a;
    }

    int v1(){
        return b;
    }

    int other(int x){
        assert(x==a || x==b);
        return x==a? b : a;
    }

    // 重载运算符号
    // 输出边的信息
        friend ostream& operator<<(ostream &os, const Edge &e){
            os<<e.a<<"-"<<e.b<<": "<<e.weight;
            return os;
        }

        // 边的大小比较, 是对边的权值的大小比较
        bool operator<(Edge<Weight>& e){
            return w < e.wt();
        }
        bool operator<=(Edge<Weight>& e){
            return w <= e.wt();
        }
        bool operator>(Edge<Weight>& e){
            return w > e.wt();
        }
        bool operator>=(Edge<Weight>& e){
            return w >= e.wt();
        }
        bool operator==(Edge<Weight>& e){
            return w == e.wt();
        }

};


/**
 * @brief The DenseGraph class 稠密图
 */
template <typename Weight>
class DenseGraph
{
private:
    int n, m; // 节点个数和边界数
    bool directed; // 有向图
    vector<vector<Edge<Weight>*>> g; //邻接矩阵表示 0 0 0 0 0 对角线几乎都是 0

public:
    DenseGraph(int n, bool directed):n(n), directed(directed){
        m = 0;
        for(int i=0; i<n; i++){
            g.push_back(vector<Edge<Weight>*>(n, nullptr));
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

    void addEdge(int v, int w, Weight weight){
        assert(v>=0 && v<=n);
        assert(w>=0 && w<=n);

        if(haseEdge(v, w)){
            delete g[v][w];
            if(!directed)
                delete g[w][v];
            m --;
        }

        g[v][w] = new Edge<Weight>(v, w, weight);
        if(!directed)
            g[w][v] = new Edge<Weight>(w, v, weight);

        m++;
    }


    bool haseEdge(int v, int w){
        assert(v>=0 && v<=n);
        assert(w>=0 && w<=n);
        return g[v][w]==nullptr;
    }

    void show(){
        for(int v=0; v<n; v++){
            for(int i=0; i<n; i++){
                if(g[v][i]!=nullptr)
                    cout << " " << g[v][i]->W();
                else
                    cout << " " << "NULL";
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


        Edge<Weight>* begin(){
            index = -1;
            return next();
        }

        Edge<Weight>* next(){
            for(index += 1; index < G.V(); index++){
                if(G.g[v][index]!=nullptr)
                    return G.g[v][index];
            }

            return nullptr;
        }

        bool end(){
            return index >= G.V();
        }

    };

}; // DenseGraph

/**
 * @brief The SparseGraph class 稀疏图
 */
template <typename Weight>
class SparseGraph
{
private:
    int n, m;
    bool directed;
    vector<vector<Edge<Weight>*>> g;  // 邻接链表表示

public:
    SparseGraph(int n, bool directed):n(n), directed(directed){
        m = 0;
        for(int i=0; i<n; i++){
            g.push_back(vector<Edge<Weight>*>());
        }
    }

    ~SparseGraph(){}

    int V(){
        return n;
    }

    int E(){
        return m;
    }

    void addEdge(int v, int w, Weight weight){
        assert(v>=0 && v<=n);
        assert(w>=0 && w<=n);
        g[v].push_back(new Edge<Weight>(v, w, weight));
        if(v!=w && !directed)
            g[w].push_back(new Edge<Weight>(w, v, weight));
    }


    //
    bool hasEdge(int v, int w){
        assert(v>=0 && v<=n);
        assert(w>=0 && w<=n);

        for(int i=0; i<g[v].size(); i++){
            if(g[v][i]->v0()==v && g[v][i]->v1() == w)
                return true;
        }

        return false;
    }

    void show(){
        for(int v=0; v<n; v++){
            cout << "vertex: " << v;
            for(int i=0; i<g[v].size(); i++){
                cout << " " << g[v][i]->v1();
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


        Edge<Weight>* begin(){
            index = -1;
            return next();
        }

        Edge<Weight>* next(){
            index += 1;
            if(index < G.g[v].size()){
                return G.g[v][index];
            }

            return nullptr;

        }

        bool end(){
            return index >= G.g[v].size();
        }

    };

}; // SparseGraph



/**
 * @brief The ReadGraph class
 * 读取数据
 */
template <typename Graph, typename Weight>
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
                Weight c;
                ss >> a >> b >> c;
                g.addEdge(a, b, c);
            }
        }

    }
};


/**
 * 最小生成树 Lazy Prim MST
 * minimum spanning tree
 */
template <typename Graph, typename Weight>
class LazyPrimMST
{
private:
    Graph G;
    bool* visited;
    MinHeap<Edge<Weight>> heap;
    vector<Edge<Weight>> mst;
    Weight wt; // 权重和的计算


public:
    LazyPrimMST(Graph& g)
    {
        this->G = g;
        visited = new bool[G.V()];
        heap = MinHeap<Edge<Weight>>(G.E()); // 初始化一个小顶堆，用来选择最小权重的边,容量为边的个数
        for(int i=0; i<G.V(); i++){
            visited[i] = false;
        }

        mst.clear();
        //选择第一个点的临边
        visit(0);
        while (!heap.isEmpty()) {

           Edge<Weight> minedge=heap.pop();

           //如果两个边都被访问就Pass
//           if(visited[minedge.v0()] == visited[minedge.v1])
//               continue;

           mst.push_back(minedge);

           if(!visited[minedge.v0()])
                visit(minedge.v0());
           else
               visit(minedge.v1());
        }
        // 输出权重计算权重和

        wt = mst[0].wt();
        for(int i=1; i<mst.size(); i++){
            wt += mst[i].wt();
        }

    }

    ~LazyPrimMST(){
        delete []  visited;
    }

    // 返回最小生成树的所有边
    vector<Edge<Weight>> mstEdges(){
        return mst;
    }

    // 返回最小生成树的权值
    Weight result(){
        return wt;
    }

private:
    // 访问k个节点
    void visit(int k){
        assert(k>=0 && k<=G.V());
        visited[k]=true;
        typename Graph::Iterator it(G, k);
        for(Edge<Weight>* e = it.begin(); !it.end(); e= it.next()){
            if(!visited[e->other(k)])
                heap.insert(*e);
        }
    }

};


}  // namespace


#endif // WEIGHTGRAPH_H
