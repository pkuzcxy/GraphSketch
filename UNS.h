#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
#include<stdlib.h>
using namespace std;
#define prime 739
#define bigger_p 6781
#define timer 7
#define M 80000
#define hashindex 3
struct basket
{
	short source;
	short dest;
	short shift1;
	short shift2;
	short v;
};
struct mapnode
{
	short h;
	short g;
};
struct linknode
{
	unsigned int key;
	short v;
	linknode* next;
};
struct NodeQueryResult
{
	int weight;
	int degree;
};
class UNS
{
	private:
		int w;
		int r;
		int p;
		int k;
		int s;
		int f;
	//	short* BF1;
		short* BF2;
		basket** value;
	public:
		vector<linknode*> buffer;
		map<int, short> index;
		int n;
		UNS(int width, int range, int p_num, int k_num, int size,int f_num);
		~UNS()
		{
			//delete []BF1;
			delete []BF2;
			for(int i=0;i<w*w;i++)
			{
				delete value[i];
				//delete value[i];
				//delete value[i];
			}
			delete []value;
		 }
		 void insert(string s1, string s2,int v);
		 bool query(string s1, string s2); 	
		 int edgequery(string s1,string s2);	
		 int nodedegreequery(string s1);
		 int nodevaluequery(string s1);
};

UNS::UNS(int width, int range, int p_num, int k_num, int size,int f_num)
{
	w = width;
	r = range;
	p = p_num;
	k = k_num;
	s = size;
	f = f_num;
	n = 0;
//	BF1 = new short[M];
//	BF2 = new short[M];
/*	for(int i=0;i<M;i++)
	{
		//BF1[i] = 0;
		BF2[i] = 0;
	}*/
	value = new basket*[w*w];
	for(int i=0;i<w*w;i++)
	{
		value[i]=new basket;
		value[i]->source = 0;
		value[i]->dest = 0;
		value[i]->shift1 = 0;
		value[i]->shift2 = 0;
		value[i]->v=0;
		/*for(int j=0;j<s;j++)
		{
			value[i]->source[j]=0;
			value[i]->dest[j]=0;
			value[i]->shift[j]=0;
		 } */ 
	}
}
void UNS::insert(string s1, string s2,int v)
{		
		unsigned int hash1 = (*hfunc[hashindex])((unsigned char*)(s1.c_str()), s1.length());
		unsigned int hash2 = (*hfunc[hashindex])((unsigned char*)(s2.c_str()), s2.length());
		int tmp = pow(2,f)-1;
		int g1 = hash1 & tmp;
		if(g1==0) g1+=1;
		int h1 = (hash1>>f)%w;
		int g2 = hash2 & tmp;
		if(g2==0) g2+=1;
		int h2 = (hash2>>f)%w;
	/*	bool find = true;
		unsigned int k1 = (h1<<f)+g1;
		unsigned int k2 = (h2<<f)+g2;
		char c1[8];
		for(int j=0;j<4;j++)
		{
			c1[j]=char(((k1>>(8*j))%256));
		}
		for(int j=4;j<8;j++)
		{
			c1[j]=char(((k2>>(8*(j-4)))%256));
		}
		for(int j=0;j<4;j++)
		{
			unsigned int hash = ((*hfunc[j])((const unsigned char*)c1, 8))%(M*16);
			int v1 = hash/16;
			int v2 = hash%16;
			if((BF1[v1]&(1<<(15-v2)))==0)
			{
			find = false; 
			BF1[v1] = BF1[v1]|(1<<(15-v2));
			} 
		}
		if(find)
			return;*/ 
		int* tmp1 = new int[r];
		int* tmp2 = new int[r];
		tmp1[0] = g1;
		tmp2[0] = g2;
		for(int i=1;i<r;i++)
		{
			tmp1[i]=(tmp1[i-1]*timer+prime)%bigger_p;
			tmp2[i]=(tmp2[i-1]*timer+prime)%bigger_p;
		}
		bool inserted=false;
		int key = (g1<<f)+g2; 
		for(int i=0;i<p;i++)
		{
			key = (key*3+prime)%bigger_p;
			int index = key%(r*r);
			int index1 =index/r;
			int index2 = index%r; 
			int p1 = (h1+tmp1[index1])%w;
			int p2 = (h2+tmp2[index2])%w;
			int pos = p1*w+p2;
			for(int j=0;j<s;j++)
			{
				pos = (pos+j)%(w*w);
				if((value[pos]->source==g1)&&(value[pos]->dest==g2)&&(value[pos]->shift2==index2)&&(value[pos]->shift1==index1))
				{
					value[pos]->v+=v;
					return;
				}
				if(value[pos]->source==0&&value[pos]->dest==0)
				{
					value[pos]->source=g1;
					value[pos]->dest=g2;
					value[pos]->shift2=index2;
					value[pos]->shift1=index1;
					value[pos]->v=v;
					inserted = true;
					break;
				}
			}
			if(inserted)
				break;
		} 
			if(!inserted)
			{
			unsigned int k1 = (h1<<f)+g1;
			unsigned int k2 = (h2<<f)+g2;
			/*char c1[4];
			for(int j=0;j<4;j++)
			{
				c1[j]=char(((k1>>(8*j))%256));
			}
			for(int j=0;j<4;j++)
			{
				unsigned int hash = ((*hfunc[j])((const unsigned char*)c1, 4))%(M*16);
				int v1 = hash/16;
				int v2 = hash%16;
				BF2[v1] = BF2[v1]|(1<<(15-v2));
			}*/
			map<int, short>::iterator it = index.find(k1);
			if(it!=index.end())
			{
				int tag = it->second;
				linknode* node = buffer[tag];
				while(true)
				{
					if(node->key==k2)
					{
						node->v+=v;
						break;
					}
					if(node->next==NULL)
					{
						linknode* ins = new linknode;
						ins->key = k2;
						ins->next = NULL;
						node->next = ins;
						ins->v=v;
						break;
					}
					node = node->next;
				}
			}
			else
			{
				index[k1] = n;
				n++;
				linknode* node = new linknode;
				node->key = k1;
				linknode* ins = new linknode;
				ins->key = k2;
				ins->v=0;
				ins->next = NULL;
				ins->v=v;
				node->next = ins;
				buffer.push_back(node); 
			}	
			}
	return;
}

