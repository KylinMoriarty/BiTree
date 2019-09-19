#include <iostream>
#include "BiTree.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
using namespace std;

int main()
{
    /*A    4            a     1
          / \                / \
         2   6              2   3
        / \ / \              \   \
       1  3 5  7             4    5
                            / \    \
                           6   7    8
    */
    BiTNode D(1),E(3),F(5),G(7);
    BiTNode B(2,&D,&E),C(6,&F,&G);
    BiTNode A(4,&B,&C);
    BiTNode f(6),g(7),h(8);
    BiTNode d(4,&f,&g),e(5,nullptr,&h);
    BiTNode b(2,nullptr,&d),c(3,nullptr,&e);
    BiTNode a(1,&b,&c);
    BiTree T;
    int num[18]={1,2,0,4,6,0,0,7,0,0,3,0,5,0,8,0,0};
//    T.BreadthOrder(&a);
//    cout<<endl;

    cout<<T.NumberOfLeaves(&a)<<";"<<T.NumberOfOne(&a)<<";"<<T.NumberOfTwo(&a)<<endl;
    _BiTNode test=&a;
    BiTNode *p;
    T.DeleteAllLeaves(test);
    cout<<T.NumberOfLeaves(&a)<<";"<<T.NumberOfOne(&a)<<";"<<T.NumberOfTwo(&a)<<endl;

//    cout<<T.NumberOfLeaves(&A)<<";"<<T.NumberOfOne(&A)<<";"<<T.NumberOfTwo(&A)<<endl;



//    T.BreadthOrder();
//    T.DeleteBiTree();
    //T.BreadthOrder(_a);
    cout<<endl;



   // cout<<_a->data<<endl;
    T.Build_Pre(num);
    //T.BreadthOrder(T.GetRoot());
    //T.FindAncestor(T.GetRoot(),6);
    cout<<endl;
    T.BreadthOrder(T.GetRoot());
    //cout<<(T.GetRoot()->data)<<endl;

    //cout<<T.GetRoot()->data<<endl;
    cout<<T.IsEmpty(test)<<"!!"<<endl;
   // T.PreOrder(T.GetRoot());
    cout<<endl;

//    int k=4;
//    cout<<T.FindPre_Index(T.GetRoot(),4)<<endl;
//    T.PreOrder(&A);
//    cout<<endl;
//    cout<<T.FindPre_Index(&A,k)<<endl;


    T.BreadthOrder(&a);
    cout<<endl;
    T.BreadthOrder(&a);
    cout<<endl;
    T.PreOrder(&a);
    cout<<endl;
    //T.PreOrder2(T.GetRoot());
    cout<<endl;
    T.InOrder(&a);
    cout<<endl;
    //T.InOrder2(T.GetRoot());
    cout<<endl;
    T.PostOrder(&a);
    cout<<endl;
    //T.PostOrder2(T.GetRoot());
    cout<<endl;
    //T.PostOrder3(T.GetRoot());
    cout<<endl;


//    int preorder[8]= {1,2,4,6,7,3,5,8};
//    int inorder[8] = {2,6,4,7,1,3,5,8};
//    int postorder[8]={6,7,4,2,8,5,3,1};
//    BiTNode* root1 = T.Build_pre_in(preorder,inorder,8);
//    cout << endl << "先序中序构造后广度优先遍历为:" << endl;
//    T.BreadthOrder(root1);
//    BiTNode* root2 = T.Build_pre_in(preorder,inorder,8);
//    cout << endl << "后序中序构造后广度优先遍历为:" << endl;
//    T.BreadthOrder(root2);
//    cout<<endl;

    T.BreadthReverseOrder(&A);
    cout<<endl;
    cout<<T.Depth2(&A)<<endl;
    cout<<T.IsComplete(&A)<<endl;
   // T.SwapSubTree(&A);
    T.BreadthOrder(&A);
//    cout<<endl<<T.Width(&A)<<endl;
//    cout<<endl<<T.Width(&a)<<endl;
//    cout<<endl<<T.IsBST(&A)<<endl;
//    cout<<endl<<T.IsBST(&a)<<endl;
//    cout<<endl<<T.WPL(&A)<<endl;
//    cout<<endl<<T.WPL(&a)<<endl;
    return 0;
}
