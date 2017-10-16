#include"hashfunction.h"
#include<math.h>
#include<string>
#include<iostream>
#include<memory.h>
#include<queue>
using namespace std;
unsigned int (*hfunc[14])(const unsigned char*, unsigned int)=
{
    BOB1,
    PJW,
    DJB,
    CRC32,
    OCaml,
    SML,
    STL,
    FNV32,
    BOB2,
    BOB3,
    BOB4,
    Hsieh,
    RSHash	
};

class TCM
{
private:
    int width;
    int depth;
    int hashnum;
    short **value;
public:
    TCM(int w,int d,int h);
    ~TCM()
    {
        for (int i=0; i<hashnum; ++i)
        {
                delete [] value[i];
        }
        delete [] value;
    }
    void saveOperation(int target_d,int target_w,int hashnum, int weight);
    void insert(const unsigned char* v1,const unsigned char* v2,int weight,int len);
    int query(const unsigned char* v1,const unsigned char* v2,int len);
    int nodequery(const unsigned char*v1, int len, int type);
    bool transquery(const unsigned char*v1,const unsigned char*v2, int len);
};

bool TCM::transquery(const unsigned char*v1, const unsigned char*v2, int len)
{
	for(int i=0;i<hashnum;i++)
	{
		bool found = false;
		bool* checked = new bool[width];
		for(int j=0;j<width;j++)
			checked[j] = false;
		unsigned int src=((*hfunc[2*i])(v1,len))%depth;
		unsigned int dest=((*hfunc[2*i])(v2,len))%width;
		queue<int> q;
		int v1 = src;
		int v2 = dest;
		int hash = v1*width+v2;
		if(value[i][hash]>0)
			continue;
		else
		{
			q.push(v1);
			checked[v1]=true; 
			while(!q.empty())
			{
				v1 = q.front();
				if(value[i][v1*width+dest]>0)
				{
				//	cout<<"found"<<endl;
					found = true;
					break;
				}
				for(int j=0;j<width;j++)
				{
					hash = v1*width+j;
					if(value[i][hash]>0&&checked[j]==false)
					{
						q.push(j);
				//		cout<<"in!";
						checked[j]=true;
					}
				}
				q.pop();
			}
			if(!found)
				return false;
		}
	}
	return true;
}
TCM::TCM(int w,int d,int h)
{
    width = w;
    depth = d;
    hashnum = h;
    value = new short*[hashnum];
    for (int i=0; i<hashnum; ++i)
    {
        value[i] = new short[width*depth];
        memset(value[i],0,sizeof(short)*width*depth);
    }      
}

void TCM::saveOperation(int target_d,int target_w,int hashnum,int weight)
{
    value[hashnum][target_d*width+target_w] += weight;
}

void TCM::insert(const unsigned char* v1,const unsigned char* v2,int weight,int len)
{
	for(int i=0;i<hashnum;i++)
{
    unsigned int hash1 = ((*hfunc[2*i])(v1,len))%depth;
    unsigned int hash2 = ((*hfunc[2*i])(v2,len))%width;
    saveOperation(hash1,hash2,i,weight);
}
}

int TCM::query(const unsigned char* v1,const unsigned char* v2,int len)
{
    int min=65536;
    for(int i=0;i<hashnum;i++)
    {
    	unsigned int hash1 = ((*hfunc[2*i])(v1,len))%depth;
    	unsigned int hash2 = ((*hfunc[2*i])(v2,len))%width;
    	int v = value[i][hash1*width+hash2];
    	if(v<min)
    	min = v;
	}
    return min;
}

/*class TCMS
{
	private:
		int width;
		int depth;
		int hashnum;
		int sr;
		short **value;
		int** source;
		int** dest; 
	public:
		TCMS(int w,int d, int h, int s);
		~TCMS()
		{
			for(int i=0;i<hashnum;i++)
				delete []value[i];
			delete []value;
		}
		void insert(const unsigned char* v1, const unsigned char* v2,int weight, int len);
		int edgequery(const unsigned char* v1, const unsigned char*v2, int len);
		int nodequery(const unsigned char* v1, int len,int type);
}
TCMS::TCMS(int w, int d, int h,int s)
{
	width=w;
	depth=d;
	hashnum=h;
	sr=s;
	value = new short*[hashnum];
	source = new int*[hashnum];
	dest = new int*[hashnum];
    for (int i=0; i<hashnum; ++i)
    {
    	source[i] = new int[depth];
    	dest[i] = new int[width];																																																																																				```````````````						
        value[i] = new short[width*depth];
        memset(value[i],0,sizeof(short)*width*depth);
        memset(dest[i],0,sizeof(int)*width);
        memset(source[i],0,sizeof(int)*depth);
}
}
void TCMS::insert(const unsigned char*v1, const unsigned char* v2, int weight, int len)
{
	for(int i=0;i<hashnum;i++)
{
    int hash1 = ((*hfunc[2*i])(v1,len))%depth;
    int hash2 = ((*hfunc[2*i])(v2,len))%width;
    int hash3 = ((*hfunc[2*i+1])(v1,len))%sr;
    int hash4 = ((*hfunc[2*i+1])(v2,len))%sr;
    int r = (hash1+hash4)%depth;
    int q = (hash2+hash3)%width
    value[i][r*depth+q]+=weight;
    source[i][hash1]+=weight;
    dest[i][hash2]+=weight;
}
}
int TCMS::edgequery(const unsigned char* v1, const unsigned char*v2, int len)
{
	int min=65536;
	for(int i=0;i<hashnum;i++)
	{
    int hash1 = ((*hfunc[2*i])(v1,len))%depth;
    int hash2 = ((*hfunc[2*i])(v2,len))%width;
    int hash3 = ((*hfunc[2*i+1])(v1,len))%sr;
    int hash4 = ((*hfunc[2*i+1])(v2,len))%sr;
    int r = (hash1+hash4)%depth;
    int q = (hash2+hash3)%width
    int tmp = value[i][r*depth+q];
    if(tmp<min)
    	min=tmp;
    if(min==0)
    	break;
	}
	return min;
}*/
int TCM::nodequery(const unsigned char* v1, int len, int type )
{
	if(type==0)
	{
		int min=65523*1024;
		for(int i=0;i<hashnum;i++)
		{
			unsigned int hash1 = ((*hfunc[2*i])(v1,len))%depth;
			hash1 = hash1*width;
			int sum=0;
			for(int j=0;j<width;j++)
			{
				sum+=value[i][hash1+j];
			}
			if(sum<min)
			min=sum;
			if(min==0)
				break;
		}
		return min;
	}
	else
	{
				int min=65536*1024;
		for(int i=0;i<hashnum;i++)
		{
			unsigned int hash1 = ((*hfunc[2*i])(v1,len))%width;
			int sum=0;
			for(int j=0;j<depth;j++)
				sum+=value[i][j*width+hash1];
			if(sum<min)
			min=sum;
			if(min==0)
				break;
		}
		return min;	
	}
 } 
