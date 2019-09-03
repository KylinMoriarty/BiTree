#include <iostream>
#include "BiTree.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
using namespace std;

int main()
{
//    int a[10]={1,2,3,-9999,-9999,4,-9999,-9999,5,6};
//    BiTree T;
//    int index=0;
//    int invalid=-9999;
//    BiTNode *root = T.Build_Pre(a,10,index,invalid);
//    T.PreOrder(root);
    BiTNode f(6),g(7),h(8);
    BiTNode d(4,&f,&g),e(5,nullptr,&h);
    BiTNode b(2,nullptr,&d),c(3,nullptr,&e);
    BiTNode a(1,&b,&c);
    BiTree T;
    T.BreadthOrder(&a);
    cout<<endl;
    T.PreOrder(&a);
    cout<<endl;
    T.PreOrder2(&a);
    cout<<endl;
    T.InOrder(&a);
    cout<<endl;
    T.InOrder2(&a);
    cout<<endl;
    T.PostOrder(&a);
    cout<<endl;
    T.PostOrder2(&a);
    cout<<endl;

    int preorder[8]= {1,2,4,6,7,3,5,8};
    int inorder[8] = {2,6,4,7,1,3,5,8};
    int postorder[8]={6,7,4,2,8,5,3,1};
    BiTNode* root1 = T.Build_pre_in(preorder,inorder,8);
    cout << endl << "先序中序构造后广度优先遍历为:" << endl;
    T.BreadthOrder(root1);
    BiTNode* root2 = T.Build_pre_in(preorder,inorder,8);
    cout << endl << "后序中序构造后广度优先遍历为:" << endl;
    T.BreadthOrder(root2);
    return 0;
}
