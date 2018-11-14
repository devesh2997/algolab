#include<bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> prefix(string s){
int i=1,j=0;
vector<int> t(s.length(),0);
while(i<s.length()){
if(s[i]==s[j]){
t[i]=j+1;
i++;
j++;
}
else{
if(j==0){
t[i]=0;
i++;
}
else
j=t[j-1];
}
}
return t;
}

void Check(string p,string t){
int d=26;
vector<int> a= prefix(p);
vector<vector<int> > q(1+p.length(),vector<int>(d,0));
int i,j;
i=0;
q[i][p[i]-'a']=1;
for(i=1;i<q.size();i++){
for(j=0;j<d;j++){
if(p[i]-'a'==j)
q[i][j]=i+1;
else
q[i][j]=q[a[i-1]][j];
}
}
i=0;j=0;
for(i=0;i<t.length();i++){
j=q[j][t[i]-'a'];
cout<<"numbers of characters matching at "<<i<<" shift is "<<j<<endl;
if(j==p.length())
cout<<"Found at shift "<<i-j+1<<endl;
}
}

int main(){
string p,t;
cout<<"Enter pattern and text respectively\n";
cin>>p>>t;
Check(p,t);
}
