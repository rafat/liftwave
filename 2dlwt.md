## 2D LWT Classes and Functions ##

**LWT2 CLASS**

```

lwt2 (vector< T > &signal, int rows, int cols, liftscheme &lft)
lwt2 (vector< T > &signal, int rows, int cols, liftscheme &lft, int J)

```

First declaration is for one level decomposition while the second one is for J level decomposition. Signal is a one dimensional (1D) array so we also need to enter length of rows and columns along with the lifting scheme used.

Usage Examples are as following.

A.) One Level Decomposition.

```

string name="bior3.3";

	
for (int i=0; i < 88;i ++) {
	sig.push_back((double) (i+1));
}
	
int rows=11;
int cols=8;
	
liftscheme blift(name);
lwt2<double> lift2(sig,rows,cols,blift);

```

B) J Level Decomposition

```

string name="bior3.3";
int J=2;
	
for (int i=0; i < 88;i ++) {
	sig.push_back((double) (i+1));
}
	
int rows=11;
int cols=8;
	
liftscheme blift(name);
lwt2<double> lift2(sig,rows,cols,blift,J);

```

**Functions Associated With LWT2 Class**

```

void 	getCoef (vector< T > &aLL, vector< T > &aLH, vector< T > &aHL, vector< T > &aHH)
void 	getDim (vector< int > &dimvec)
int 	getLevels ()
void    getDetails(string align, int slevel, vector<T> &det_vec,vector<int> &det_len)

```

getCoef gets all the Wavelet Transform coefficients. aLL contains Low pass-Low Pass Coefficient at level J while the three other vectors contain all the Low-High (Horizontal), High-Low (Vertical) and High-High (Diagonal) coefficients respectively at all the levels.

getDim vector contains information about length of rows of all coefficients components at all levels and is used to extract rectangular picture from 1D coefficients. Rows and columns are arranged as following

```

[rows of LL at level J, cols of LL at level J, rows of LH at level J, cols of LH at level J, rows of HL at level J,
 cols of HL at level J, rows of HH at level J, cols of HH at level J, rows of LH at level J-1, cols of LH at level J-1,
 .......,...., rows of HH at level 1, cols of HH at level 1]

```

getLevels returns the number of levels.

getDetails returns specific component at any requested level. eg., "LH" at level 2 or "HH" at level 1. See the usage example below which is a continuation of B) above.

```

vector<double> A,B,C,D;
lift2.getCoef(A,B,C,D);
vector<int> lengths;
lift2.getDim(lengths);
cout << A.size() << " " << B.size() << " " << C.size() << " " << D.size() << endl;
cout << lengths.size() << endl;
for (int i=0; i < (int) A.size(); i++) {
	cout << i << " " << A[i] << endl;
}
cout << lift2.getLevels() << endl;
	
for (int i=0; i < (int) lengths.size(); i++) {
	cout << i << " " << lengths[i] << endl;
}
	
cout << lift2.getLevels() << endl;
	
int slevel = 1;
vector<double> H;
vector<int> detlenH;
	
lift2.getDetails("LH",slevel,H,detlenH);
	
cout << " Lengths of Horizontal Component at level 2 : " << detlenH[0] << " " << detlenH[1] << endl;
	
for (int i=0; i < (int) detlenH[0]; i++) {
	for (int j=0; j < (int) detlenH[1];j++) {
		cout << H[i*detlenH[1]+j] << " ";
			
	}
	cout << endl;
		
}
cout << endl;

```

## 2D ILWT Classes and Functions ##

**ILWT2 CLASS**

```

ilwt2 (vector< T > &A, vector< T > &H, vector< T > &V, vector< T > &D, vector< int > &length, liftscheme &lft)
ilwt2 (lwt2< T > &wt, liftscheme &lft)

```

First one is for one level reconstruction while the second one can be used for any level of reconstruction. Example usage which is a continuation of previous example.

```

ilwt2<double> ilift2(lift2,blift);

```

**Functions Associated With ILWT2 class**

```

void 	getSignal (vector< T > &ilwt_oup)
void 	getDim (vector< int > &sigdim)

```

getSignal returns the signal while getDim gets the dimensions of  reconstructed 2D signal.

Usage Example

```

vector<double> oup;
ilift2.getSignal(oup);
vector<int> oup_dim;
ilift2.getDim(oup_dim);

```


### **A Simple Example demonstrating the use of LWT2/ILWT2 classes** ###

