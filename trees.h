#ifndef TREES_H
#define TREES_H
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cassert>

using namespace std;

namespace tress{

/**
 * 二叉查找树
 */
template <typename Key, typename Value>
class BinarySearchTree
{
private:
    struct Node{
      Key key; // 键
      Value value; // 值
      Node* left; // 左子树
      Node* right; // 右子树
      Node* parent; // 父节点

      Node(Key key, Value val){
          this->key = key;
          this->value = val;
          this->left = nullptr;
          this->right = nullptr;
          this->parent = nullptr;
      }
      Node(Node* node){
          this->key = node->key;
          this->value = node->value;
          this->right = node->right;
          this->left = node->left;
          this->parent = node->parent;
      }

       ~Node(){

//          if(this->left){
//              delete this->left;
//          }
//          if(this->right){
//              delete this->right;
//          }
//          if(this->parent){
//              delete this->parent;
//          }
      }

    };
    int count;

    Node* root; // 根节点


public:
    BinarySearchTree(){
        count = 0;
        root = nullptr;
    }
    ~BinarySearchTree(){
       // 后序遍历，一个一个删除
        destroy(root);
    }

    // 插入键值对
    void insert(Key key, Value val){
        root = insert(root, key, val);
    }
    // 前序遍历
    void preOrder(){
        preOrder(root);
    }
    // 中序遍历
    void inOrder(){
        inOrder(root);
    }
    // 后续遍历
    void postOrder(){
        postOrder(root);
    }
    // 是否存在
    bool exist(Key key){
        return exist(root, key);
    }
    // 查询
    Value* search(Key key){
        Node* node = search(root, key);
        if (node != nullptr){
            return &node->value;
        }
        return nullptr;
    }

    // 获得最大值
    Value getMax(){
        return maximum(root)->value;
    }

    // 获得最小值
    Value getMin(){
        return minimum(root)->value;
    }

    // 层序遍历
    void layerOrder(){
        //
        queue<Node*> _queue;
        _queue.push(root);
        while (!_queue.empty()) {
            Node* node = _queue.front();
            cout << node->key << " ";
            _queue.pop(); //

            if (node->left!=nullptr){
                _queue.push(node->left);
            }
            if (node->right!=nullptr) {
                _queue.push(node->right);
            }
        }

    }

    // 删除节点
    void remove(Key key){
        root =  remove(root, key);
    }

    bool isEmpty(){return count == 0;}
    int size() const {return count;}

private:
    Node* insert(Node* node, Key key, Value val){
        if(node == nullptr){
            count ++ ;
            return new Node(key, val);
        }

        if(key == node->key){ // 键值相等
            node->value = val;
            return node;
        }else if(key < node->key){ // 在左子树插入
           Node* addNode = insert(node->left, key, val);
           addNode->parent = node;
           node->left = addNode;
        }else if (key > node->key){ // 在右子树插入
            Node* addNode = insert(node->right, key, val);
            addNode->parent = node;
            node->right = addNode;
        }

        return node;
    }
    Node* minimum(Node* node){
        if( node->left == nullptr){
            return  node;
        }
        return minimum(node->left);
    }
    Node* maximum(Node* node){
        if(node->right == nullptr){
            return node;
        }
        return maximum(node->right);
    }
    Node* search (Node* node, Key key){
        if(node == nullptr){
            return  nullptr;
        }
        if(node->key == key){
            return node;
        }else if (node->key > key) {
            return  search(node->left, key);
        }else{
            return  search(node->right, key);
        }
    }

    Node* removeMin(Node* node){
        if (node->left==nullptr){
            Node* rightNode = node->right;
            if(rightNode!=nullptr)
                rightNode->parent = node->parent;
            delete node;
            count --;
            return rightNode;
        }

        node->left = removeMin(node->left);
        return node;
    }
    Node* removeMax(Node* node){
        if (node->right==nullptr){
            Node* leftNode = node->left;
            delete node;
            count --;
            return leftNode;
        }
        node->right = removeMax(node->right);
        return node;
    }
    void preOrder(Node* node){

        if (node!=nullptr){
            std::cout << node->key << " ";
            preOrder(node->left);
            preOrder(node->right);

        }
    }
    void inOrder(Node* node){
        if(node != nullptr){
            inOrder(node->left);
            cout << node->key << " ";
            inOrder(node->right);
        }
    }

    void postOrder(Node* node){
        if(node != nullptr){
            postOrder(node->left);
            postOrder(node->right);
            cout << node->key << " ";
        }
    }
    bool exist(Node* node, Key key){
        if(node == nullptr){
            return false;
        }
        if (node->key == key){
            return true;
        }else if(key < node->key){
            return exist(node->left);
        }else{
            return exist(node->right);
        }
    }