bool UNS::query(string s1, string s2)
{
		unsigned int hash1 = (*hfunc[hashindex])((unsigned char*)(s1.c_str()), s1.length());
		unsigned int hash2 = (*hfunc[hashindex])((unsigned char*)(s2.c_str()), s2.length());
		int tmp = pow(2,f)-1;
		int g1 = hash1 & tmp;
		if(g1==0) g1+=1;
		int h1 = (hash1>>f)%w;
		int g2 = hash2 & tmp;
		if(g2==0) g2+=1;
		int h2 = (hash2>>f)%w;
		int pos;
		bool** checked = new bool*[w];
		int lf = pow(2,f);
		for(int it=0;it<w;it++)
		{
			checked[it] = new bool[lf];
			for(int j=0;j<lf;j++)
				checked[it][j] = false;
		 }
		queue<mapnode> q;
		mapnode e;
		e.h = h1;
		e.g = g1;
		q.push(e);
		checked[h1][g1]=true;
	//	int sq1;
	//	int sq2;
	//	int pos1, pos2;
		while(!q.empty())
		{
			e = q.front();
			h1 = e.h;
			g1 = e.g;
			int* tmp1 = new int[r];
			int* tmp2 = new int[r];
			tmp2[0]=g2;
			tmp1[0]=g1;
			for(int i=1;i<r;i++)
			{
				tmp1[i] = (tmp1[i-1]*timer+prime)%bigger_p;
				tmp2[i] = (tmp2[i-1]*timer+prime)%bigger_p;
			}
			for(int i1=0;i1<r;i1++)
			{
				int p1 = (h1+tmp1[i1])%w;
				for(int i2=0;i2<r;i2++)
				{
					int p2 = (h2+tmp2[i2])%w;
					int pos = p1*w+p2;
					for(int i3=0;i3<s;i3++)
					{
						pos = (pos+i3)%(w*w);
						if((value[pos]->source==g1)&&(value[pos]->dest==g2))
						{
							if((value[pos]->shift2==i2)&&(value[pos]->shift1==i1))
								return true;
						}
					} 
				}
			}
			unsigned int k1 = (h1<<f)+g1;
			/*char c1[4];
			for(int j=0;j<4;j++)
			{
				c1[j]=char(((k1>>(8*j))%256));
			}*/
			bool find = true;
		/*	for(int i=0;i<4;i++)
			{
				int hash = ((*hfunc[i])((const unsigned char*)c1, 4))%(M*16);
				int hash1 = hash/16;
				int hash2 = hash%16;
				if((BF2[hash1]&(1<<(15-hash2)))==0)
				{
					find=false;
					break;
				}
			}*/
			if(find)
			{
				map<int, short>::iterator it = index.find(k1);
				if(it!=index.end())
				{
					int tag = it->second;
					linknode* node = buffer[tag];
					while(node!=NULL)
					{
						if(node->key!=k1)
						{
							int temp_h = (node->key)>>f;
							int tmp = pow(2,f);
							int temp_g = ((node->key)%tmp);
							if((temp_h==h2)&&(temp_g==g2))
								return true;
						//	cout<<node->key<<endl;
							if(!checked[temp_h][temp_g])
						{
							mapnode temp_e;
							temp_e.h = temp_h;
							temp_e.g = temp_g;
							q.push(temp_e);
							checked[temp_h][temp_g] = true;
						}
						}
						node=node->next;	
					}	
				}
			}
			for(int i1=0;i1<r;i1++)
			{
				int p1 = (h1+tmp1[i1])%w;
				for(int i2=0;i2<w;i2++)
				{
					int pos = p1*w+i2;
						if(value[pos]->source==g1&&value[pos]->shift1==i1)
						{
							int tmp_g = value[pos]->dest;
							int tmp_s = value[pos]->shift2;
							int shifter = tmp_g;
							for(int v=0;v<tmp_s;v++)
								shifter = (shifter*timer+prime)%bigger_p;
							int tmp_h = i2;
							while(tmp_h<shifter)
								tmp_h+=w;
							tmp_h-=shifter;
							if(!checked[tmp_h][tmp_g])
							{
								mapnode tmp_e;
								tmp_e.h = tmp_h;
								tmp_e.g = tmp_g;
								q.push(tmp_e);
								checked[tmp_h][tmp_g] = true; 
							 } 
						}
				}
			}
			q.pop();
		}
		return false;
 }
 int UNS::edgequery(string s1, string s2)
 {
 		unsigned int hash1 = (*hfunc[hashindex])((unsigned char*)(s1.c_str()), s1.length());
		unsigned int hash2 = (*hfunc[hashindex])((unsigned char*)(s2.c_str()), s2.length());
		int tmp = pow(2,f)-1;
		int g1 = hash1 & tmp;
		if(g1==0) g1+=1;
		int h1 = (hash1>>f)%w;
		int g2 = hash2 & tmp;
		if(g2==0) g2+=1;
		int h2 = (hash2>>f)%w;
		int pos;
		int* tmp1 = new int[r];
		int* tmp2 = new int[r];
		tmp1[0] = g1;
		tmp2[0] = g2;
		for(int i=1;i<r;i++)
		{
			tmp1[i]=(tmp1[i-1]*timer+prime)%bigger_p;
			tmp2[i]=(tmp2[i-1]*timer+prime)%bigger_p;
		}
		int key = (g1<<f)+g2; 
		for(int i=0;i<p;i++)
		{
			key = (key*3+prime)%bigger_p;
			int index = key%(r*r);
			int index1 =index/r;
			int index2 = index%r; 
			int p1 = (h1+tmp1[index1])%w;
			int p2 = (h2+tmp2[index2])%w;
			int pos = p1*w+p2;
			for(int j=0;j<s;j++)
			{
				pos = (pos+j)%(w*w);
				if((value[pos]->source==g1)&&(value[pos]->dest==g2)&&(value[pos]->shift2==index2)&&(value[pos]->shift1==index1))
				{
					return value[pos]->v;
				}
			}
		}
			unsigned int k1 = (h1<<f)+g1;
			unsigned int k2 = (h2<<f)+g2;
			/*char c1[4];
			for(int j=0;j<4;j++)
			{
				c1[j]=char(((k1>>(8*j))%256));
			}
			for(int j=0;j<4;j++)
			{
				unsigned int hash = ((*hfunc[j])((const unsigned char*)c1, 4))%(M*16);
				int v1 = hash/16;
				int v2 = hash%16;
				BF2[v1] = BF2[v1]|(1<<(15-v2));
			}*/
			map<int, short>::iterator it = index.find(k1);
			if(it!=index.end())
			{
				int tag = it->second;
				linknode* node = buffer[tag];
				while(true)
				{
					if(node->key==k2)
						return node->v;
					node=node->next;
				}
			}
	return 0;
  } 

