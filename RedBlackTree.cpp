#include <iostream>
using namespace std;
enum Color
{
    Red,
    Black
};
struct Node
{
    Color color;
    int key;
    Node *pLeft;
    Node *pRight;
    Node *pParent;
    Node()
    {
        pLeft = pRight = pParent = nullptr;
        color = Black;
    }
    Node(int _key)
    {
        key = _key;
        color = Black;
        pLeft = pRight = pParent = nullptr;
    }
};
class RedBlackTree
{
    Node *root;
    void Left_Rotation(Node *&);
    void Right_Rotation(Node *&);
    void insert(Node *&);
    void InsertFixup(Node *&);

public:
    RedBlackTree()
    {
        root = NULL;
    }
    ~RedBlackTree()
    {
    }
    void insert(int _key)
    {
        Node *new_node = new Node(_key);
        insert(new_node);
    }
};
void RedBlackTree::Left_Rotation(Node *&_root)
{
    Node *y = _root->pRight;
    _root->pRight = y->pLeft;
    if (y->pLeft != NULL)
    {
        y->pLeft->pParent = _root;
    }
    y->pParent = _root->pParent;
    if (_root->pParent == NULL)
    {
        this->root = y;
    }
    else if (_root == _root->pParent->pLeft)
        _root->pParent->pLeft = y;
    else
    {
        _root->pParent->pRight = y;
    }
    y->pLeft = _root;
    _root->pParent = y;
    //_root = y;
}
void RedBlackTree::Right_Rotation(Node *&_root)
{
    Node *y = _root->pLeft;
    _root->pLeft = y->pRight;
    if (y->pRight != NULL)
    {
        y->pRight->pParent = _root;
    }
    y->pParent = _root->pParent;
    if (_root->pParent == NULL)
    {
        this->root = y;
    }
    else if (_root == _root->pParent->pLeft)
        _root->pParent->pLeft = y;
    else
    {
        _root->pParent->pRight = y;
    }
    y->pRight = _root;
    _root->pParent = y;
    //_root = y;
}
void RedBlackTree::insert(Node *&new_node)
{
    Node *prev = NULL;
    Node *temp = this->root;
    while (temp != nullptr)
    {
        prev = temp;
        if (new_node->key < temp->key)
            temp = temp->pLeft;
        else
        {
            temp = temp->pRight;
        }
    }
    new_node->pParent = prev;
    if (prev == NULL)
    {
        this->root = new_node;
    }
    else if (new_node->key < prev->key)
        prev->pLeft = new_node;
    else
    {
        prev->pRight = new_node;
    }
    new_node->pLeft = new_node->pRight = NULL;
    new_node->color = Red;
    InsertFixup(new_node);
}
void RedBlackTree::InsertFixup(Node *&fixed_Node)
{
    while (fixed_Node->pParent->color == Red)
    {
        if (fixed_Node->pParent == fixed_Node->pParent->pParent->pLeft)
        {
            Node *temp = fixed_Node->pParent->pParent->pRight;
            if (temp->color == Red)
            //Case1
            {
                fixed_Node->pParent->color = Black;
                temp->color = Black;
                fixed_Node->pParent->pParent->color = Red;
                fixed_Node = fixed_Node->pParent->pParent;
            }
            else
            {
                if (fixed_Node == fixed_Node->pParent->pRight)
                {
                    fixed_Node = fixed_Node->pParent;
                    Left_Rotation(fixed_Node);
                }
            }
        }
        else
        {
        }
    }
}