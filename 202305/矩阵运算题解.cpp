#include<iostream>
#include<map>
using namespace std;
 
int main(){
	int n, d;
	cin>>n>>d;
	//输入 
	map<int, map<int, int> > Q, K, V, W;
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=d;j++)
	        cin>>Q[i][j];
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=d;j++)
	        cin>>K[j][i];
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=d;j++)
	        cin>>V[i][j];
	for(int i=1;i<=n;i++)
	    cin>>W[1][i];
	    
	//V*K
	map<long long, map<long long, long long> > ans;
	for(int i=1;i<=d;i++){
		for(int j=1;j<=d;j++){
			int x=0;
			for(int k=1;k<=n;k++) x+=K[i][k]*V[k][j];
			ans[i][j] = x;
		}
	}
	//Q*ans
	for(int i=1;i<=n;i++){
		for(int j=1;j<=d;j++){
			long long x=0;
			for(int k=1;k<=d;k++) x+=Q[i][k]*ans[k][j];
			x*=W[1][i];
			cout<<x<<' ';
		}
		cout<<endl;
	}
}