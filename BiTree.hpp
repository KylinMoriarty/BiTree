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
    BiTree();//�������ڵ�
    ~BiTree();//�ͷŸ��ڵ�

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

    int FindPre_Index(BiTNode* ,int );//��������ĵ�Index��
    int FindIn_Index(BiTNode* ,int );//��������ĵ�Index��
    int FindPost_Index(BiTNode* ,int );//��������ĵ�Index��
    void FindAncestor(BiTNode* ,int );//��ӡ����

    void DeleteBiTree(_BiTNode &);
    void DeleteAllLeaves(_BiTNode &,BiTNode* );//ɾ������Ҷ�ڵ㣬�ڶ�����������

    BiTNode* Build_pre_in(int[] ,int[] ,int );
    BiTNode* Build_post_in(int[] ,int[] ,int );

    int Depth(BiTNode* );//��ȵݹ�
    int Depth2(BiTNode* );//��ȷǵݹ�
    int Width(BiTNode* );
    void SwapSubTree(BiTNode* );//������������
    int WPL(BiTNode* );

    int NumberOfLeaves(BiTNode* );//Ҷ�ӽ���ܸ���
    int NumberOfOne(BiTNode* );//��Ϊһ�ĸ���
    int NumberOfTwo(BiTNode* );//��Ϊ���ĸ���




private:
    BiTNode *root;
};

#endif // BITREE_HPP_INCLUDED
