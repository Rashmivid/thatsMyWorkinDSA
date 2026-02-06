#include<bits/stdc++.h>
using namespace std;
struct node{
    int val;
    struct node*next;

}
int main(){
    struct node*head=(struct node*)malloc(sizeof(struct node));
    head->val=20;
    head->next=(struct node*)malloc(size(struct node));
    head->next->val=100;

}