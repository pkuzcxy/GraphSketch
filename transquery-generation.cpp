#include<iostream>
#include<fstream>
#include"Graph.h"
#include<stdlib.h>
using namespace std;
int main()
{
	ifstream fin("Amazon.txt");
	ofstream fout("transquery-a.txt"); 
	//ifstream ("transquery.txt");
	ifstream fcheck("data.txt"); 
	string s1,s2;
	int n;
	bool ans1,ans2;
	graph* g=new graph();
	int sum=0;
//	bool in[4000];
//	bool out[4000];
	/*for(int i=0;i<4000;i++)
	{
		in[i]=false;
		out[i]=false;
	}*/
	while(fin>>s1)
	{
//		sum++;
		fin>>s2;
		g->insert(s1,s2,0,1);
		int n1=(g->index.find(s1))->second;
		int n2=(g->index.find(s2))->second;
//		out[n1]=true;
//		in[n2]=true;
	//	g->insert(s2,s1,0,n);
	}
	cout<<g->get_edgenum()<<' '<<g->get_nodenum()<<endl;
	sum=0;
//	int s=0;
	int num=g->node.size();
	cout<<num<<endl;
	int i=0;
	while(i<10000000)
	{
		int n1 = (rand()+200)%num;
		int n2 = (rand()+300)%num;
		//if(n1==n2)
		//	continue;
		//cout<<n1<<' '<<n2<<endl;
	//int s=0;
	//for(int n1=0;n1<num;n1++)
	//{
	//	for(int n2=0;n2<num;n2++)
	//{
		if(n1==n2)
			continue;
	//	if(!out[n1]||!in[n2])
	//		continue; 
	//	s++;
		s1=g->node[n1];
		s2=g->node[n2];
	//	cout<<s1<<' '<<s2<<endl;
		ans1=g->transquery(s1,s2,0);
	//	cout<<"over"<<endl;
	//	ans2=g->transquery(s2,s1,0);
		if(!ans1)
		{
			fout<<s1<<' '<<s2<<endl;
			sum++;
			if(sum==1000)
			return 0;
		}
		i++;
	//	if(s>10000)
			//break;
	}
//	cout<<sum<<endl;
//}
//	}
	/*int num=0;
	while(fcheck>>s1)
	{
		fcheck>>s2>>n;
		int v=g->query(s1,s2,0);
		if(v==n)
			num++;
	}*/
	//cout<<float(num)/sum<<endl;
	return 0;
 } 
