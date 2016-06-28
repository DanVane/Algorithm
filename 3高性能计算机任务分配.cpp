#include<fstream>
#define MAXSIZE  (1<<(sizeof(int)*8-1))-1
#define A 5
#define B 5
#define P 3
using namespace std;

int p0[P][A+1][B+1];
int p1[P][A+1][B+1];
int f[P][A+1][B+1];
int c[P][A+1][B+1];

int na;
int nb;
int p;

void infile( int ta[],int tb[],int ka[],int kb[]){
	ifstream infile;
	infile.open("hpc.in");
	infile>>na>>nb>>p;
	for(int i=0;i<P;i++)
		infile>>ta[i]>>tb[i]>>ka[i]>>kb[i];
}

void outfile(int time){	
	 ofstream outfile;
     outfile.open("hpc.out.txt");
	 outfile<<time;
}

void assignment1(int ta[],int tb[],int ka[],int kb[]){
	for(int x=0;x<P;x++)
		for(int y=0;y<=A;y++ )
			for(int z=0;z<=B;z++){
				if(y==0&&z==0)
					p0[x][y][z]=p1[x][y][z]=0;
				 if(y==0&&z!=0){
					p0[x][y][z]=MAXSIZE;
					p1[x][y][z]=tb[x]+kb[x]*z*z;
				}
				if(y!=0&&z==0){
					p0[x][y][z]=ta[x]+ka[x]*y*y;
					p1[x][y][z]=MAXSIZE;
				}
			   if(y!=0&&z!=0){
				   int min0=MAXSIZE;
				   for(int w=1;w<=y;w++){	
					   if(min0>p1[x][y-w][z]+ta[x]+ka[x]*w*w)
							min0=p1[x][y-w][z]+ta[x]+ka[x]*w*w;
					}
				    p0[x][y][z]=min0;
					int min1=MAXSIZE;
					for( w=1;w<=z;w++){	
						if(min1>p0[x][y][z-w]+tb[x]+kb[x]*w*w)
							min1=p0[x][y][z-w]+tb[x]+kb[x]*w*w;
					}
				     p1[x][y][z]=min1;
				}
				f[x][y][z]=p0[x][y][z];
				if(p0[x][y][z]>p1[x][y][z])
					f[x][y][z]=p1[x][y][z];
			}
}
int assignment2(){
	for(int i=0;i<P;i++)
		for(int j=0;j<=A;j++ )
			for(int k=0;k<=B;k++){
				if(i==0)
					 c[i][j][k]=f[i][j][k];
				 else{
					 int min2=MAXSIZE;
			   	     for(int w1=0;w1<=j;w1++)
						 for(int w2=0;w2<=k;w2++){  
							if((w1!=0||w2!=0)&&(w1!=j||w2!=k)){
								int max=0;
								if(f[i][w1][w2]>max)
									max=f[i][w1][w2];
								if(	c[i-1][j-w1][k-w2]>max)
								    max=c[i-1][j-w1][k-w2];
						       if(max<min2)
								   min2=max;
							}
						 }
						 c[i][j][k]=min2;
				 }
			}
   return c[P-1][A][B];
}

void main(){
	int n;
	int ta[P];int tb[P];int ka[P];int kb[P];
	infile(ta,tb,ka,kb);
	assignment1(ta,tb,ka,kb);
	n=assignment2();
	outfile(n);
}
