#include "BiTree.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

BiTree::BiTree(){
    root=new BiTNode;
    root->left=nullptr;
    root->right=nullptr;
}

BiTree::~BiTree(){
    delete root;
}

BiTNode* BiTree::Build_Pre(int *a,int len,int &index,int invalid){
    BiTNode *temp=nullptr;
    if(index<len&&a[index]!=invalid){
        temp= new BiTNode;
        temp->data=a[index];
        index++;
        temp->left=Build_Pre(a,len,index,invalid);
        temp->right=Build_Pre(a,len,index,invalid);
    }
    return temp;
}

BiTNode* BiTree::GetRoot(){
    return root;
}

void BiTree::PreOrder(BiTNode *T){
    if(T!=nullptr){
        visit(T);
        PreOrder(T->left);
        PreOrder(T->right);
    }
}

/*1.���ʵ�ǰ���
2.��ǰ�����Ҷ��ӽ��ǿգ�����ջ
3.����ӽ��ǿգ�ʹ֮��Ϊ��ǰ��㣬���򵯳�ջ��Ԫ�أ�ʹ֮��Ϊ��ǰ���
4.����ִ��1��2��3����ջ��Ϊֹ*/
void BiTree::PreOrder2(BiTNode *T){
    Stack<BiTNode* > s;
    BiTNode *p=T;
    while(!s.isEmpty()||p){
        if(p){
            visit(p);
            if(p->right!=nullptr)
                s.Push(p->right);
            p=p->left;
        }
        else{
            p=s.Pop();
        }
    }
}

void BiTree::InOrder(BiTNode *T){
    if(T!=nullptr){
        InOrder(T->left);
        visit(T);
        InOrder(T->right);
    }
}

/*1.ÿ����һ�����Ͱ���ѹջ��Ȼ��ȥ������������
2.�������������󣬴�ջ�����������㲢����֮
3.Ȼ������ý���������*/
void BiTree::InOrder2(BiTNode *T){
    Stack<BiTNode* > s;
    BiTNode *p=T;
    while(!s.isEmpty()||p){
        if(p){
            s.Push(p);
            p=p->left;
        }
        else{
            p=s.Pop();
            visit(p);
            p=p->right;
        }
    }
}

void BiTree::PostOrder(BiTNode *T){
    if(T!=nullptr){
        PostOrder(T->left);
        PostOrder(T->right);
        visit(T);
    }
}
/*
������˼�롿
1.ÿ����һ����㣬�Ȱ�������ջ�У�ȥ��������������
2.������������������Ӧ���������ý���������
3.������������֮�󣬲Ŵ�ջ�������ý�㲢������
�����������
0.���������Ϊ��ǰ���
1.��ջ���̣�
  a.�����ǰ��㲻���Ҿ���������������ǰ���ѹ��ջ�У��������2
  b.����ǰ�����������ĸ��������Ϊ��ǰ���
  c.�ظ� a
2.��ջ���̣�
  a.�����ǰ��㲻����û�����������������������ĸ�����Ѿ����ʣ�����֮���������3
  b.��ջ�գ�����������ȡ����ǰջ�������Ϊ��ǰ���
  c.�ظ� a
3.����ǰ���ѹ��ջ��
4.����ǰ�����������ĸ������Ϊ��ǰ��㣬�ظ� 1*/
void BiTree::PostOrder2(BiTNode *T){
    Stack<BiTNode* >s;
    BiTNode *p=T,*pre=T;
    while(p){
       for(;p->left!=nullptr;p=p->left)
        s.Push(p);
       while(p!=nullptr&&(p->right==nullptr||p->right==pre)){
        visit(p);
        pre=p;
        if(s.isEmpty())
            return ;
        p=s.Pop();
       }
       s.Push(p);
       p=p->right;
    }
}

void BiTree::BreadthOrder(BiTNode *T){
    Queue<BiTNode* > Q;
    BiTNode *p=T;
    if(root)
        Q.EnQueue(p);
    while(!Q.isEmpty()){
        p=Q.DeQueue();
        visit(p);
        if(p->left!=nullptr)
            Q.EnQueue(p->left);
        if(p->right!=nullptr)
            Q.EnQueue(p->right);
    }
}

void BiTree::DeleteBiTree(BiTNode *T){
    if(T->left!=nullptr)
        DeleteBiTree(T->left);
    if(T->right!=nullptr)
        DeleteBiTree(T->right);
    delete T;
    T=nullptr;
}

BiTNode* BiTree::Build_pre_in(int *preorder, int *inorder,int n){
    if (n == 0)
        return nullptr;
    int root_data = preorder[0];
    int i = 0;
    for( ;i < n;i ++){
        if(root_data == inorder[i])
             break;
    }
    BiTNode* T = new BiTNode;
    T->data = root_data;
    T->left = Build_pre_in(preorder + 1, inorder, i);
    T->right = Build_pre_in(preorder + i + 1, inorder + i + 1, n - i - 1);
    return T;
}

BiTNode* BiTree::Build_post_in(int *postorder,int *inorder,int m){
    if (m == 0)
        return nullptr;
    int root_data = postorder[m - 1];
    int i = 0;
    for( ;i < m;i ++){
        if(root_data == inorder[i])
             break;
    }
    BiTNode* T = new BiTNode;
    T->data = root_data;
    T->left = Build_post_in(postorder, inorder, i);
    T->right = Build_post_in(postorder+i, inorder + i+1, m-i-1);
    return T;
}