int  UNS::nodedegreequery(string s1)
 {
	 unsigned int hash1 = (*hfunc[hashindex])((unsigned char*)(s1.c_str()), s1.length());
	 int tmp = pow(2, f) - 1;

	 int g1 = hash1 & tmp;
	 if (g1 == 0) g1 += 1;
	 int h1 = (hash1 >> f) % w;

	 int pos;
	 int* tmp1 = new int[r];
	 tmp1[0] = g1;
	 for (int i = 1; i < r; i++)
	 {
		 tmp1[i] = (tmp1[i - 1] * timer + prime) % bigger_p;
	 }
	 int d = 0;
	 for (int i = 0; i < r; ++i)
	 {
		 int p1 = (h1 + tmp1[i]) % w;
		 for (int j = 0; j < w; ++j)
		 {
			 int pos = p1*w + j;
			 if ((value[pos]->source == g1) && (value[pos]->shift1 == i)) ++d;
		 }
	 }

	 unsigned int k1 = (h1 << f) + g1;
	 map<int, short>::iterator it = index.find(k1);
	 if (it != index.end())
	 {
		 int tag = it->second;
		 linknode* node = buffer[tag];
		 while (node->next != NULL)
		 {
			 node = node->next;
			 ++d;
		 }
		 ++d;
	 }
	 return d;
}

int  UNS::nodevaluequery(string s1)
{
	unsigned int hash1 = (*hfunc[hashindex])((unsigned char*)(s1.c_str()), s1.length());
	int tmp = pow(2, f) - 1;

	int g1 = hash1 & tmp;
	if (g1 == 0) g1 += 1;
	int h1 = (hash1 >> f) % w;

	int pos;
	int* tmp1 = new int[r];
	tmp1[0] = g1;
	for (int i = 1; i < r; i++)
	{
		tmp1[i] = (tmp1[i - 1] * timer + prime) % bigger_p;
	}
	int d = 0;
	for (int i = 0; i < r; ++i)
	{
		int p1 = (h1 + tmp1[i]) % w;
		for (int j = 0; j < w; ++j)
		{
			int pos = p1*w + j;
			if ((value[pos]->source == g1) && (value[pos]->shift1 == i)) 
				d += value[pos]->v;
		}
	}
	unsigned int k1 = (h1 << f) + g1;
	map<int, short>::iterator it = index.find(k1);
	if (it != index.end())
	{
		int tag = it->second;
		linknode* node = buffer[tag];
		while (node->next != NULL)
		{
			d += node->v;
			node = node->next;
		}
		d += node->v;
	}
	return d;
}