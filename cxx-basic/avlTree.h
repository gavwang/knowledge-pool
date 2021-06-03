#include <iostream>
// #include <string>
#include <cstring>

using namespace std;


/**
 * @brief 
 *  AVL tree is a self-balancing Bianry Search Tree where the difference heights of left and right subtrees cannot be more than one for all nodes 
 * 
 * @tparam T 
 */
template <typename Key, typename T>
class  Avltree
{
    class avltreeNode {
        Key key;
        T value;
        int height;
        avltreeNode* parent;
        avltreeNode* left, right;
        avltreeNode(Key k, T v):parent(nullptr),
        left(nullptr),
        right(nullptr)
        {
            key = k;
            value = v;
        }

        bool operator < (const avltreeNode& v)
        {
            if(this->key < v.key)
                return true;
            else
                return false;
        };
        
        bool operator == (const avltreeNode& v)
        {
            if(this->key == v.key)
                return true;
            else
                return false;
        };
    };

    typedef class avltreeNode node_t;
    typedef class avltreeNode* nodeptr_t;

    //node height
    int treeHeight (nodeptr_t node){
        if(node == nullptr)
        {
            return 0;
        }else
        {
            return max(treeHeight(node->left), treeHeight(node->right)) + 1;
        }
    }

    //get node balance factor
    int treeNodeBalanceFactor(nodeptr_t node){
        if(node == nullptr)
            return 0;
        else {
            return treeHeight(node->left) - treeHeight(node->right);
        }
    }

/**
 * @brief  LL type roata right  
 *          C               C                    C
 *         /                                    /                    B
 *        B       -->      B       -->         E         -->       /   \
 *       / \             /   \                     B              A     C
 *      A   E           A     E                   /                    /
 *                                                A                    E
 * @param node  = C
 * @return nodeptr_t 
 */
    nodeptr_t treeRotateRight(nodeptr_t node){
        if(node == nullptr || node->left == nullptr)
            return nullptr;
        nodeptr_t left = node->left;
        node->left = left->left;
        left->right = root;
        return left;
    }


    //RR type
/**
 * @brief 
 * 
 * @param node 
 * @return nodeptr_t
 * https://zhuanlan.zhihu.com/p/34899732
 * https://blog.csdn.net/qq_21993785/article/details/80576642 
 */
    nodeptr_t treeRotateLeft(nodeptr_t node)
    {
        if(node == nullptr || node->right == nullptr)
            return nullptr;
        nodeptr_t right = root->right;

        root->right = right->left;
        right->left = root;

        return right;       
    }

    /**
     * @brief 
     *  
     *   LL -->   +2 +1 
     *   LR -->   +2 -1
     *   RL -->   -2 +1/-1
     *   RR -->   -2 -1
     * @param root 
     * @return nodeptr_t 
     */
    nodeptr_t treeRebalance(nodeptr_t root)
    {
        int factor = treeNodeBalanceFactor(root);

        if(factor > 1 && treeNodeBalanceFactor(root->left) > 0) // LL 
        {
            return treeRotateRight(root);
        }else if(factor > 1 && treeNodeBalanceFactor(root->left) <= 0) //LR
        {
            root->left = treeRotateLeft(root->left);
            return treeRotateRight(root);
        }else if(factor < -1 && treeNodeBalanceFactor(root->right) <= 0) //RR
        {
            return treeRotateLeft(root);
        }else if (factor < -1 && treeNodeBalanceFactor(root->left) > 0) //RL
        {
            root->right = treeRotateRight(root->right);
            return treeRotateLeft(root);
        }else
            return root;
    }


    void treeInsert(nodeptr_t* node, Key key)
    {
        nodeptr_t newNode;
        nodeptr_t root = *node;

        if(root == nullptr)
        {
            newNode = new node_t;
            newNode->key = key;
            newNode->left = newNode->right = nullptr;
            *node = newNode;
            return;
        }else if (root->key == key)
        {
            return;
        }else 
        {
            if (root->key < key)
            {
                treeInsert(root->right , key);
            }else
            {
                treeInsert(root->left , key);
            }
        }

        treeRebalance(node);
        
    }
    void freeNode(nodeptr_t *node)
    {
        delete *node;
        *node =  nullptr;
    }

