#include<string>
#include<fstream>

using namespace std;

void infile(string &a,string &b){   
	ifstream infile;
	infile.open("multy.in.txt");
    infile>>a;
	infile>>b;
}

void main(){
	string a,b;
	infile(a,b);
	int t,k,i,j;
	bool iszero=0,isallzero1=1,isallzero2=1;
	infile(a,b);
	ofstream outfile;
	outfile.open("multy.out.txt");
	int d=0;
	for(d=0 ;d< a.size();d++){
		if (a[d]<'0' || a[d]>'9') {
			outfile<<"您输入的数据不合法!"<<endl;
			exit(0);
		}
	}
	for(d=0 ;d< b.size();d++){
		if (b[d]<'0' || b[d]>'9'){
			outfile<<"您输入的数据不合法"<<endl;
			exit(0);
		}
	} 			
	int len1=a.length();
	int len2=b.length();
	int templen;
	if(len1>=len2){
		templen=2*len1+1;
	}else{
		templen=2*len2+1;
	}
	int *p,*q,*r;
	p=new int[len1+1];
	q=new int[len2+1];
	r=new int[templen+1];
	memset(r,0,(templen+2)*sizeof(int));
	for(i=0;i<len1;i++)
		p[i]=a[len1-1-i]-48;
	for(j=0;j<len2;j++)
		q[j]=b[len2-1-j]-48;
	for(j=0;j<len2;j++){
		for( i=0;i<len1;i++){
			 t=p[i]*q[j]%10;
			 k=p[i]*q[j]/10;
			 r[i+j]+=t;
			 r[i+j+1]+=k;
			 if(r[i+j]>9){
				r[i+j+1]+=r[i+j]/10;
				r[i+j]=r[i+j]%10;
			}
		}
	}
	for( i=0;i<len1;i++){
		if(p[i]!=0){
			isallzero1=0;
			break;
		}
	}
	for(i=0;i<len2;i++){
		if(q[i]!=0){
			isallzero2=0;
		break;
		}
	}
	outfile<<a<<"*"<<b<<"=";
	for(i=templen;i>=0;i--){
		if(isallzero1==1||isallzero2==1){
			outfile<<'0';
			break;
		}
		if(iszero)
			outfile<<r[i];
		else if(r[i]!=0&&!iszero){
			outfile<<r[i];
			iszero=1;
		}
	}

}