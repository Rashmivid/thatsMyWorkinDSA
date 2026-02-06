#include<bits/stdc++.h>
using namespace std;

class node{
public:    
  int data;
  node*next;
  node*prev;

  node(int data1,node*next1,node*prev1){
    data=data1;
    next=next1;
    prev=prev1;
  }

  node(int data1){
    data=data1;
    next=nullptr;
    prev=nullptr;
  }
};

node* dlarr(vector<int>&arr){
    node*head=new node(arr[0]);
    node*temp=head;
    int n=arr.size();
    for(int i=1;i<n;i++){
        node* c=new node(arr[i],NULL,temp);
        temp->next=c;
        temp=temp->next;
    }
    return head;
}

node* ddlHead(node* head){
  if(head==NULL || head->next==NULL) return NULL;
  node*previ=head;
  head=head->next;
  head->prev=nullptr;
  previ->next=nullptr;
  delete previ;
  return head;
}

node* ddlTail(node* head){
  if(!head) return NULL;
  if(!head->next){
    delete head;
    return NULL;
  }
  node* temp=head;
  while(temp->next!=NULL){
    temp=temp->next;
  }
  node* previ=temp->prev;
  previ->next=NULL;
  temp->prev=NULL;
  delete temp;
  return head;
}

node* ddlKthElement(node* head,int k){
  if(head==NULL) return head;
  node* temp=head;
  int cnt=0;

  while(temp!=NULL){
    cnt++;
    if(cnt==k) break;
    temp=temp->next;
  }

if(temp==NULL) return head; // k > size

  node* previ=temp->prev;
  node* front=temp->next;

  // only one node
  if(front==NULL && previ==NULL){
    return NULL;
  }

  // deleting last node
  else if(front==NULL){
   return ddlTail(head);
    
  }

  // deleting first node
  else if(previ==NULL){
    return ddlHead(head);
  }

  // middle
  previ->next=front;
  front->prev=previ;
  temp->prev=NULL;
  temp->next=NULL;
  delete temp;

  return head;
}

node* ddlVal(node* head,int val){
  if(head==NULL) return head;

  node* temp=head;
  while(temp!=NULL){
    if(temp->data==val) break;
    temp=temp->next;
  }

  if(temp==NULL) return head;  // value not found

  node* previ=temp->prev;
  node* front=temp->next;

  // only one node
  if(front==NULL && previ==NULL){
    return NULL;
  }

  // deleting last node
  else if(front==NULL){
 return ddlTail(head);
  }

  // deleting first node
  else if(previ==NULL){
   return ddlHead(head);
  }

  // deleting middle
  previ->next=front;
  front->prev=previ;
  delete temp;

  return head;
}

void printy(node*head){
    node*temp=head;
    while(temp){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
}
void ddlNode(node*temp){
  node*previ=temp->prev;
  node*front=temp->next;
  if(front==NULL){
    previ->next=NULL;
    temp->prev=NULL;
    delete temp;
    return;
  }
  previ->next=front;
  front->prev=previ;
  temp->next=temp->prev=nullptr;
  delete temp;
  return;
}
node* ddlInsertHead(node* head){
node* newNode=new node(10,head,nullptr);
head->prev=newNode;
return newNode;
}
node* ddlInsertTail(node* head){
  node* temp=head;
  while(temp->next!=nullptr){
    temp=temp->next;
  }
  node* newNode=new node(10,nullptr,temp);
  temp->next=newNode;
  return head;
}
node* ddlKthInsert(node* head,int k){
  if(k==1) return ddlInsertHead(head);
  node* temp=head;
  int cnt=0;
  while(temp!=nullptr){
    cnt++;
    if(cnt==k) break;
    temp=temp->next;
  }
  if(temp==NULL) return ddlInsertHead(head);
  node* previ=temp->prev;
  node* newNode=new node(10,temp,previ);
  temp->prev=newNode;
  previ->next=newNode;
  return head;
}
void ddlNodeInsert(node* temp){
  node* newNode=new node(10,temp,temp->prev);
  node* previ=temp->prev;
  temp->prev=newNode;
  previ->next=newNode;
}
int main(){
    vector<int>arr={2,3,5,4,5,9,8};
    node*head=dlarr(arr);
     //head=ddlHead(head);
    //head=ddlTail(head);
    // int k;
    // cin>>k;
    // head=ddlKthElement(head,k);

    // int val;
    // cin>>val;
    // head=ddlVal(head,val);
    // ddlNode(head->next);
    // head=ddlInsertHead(head);
    // head=ddlInsertTail(head);
    head=ddlKthInsert(head,1);
    // ddlNodeInsert(head->next->next);
    printy(head);
}
