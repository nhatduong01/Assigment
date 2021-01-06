// Interval tree
// Segment tree
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <math.h>
using namespace std;
// Test
int max(int a, int b)
{
    return (a > b) ? a : b;
}
void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}
void printInteger(int &n)
{
    cout << n << " ";
}
enum Color
{
    Red,
    Black
};
class Interval
{
public:
    int start;
    int end;
    Interval(int start = 0, int end = 0)
    {
        this->start = start;
        this->end = end;
    }
};
struct Node
{
    Color color;
    Interval key;
    Node *pLeft;
    Node *pRight;
    Node *pParent;
    int max;
    Node()
    {
        pLeft = pRight = pParent = NULL;
        color = Black;
        max = 0;
    }
    Node(Interval _key)
    {
        key = _key;
        color = Black;
        pLeft = pRight = pParent = NULL;
        max = _key.end;
    }
};
class BusParking
{
public:
    class RedBlackTree;
    class RedBlackTree
    {
        void removeFixup(Node *);
        Node *BiggestLeft(Node *);
        Node *root;
        void remove(Node *&, int, int);
        void NLR_traverse(Node *_root)
        {
            if (_root)
            {
                //cout << _root->key.start << "" << _root->color << " ";
                cout << "(" << _root->key.start << "," << _root->key.end << ")"
                     << _root->max << " ";
                NLR_traverse(_root->pLeft);
                NLR_traverse(_root->pRight);
            }
        }
        void LRN_traverse(Node *_root)
        {
            if (_root)
            {
                LRN_traverse(_root->pLeft);
                LRN_traverse(_root->pRight);
                //cout << _root->key.start << "_" << _root->color << " ";
                cout << "(" << _root->key.start << "," << _root->key.end << ")"
                     << _root->max << " ";
            }
        }
        void Left_Rotation(Node *);
        void Right_Rotation(Node *);
        void insert(Node *&);
        void InsertFixup(Node *);
        void clear(Node *&root)
        {
            if (root)
            {
                clear(root->pLeft);
                clear(root->pRight);
                delete root;
            }
        }
        int getHeightRec(Node *node)
        {
            if (node == NULL)
                return 0;
            int lh = this->getHeightRec(node->pLeft);
            int rh = this->getHeightRec(node->pRight);
            return (lh > rh ? lh : rh) + 1;
        }

