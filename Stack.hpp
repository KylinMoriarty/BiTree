#ifndef STACK_HPP_INCLUDED
#define STACK_HPP_INCLUDED
#define Max 50

using std::cout;
using std::endl;

template <class Type>
struct SqStack{
    Type data[Max];
    int top;
};

template <class Type>
class Stack{
public:
    Stack();
    ~Stack();

    void InitStack();
    bool isEmpty();
    bool Push(Type );
    Type* ReturnFromBottom();
    Type Pop();
    Type GetTop();
private:
    SqStack<Type> s;
};

template<class Type>
Stack<Type>::Stack(){
    InitStack();
}

template<class Type>
Stack<Type>::~Stack(){

}

template<class Type>
void Stack<Type>::InitStack(){
    s.top=-1;
}

template<class Type>
bool Stack<Type>::isEmpty(){
    if(s.top==-1)
        return true;
    else
        return false;
}

template<class Type>
bool Stack<Type>::Push(Type x){
    if(s.top==Max-1)
        return false;
    s.data[++s.top]=x;
    return true;
}

template<class Type>
Type* Stack<Type>::ReturnFromBottom(){
    Type *p = new Type[s.top+2];//×¢ÒâÒª¼Ó2 ÎªÉ¶ÄØ
    while(s.top!=-1){
        //cout<<s.top<<endl;
        //cout<<s.data[s.top]<<endl;
        p[s.top]=s.data[s.top];
        //cout<<p[s.top]<<endl;
        s.top--;
    }
    return p;
}

template<class Type>
Type Stack<Type>::Pop(){
    Type Invalid;
    if(s.top==-1){
        cout<<"Õ»¿Õ£¡"<<endl;
        return Invalid;
    }

    return s.data[s.top--];
}

template<class Type>
Type Stack<Type>::GetTop(){
    Type Invalid;
    if(s.top==-1){
        cout<<"Õ»¿Õ£¡"<<endl;
        return Invalid;
    }
    return s.data[s.top];
}

//    Stack s;
//    cout<<s.GetTop()<<endl;
//    cout<<s.Pop()<<endl;
//    s.Push(1);
//    s.Push(2);
//    cout<<s.GetTop()<<endl;
//    cout<<s.Pop()<<endl;
//    cout<<s.GetTop()<<endl;
//    cout<<s.Pop()<<endl;

#endif // STACK_HPP_INCLUDED
