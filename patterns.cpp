#include<bits/stdc++.h>
using namespace std;
int main(){
    //pattern 1:
    //*****
    //*****
    //*****
    int n;
    cin>>n;//input from user
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<"*"<<" ";
    //     }
    //     cout<<endl;
    // }
    //pattern2:
    // *
    // **
    // ***
    // ****
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<=i;j++){
    //         cout<<"*"<<" ";
    //     }
    //     cout<<endl;
    // }
    //patter3:
    // 1
    // 12
    // 123
    // 1234
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=i;j++){
    //         cout<<j<<" ";
    //     }
    //     cout<<endl;
    // }
    //pattern4:
    // *****
    // ****
    // ***
    // **
    // *
    // for(int i=n;i>=1;i--){
    //     for(int j=1;j<=i;j++){
    //         cout<<"*"<<' ';
    //     }
    //     cout<<endl;
    // }
    // OR
    // for(int i=1;i<=n;i++){
    //     for(int j=0;j<=n-i;j++){
    //         cout<<"*"<<' ';
    //     }
    //     cout<<endl;
    // }
    //pattern5:
    // 12345
    // 1234
    // 123
    // 12
    // 1
    // for(int i=n;i>=1;i--){
    //     for(int j=1;j<=i;j++){
    //         cout<<j<<' ';
    //     }
    //     cout<<endl;
    // }
    //OR
    // for(int i=0;i<n;i++){
    //     for(int j=1;j<=n-i;j++){
    //         cout<<j<<' ';
    //     }
    //     cout<<endl;
    // }
    //pattern6:
    //     *
    //    ***
    //   *****
    //  *******   
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n-i-1;j++){
    //         cout<<" ";
    //     }
    //     for(int k=0;k<2*i+1;k++){
    //         cout<<"*";

    //     }
    //     for(int j=0;j<n-i-1;j++){
    //         cout<<" ";
    //     }
    //     cout<<endl;
    // }
    //OR
    //  for(int i=0;i<n;i++){
    //     for(int j=n-1;j>i;j--){
    //         cout<<" ";
    //     }
    //     for(int k=0;k<2*i+1;k++){
    //         cout<<"*";

    //     }
    //     for(int j=n-1;j>i;j--){
    //         cout<<" ";
    //     }
    //     cout<<endl;
    // }
    //pattern7:
    // *****
    //  ***
    //   *
    // for(int i=n-1;i>=0;i--){
    //     for(int k=0;k<n-i-1;k++) cout<<" ";
    //     for(int j=0;j<2*i+1;j++)cout<<"*";
    //     for(int k=0;k<n-i-1;k++) cout<<" ";
    //      cout<<endl;
    // }
    //or
    //  for(int i=0;i<n;i++){
    //     for(int k=0;k<i;k++) cout<<" ";
    //     for(int j=0;j<2*n-(2*i+1);j++)cout<<"*";
    //     for(int k=0;k<i;k++) cout<<" ";
    //      cout<<endl;
    // }
    //pattern8:
        //   *
        //  ***
        // *****
        //  ***
        //   *  
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n-i-1;j++){
    //         cout<<" ";
    //     }
    //     for(int k=0;k<2*i+1;k++){
    //         cout<<"*";

    //     }
    //     for(int j=0;j<n-i-1;j++){
    //         cout<<" ";
    //     }
    //     cout<<endl;
    // }
    // for(int i=n-2;i>=0;i--){
    //     for(int k=0;k<n-i-1;k++) cout<<" ";
    //     for(int j=0;j<2*i+1;j++)cout<<"*";
    //     for(int k=0;k<n-i-1;k++) cout<<" ";
    //      cout<<endl;
    // }
    //pattern 9:
    // *
    // **
    // ***
    // ****
    // ***
    // **
    // *
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<=i;j++)cout<<"*";
    //     cout<<endl;
    // }
    // for(int i=n-2;i>=0;i--){
    //     for(int j=0;j<=i;j++) cout<<"*";
    //     cout<<endl;
    // }
    //pattern10:
    // 1
    // 01
    // 101
    // 0101
    int y;
    for(int i=0;i<n;i++){
        if (i%2==0) y=1;
        else y=0;
        for(int j=0;j<=i;j++){          
            cout<<y;
            y=1-y;
        }
        cout<<endl;
    }
   
}