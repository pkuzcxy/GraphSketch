#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include"tcm.h" 
//#include"MSG-shift.h"
//#include"TCM-R.h"
//#include"GBF.h"
#include"UNS.h"
#include<time.h>
//#include"Graph.h" 
using namespace std;
int main()
{
//	ifstream f("data.txt");
	//string s1,s2;
	//int v,l;
/*	graph* gr=new graph();
	while(f>>s1)
	{
		f>>s2>>l>>v;
		gr->insert(s1,s2,l,v);
	}*/ 
//	int w=40;
	//int w=1000;
	ofstream fout1("edge-ARE.txt");
	ofstream fout2("node-ARE.txt");
	ofstream fout3("trans_accuracy-s.txt");
	for(int w=800;w<1000;w+=100)
	{ 
		ifstream fin("Email-EuAll.txt");
		ifstream fsrc("source-count.txt");
		ifstream fdest("destination-count.txt");
		ifstream fcheck("stdans.txt");
		//ifstream fnode("nodequery.txt");
		ifstream ftrans("transquery-e.txt");
	//	MSG *msg = new MSG(0.74*w,4,4);
		TCM *tcm = new TCM(6*w,6*w,7);
		//RCM* rcm =new RCM(2*w,1,4);
	//	GBF *gbf = new GBF(w,4,4);
		UNS *uns = new UNS(2*w,16,8,1,4,12);
		string s1, s2;
		int v;
	//	int l, v;
		int n=0;
		string so1, si2;
		while(fin>>s1)
		{
			fin>>s2;
		//	fin>>v;
			so1 = s1+'o';
			si2 = s2+'i';
			tcm->insert(((const unsigned char*)s1.c_str()), ((const unsigned char*)s2.c_str()),1,s1.length());
		//	tcm->insert(((const unsigned char*)s2.c_str()), ((const unsigned char*)s1.c_str()),1,s1.length());
		//	msg->insert((const unsigned char*)(s1.c_str()), (const unsigned char*)(s2.c_str()),1,s1.length());
		//	rcm->insert(so1,si2,1,so1.length());
			//gbf->insert(s1,s2);
			uns->insert(s1,s2);
		//	rcm->insert(s2,s1,v,s1.length());
		//	n++;
		}
		cout<<" Insertion done"<<endl;
		cout<<uns->n<<endl;
		int sum = 0;
		for(int i=0;i<uns->n;i++)
		{
			linknode* l = uns->buffer[i];
			while(l!=NULL)
			{
				sum++;
				l=l->next;
			}
		 }
		 cout<<sum<<endl;  
	//	int n1=0;
	//	int n2=0;
		float n1 = 0;
		float n2 = 0;
		float n3 = 0;
		n=0;
		//int s =gr->node.size();
		//for(int i=0;i<200000;i++)
	//	for(int i=0;i<6;i++)
	//	{	for(int j=0;j<1;j++) 
	//			cout<<msg->noise_v[i][j]<<endl;
	//	}
	/*	int cnt=0; 
		for(int i=0;i<w;i++)
		{
			if(rcm->filled[0][i]>0)
			{//cout<<rcm->filled[0][i]<<endl;
				cnt++;
			}
		}
	//	cout<<cnt<<endl;*/
	/*	while(fcheck>>v)
		{
			//fsrc>>v;
			n++;
			//int l1,l2;
			while(true)
			{
				l1=rand()%s;
				l2=rand()%s;
				if(l1==l2)continue;
			}
			s1=gr->node[l1];
			s2=gr->node[l2];
			l =rand()%4+1;
			v = gr->query(s1,s2,l);*/ 
			//fcheck>>s1>>s2;
		/*	fcheck>>s1>>s2;
			//ftrans>>s2;
		//	so1 = s1+'o';
		//	si2 = s2+'i';
			int v1=0;
			int v2=0;
		//bool v1,v2,v3;
		 	v1 = tcm->query((const unsigned char*)(s1.c_str()), (const unsigned char*)(s2.c_str()),s1.length());
		 //	v2 = rcm->query(s1,s2,s1.length());
			v2 = msg->edgequery((const unsigned char*)(s1.c_str()), (const unsigned char*)(s2.c_str()),s1.length());
		//	v1 = tcm->nodequery((const unsigned char*)(s1.c_str()), s1.length(), 0);
		//	v2 = msg->nodequery((const unsigned char*)(s1.c_str()), s1.length(), 0);
		//	if(n<20)
		//	cout<<v<<' '<<v1<<' '<<v2<<endl;
		//	if(v1==v)	n1++;
		//	if(v2==v)	n2++;
			n1+=float(v1-v)/v;
			n2+=float(v2-v)/v;
		//v1 = tcm->transquery((const unsigned char*)(s1.c_str()), (const unsigned char*)(s2.c_str()),s1.length());
		//v2 = msg->transquery((const unsigned char*)(s1.c_str()), (const unsigned char*)(s2.c_str()),s1.length(),20000);
	//	v3 = rcm->transquery(so1,si2,so1.length());	
		//if(!v1)
		//	n1++;
		//cout<<v1<<endl;
		if(!v2)
			n2++;
		if(!v3)
			n3++;*/
	/*	}
		fout1<<w<<' '<<float(n1)/n<<' '<<float(n2)/n<<endl;
		n=0;
		n1=0;
		n2=0;
		while(fsrc>>s1)
		{
			fsrc>>v;
			int v1,v2;
			n++;
			v1 = tcm->nodequery((const unsigned char*)(s1.c_str()), s1.length(), 0);
			v2 = msg->nodequery((const unsigned char*)(s1.c_str()), s1.length(), 0); 
			n1+=float(v1-v)/v;
			n2+=float(v2-v)/v;
		}
		fout2<<w<<' '<<float(n1)/n<<' '<<float(n2)/n<<endl;*/
	//	ftrans>>v;
	//	ftrans>>v;
		n=0;
		n1=0;
		n2=0;
		clock_t start, finish;
		string str1[1500];
		string str2[1500];
		while(ftrans>>str1[n])
		{
			ftrans>>str2[n];
			n++;
			if(n>100)
				break;
		}	
			//so1=s1+'o';
			//si2=s2+'i';
			bool v1,v2,v3;
			//v1 = tcm->transquery((const unsigned char*)(s1.c_str()), (const unsigned char*)(s2.c_str()),s1.length());
			//v2 = msg->transquery((const unsigned char*)(s1.c_str()), (const unsigned char*)(s2.c_str()),s1.length(),10000000);
		//	v3 = rcm->transquery(so1, si2, so1.length());
		start=clock();
		for(int i=0;i<n;i++)
		{
			v1 = tcm->transquery((const unsigned char*)(str1[i].c_str()), (const unsigned char*)(str2[i].c_str()),s1.length());
			v3 = uns->query(str1[i],str2[i]);
			   if(!v1)
				n1++;
		/*	if(!v2)
				n2++;*/
			if(!v3)
				n3++;
		}
		finish = clock();
		double d3= double(finish-start)/CLOCKS_PER_SEC;
		cout<<2*w<<' '<<float(n1)/n<<' '<<float(n2)/n<<' '<<n3/n<<' '<<d3<<endl;
		//fout<<float(n1)/n<<endl;
		fin.close();
		ftrans.close();
		fsrc.close();
		fdest.close();
		fcheck.close();
	//	delete uns;
		delete tcm;
	} 
	return 0;
}