    public:
        void remove(int, int);
        void NLR_traverse()
        {
            NLR_traverse(this->root);
        }
        void LRN_traverse()
        {
            LRN_traverse(this->root);
        }
        int getHeight()
        {
            return this->getHeightRec(this->root);
        }
        void printTreeStructure();
        RedBlackTree()
        {
            root = NULL;
        }
        ~RedBlackTree()
        {
            clear();
        }
        void insert(int start, int end)
        {
            Node *new_node = new Node(Interval(start, end));
            insert(new_node);
        }
        void clear()
        {
            clear(this->root);
            this->root = NULL;
        }
    };
    BusParking()
    {
        Root_tree = new RedBlackTree();
        MinPark = 0;
    }
    ~BusParking()
    {
        Root_tree->clear();
    }
    void insert(int start, int end)
    {
        Root_tree->insert(start, end);
    }
    void remove(int start, int end)
    {
        Root_tree->remove(start, end);
    }
    void printNLR()
    {
        Root_tree->NLR_traverse();
    }
    void printLNR()
    {
        Root_tree->LRN_traverse();
    }
    void printStructure()
    {
        Root_tree->printTreeStructure();
    }
    int minPark()
    {
        return MinPark;
    }

private:
    RedBlackTree *Root_tree;
    int MinPark;
};
void BusParking::RedBlackTree::removeFixup(Node *fixedNode)
{
    while (fixedNode != this->root && fixedNode->color == Black)
    {
        if (fixedNode == fixedNode->pParent->pLeft)
        {
            Node *temp = fixedNode->pParent->pRight;
            if (temp->color == Red)
            // Case 1 we turn to 2, 3, 4
            {
                temp->color = Black;
                fixedNode->pParent->color = Red;
                Left_Rotation(fixedNode->pParent);
                temp = fixedNode->pParent->pRight;
            }
            int a = 0;
            int b = 0;
            if (temp->pRight == nullptr || temp->pRight->color == Black)
                a = 1;
            if (temp->pLeft == nullptr || temp->pLeft->color == Black)
                b = 1;
            if (a && b)
            {
                temp->color = Red;
                fixedNode = fixedNode->pParent;
            }
            else
            {
                if (b == 0 && a == 1)
                // Case 3 we turn to case 4
                {
                    temp->pLeft->color = Black;
                    temp->color = Red;
                    Right_Rotation(temp);
                    temp = fixedNode->pParent->pRight;
                }
                // Case 4
                temp->color = fixedNode->pParent->color;
                fixedNode->pParent->color = Black;
                temp->pRight->color = Black;
                Left_Rotation(fixedNode->pParent);
                fixedNode = this->root;
            }
        }
        else
        {
            Node *temp = fixedNode->pParent->pLeft;
            if (temp->color == Red)
            {
                temp->color = Black;
                fixedNode->pParent->color = Red;
                Right_Rotation(fixedNode->pParent);
                temp = fixedNode->pParent->pLeft;
            }
            int a = 0;
            int b = 0;
            if (temp->pRight == nullptr || temp->pRight->color == Black)
                a = 1;
            if (temp->pLeft == nullptr || temp->pLeft->color == Black)
                b = 1;
            if (b && a)
            {
                temp->color = Red;
                fixedNode = fixedNode->pParent;
            }
            else
            {
                if (b == 1 && a == 0)
                {
                    temp->pRight->color = Black;
                    temp->color = Red;
                    Left_Rotation(temp);
                    temp = fixedNode->pParent->pLeft;
                }
                temp->color = fixedNode->pParent->color;
                fixedNode->pParent->color = Black;
                temp->pLeft->color = Black;
                Right_Rotation(fixedNode->pParent);
                fixedNode = this->root;
            }
        }
    }
    fixedNode->color = Black;
}
Node *BusParking::RedBlackTree::BiggestLeft(Node *root)
{
    if (root->pRight)
        return BiggestLeft(root->pRight);
    else
    {
        return root;
    }
}
void BusParking::RedBlackTree::remove(Node *&_root, int start, int end)
{
    if (_root == nullptr)
        return;
    else
    {
        if (_root->key.start > start)
        {
            remove(_root->pLeft, start, end);
            return;
        }
        else if (_root->key.start < start)
        {
            remove(_root->pRight, start, end);
            return;
        }
        else
        {
            if (_root->key.end != end)
            {
                remove(_root->pRight, start, end);
                return;
            }
            if (!_root->pRight && !_root->pLeft)
            //The node have no child
            {
                Node *temp = _root;
                if (temp == this->root)
                {
                    delete temp;
                    this->root = nullptr;
                    _root = nullptr;
                    return;
                }
                if (_root->max == this->root->max)
                {
                    Node *temp2 = _root->pParent;
                    if (_root == temp2->pLeft)
                        temp2->max = max(temp2->pRight->max, temp2->key.end);
                    else
                    {
                        temp2->max = max(temp2->pLeft->max, temp2->key.end);
                    }
                    temp2 = temp2->pParent;
                    while (temp2)
                    {
                        int a = 0, b = 0;
                        if (temp2->pLeft)
                            a = temp2->pLeft->max;
                        if (temp2->pRight)
                            b = temp2->pRight->max;
                        temp2->max = max(a, b);
                        temp2 = temp2->pParent;
                    }
                }
                if (_root->color == Black)
                {
                    removeFixup(temp);
                }
                if (temp == temp->pParent->pRight)
                {
                    temp->pParent->pRight = nullptr;
                }
                else
                {
                    temp->pParent->pLeft = nullptr;
                }
                _root = nullptr;
                delete temp;
            }
            else if (!_root->pRight)
            {
                if (_root->max == this->root->max)
                {
                    Node *temp2 = _root->pParent;
                    if (_root == temp2->pLeft)
                        temp2->max = max(temp2->pRight->max, temp2->key.end);
                    else
                    {
                        temp2->max = max(temp2->pLeft->max, temp2->key.end);
                    }
                    temp2 = temp2->pParent;
                    while (temp2)
                    {
                        int a = 0, b = 0;
                        if (temp2->pLeft)
                            a = temp2->pLeft->max;
                        if (temp2->pRight)
                            b = temp2->pRight->max;
                        temp2->max = max(a, b);
                        temp2 = temp2->pParent;
                    }
                }
                Node *temp = _root;
                _root->pLeft->pParent = _root->pParent;
                if (_root->pParent)
                {
                    if (temp->color == Black)
                    {
                        removeFixup(_root->pLeft);
                    }
                    if (_root == _root->pParent->pLeft)
                    {
                        _root->pParent->pLeft = _root->pLeft;
                    }
                    else
                    {
                        _root->pParent->pRight = _root->pLeft;
                    }
                    //_root = _root->pLeft;
                    delete temp;
                }
                else
                {
                    this->root = _root->pLeft;
                    delete temp;
                    removeFixup(_root);
                    return;
                }
            }
            else if (!_root->pLeft)
            {
                if (_root->max == this->root->max)
                {
                    Node *temp2 = _root->pParent;
                    if (_root == temp2->pLeft)
                        temp2->max = max(temp2->pRight->max, temp2->key.end);
                    else
                    {
                        temp2->max = max(temp2->pLeft->max, temp2->key.end);
                    }
                    temp2 = temp2->pParent;
                    while (temp2)
                    {
                        int a = 0, b = 0;
                        if (temp2->pLeft)
                            a = temp2->pLeft->max;
                        if (temp2->pRight)
                            b = temp2->pRight->max;
                        temp2->max = max(a, b);
                        temp2 = temp2->pParent;
                    }
                }
                Node *temp = _root;
                _root->pRight->pParent = _root->pParent;
                if (_root->pParent)
                {
                    if (temp->color == Black)
                    {
                        removeFixup(_root->pRight);
                    }
                    if (_root == _root->pParent->pLeft)
                    {
                        _root->pParent->pLeft = _root->pRight;
                    }
                    else
                    {
                        _root->pParent->pRight = _root->pRight;
                    }
                    delete temp;
                    //_root = _root->pRight;
                }
                else
                {
                    this->root = _root->pRight;
                    delete temp;
                    removeFixup(_root);
                    return;
                }
                // _root = nullptr;
                // delete temp;
            }
            else
            {
                Node *temp = BiggestLeft(_root->pLeft);
                _root->key = temp->key;
                if (_root->max == temp->max)
                {
                    Node *temp2 = temp->pParent;
                    if (temp == temp2->pLeft)
                        temp2->max = max(temp2->pRight->max, temp2->key.end);
                    else
                    {
                        temp2->max = max(temp2->pLeft->max, temp2->key.end);
                    }
                    temp2 = temp2->pParent;
                    while (temp2 != _root && temp2)
                    {
                        int a = 0, b = 0;
                        if (temp2->pLeft)
                            a = temp2->pLeft->max;
                        if (temp2->pRight)
                            b = temp2->pRight->max;
                        temp2->max = max(a, b);
                        temp2 = temp2->pParent;
                    }
                }
                remove(temp, temp->key.start, temp->key.end);
            }
        }
    }
}
void BusParking::RedBlackTree::remove(int start, int end)
{
    remove(this->root, start, end);
}
void BusParking::RedBlackTree::Left_Rotation(Node *_root)
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
    y->max = _root->max;
    int a = 0, b = 0;
    if (_root->pLeft)
        a = _root->pLeft->max;
    if (_root->pRight)
        b = _root->pRight->max;
    _root->max = max(max(a, b), _root->key.end);
}
void BusParking::RedBlackTree::Right_Rotation(Node *_root)
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
    int c = 0, d = 0;
    if (y->pLeft)
        c = y->pLeft->max;
    if (y->pRight)
        d = y->pRight->max;
    y->max = _root->max;
    int a = 0, b = 0;
    if (_root->pLeft)
        a = _root->pLeft->max;
    if (_root->pRight)
        b = _root->pRight->max;
    _root->max = max(max(a, b), _root->key.end);
}
void BusParking::RedBlackTree::insert(Node *&new_node)
{
    Node *prev = NULL;
    Node *temp = this->root;
    while (temp != NULL)
    {
        prev = temp;
        if (new_node->key.start < temp->key.start)
        {
            if (temp->max < new_node->max)
                temp->max = new_node->max;
            temp = temp->pLeft;
        }
        else
        {
            if (temp->max < new_node->max)
                temp->max = new_node->max;
            temp = temp->pRight;
        }
    }
    if (prev)
    {
        if (new_node->key.start == prev->key.start && new_node->key.end == prev->key.end)
        {
            delete new_node;
            new_node = NULL;
            return;
        }
    }
    new_node->pParent = prev;
    if (prev == NULL)
    {
        new_node->color = Black;
        this->root = new_node;
        return;
    }
    else if (new_node->key.start < prev->key.start)
        prev->pLeft = new_node;
    else
    {
        prev->pRight = new_node;
    }
    new_node->pLeft = new_node->pRight = NULL;
    new_node->color = Red;
    InsertFixup(new_node);
}
void BusParking::RedBlackTree::printTreeStructure()
{
    int height = this->getHeight();
    if (this->root == NULL)
    {
        cout << "NULL\n";
        return;
    }
    queue<Node *> q;
    q.push(root);
    Node *temp;
    int count = 0;
    int maxNode = 1;
    int level = 0;
    int space = pow(2, height);
    printNSpace(space / 2);
    while (!q.empty())
    {
        temp = q.front();
        q.pop();
        if (temp == NULL)
        {
            cout << " ";
            q.push(NULL);
            q.push(NULL);
        }
        else
        {
            cout << "(" << temp->key.start << "," << temp->key.end << ")";
            q.push(temp->pLeft);
            q.push(temp->pRight);
        }
        printNSpace(space);
        count++;
        if (count == maxNode)
        {
            cout << endl;
            count = 0;
            maxNode *= 2;
            level++;
            space /= 2;
            printNSpace(space / 2);
        }
        if (level == height)
            return;
    }
}
void BusParking::RedBlackTree::InsertFixup(Node *fixed_Node)
{
    if (fixed_Node->pParent == this->root)
    {
        if (fixed_Node->max > this->root->max)
            this->root->max = fixed_Node->max;
    }
    while (fixed_Node->pParent && fixed_Node->pParent->color == Red)
    {
        if (fixed_Node->pParent == fixed_Node->pParent->pParent->pLeft)
        {
            Node *temp = fixed_Node->pParent->pParent->pRight;
            if (temp)
            {
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
                    // Case 2 we rotate to become case 3
                    {
                        fixed_Node = fixed_Node->pParent;
                        Left_Rotation(fixed_Node);
                    }
                    // This is case 3
                    fixed_Node->pParent->color = Black;
                    fixed_Node->pParent->pParent->color = Red;
                    Right_Rotation(fixed_Node->pParent->pParent);
                }
                //The cases are symmetric
            }
            else
            {
                if (fixed_Node == fixed_Node->pParent->pRight)
                // Case 2 we rotate to become case 3
                {
                    fixed_Node = fixed_Node->pParent;
                    Left_Rotation(fixed_Node);
                }
                // This is case 3
                fixed_Node->pParent->color = Black;
                fixed_Node->pParent->pParent->color = Red;
                Right_Rotation(fixed_Node->pParent->pParent);
            }
        }
        else
        {
            Node *temp = fixed_Node->pParent->pParent->pLeft;
            if (temp)
            {
                if (temp->color == Red)
                {
                    fixed_Node->pParent->color = Black;
                    temp->color = Black;
                    fixed_Node->pParent->pParent->color = Red;
                    fixed_Node = fixed_Node->pParent->pParent;
                }
                else
                {
                    if (fixed_Node == fixed_Node->pParent->pLeft)
                    {
                        fixed_Node = fixed_Node->pParent;
                        Right_Rotation(fixed_Node);
                    }
                    fixed_Node->pParent->color = Black;
                    fixed_Node->pParent->pParent->color = Red;
                    Left_Rotation(fixed_Node->pParent->pParent);
                }
            }
            else
            {
                if (fixed_Node == fixed_Node->pParent->pLeft)
                {
                    fixed_Node = fixed_Node->pParent;
                    Right_Rotation(fixed_Node);
                }
                fixed_Node->pParent->color = Black;
                fixed_Node->pParent->pParent->color = Red;
                Left_Rotation(fixed_Node->pParent->pParent);
            }
        }
    }
    this->root->color = Black;
}
int minPark(vector<Interval> lInterval)
{
    int i = 0, j = 1;
    int bus_in = 1, max_bus = 1;
    int _size = lInterval.size();
    int *start = new int[_size];
    int *end = new int[_size];
    for (int i = 0; i < _size; i++)
    {
        start[i] = lInterval[i].start;
        end[i] = lInterval[i].end;
    }
    sort(start, start + _size);
    sort(end, end + _size);
    while (i < _size && j < _size)
    {
        if (start[j] > end[i])
        // The bus has returned
        {
            bus_in--;
            i++;
        }
        else
        {
            bus_in++;
            if (bus_in > max_bus)
            {
                max_bus = bus_in;
            }
            j++;
        }
    }
    delete[] start;
    delete[] end;
    return max_bus;
}
int main()
{
    // vector<Interval> intervals;
    // intervals.push_back(Interval(3, 6));
    // intervals.push_back(Interval(1, 8));
    // intervals.push_back(Interval(2, 5));
    // intervals.push_back(Interval(5, 6));
    // intervals.push_back(Interval(3, 7));
    // intervals.push_back(Interval(2, 4));
    // cout << minPark(intervals);
    BusParking test_bus;
    test_bus.insert(3, 6);
    test_bus.insert(1, 8);
    test_bus.insert(16, 21);
    test_bus.insert(2, 5);
    test_bus.insert(1, 30);
    test_bus.insert(2, 60);
    test_bus.insert(3, 40);
    test_bus.insert(1, 52);
    test_bus.insert(15, 20);
    test_bus.insert(17, 30);
    test_bus.insert(18, 60);
    cout << endl;
    test_bus.printNLR();
    cout << endl;
    test_bus.printLNR();
    test_bus.insert(18, 60);
    cout << endl;
    test_bus.printNLR();
    cout << endl;
    test_bus.printLNR();
    cout << "\nTesting Deleting \n";
    test_bus.remove(3, 6);
    test_bus.printNLR();
    cout << endl;
    test_bus.printLNR();
    cout << endl;
    test_bus.remove(18, 60);
    test_bus.printNLR();
    cout << endl;
    test_bus.printLNR();
    for (int i = 0; i < 1000; i++)
    {
        test_bus.insert(i, i + 5);
    }
    system("pause");
    return 0;
}