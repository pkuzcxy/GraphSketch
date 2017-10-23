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
#include"Graph.h" 
using namespace std;
int main()
{
	ofstream fout1("ws_edge-res.txt",ios::app);
	ofstream fout2("ws_node-res.txt",ios::app);
	ofstream fout3("ws_trans_accuracy-res.txt",ios::app);
	for(int w=800;w<1000;w+=100)
	{ 
		ifstream fin("ws2.txt");
		ifstream fcheck("ws2check.txt");
		ifstream fsrc("ws2srcnode.txt");
		ifstream ftrans("transquery-ws.txt");
		int uns_w = w;
		TCM *tcm = new TCM(0.9  * uns_w, 0.9 * uns_w, 4);
		UNS *uns = new UNS(uns_w,16,8,1,4,12);
		graph *g = new graph();
		string s1, s2;
		int v;
		int n=0;
		while(fin>>s1)
		{
			fin>>s2;
			int weight;
			fin >> weight;
			tcm->insert(((const unsigned char*)s1.c_str()), ((const unsigned char*)s2.c_str()),weight,s1.length(),s2.length());
			uns->insert(s1, s2, weight);
			g->insert(s1, s2, 0, weight);
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

		 
		double n1 = 0;
		double n2 = 0;
		double n3 = 0;
		double n4 = 0;

		double d3 = 0;//测时间
		double d4 = 0;
		int g_res = 0;
		int tcm_res = 0;
		int uns_res = 0;
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
		clock_t start, finish;
		string str1[10000];
		string str2[10000];

		//edge_querry
		while(fcheck>>str1[n])
		{
			fcheck>>str2[n];
			int weight;
			fcheck >> weight;
			n++;
			if(n==5000)
				break;
		}
		start=clock();
		for(int i=0;i<n;i++)
		{
			g_res = g->query(str1[i], str2[i], 0);
			uns_res = uns->edgequery(str1[i], str2[i]);
			n1 += double(uns_res) / g_res - 1;
			n2 += uns_res - g_res;
		}
		finish = clock();
		d3= double(finish-start)/CLOCKS_PER_SEC;

		start = clock();
		for (int i = 0; i<n; i++)
		{
			g_res = g->query(str1[i], str2[i], 0);
			tcm_res = tcm->query((const unsigned char*)(str1[i].c_str()), (const unsigned char*)(str2[i].c_str()), str1[i].length(),str2[i].length());
			n3 += double(tcm_res) / g_res - 1;
			n4 += tcm_res - g_res;
		}
		finish = clock();
		d4 = double(finish - start) / CLOCKS_PER_SEC;

		fout1<<uns_w<<" "<<n1/n<<' '<<n3/n<<"  "<<n2/n<<' '<<n4/n<<"  "<<d3<<" "<<d4<<endl;

		n = 0;
		while (fsrc >> str1[n])
		{
			n++;
			if (n == 5000)
				break;
		}

		//nodevalue_query

		n1 = n2 = n3 = n4 = 0;
		g_res = tcm_res = uns_res = 0;

		start = clock();
		for (int i = 0; i<n; i++)
		{
			g_res = g->nodequery(str1[i],0);
			uns_res = uns->nodevaluequery(str1[i],0);
			n1 += double(uns_res) / g_res - 1;
			n2 += uns_res - g_res;
		}
		finish = clock();
		d3 = double(finish - start) / CLOCKS_PER_SEC;

		start = clock();
		for (int i = 0; i<n; i++)
		{
			g_res = g->nodequery(str1[i],0);
			tcm_res = tcm->nodequery((const unsigned char*)(str1[i].c_str()),str1[i].length(),0);
			n3 += double(tcm_res) / g_res - 1;
			n4 += tcm_res - g_res;
		}
		finish = clock();
		d4 = double(finish - start) / CLOCKS_PER_SEC;
		fout2 << uns_w << " " << n1 / n << ' ' << n3 / n << "  " << n2 / n << ' ' << n4 / n << "  " << d3 << " " << d4 << endl;
		

		//nodedegree_query
		fout2 << "degree_query" << endl;
		n1 = n2 = n3 = n4 = 0;
		g_res = tcm_res = uns_res = 0;
		start = clock();
		for (int i = 0; i<n; i++)
		{
			g_res = g->degree[str1[i]];
			uns_res = uns->nodedegreequery(str1[i]);
			if (g_res != 0)
			{
				n1 += double(uns_res) / g_res - 1;
				n2 += uns_res - g_res;
			}
		}
		finish = clock();
		d3 = double(finish - start) / CLOCKS_PER_SEC;

		start = clock();
		for (int i = 0; i<n; i++)
		{
			g_res = g->degree[str1[i]];
			tcm_res = tcm->nodedegreequery((const unsigned char*)(str1[i].c_str()), str1[i].length(), 0);
			if (g_res != 0)
			{
				n3 += double(tcm_res) / g_res - 1;
				n4 += tcm_res - g_res;
			}
		}
		finish = clock();

		d4 = double(finish - start) / CLOCKS_PER_SEC;
		fout2 << uns_w << " " << n1 / n << ' ' << n3 / n << "  " << n2 / n << ' ' << n4 / n << "  " << d3 << " " << d4 << endl;

		//trans_querry

		n1 = n2 = n3 = n4 = 0;
		g_res = tcm_res = uns_res = 0;

		n = 0;
		while (ftrans >> str1[n])
		{   
			ftrans >> str2[n];
			n++;
			if (n == 1000)
				break;
		}


		start = clock();
		for (int i = 0; i<n; i++)
		{
			uns_res = uns->query(str1[i], str2[i]);
			if (uns_res) n1++;//代表误报
		}
		finish = clock();
		d3 = double(finish - start) / CLOCKS_PER_SEC;

		start = clock();
		for (int i = 0; i<n; i++)
		{
			tcm_res = tcm->transquery((const unsigned char*)(str1[i].c_str()), (const unsigned char*)(str2[i].c_str()), str1[i].length(), str2[i].length());
			if (tcm_res)n3++;//代表误报
		}
		finish = clock();

		d4 = double(finish - start) / CLOCKS_PER_SEC;
		fout3 << uns_w << " " << n1<< ' ' << n3<<"  " << d3 <<' '<< d4 << endl;
		fin.close();
		fsrc.close();
		fcheck.close();
		ftrans.close();
	} 
	return 0;
}