    void treeDelete(nodeptr_t *node, Key key){
        nodeptr_t *toFree;
        nodeptr_t root = *node;
        if(root)
        {
            if(root->key == key)
            {
                if(root->right)
                {
                    nodeptr_t min = treeDeleteMin(&(root->right));
                    root->key = min->key;
                    root->date = min -> data;
                    delete min;

                }else
                {
                    toFree = root;
                    *node = toFree->left;
                    free(toFree);
                }
            }else
            {
                if(root->key < key)
                {
                    treeDelete(&root->right, key);
                }else
                {
                    treeDelete(&root->right, key);
                }
            }

            treeRebalance(root);
        }

    }

    /**
     * @brief 
     * 
     * @param node 
     * @return nodeptr_t the point should be deleted external  
     */
    nodeptr_t treeDeleteMin(nodeptr_t* node)
    {
        nodeptr_t root = *node;
        if(node->left)
        {
            return treeDeleteMin(node->left); 
        }else
        {
            *node = NULL;
            return node;
        }
    }


private:
    avltreeNode* insert(Key key, T v)
    {
        avltreeNode* newNode = new avltreeNode(key, v);
        if(root == nullptr)
        {
            root = newNode;
            return root;
        }

        avltreeNode* curPos = root;
        while ( curPos )
        {
            if(curPos == newNode)
            {
                cout << "find node, origin value = "<< curPos->value << ", new value = " << newNode->value <<endl;
                curPos->value = newNode->value;
                delete newNode;
                return curPos;
            }else if(curPos < newNode) // insert or traversal right subtree
            {
                if(curPos->right && newNode < curPos->right) // insert
                {

                }

            }else{

            }
            /* code */
        }
        
    }
private:
    avltreeNode* root;
public:
     Avltree(/* args */) {};
    ~ Avltree(){};

};


template <typename Key, typename T>
class  BTreeNode {
public:
    Key key;
    T value;
    int data;
    BTreeNode* left;
    BTreeNode* right;
    BTreeNode* parent;

};

template <typename Key, typename T>
class BTree {
public:
    BTree(){
    };
    ~BTree(){};

    void create(BTreeNode<Key, T>* &Node){
        int data;
        cout << "input data" << endl;
        cin >> data;
        if(data){
            Node = new BTreeNode<Key,T>();
            Node->data = data;
            //cout<<"data:"<<data<<endl;
            create(Node->left);
            create(Node->right);
        } else{
            Node=NULL;
        }
    }

    void clear(BTreeNode<Key, T>* node)
    {
        if(node)
        {
            clear(node->left);
            clear(node->right);

            delete node;
            node = nullptr;
        }
    }

    void inorderTraversal(BTreeNode<Key, T>* node)
    {
        if(!node)
            return;

        if(node->left)
        {
            inorderTraversal(node->left);
        }

        cout << node->data << "," <<endl;

        if(node->right)
        {
            inorderTraversal(node->right);
        }
    }

private:
    BTreeNode<Key, T>* root;

};


enum RBColor{
    RBColor_Red,
    RBColor_Black
};
template <typename Key, typename T>
class RBTreeNode {
    Key key;
    T value;
    RBColor color;
    RBTreeNode* left, right;
};



/**
 * @brief 
 *  RBTree
 *  root is black
 *  there are no two adjacent red nodes (a red node can't have a red parent or child)
 *  every path from a node to any of its descendants NULL nodes has the same number of black nodes  
 * 
 * 
 * 
 */
template <typename Key, typename T>
class RBTree {

private:
    RBTreeNode<Key, T> root;

};
// int  main (int agrc, char* argv [])
// {

//     cout << "This is a class for AVL Tree" <<endl;
//     return 0;
// }
