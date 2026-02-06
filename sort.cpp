#include<bits/stdc++.h>
using namespace std;
void bubbleSort(int n,int arr[]){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]) swap(arr[j],arr[j+1]);
        }
    }
}
void selectionSort(int n,int arr[]){
    int minn=0;
    for(int i=0;i<n-1;i++){
        int minn=i;
       for(int j=i;j<n;j++){
        if(arr[minn]>arr[j]) minn=j;
       }
       swap(arr[minn],arr[i]);
    }
}
void insertionSort(int n,int arr[]){
    for(int i=0;i<n;i++){
        int j=i;
        while(j>0 && arr[j-1]>arr[j]){
            swap(arr[j],arr[j-1]);
            j--;
        }
    }
    
}

void mergeParts(int arr[], int l, int h, int m) {
    vector<int> vec;
    int left = l, right = m + 1;
    while (left <= m && right <= h) {
        if (arr[left] <= arr[right]) {
            vec.push_back(arr[left++]);
        } else {
            vec.push_back(arr[right++]);
        }
    }
    while (left <= m) vec.push_back(arr[left++]);
    while (right <= h) vec.push_back(arr[right++]);

    for (int i = l; i <= h; i++) {
        arr[i] = vec[i - l];
    }
}
void mergeSort(int arr[], int l, int h) {
    if (l >= h) return;
    int mid = (l + h) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, h);
    mergeParts(arr, l, h, mid); // changed here
}
int qF(int arr[],int low,int high){
    int pivot =arr[low];
    int i=low,j=high;
    while(i<j){
        while(arr[i]>=pivot && i<=high-1) i++;
        while(arr[j]<pivot && j>=low+1) j--;
        if(i<j) swap(arr[i],arr[j]);
    }
    swap(arr[low],arr[j]);
    return j;
}
void quickSort(int arr[],int low,int high){
    if(low<high){
        int pI=qF(arr,low,high);
        quickSort(arr,low,pI-1);
        quickSort(arr,pI+1,high);
    }
}

int main(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int low=0,high=n-1;
    //insertionSort(n,arr);
    //selectionSort(n,arr);
    //bubbleSort(n,arr);
    //mergeSort(arr,low,high);
    quickSort(arr,0,n-1);//descending order
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
}