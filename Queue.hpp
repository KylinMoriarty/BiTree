#ifndef QUEUE_HPP_INCLUDED
#define QUEUE_HPP_INCLUDED
#define Max_Q 10

using std::cout;
using std::endl;

template<class Type>
struct SqQueue{
    Type data[Max_Q];
    int front,rear;
};

template<class Type>
class Queue{
public:
    Queue();
    ~Queue();

    void InitQueue();
    bool isEmpty();
    bool EnQueue(Type );
    Type DeQueue();
private:
    SqQueue<Type> q;

};

template<class Type>
Queue<Type>::Queue(){
    InitQueue();
}

template<class Type>
Queue<Type>::~Queue(){

}

template<class Type>
void Queue<Type>::InitQueue(){
    q.rear=0;
    q.front=0;
}

template<class Type>
bool Queue<Type>::isEmpty(){
    if(q.rear==q.front)
        return true;
    else
        return false;
}

template<class Type>
bool Queue<Type>::EnQueue(Type x){
    if((q.rear+1)%Max_Q==q.front){
        cout<<x<<"�޷����룬������"<<endl;
        return false;
    }//Լ����ͷָ���ڶ�βָ�����һλ����Ϊ�����ı�־
    q.data[q.rear]=x;
    q.rear=(q.rear+1)%Max_Q;
    return true;
}

template<class Type>
Type Queue<Type>::DeQueue(){
    Type Invalid;
    if(q.rear==q.front){
        cout<<"�ӿ�"<<endl;
        return Invalid;
    }
    Type x =q.data[q.front];
    q.front=(q.front+1)%Max_Q;
    return x;
}

//    Queue<char> s;
//    cout<<s.DeQueue()<<endl;
//    s.EnQueue('x');
//    s.EnQueue('y');
//    s.EnQueue('z');
//    cout<<s.DeQueue()<<endl;
//    cout<<s.DeQueue()<<endl;
//    cout<<s.DeQueue()<<endl;
//    for(int i=1;i<=7;i++)
//        s.EnQueue((char)(i+'0'));

#endif // QUEUE_HPP_INCLUDED
