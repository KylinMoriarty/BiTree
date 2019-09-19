#include "BiTree.hpp"
#include <iostream>
#include <cstdlib>
#define MIN_DATA -32767

using namespace std;

BiTree::BiTree(){
    root=new BiTNode;
    root->left=nullptr;
    root->right=nullptr;
}

BiTree::~BiTree(){
    delete root;
    root=nullptr;
}

//请按先序顺序输入，空指针用0代替
BiTNode* BiTree::Build_Pre(){
    int x;
    BiTNode* T;
    cout<<"请按先序输入，用0代替空指针"<<endl;
    cin>>x;
    if(x==0) T=nullptr;
    else
    {
        T=new BiTNode;
        T->data=x;
        T->left=Build_Pre();
        T->right=Build_Pre();
    }
    root=T;
    return T;
}

int INDEX=0;
BiTNode* BiTree::Build_Pre(int *num){
    int x;
    BiTNode* T;
    x=num[INDEX];
    INDEX++;
    if(x==0) T=nullptr;
    else
    {
        T=new BiTNode;
        T->data=x;
        T->left=Build_Pre(num);
        T->right=Build_Pre(num);
    }
    root=T;
    /*if(T!=nullptr)
    cout<<T->data<<"+"<<endl;
    if(T==nullptr)
    cout<<INDEX<<"-"<<endl;*/ //理解递归过程
    return T;
}

BiTNode* BiTree::GetRoot(){
    return root;
}

bool BiTree::IsEmpty(BiTNode *T){
    if(T==nullptr)
        return true;
    return false;
}

/*将所有节点加入队列，包括空节点。当遇到空节点时，检查其后是否有
非空节点，若有则不是完全二叉树*/
bool BiTree::IsComplete(BiTNode *T){
    Queue<BiTNode* > Q;
    if(!T) return true;
    Q.EnQueue(T);
    BiTNode *p;
    while(!Q.isEmpty()){
        p=Q.DeQueue();
        if(p){
            Q.EnQueue(p->left);
            Q.EnQueue(p->right);
        }
        else{
            while(!Q.isEmpty()){
                p=Q.DeQueue();
                if(p)
                    return false;
            }
        }
    }
    return true;
}

int PRE=MIN_DATA;//为全局变量，中序遍历，保证每个前面的值小于后面的值
bool BiTree::IsBST(BiTNode* T){
    int l,r;
    if(T==nullptr)
        return true;
    else{
        l=IsBST(T->left);
        if(l==0||PRE>=T->data)
            return 0;
        PRE=T->data;
        r=IsBST(T->right);
        return r;
    }
}

