#include<bits/stdc++.h>
using namespace std;
//here struct can be used but it cant allow benefits of class like opps
struct node{
public:
    int data;
    node* next;

public:
    node(int data1, node* next1){
        data = data1;
        next = next1;
    }
public:
    node(int data1){
        data = data1;
        next = nullptr;
    } //due to this nullptr can get intialized
};
node*convert2ll(vector<int>&A){
    node*head=new node(A[0]);
    node*mover=head;
    for(int i=1;i<A.size();i++){
        node* temp= new node(A[i]);
        mover->next=temp;
        mover=mover->next;//mover=temp
    }
    return head;
}
bool searchLL(node* head,int k){
    node* temp=head;
    while(temp){
        if(temp->data==k) return 1;
        temp=temp->next;        
    }
    return 0;
}
node*deleteHead(node*head){
    if(head==NULL) return head;
    node*temp=head;
    head=head->next;
    free(temp);//delete temp;
    return head;
}
void printy(node*head){
    node*temp=head;
    while(temp){
        cout<<temp->data<<" ";
        temp=temp=temp->next;
    }
}
node* deleteLastNode(node*head){
    if(head==NULL || head->next==NULL) return nullptr;
    node*temp=head;
    while(temp->next->next!=NULL){
        temp=temp->next;
    }
    delete temp->next;
    temp->next=nullptr;
    return head;

}
node* deleteKthPosition(node* head,int k){
 if(head==NULL) return head;
 if(k==1){
    node*temp=head;
    head=head->next;
    free(temp);
    return head;
 }
 int cnt=0;
 node* temp=head;
 node* prev=nullptr;
 while(temp){
    cnt++;
    if(cnt==k){
        prev->next=prev->next->next;
        free(temp);
        break;
    }
    prev=temp;
    temp=temp->next;
 }
 return head;
}
node* deleteVal(node*head,int val){
    if(head==NULL) return head;
    node* temp=head;
    node*prev=nullptr;
    while(temp){
        if(temp->data==val){
            prev->next=prev->next->next;
            free(temp);
            break;
        }
        prev=temp;
        temp=temp->next;
    }
    return head;
}
node* insertNodeFirst(node*head,int val){
    return new node(val,head);
}
node* insertTail(node* head,int val){
    if(head==NULL){
        return new node(val);
    }
    node* temp=head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    node*newone=new node(val);
    temp->next=newone;
    return head;
}
node* insertPostion(node* head,int val,int k){
    if(head==NULL){
        if(k==1){
            return new node(val);
        }
        else return NULL;
    }
    node* temp=head;
    int cnt=0;
    while(temp!=NULL){
        cnt++;
        if(cnt==k-1){
            node*c=new node(val);
            c->next=temp->next;
            temp->next=c;
            break;
        }
        temp=temp->next;
    }
    return head;
}
node* insertVal(node* head,int val,int el){
    if(head==NULL) return NULL;
    node*temp=head;
    while(temp->next!=NULL){
        if(temp->next->data==val){
            node* n=new node(el);
            n=temp->next;
            temp->next=n;
            break;
        }
        temp=temp->next;
    }
    return head;
}

int main(){
    vector<int>arr = {1,2,3,41,15};
    node*head=convert2ll(arr); 
    // node* temp=head;
    // int cnt=0;
    // int serachElement;
    // cout<<"Search element"<<endl;;
    // cin>>serachElement;
    // if(searchLL(head,serachElement)) cout<< "Present";
    // else cout<<"Not Present";
    // while(temp!=nullptr){
    //     cout<<temp->data<<" ";
    //     temp=temp->next;
    //     cnt++;
    // }
    // cout<<'\n'<<cnt<<endl;
    // node y = node(arr[0], nullptr);
    // cout << y.data<<endl;
    // cout<<y.next;
    // node*y=new node(arr[0],nullptr);
    // cout<<y->data<<'\n';
    // cout<<y->next<<'\n';
    // node*y=new node(arr[0]);for when new contructor intialized then aullptr is not important
    // cout<<y->data<<'\n';
    // cout<<y->next<<'\n';
    //head=deleteHead(head);
    //head=deleteLastNode(head);
    //int val;
    //cin>>val;
    //head=deleteKthPosition(head,k);
    //head=deleteVal(head,val);
    //head=insertNodeFirst(head,100);
    //head=insertTail(head,50);
    int val;
    cin>>val;
    //head=insertPostion(head,100,k);
    head=insertVal(head,val,100);
    printy(head);
}
