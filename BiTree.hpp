#ifndef BITREE_HPP_INCLUDED
#define BITREE_HPP_INCLUDED

#include <cstdlib>
#include <vector>
#include <iostream>
#include "Queue.hpp"
#include "Stack.hpp"
using namespace std;

typedef unsigned long long ULL;

typedef struct BiTNode {
     int data;
     BiTNode *left;
     BiTNode *right;
     BiTNode(){}
     BiTNode(int x) : data(x), left(nullptr), right(nullptr) {}
     BiTNode(int x,BiTNode* l,BiTNode* r) : data(x), left(l), right(r) {}
}BiTNode,*_BiTNode;

class BiTree{
public:
    BiTree();//建立根节点
    ~BiTree();//释放根节点

    BiTNode* Build_Pre();
    BiTNode* Build_Pre(int[] );
    BiTNode* GetRoot();

    void visit(BiTNode *T){ cout<<T->data<<" ";}

    bool IsEmpty(BiTNode* );
    bool IsComplete(BiTNode* );
    bool IsBST(BiTNode* );
    bool IsAVL(BiTNode* );

    void PreOrder(BiTNode* );
    void PreOrder2(BiTNode* );
    void InOrder(BiTNode* );
    void InOrder2(BiTNode* );
    void PostOrder(BiTNode* );
    void PostOrder2(BiTNode* );
    void PostOrder3(BiTNode* );
    void BreadthOrder(BiTNode* );
    void BreadthReverseOrder(BiTNode* );

    int FindPre_Index(BiTNode* ,int );//先序遍历的第Index个
    int FindIn_Index(BiTNode* ,int );//中序遍历的第Index个
    int FindPost_Index(BiTNode* ,int );//后序遍历的第Index个
    void FindAncestor(BiTNode* ,int );//打印祖先

    void DeleteBiTree(_BiTNode &);
    void DeleteAllLeaves(_BiTNode &,BiTNode* );//删除所有叶节点，第二个参数任意

    BiTNode* Build_pre_in(int[] ,int[] ,int );
    BiTNode* Build_post_in(int[] ,int[] ,int );

    int Depth(BiTNode* );//深度递归
    int Depth2(BiTNode* );//深度非递归
    int Width(BiTNode* );
    void SwapSubTree(BiTNode* );//镜像左右子树
    int WPL(BiTNode* );

    int NumberOfLeaves(BiTNode* );//叶子结点总个数
    int NumberOfOne(BiTNode* );//度为一的个数
    int NumberOfTwo(BiTNode* );//度为二的个数




private:
    BiTNode *root;
};

#endif // BITREE_HPP_INCLUDED
