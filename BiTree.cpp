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

/*1.访问当前结点
2.当前结点的右儿子结点非空，则入栈
3.左儿子结点非空，使之作为当前结点，否则弹出栈顶元素，使之作为当前结点
4.反复执行1、2、3，至栈空为止*/
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

/*1.每遇到一个结点就把它压栈，然后去遍历其左子树
2.遍历完左子树后，从栈顶弹出这个结点并访问之
3.然后遍历该结点的右子树*/
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
【基本思想】
1.每遇到一个结点，先把它推入栈中，去遍历它的左子树
2.遍历完它的左子树后，应继续遍历该结点的右子树
3.遍历完右子树之后，才从栈顶弹出该结点并访问它
【解决方案】
0.将根结点作为当前结点
1.进栈过程：
  a.如果当前结点不空且具有左子树，将当前结点压入栈中，否则进入2
  b.将当前结点的左子树的根结点设置为当前结点
  c.重复 a
2.出栈过程：
  a.如果当前结点不空且没有右子树，或者其右子树的根结点已经访问，访问之，否则进入3
  b.若栈空，结束，否则取出当前栈顶结点作为当前结点
  c.重复 a
3.将当前结点压入栈中
4.将当前结点的右子树的根结点设为当前结点，重复 1*/
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





