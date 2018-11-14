#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
ll a,n,r=1,m;
cout<<"Enter Number, exponent and modulus value\n";
cin>>a>>n>>m;
while(n){
if(n&1)
r=(r*a)%m;
a=(a*a)%m;
cout<<" at exponent value = "<<n<<" value returned = "<<r<<endl;
n=n>>1;
}
cout<<"answer is "<<r<<endl;
}
