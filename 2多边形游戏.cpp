#include<math.h>
#include<fstream.h>
#include<stdlib.h>
#define N 4

int v[N+1];
char op[N+1];

int fmax[N+1][N+1];
int fmin[N+1][N+1];

void infile(){   
	int n;
	ifstream infile;
	infile.open("POLYGON.IN");
    infile>>n;
	if(n!=4){
		cout<<"请确定输入4条边"<<'\n';
		exit(0);
	}
	for(int i=1;i<=N;i++){ 
	  infile>>op[i]>>v[i%N+1];
	} 
}

void outfile(int fmax[][N+1]){
	int max;
	ofstream outfile;
	outfile.open("POLYGON.out.txt");
	max=fmax[1][N-1];
	for(int i=1;i<=N;i++){
		if(fmax[i][N-1]>max)
		max=fmax[i][N-1];
	}
	outfile<<max<<endl;
	for( i=1;i<=N;i++){
		if(fmax[i][N-1]==max)
		outfile<<i-1<<" ";
	}
}

void polygon(){
	int min=0;
    int max=0;
	for(int i=1;i<=N;i++)
		fmin[i][0]=fmax[i][0]=v[i];
	for(int j=0;j<=N;j++)
		for(i=1;i<=N;i++){
			for(int t=0;t<=j-1;t++){
				if(op[(i+t-1)%N+1]=='+'){
					fmin[i][j]=fmin[i][t]+fmin[(i+t)%N+1][j-t-1];
					fmax[i][j]=fmax[i][t]+fmax[(i+t)%N+1][j-t-1];
				}
			    if(op[(i+t-1)%N+1]=='*'){
				   	 min=fmin[i][t]*fmin[(i+t)%N+1][j-t-1];
					 if(fmin[i][t]*fmax[(i+t)%N+1][j-t-1]<min)
						 min=fmin[i][t]*fmax[(i+t)%N+1][j-t-1];
					 if(fmax[i][t]*fmin[(i+t)%N+1][j-t-1]<min)
						 min=fmax[i][t]*fmin[(i+t)%N+1][j-t-1];
					 if(fmax[i][t]*fmax[(i+t)%N+1][j-t-1]<min)
						min=fmax[i][t]*fmax[(i+t)%N+1][j-t-1];
					 if(fmin[i][j]==0)
						 fmin[i][j]=min;
					 if(min<fmin[i][j]&&fmin[i][j]!=0)
				    	fmin[i][j]=min;
					 max=fmin[i][t]*fmin[(i+t)%N+1][j-t-1];
					 if(fmin[i][t]*fmax[(i+t)%N+1][j-t-1]>max)
						max=fmin[i][t]*fmax[(i+t)%N+1][j-t-1];
				     if(fmax[i][t]*fmin[(i+t)%N+1][j-t-1]>max)
                        max=fmax[i][t]*fmin[(i+t)%N+1][j-t-1];
					 if(fmax[i][t]*fmax[(i+t)%N+1][j-t-1]>max)
						max=fmax[i][t]*fmax[(i+t)%N+1][j-t-1];
					 if(max>fmax[i][j])
						fmax[i][j]=max;
				}
			}
		}
}

void main(){
	infile();
	polygon();
	outfile(fmax);
}