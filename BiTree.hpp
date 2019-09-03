#ifndef BITREE_HPP_INCLUDED
#define BITREE_HPP_INCLUDED

#include <cstdlib>
#include <vector>
#include <iostream>
#include "Queue.hpp"
#include "Stack.hpp"
using namespace std;

typedef unsigned long long ULL;

struct BiTNode {
     int data;
     BiTNode *left;
     BiTNode *right;
     BiTNode(){}
     BiTNode(int x) : data(x), left(nullptr), right(nullptr) {}
     BiTNode(int x,BiTNode* l,BiTNode* r) : data(x), left(l), right(r) {}
};

class BiTree{
public:
    BiTree();//建立根节点
    ~BiTree();//释放根节点

    BiTNode* Build_Pre(int* ,int ,int& ,int );
    bool IsEmpty();
    BiTNode* GetRoot();
    void visit(BiTNode *T){ cout<<T->data<<" ";}
    void PreOrder(BiTNode* );
    void PreOrder2(BiTNode* );
    void InOrder(BiTNode* );
    void InOrder2(BiTNode* );
    void PostOrder(BiTNode* );
    void PostOrder2(BiTNode* );
    void BreadthOrder(BiTNode* );
    void DeleteBiTree(BiTNode* );
    BiTNode* Build_pre_in(int[] ,int[] ,int );
    BiTNode* Build_post_in(int[] ,int[] ,int );

private:
    BiTNode *root;
};

#endif // BITREE_HPP_INCLUDED