```

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include "lwave.h"


using namespace std;

int main()
{
	
	string name="bior3.3";
	int J=2;
	vector<double> sig;
	
	for (int i=0; i < 88;i ++) {
		sig.push_back((double) (i+1));
	}
	
	int rows=11;
	int cols=8;
	
	cout << "INPUT : " << endl;
	for (int i=0; i < (int) rows; i++) {
		for (int j=0; j < (int) cols;j++) {
			cout << sig[i*cols+j] << " ";
			
		}
		cout << endl;
		
	}
	
	liftscheme blift(name);
	lwt2<double> lift2(sig,rows,cols,blift,J);
	
	vector<double> A,B,C,D;
	lift2.getCoef(A,B,C,D);
	vector<int> lengths;
	lift2.getDim(lengths);
	cout << "Respective Size of All 4 Output vectors (LL,LH,HL,HH) : " ;
	cout << A.size() << " " << B.size() << " " << C.size() << " " << D.size() << endl;
	cout << "Length of Dimension Vector (8 at Level 1 + 6 at Level 2) :" <<  lengths.size() << endl;
	cout << "Low Pass Component At Level 2 : " << endl;
	for (int i=0; i < (int) lengths[0]; i++) {
		for (int j=0; j < (int) lengths[1];j++) {
			cout << A[i*lengths[1]+j] << " ";
			
		}
		cout << endl;
		
	}
	cout << " Levels : " << lift2.getLevels() << endl;
	cout << " All 7 row/col pairs : " << endl;
	for (int i=0; i < (int) lengths.size()/2; i++) {
		cout << lengths[2*i] << " " << lengths[2*i+1 ] << endl;
	}
	
	
	int slevel = 1;
	vector<double> H;
	vector<int> detlenH;
	
	lift2.getDetails("LH",slevel,H,detlenH);
	
	cout << " Lengths of Horizontal Component at level 1 : " << detlenH[0] << " " << detlenH[1] << endl;
	cout << " Horizontal Component at level 1 : " << endl;
	
	for (int i=0; i < (int) detlenH[0]; i++) {
		for (int j=0; j < (int) detlenH[1];j++) {
			cout << H[i*detlenH[1]+j] << " ";
			
		}
		cout << endl;
		
	}
	cout << endl;
	
	ilwt2<double> ilift2(lift2,blift);
	vector<double> oup;
	ilift2.getSignal(oup);
	vector<int> oup_dim;
	ilift2.getDim(oup_dim);
	cout << "Output Dimensions : " << oup_dim[0] << " :: " << oup_dim[1] << endl;
	cout << "OUTPUT : " << endl;
	for (int i=0; i < (int) oup_dim[0]; i++) {
		for (int j=0; j < (int) oup_dim[1];j++) {
			cout << oup[i*oup_dim[1]+j] << " ";
			
		}
		cout << endl;
		
	}
	
	
	 

	return 0;
}

```

The Outputs.
```

INPUT :
1 2 3 4 5 6 7 8
9 10 11 12 13 14 15 16
17 18 19 20 21 22 23 24
25 26 27 28 29 30 31 32
33 34 35 36 37 38 39 40
41 42 43 44 45 46 47 48
49 50 51 52 53 54 55 56
57 58 59 60 61 62 63 64
65 66 67 68 69 70 71 72
73 74 75 76 77 78 79 80
81 82 83 84 85 86 87 88
Respective Size of All 4 Output vectors (LL,LH,HL,HH) : 6 26 30 26
Length of Dimension Vector (8 at Level 1 + 6 at Level 2) :14
Low Pass Component At Level 2 :
50.247 85.5542
214.519 211.949
627.337 588.489
 Levels : 2
 All 7 row/col pairs :
3 2
3 2
3 2
3 2
5 4
6 4
5 4
 Lengths of Horizontal Component at level 1 : 5 4
 Horizontal Component at level 1 :
2.125 1.03125 0.636718 0.0624986
-5.5e-006 -4.97917e-006 -5.60938e-006 -7.69444e-006
-1.21667e-005 -1.00625e-005 -1.0776e-005 -1.39167e-005
-1.88333e-005 -1.51458e-005 -1.59427e-005 -2.01389e-005
-7.62502 -6.01043 -6.24611 -7.75696

Output Dimensions : 11 :: 8
OUTPUT :
1 2 3 4 5 6 7 8
9 10 11 12 13 14 15 16
17 18 19 20 21 22 23 24
25 26 27 28 29 30 31 32
33 34 35 36 37 38 39 40
41 42 43 44 45 46 47 48
49 50 51 52 53 54 55 56
57 58 59 60 61 62 63 64
65 66 67 68 69 70 71 72
73 74 75 76 77 78 79 80
81 82 83 84 85 86 87 88

Press any key to continue.



```