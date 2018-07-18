#include<iostream>    //问题：若该房子不是一条线的结构，而是环状或二叉树形式 
#include<cstdio>            //对该结构进行求解 
#include<vector>
#include<cassert>

using namespace std;
vector<int> memo;
vector<int> V;
int n;  //n为全局，则不用nums.size() 
       //房子从0引索开始，so取不到nums.size() 

int tryrob(vector<int>& nums,int index){ //自上而下 
	if(index>=nums.size()) return 0;
	if(memo[index]!=-1){   //记忆化搜索 
		return memo[index];
	}
	
	int res=0;
	for(int i=index;i<nums.size();i++){
		res=max(res,nums[i]+tryrob(nums,i+2));
	}
	memo[index]=res;
	return res;
}

int DPtryrob(vector<int>& nums,int n){  //自下而上，先求解最小子问题，逐渐 
	if(n==0) return 0;                 //扩展为全问题 
	
	int res=0;
	vector<int> meno(n,0);
	meno[n-1]=nums[n-1]; //该问题的最小子问题就是前面n-1的房子都不偷，就只偷 
	for(int i=n-2;i>=0;i--){ // 第n-1个房子 然后从后面开始逐渐扩大范围 
		//依旧对memo[i]进行求解 
		for(int j=i;j<n;j++){  
			memo[i]=max(memo[i],nums[j]+(j+2<n?meno[j+2]:0)); //防止j+2不越界
			//用到数组相关，就要考虑数组下标问题 
		}
	}
	return memo[0];
}

int main(){
	int data;
	cin>>n;
	V=vector<int>(n,0);//这里对V进行初始化，且赋值均为0，如果用push_back() 
	memo=vector<int>(n,-1);//就是对容器V尾进行压值，那V[0...n]=0
	for(int i=0;i<n;i++){ //直接用访问数组的形式进行赋值，push_back()感觉有点打开方式不对 
		cin>>V[i];
	}
	cout<<V[0]<<" "<<V[1]<<endl;
	cout<<tryrob(V,0)<<endl;
	cout<<DPtryrob(V,n)<<endl;
	
	return 0;
}
