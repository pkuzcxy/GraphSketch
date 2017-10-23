#include<iostream>
#include<fstream>
#include"Graph.h"
#include<stdlib.h>
using namespace std;
int main()
{
	ifstream fin("C:/Users/dkzcx/Desktop/EE2.txt");
	ofstream fout("C:/Users/dkzcx/Desktop/transEE2.txt"); 
	string s1,s2;
	int n;
	bool ans1,ans2;
	graph* g=new graph();
	int sum=0;
	while(fin>>s1)
	{
		fin>>s2;
		int weight;
		fin >> weight;
		g->insert(s1,s2,0,weight);
	}
	cout<<g->get_edgenum()<<' '<<g->get_nodenum()<<endl;
	sum=0;
	int num=g->node.size();
	cout<<num<<endl;
	cout << g->chong << endl;
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
		s1 = g->node[n1];
		s2 = g->node[n2];
	//	cout<<s1<<' '<<s2<<endl;
		ans1 = g->transquery(s1,s2,0);
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