    void destroy(Node* node){
        if(node == nullptr){
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    Node* remove(Node* node, Key key){
        if(node == nullptr){
            return nullptr;
        }
        if(key == node->key){
            if(node->left == nullptr){
                //右子树顶上去
                Node* rightNode = node->right;
                if(rightNode!=nullptr)
                    rightNode->parent = node->parent;
                delete node;
                count --;
                return rightNode;
            }
            // 只有右子树；
            if(node->right == nullptr){
                Node* leftNode = node->left;
                if(leftNode!=nullptr)
                    leftNode->parent = node->parent;
                delete node;
                count --;
                return leftNode;
            }

            // 利用后继节点去替换
            Node* successor = minimum(node->right);
            Node* addNode = new Node(successor->key, successor->value);
            count ++;
            addNode->right =removeMin(node->right); // 这个地方递减了一次 count -- , 所以前面先count++
            addNode->left = node->left;
            addNode->parent = node->parent;

            delete node;
            count --;
            return addNode;

        }else if (key < node->key){
            node->left = remove(node->left, key);
            return node;
        }else {
            node->right = remove(node->right, key);
            return node;
        }
    }

}; // binary search tree class end




/**
 * 可以参考 《大话结构数据》 之 哈夫曼树的定义
 */
template <typename Key, typename Value>
class HuffmanTree
{

private:
    struct Node{
        Key key; // 键
        Value value; //权重
        int code;   // 编码 0 1 ， 左孩子为0，有孩子为1
        Node* left; // 左子树
        Node* right; // 右子树
        Node* parent; // 父节点

        Node(Key key, Value val){
            this->key = key;
            this->value = val;
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
        }
        Node(Node* node){
            this->key = node->key;
            this->value = node->value;
            this->right = node->right;
            this->left = node->left;
            this->parent = node->parent;
        }
        Node(){
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
        }
         ~Node(){}
    };
    Node* root;
    int count;
public:
    HuffmanTree(){
        root = nullptr;
        count = 0;
    }
    ~HuffmanTree(){};

    int size() const{return  count;}
    int isEmpty(){return count == 0;}

    void create(vector<pair<Key, Value>>& arr)
    {
        // 创建Huffman tree
        // 首先对value 进行排序， 排序后的数据按照从小到大的顺序，
        // 取出前两个，分别为左子树和右子树，创建父节点，然后放进队列中
        // 循环执行前两步， 只到队列中的元素为空。
        int length = arr.size();
        assert(length >= 2);
        vector<Node*> _list;
        for(int i=0; i<arr.size(); i++){
            _list.push_back(new Node(arr[i].first, arr[i].second));
        }

        while (!_list.empty()) {
            sort(_list);
            // 取数据之前要进行排序（小->大);
             Node* node1 = front(_list);
             Node* node2 = front(_list);

             Node* parent = new Node();
             node1->parent = parent;
             node2->parent = parent;
             parent->value = node1->value + node2->value;

             if(node1->value <= node2->value){
                 node1->code = 0;
                 node2->code = 1;
                 parent->left = node1;
                 parent->right = node2;

             }else{
                 node1->code = 1;
                 node2->code = 0;
                 parent->left = node2;
                 parent->right = node1;
             }

             // 如果没有元素，就到底了，不需要添加新的节点
             if(!_list.empty()){
                 _list.push_back(parent);
             }
            root = parent;
        }
    }

    // 打印所有的编码
    void postOrder(){
        // 先查询出，叶子节点，然后向上搜索，不过需要知道父节点
        postOrder(root);
    }


private:
    // 后序遍历，并打印对应叶子节点的编码
    void postOrder(Node* node){
        if(node != nullptr){

            postOrder(node->left);
            postOrder(node->right);
            if(node->left==nullptr && node->right == nullptr){
                cout << "Key = " << node->key << " code = " ;

                // 遍历编码 逆序，然后再正序输出即可
                Node* pnode= node;
                vector<int> codes;
                while (pnode->parent!=nullptr) {
                    codes.push_back(pnode->code);
                    pnode = pnode->parent;
                }
                for(int i=codes.size()-1; i>=0; i--){
                    cout << codes[i] << " ";
                }
                cout << endl;
            }
        }
    }


    // 取出链表中第一个元素，并删除第一个元素
    Node* front(vector<Node*>& arr){
        Node* first = arr.front();
        arr.erase(arr.begin());
        return first;
    }

    // 排序 从小到大排列
    void sort(vector<Node*>& arr){
        std::sort(arr.begin(), arr.end(), [](Node* a, Node* b){
            return a->value < b->value;
        });
    }

}; // Huffman tree class end


} // namespace trees



#endif // TREES_H
