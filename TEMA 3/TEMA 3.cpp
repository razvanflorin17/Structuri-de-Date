
/// TREAPURI ///

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

ifstream f("abce.in");
ofstream g("abce.out");

const int infinite = 1000000000;


/// NODE ///


struct node
{

    int key, priority;
    node *left, *right;

    node() {}

    node(int key, int priority, node *left, node *right)
    {
        this->key = key;
        this->priority = priority;
        this->left = left;
        this->right = right;
    }

};


node *root, *nil;


/// SEARCH ///


int search_node(node *n, int key)
{
    if(n == nil) return 0;

    if(key == n->key) return 1;

    if(key < n->key)
        return search_node(n->left, key);
    else
        return search_node(n->right, key);
}


/// ROTATE ///


void rotate_left(node* &n)
{
    node *aux = n->left;
    n->left = aux->right;
    aux->right = n;
    n = aux;
}


void rotate_right(node* &n)
{
    node *aux = n->right;
    n->right = aux->left;
    aux->left = n;
    n = aux;
}


void balance(node* &n)
{
    if(n->left->priority > n->priority)
        rotate_left(n);
    else if(n->right->priority > n->priority)
        rotate_right(n);
}


/// INSERT ///


void insert_node(node* &n, int key)
{
    if(n == nil)
    {
        n = new node(key, rand(), nil, nil);    // Daca e null il punem ca radacina
        return;
    }

    if(key < n->key)
        insert_node(n->left, key);
    else if(key > n->key)
        insert_node(n->right, key);

    balance(n);
}


/// DELETE ///


void delete_node(node* &n, int x)
{
    if(n == nil) return;

    if(x < n -> key)
        delete_node(n -> left, x);
    else if(x > n -> key)
        delete_node(n -> right, x);
    else
    {
        if(n -> left == nil and n -> right == nil)
        {
            delete n;
            n = nil;
            return;
        }
        else if(n -> left == nil)
        {
            rotate_right(n);
            delete_node(n, x);
        }
        else if(n -> right == nil)
        {
            rotate_left(n);
            delete_node(n, x);
        }
        else if(n -> left -> priority > n -> right -> priority)
        {
            rotate_left(n);
            delete_node(n, x);
        }
        else
        {
            rotate_right(n);
            delete_node(n, x);
        }
    }
}


/// PREDECESSOR ///


int predecessor(node *n, int x)
{
    if(n == nil)    return -infinite;

    if(n->key == x) return x;

    if(n->key > x)
        return predecessor(n->left, x);
    else
        return max(n->key, predecessor(n->right, x));
}


/// SUCCESSOR ///


int successor(node *n, int x)
{
    if(n == nil)    return infinite;

    if(n->key == x) return x;

    if(n->key < x)
        return successor(n->right, x);
    else
        return min(n->key, successor(n->left, x));

}


/// SORT ///


void sort_treap(node *n, int x, int y)
{
    if(n == nil)    return;

    if(n->key > x)  sort_treap(n->left, x, y);

    if(n->key >= x && n->key <= y)  g << n->key <<" ";

    if(n->key < y)  sort_treap(n->right, x, y);
}

int main()
{
    int q, t, x, y;

    f >> q;

    root = nil = new node(0, 0, nullptr, nullptr);

    for(int i = 0; i < q; i++)
    {
        f >> t;
        if(t == 1)
        {
            f >> x;
            insert_node(root, x);
        }
        if(t == 2)
        {
            f >> x;
            delete_node(root, x);
        }
        if(t == 3)
        {
            f >> x;
            g << search_node(root, x) << "\n";
        }
        if(t == 4)
        {
            f >> x;
            g << predecessor(root, x) << "\n";
        }
        if(t == 5)
        {
            f >> x;
            g << successor(root, x) << "\n";
        }
        if(t == 6)
        {
            f >> x >> y;
            sort_treap(root, x, y);
            g << "\n";
        }
    }

    return 0;
}
