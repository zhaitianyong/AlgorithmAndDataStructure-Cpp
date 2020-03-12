#include <QCoreApplication>
#include "sorts.h"
#include "maxheap.h"
#include "singlelink.h"
#include "linkstack.h"
#include "linkqueue.h"
#include "search.h"
#include "trees.h"
#include "graphs.h"
#include "weightgraph.h"

/**
 * @brief main0 测试排序
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int n = 10000;
    int* arr1 = generateRandomArray(n, 0, 10000);
    int* arr2 = copyArray(arr1, n);
    int* arr3 = copyArray(arr1, n);
    int* arr4 = copyArray(arr1, n);
    //testSort("bubble sort", bubble_sort, arr1, n);
    //print_sort(arr, n);
    //printArray(arr1, n);
    testSort("inser sort2", insert_sort2, arr1, n);
    testSort("inser sort3", insert_sort3, arr2, n);

    //printArray(arr2, n);
    //testSort("shell sort", shell_sort, arr1, n);
    //testSort("quick sort", quick_sort, arr1, n);
    //testSort("heap sort1", heap_sort1, arr2, n);
    //testSort("heap sort2", heap_sort2, arr3, n);
    //testSort("heap sort", heap_sort, arr4, n);
    //printArray(arr1, n);
    //printArray(arr4, n);
    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
    delete [] arr4;
    return a.exec();
}

/**
 * @brief main 测试链表
 * @param argc
 * @param argv
 * @return
 */
int main2(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    SingleLink<int> link;
//    for(int i=1; i<11; i++){
//        link.insert_end(i);
//    }
//    link.printLink();

//    link.insert_head(20);
//    link.printLink();

//    link.insert_end(40);
//    link.printLink();

//    link.insert(0, 10);
//    link.printLink();
//    link.insert(3, 10);
//    link.printLink();

//    link.remove(4);
//    link.printLink();

//    LinkStack<int> stack;
//    for(int i=1; i<11; i++){
//        stack.push(i);
//    }
//    stack.printLink();
//    stack.pop();
//    stack.printLink();
    LinkQueue<int> queue;
    for(int i=1; i<11; i++){
        queue.push(i);
    }
    queue.printLink();

    queue.pop();
    queue.printLink();

    return a.exec();
}

/**
 * @brief main 测试查找
 * @param argc
 * @param argv
 * @return
 */
int main3(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int n= 10;
    int* arr1 = generateRandomArray(n, 0, 100);
    quick_sort(arr1, n);
    printArray(arr1, n);
    int index = binary_search(arr1, n, arr1[n/2]);
    std::cout << "iter index = " << index << std::endl;

    int index2 = binary_search_recurve(arr1, n, arr1[n/2]);
    std::cout << "recurve index = " << index2 << std::endl;


    delete [] arr1;


    return a.exec();
}

/**
 * @brief main 二叉树
 * @param argc
 * @param argv
 * @return
 */
int main4(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    {
        tress::BinarySearchTree<int, int> bst;
        int arr[10]={6, 3,9, 1, 10, 4, 7, 5, 2, 8};

        for (int& item : arr){
            bst.insert(item, item);
        }

        cout << "preorder" << endl;
        bst.preOrder();
        cout << endl;
        cout << "inorder" << endl;
        bst.inOrder();
        cout << endl;
        cout << "postorder" << endl;
        bst.postOrder();
        cout << endl;
        cout << "layerorder" << endl;
        bst.layerOrder();
        cout << endl;

        int max = bst.getMax();
        int min = bst.getMin();

        cout << "max = " << max << " min = " << min << endl;

        int* cur = bst.search(8);
        cout << "searc result = " << *cur << endl;

        bst.remove(9);

        cout << "inorder" << endl;
        bst.inOrder();
        cout << endl;

        cout << "Huffman tree test" << endl;

        tress::HuffmanTree<string, int> huffmanTree;

        vector<pair<string, int>> arrs={
            make_pair("E", 30),
            make_pair("F", 5),
            make_pair("B", 8),
            make_pair("C", 15),
            make_pair("D", 15),
            make_pair("A", 27)
        };
        huffmanTree.create(arrs);

        huffmanTree.postOrder();

    }


    cout << "end" << endl;
    return a.exec();
}

/**
 * @brief main 图
 * @param argc
 * @param argv
 * @return
 */
int main5(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    using namespace graphs;
    int n = 13;
    SparseGraph sg(n,false);
    ReadGraph<SparseGraph> readGraph(sg, "D:/g1.txt");
    sg.show();

    DenseGraph dg(n, false);
    ReadGraph<DenseGraph> readDenseGraph(dg,"D:/g1.txt");
    dg.show();

    Component<SparseGraph> scomponent(sg);
    cout << "SparseGraph component count " << scomponent.size() << endl;
    Component<DenseGraph> dcomponent(dg);
    cout << "DenseGraph component count " << dcomponent.size() << endl;

//    for(int v=0; v<n; v++){
//        DenseGraph::Iterator it(dg, v);
//        cout << "Vertex " << v;
//        for(int i=it.begin(); !it.end(); i=it.next()){
//            cout << " " << i;
//        }
//        cout << endl;

//    }


    SparseGraph g(7,false);
    ReadGraph<SparseGraph> _readGraph(g, "D:/g2.txt");
    g.show();

    Path<SparseGraph> dfs(g, 0);
    dfs.showPath(6);

    BFSPath<SparseGraph> bfs(g, 0);
    bfs.showPath(6);

    return a.exec();
}

/**
 * @brief main 无向图
 * @param argc
 * @param argv
 * @return
 */
int main6(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int n = 8;
    typedef WeightGraph::DenseGraph<double> WDenseGraph;
    typedef WeightGraph::SparseGraph<double> WSparseGraph;

    WSparseGraph dg(n, false);
    WeightGraph::ReadGraph<WSparseGraph, double> rg(dg, "D:/g3.txt");

    dg.show();

//    for(int v=0; v<n; v++){
//        WSparseGraph::Iterator it(dg, v);
//        cout << "Vertex " << v << ": ";
//        for(Edge* i=it.begin(); !it.end(); i=it.next()){
//            cout <<  i->v1()  << " ";
//        }
//        cout << endl;
//    }
    // Test Lazy Prim MST
    cout<<"Test Lazy Prim MST:"<<endl;
    //WeightGraph::LazyPrimMST<WeightGraph::SparseGraph<double>, double> lazyPrimMST(dg);
    //std::vector<WeightGraph::Edge<double>> mst = lazyPrimMST.mstEdges();

    //for( int i = 0 ; i < mst.size() ; i ++ )
    //    cout<<mst[i]<<endl;
    //cout<<"The MST weight is: "<<lazyPrimMST.result()<<endl;

    cout<<endl;

    return a.exec();
}