bool BiTree::IsAVL(BiTNode* T){
    if(T==nullptr)
        return true;
    int rDepth=Depth(T->right);
    int lDepth=Depth(T->left);
    if(rDepth>lDepth+1||lDepth>rDepth+1)
        return false;
    else return IsAVL(T->left)&&IsAVL(T->right);
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
    Stack<BiTNode* > s;
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

void BiTree::PostOrder3(BiTNode *T){
    Stack<BiTNode* > s;
    BiTNode *p=T,*r=nullptr;
    while(p||!s.isEmpty()){
        if(p){
            s.Push(p);
            p=p->left;                 //走到最左边
        }
        else{                          //向右
            p=s.GetTop();              //取栈顶节点
            if(p->right&&p->right!=r){ //如果右子树存在，且没有被访问过
                p=p->right;            //转向右
                s.Push(p);             //压入栈
                p=p->left;             //再走到最左
            }
            else{                      //否则，弹出结点并访问
                s.Pop();               //将结点弹出
                visit(p);              //访问该节点
                r=p;                   //记录最近访问过得结点
                p=nullptr;             //结点访问完后，重置p指针
            }
        }
    }
}

//层次遍历
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

void BiTree::BreadthReverseOrder(BiTNode *T){
    Stack<BiTNode* > s;
    Queue<BiTNode* > Q;
    BiTNode *p=T;
    if(T!=nullptr){
        Q.EnQueue(p);
        while(!Q.isEmpty()){
            p=Q.DeQueue();
            s.Push(p);
            if(p->left)
                Q.EnQueue(p->left);
            if(p->right)
                Q.EnQueue(p->right);
        }
        while(!s.isEmpty()){
            p=s.Pop();
            visit(p);
        }
    }
}

//递归方法没有解决
//int BiTree::FindPre_Index(BiTNode* T,int k){
//    if(T!=nullptr)
//    {
//        ++N;
//        cout<<T->data<<" "<<N<<" "<<k<<endl;
//        if(N==k){
//            N=0;
//            cout<<T->data<<endl;
//            //return T->data;
//        }
//        FindPre_Index(T->left,k);
//        FindPre_Index(T->right,k);
//    }
//    return 0;
//}

int N=0;
int BiTree::FindPre_Index(BiTNode *T,int k){
    Stack<BiTNode* > s;
    BiTNode *p=T;
    while(!s.isEmpty()||p){
        if(p){
            N++;
            if(k==N){
                N=0;
                return p->data;
            }
            if(p->right!=nullptr)
                s.Push(p->right);
            p=p->left;
        }
        else{
            p=s.Pop();
        }
    }
    N=0;
    return 0;
}

void BiTree::FindAncestor(BiTNode *T,int k){
    Stack<BiTNode* > s;
    BiTNode *p=T,*r=nullptr;
    while(p||!s.isEmpty()){
        if(p){
            s.Push(p);
            p=p->left;                 //走到最左边
        }
        else{                          //向右
            p=s.GetTop();              //取栈顶节点
            if(p->data==k){
//                while(!s.isEmpty()){
//                    p=s.Pop();
//                    visit(p);
//                }
                _BiTNode *temp=s.ReturnFromBottom();
                while((*temp))
                    cout<<(*(temp++))->data<<" ";
                cout<<endl;
                return ;
            }
            if(p->right&&p->right!=r){ //如果右子树存在，且没有被访问过
                p=p->right;            //转向右
                s.Push(p);             //压入栈
                p=p->left;             //再走到最左
            }
            else{                      //否则，弹出结点并访问
                s.Pop();               //将结点弹出
                r=p;                   //记录最近访问过得结点
                p=nullptr;             //结点访问完后，重置p指针
            }
        }
    }
}

void BiTree::DeleteBiTree(_BiTNode &T){//注意一定要传指针的引用！！！！
    if(T==nullptr)
        return ;
    if(T->left!=nullptr)
        DeleteBiTree(T->left);
    if(T->right!=nullptr)
        DeleteBiTree(T->right);
    delete T;
    T=nullptr;//必须要置空,否则成为野指针
    return ;
}
    /*_BiTNode _a=new BiTNode;
    _BiTNode _b=new BiTNode;
    _BiTNode _c=new BiTNode;
    _a->data=1;_b->data=2;_c->data=3;
    _a->left=_b,_a->right=_c;
    _b->left=nullptr,_b->right=nullptr;
    _c->left=nullptr,_c->right=nullptr;*/
//在传递过程中，即使是传的引用，也只是传的_a的左右节点，并不是_b和_c，
//但是空间的确是释放了，b和c内存地址不变，但是指向的内容已经空了。

void BiTree::DeleteAllLeaves(_BiTNode &T,BiTNode *p){//要注意保存父节点，由父节点使其左右子树为空
    if(T){
        if(T->left==nullptr&&T->right==nullptr){
            if(p==nullptr){
                delete T;
                T==nullptr;
                return ;
            }
            else{
                delete T;
                T==nullptr;
                cout<<p->data<<"~"<<endl;
                p->left=nullptr;
                p->right=nullptr;
            }
        }
        else{
            p=T;
            if(T->left!=nullptr)
            DeleteAllLeaves(T->left,p);
            if(T->right!=nullptr)
            DeleteAllLeaves(T->right,p);
        }
    }
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
    T->left = Build_post_in(postorder,inorder,i);
    T->right = Build_post_in(postorder+i,inorder+i+1, m-i-1);
    return T;
}

/*如果一个树只有一个节点，它的深度为1；
如果根节点既有左子树又有右子树，那么树的深度应该是左右字数深度的较大值+1*/
int BiTree::Depth(BiTNode *T){
    if(T==nullptr)
        return 0;
    int l=Depth(T->left);
    int r=Depth(T->right);
    if(l>r)
        return l+1;
    else
        return r+1;
}

//采用层次遍历的非递归方法求解二叉树高度 重点！！
int BiTree::Depth2(BiTNode *T){
    if(!T) return 0;
    int front=-1,rear=-1;
    int last=0,level=0;//last指下一层第一个节点的位置
    Queue<BiTNode* > Q;
    Q.EnQueue(T);
    rear++;
    BiTNode *p;
    while(!Q.isEmpty()){
        p=Q.DeQueue();
        front++;
        if(p->left){
            Q.EnQueue(p->left);
            rear++;
        }
        if(p->right){
            Q.EnQueue(p->right);
            rear++;
        }
        if(front==last){//处理该层的最右节点
            level++;
            last=rear;
        }
    }
    return level;
}

int BiTree::Width(BiTNode* T){
    if(!T) return 0;
    int front=-1,rear=-1,width=0;
    int last=0,level=0,i=0;//last指下一层第一个节点的位置
    Queue<BiTNode* > Q;
    Q.EnQueue(T);
    rear++;
    BiTNode *p;
    while(!Q.isEmpty()){
        p=Q.DeQueue();
        front++;
        i++;
        if(p->left){
            Q.EnQueue(p->left);
            rear++;
        }
        if(p->right){
            Q.EnQueue(p->right);
            rear++;
        }
        if(front==last){//处理该层的最右节点
            level++;
            last=rear;
            if(i>width)
                width=i;
                i=0;
        }
    }
    return width;
}

void BiTree::SwapSubTree(BiTNode *T){
    if(T){
        BiTNode *p;
        p=T->left;
        T->left=T->right;
        T->right=p;
        SwapSubTree(T->left);
        SwapSubTree(T->right);
    }
}

int BiTree::WPL(BiTNode *T){
    if(!T) return 0;
    int front=-1,rear=-1;
    int last=0,level=0,wpl=0;//last指下一层第一个节点的位置
    Queue<BiTNode* > Q;
    Q.EnQueue(T);
    rear++;
    BiTNode *p;
    while(!Q.isEmpty()){
        p=Q.DeQueue();
        front++;
        wpl+=p->data*level;
        if(p->left){
            Q.EnQueue(p->left);
            rear++;
        }
        if(p->right){
            Q.EnQueue(p->right);
            rear++;
        }
        if(front==last){//处理该层的最右节点
            level++;
            last=rear;
        }
    }
    return wpl;
}

int BiTree::NumberOfLeaves(BiTNode *T){
    if(T==nullptr)
        return 0;
    else if(T->left==nullptr&&T->right==nullptr)
        return 1;
    else
        return NumberOfLeaves(T->left)+NumberOfLeaves(T->right);
}

int BiTree::NumberOfOne(BiTNode *T){
    if(T==nullptr)
        return 0;
    else if((T->left==nullptr&&T->right!=nullptr)||(T->left!=nullptr&&T->right==nullptr))
        return 1+NumberOfOne(T->left)+NumberOfOne(T->right);
    else
        return NumberOfOne(T->left)+NumberOfOne(T->right);
}

int BiTree::NumberOfTwo(BiTNode *T){
    if(T==nullptr)
        return 0;
    else if(T->left!=nullptr&&T->right!=nullptr)
        return 1+NumberOfTwo(T->left)+NumberOfTwo(T->right);
    else
        return NumberOfTwo(T->left)+NumberOfTwo(T->right);
}

















