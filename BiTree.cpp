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

//�밴����˳�����룬��ָ����0����
BiTNode* BiTree::Build_Pre(){
    int x;
    BiTNode* T;
    cout<<"�밴�������룬��0�����ָ��"<<endl;
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
    cout<<INDEX<<"-"<<endl;*/ //���ݹ����
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

/*�����нڵ������У������սڵ㡣�������սڵ�ʱ���������Ƿ���
�ǿսڵ㣬����������ȫ������*/
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

int PRE=MIN_DATA;//Ϊȫ�ֱ����������������֤ÿ��ǰ���ֵС�ں����ֵ
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
            p=p->left;                 //�ߵ������
        }
        else{                          //����
            p=s.GetTop();              //ȡջ���ڵ�
            if(p->right&&p->right!=r){ //������������ڣ���û�б����ʹ�
                p=p->right;            //ת����
                s.Push(p);             //ѹ��ջ
                p=p->left;             //���ߵ�����
            }
            else{                      //���򣬵�����㲢����
                s.Pop();               //����㵯��
                visit(p);              //���ʸýڵ�
                r=p;                   //��¼������ʹ��ý��
                p=nullptr;             //�������������pָ��
            }
        }
    }
}

//��α���
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

//�ݹ鷽��û�н��
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
            p=p->left;                 //�ߵ������
        }
        else{                          //����
            p=s.GetTop();              //ȡջ���ڵ�
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
            if(p->right&&p->right!=r){ //������������ڣ���û�б����ʹ�
                p=p->right;            //ת����
                s.Push(p);             //ѹ��ջ
                p=p->left;             //���ߵ�����
            }
            else{                      //���򣬵�����㲢����
                s.Pop();               //����㵯��
                r=p;                   //��¼������ʹ��ý��
                p=nullptr;             //�������������pָ��
            }
        }
    }
}

void BiTree::DeleteBiTree(_BiTNode &T){//ע��һ��Ҫ��ָ������ã�������
    if(T==nullptr)
        return ;
    if(T->left!=nullptr)
        DeleteBiTree(T->left);
    if(T->right!=nullptr)
        DeleteBiTree(T->right);
    delete T;
    T=nullptr;//����Ҫ�ÿ�,�����ΪҰָ��
    return ;
}
    /*_BiTNode _a=new BiTNode;
    _BiTNode _b=new BiTNode;
    _BiTNode _c=new BiTNode;
    _a->data=1;_b->data=2;_c->data=3;
    _a->left=_b,_a->right=_c;
    _b->left=nullptr,_b->right=nullptr;
    _c->left=nullptr,_c->right=nullptr;*/
//�ڴ��ݹ����У���ʹ�Ǵ������ã�Ҳֻ�Ǵ���_a�����ҽڵ㣬������_b��_c��
//���ǿռ��ȷ���ͷ��ˣ�b��c�ڴ��ַ���䣬����ָ��������Ѿ����ˡ�

void BiTree::DeleteAllLeaves(_BiTNode &T,BiTNode *p){//Ҫע�Ᵽ�游�ڵ㣬�ɸ��ڵ�ʹ����������Ϊ��
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

/*���һ����ֻ��һ���ڵ㣬�������Ϊ1��
������ڵ������������������������ô�������Ӧ��������������ȵĽϴ�ֵ+1*/
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

//���ò�α����ķǵݹ鷽�����������߶� �ص㣡��
int BiTree::Depth2(BiTNode *T){
    if(!T) return 0;
    int front=-1,rear=-1;
    int last=0,level=0;//lastָ��һ���һ���ڵ��λ��
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
        if(front==last){//����ò�����ҽڵ�
            level++;
            last=rear;
        }
    }
    return level;
}

int BiTree::Width(BiTNode* T){
    if(!T) return 0;
    int front=-1,rear=-1,width=0;
    int last=0,level=0,i=0;//lastָ��һ���һ���ڵ��λ��
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
        if(front==last){//����ò�����ҽڵ�
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
    int last=0,level=0,wpl=0;//lastָ��һ���һ���ڵ��λ��
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
        if(front==last){//����ò�����ҽڵ�
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

















