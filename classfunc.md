# Lifting Wavelet Transform Classes and Functions #

## Lifting Scheme Class and Functions ##

**liftscheme Class**
```

liftscheme (string &name)

```

Liftscheme Implements lifting scheme based on Sweldens/Daubechies paper. _I. Daubechies, W. Sweldens, Factoring wavelets transforms into lifting steps, J. Fourier Anal. Appl. 4 (3) (1998) 247-269._
It is highly recommended that you download a copy of the paper from either the website of the Journal or from http://cm.bell-labs.com/who/wim/papers/factor/index.html
(_See Figure 7 and 8 for implementation details_)

_name_ is the wavelet name and as of now the supported wavelets are
_Lazy, Haar(db1),db2-8, sym2-8, bior2.2-8, bior3.1-9, bior4.4_

Usage Example is straightforward ;
```

string name="bior4.4";
liftscheme blift(name);

```

**Functions Associated With liftscheme Class**

```

int 	nlifts ()
double 	K ()
string 	getName ()
void 	getScheme (vector< double > &coeff, vector< int > &lenvec, string &lattice, double &Kc)
void 	disp ()
void 	addLift (string &c, vector< double > addcoeff, int mp)

```

_**Adding A Lifting Stage to liftscheme**_

Consider the liftscheme class defined as above. Suppose we want to add a dual lifiting stage to the scheme. We use addLift function as shown below.

```

// Adding a Dual Lifting Stage

string c="d"; //d corrsponds to dual while p corresponds to primal
vector<double> addl;
addl.push_back(0.500);
addl.push_back(-0.125);

int mp=0;
blift.addLift(c,addl,mp);

```

_addl_ is a vector [0.500,-0.125] while _mp_ is its maximum power such that the lift stage corresponds to the Laurent Polynomial `0.5*z^(0)-0.125*z^(-1)`.

### **A Simple Example demonstrating the usage of liftscheme class** ###

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

string name="bior4.4";

liftscheme blift(name);

// Adding a Dual Lifting Stage

string c="d"; //d corrsponds to dual while p corresponds to primal
vector<double> addl;
addl.push_back(0.500);
addl.push_back(-0.125);

int mp=0;
blift.addLift(c,addl,mp);

//Getting Information

cout << " Number Of Lifting Stages : " << blift.nlifts() << endl;
cout << " K Constant : " << blift.K() << endl;
cout << " Name : " << blift.getName() << endl;

vector<double> coeff;
vector<int> lenvec;
string lattice;
double Kc;

// Getting Full Scheme

blift.getScheme(coeff,lenvec,lattice,Kc);

cout << "Lifting Structure : " << lattice << endl;
cout << " K Constant (Same As Above) : " << Kc << endl;

cout << "A Single Vector Containing All Lifting Coefficients " << endl;

for (int i=0; i <  (int)coeff.size(); i++) {
	cout << coeff[i] << " " ;
}
cout << endl;

cout << "Length Vector that corresponds to lengths of Lifting Coefficients and Maximum Power at each Stage" << endl;

for (int i=0; i <(int) lenvec.size(); i++) {
	cout << lenvec[i] << " " ;
}
cout << endl;
// disp() Function Displays Coefficients and Laurent Polynomials At Each Stage 
blift.disp();


return 0;
}

```

The Corresponding Output is shown below. The program is very descriptive and users will have no problem understanding it. getScheme() can be used to obtain filter coefficients of each lifting stage. The first vector contains all the coefficients. The second vector (lenvec) may be used to extract individual coefficients at each stage. eg., lenvec[2\*i] contains the length of the coefficient vector at stage i while lenvec[2\*i+1] contains the maximum power. See the output below for more details.

```

 Number Of Lifting Stages : 5
 K Constant : -0.869864
 Name : bior4.4
Lifting Structure : dpdpd
 K Constant (Same As Above) : -0.869864
A Single Vector Containing All Lifting Coefficients
1.58613 1.58613 -1.07964 0.0529801 0.882911 0.882911 -0.443507 -1.57612 0.5 -0.1
25
Length Vector that corresponds to lengths of Lifting Coefficients and Maximum Po
wer at each Stage
2 1 2 0 2 0 2 2 2 0
Total Number of Stages : 5
--------------------------
Stage : 1
Dual Lift
Coefficients : 1.58613 1.58613
Laurent Polynomial : 1.58613*z^(1)+1.58613*z^(0)

Stage : 2
Primal Lifting
Coefficients : -1.07964 0.0529801
Laurent Polynomial : -1.07964*z^(0)+0.0529801*z^(-1)

Stage : 3
Dual Lift
Coefficients : 0.882911 0.882911
Laurent Polynomial : 0.882911*z^(0)+0.882911*z^(-1)

Stage : 4
Primal Lifting
Coefficients : -0.443507 -1.57612
Laurent Polynomial : -0.443507*z^(2)-1.57612*z^(1)

Stage : 5
Dual Lift
Coefficients : 0.5 -0.125
Laurent Polynomial : 0.5*z^(0)-0.125*z^(-1)

--------------------------
 K : -0.869864

Press any key to continue.


```

## 1D LWT Classes and Functions ##

**LWT Class**
```
lwt (vector< T > &signal, liftscheme &lft)
lwt (vector< T > &signal, string &name)
lwt (vector< T > &signal, liftscheme &lft, int &J)
lwt (vector< T > &signal, string &name, int &J)
```

First two declarations are for a single level Lifting Wavelet Transform decomposition. The last two are J-level of decomposition where J=1,2,... .

Usage Examples are as following.

A.) One Level Decomposition using wavelet name.

```
string name="bior2.2";
double lp1_a[] = {0.9501,0.2311,0.6068,0.4860,0.8913,0.7621,0.4565,0.0185,0.8214,
	0.4447,0.6154,0.7919,0.9218,0.7382,0.1763,0.4057};
vector<double> sig;
sig.assign(lp1_a,lp1_a + sizeof(lp1_a)/sizeof(double));

lwt<double> dlift(sig,name);

```

B.) One Level Decomposition using Lifting Scheme.

```
string name="db3";
double lp1_a[] = {0.9501,0.2311,0.6068,0.4860,0.8913,0.7621,0.4565,0.0185,0.8214,
	0.4447,0.6154,0.7919,0.9218,0.7382,0.1763,0.4057};
vector<double> sig;
sig.assign(lp1_a,lp1_a + sizeof(lp1_a)/sizeof(double));

liftscheme blift(name);
string c="d";
vector<double> addl;
addl.push_back(0.500);
addl.push_back(-0.125);

int mp=0;
blift.addLift(c,addl,mp);
blift.disp();

lwt<double> dlift(sig,blift);

```

There are intermediate steps in this program which add a dual stage to the defined lifting scheme but the important steps are (i) defining a lifting scheme blift and (ii) using the so defined lifting scheme to find the single Level Lifting transform.

C.) J Level Decomposition using wavelet name.

```
string name="bior2.2";
int J=2;
double lp1_a[] = {0.9501,0.2311,0.6068,0.4860,0.8913,0.7621,0.4565,0.0185,0.8214,
	0.4447,0.6154,0.7919,0.9218,0.7382,0.1763,0.4057};
vector<double> sig;
sig.assign(lp1_a,lp1_a + sizeof(lp1_a)/sizeof(double));

lwt<double> dlift(sig,name,J);

```

D.) J Level Decomposition using Lifting Scheme is also straightforward and works for J=1,2,..., N where N is appropriate level based on signal length.

```
string name="db3";
int J=2;
double lp1_a[] = {0.9501,0.2311,0.6068,0.4860,0.8913,0.7621,0.4565,0.0185,0.8214,
	0.4447,0.6154,0.7919,0.9218,0.7382,0.1763,0.4057};
vector<double> sig;
sig.assign(lp1_a,lp1_a + sizeof(lp1_a)/sizeof(double));

liftscheme blift(name);
string c="d";
vector<double> addl;
addl.push_back(0.500);
addl.push_back(-0.125);

int mp=0;
blift.addLift(c,addl,mp);
blift.disp();

lwt<double> dlift(sig,blift,J);

```

There are intermediate steps in this program which add a dual stage to the defined lifting scheme but the important steps are (i) defining a lifting scheme blift and (ii) using the so defined lifting scheme to find the single Level Lifting transform.

**Functions Associated With LWT Class**

```

void 	getCoeff (vector< T > &appx, vector< T > &det)
void 	getDetailVec (vector< int > &detvec)
int 	getLevels ()

```

getCoeff returns the approximation and detail vectors. Approximation Vector consists of the values at Jth level while detail vector consists of all the values from Jth down to first level. This necessitates getDetailVec function which returns the respective lengths of all J detail vectors contained in the detail vector. getLevels returns the number of decomposition levels.

Usage Example- Consider Example D from above with lifting scheme blift and J=2.

```

lwt<double> dlift(sig,blift,J);
vector<double> a,d;
vector<int> lengths;
dlift.getCoeff(a,d);
dlift.getDetailVec(lengths);
cout << " Approximation : " << endl;
for (int i=0; i < a.size();i++) {
cout << a[i] << " ";
}
cout << endl;

cout << " Detail : " << endl;
for (int i=0; i < d.size();i++) {
cout << d[i] << " ";
}
cout << endl;

cout << " Lengths Of Detail Vectors : " << endl;
for (int i=0; i < lengths.size();i++) {
cout << lengths[i] << " ";
}
cout << endl;

```


The Output follows :

```

 Approximation :
0.0443938 0.9017 1.1909 1.39608
 Detail :
-0.066988 -1.22228 -2.09606 0.711298 -0.775945 -1.26932 -1.23474 -2.10261 -0.291
774 -1.29618 -1.43258 -0.4876
 Lengths Of Detail Vectors :
4 8

```

The example above is very intuitive. We start with a signal of length 16 and end up with length 4 approximation/detail vectors at level 2 and length 8 detail vector at level 1. You can use "lengths" vector to extract individual vectors from the main detail vector. In this case, first 4 samples of the length 12 vector belong to the second stage while the first 8 belong to the first stage.


## 1D ILWT Classes and Functions ##

```

ilwt (vector< T > &sl, vector< T > &dl, liftscheme &lft)
ilwt (vector< T > &sl, vector< T > &dl, string &name)
ilwt (lwt< T > &wt, liftscheme &lft)
ilwt (lwt< T > &wt, string &name)

```

Inverse LWT functions are used in accordance with the LWT function already used.

Example Usage

A. One Level Lifting Reconstruction with string Name. See A) in LWT class above.

```

vector<double> a,d;
dlift.getCoeff(a,d);
ilwt(a,d,name);

```

B.) One Level Reconstruction using Lifting Scheme.  See B) in lwt class above

```

vector<double> a,d;
dlift.getCoeff(a,d);
ilwt(a,d,blift);

```

C.) J Level Reconstruction using wavelet name. In this case, instead of using coefficients as input we use the lwt class as the input to the ilwt class. This method is more user friendly and compact.

```

ilwt<double> idlift(dlift,name);

```

D.) J Level Reconstruction using lifting scheme. In this case, instead of using coefficients as input we use the lwt class as the input to the ilwt class. This method is more user friendly and compact.

```

ilwt<double> idlift(dlift,blift);

```

**Functions Associated With ILWT Class**

```

void 	getSignal (vector< T > &sig)

```

The function getSignal returns the reconstructed signal.

Usage Example- Consider Example D from above with lifting scheme blift and J=2

```

ilwt<double> idlift(dlift,blift);
vector<double> oup;
idlift.getSignal(oup);

cout << " Reconstructed : " << endl;
for (int i=0; i < oup.size();i++) {
cout << oup[i] << " ";
}
cout << endl;

```

The output follows.

```

 Reconstructed :
0.9501 0.2311 0.6068 0.486 0.8913 0.7621 0.4565 0.0185 0.8214 0.4447 0.6154 0.79
19 0.9218 0.7382 0.1763 0.4057

```


### **A Simple Example using D) declarations** ###

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

string name="db3";
int J=2;
double lp1_a[] = {0.9501,0.2311,0.6068,0.4860,0.8913,0.7621,0.4565,0.0185,0.8214,
0.4447,0.6154,0.7919,0.9218,0.7382,0.1763,0.4057};
/*double lp1_a[] = {1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,1.000,
1.000,1.000,1.000,1.000,1.000,1.000,1.000};*/
vector<double> sig;
    sig.assign(lp1_a,lp1_a + sizeof(lp1_a)/sizeof(double));

liftscheme blift(name);
string c="d";
vector<double> addl;
addl.push_back(0.500);
addl.push_back(-0.125);

int mp=0;
blift.addLift(c,addl,mp);
blift.disp();

lwt<double> dlift(sig,blift,J);
vector<double> a,d;
vector<int> lengths;
dlift.getCoeff(a,d);
dlift.getDetailVec(lengths);
cout << " Approximation : " << endl;
for (int i=0; i < a.size();i++) {
cout << a[i] << " ";
}
cout << endl;

cout << " Detail : " << endl;
for (int i=0; i < d.size();i++) {
cout << d[i] << " ";
}
cout << endl;

cout << " Lengths Of Detail Vectors : " << endl;
for (int i=0; i < lengths.size();i++) {
cout << lengths[i] << " ";
}
cout << endl;


ilwt<double> idlift(dlift,blift);
vector<double> oup;
idlift.getSignal(oup);

cout << " Reconstructed : " << endl;
for (int i=0; i < oup.size();i++) {
cout << oup[i] << " ";
}
cout << endl;


return 0;
}

```

The Outputs :

```

Total Number of Stages : 5
--------------------------
Stage : 1
Dual Lift
Coefficients : -0.412287
Laurent Polynomial : -0.412287*z^(0)

Stage : 2
Primal Lifting
Coefficients : 0.352388 -1.56514
Laurent Polynomial : 0.352388*z^(0)-1.56514*z^(-1)

Stage : 3
Dual Lift
Coefficients : 0.492152 0.0284591
Laurent Polynomial : 0.492152*z^(1)+0.0284591*z^(0)

Stage : 4
Primal Lifting
Coefficients : -0.38962
Laurent Polynomial : -0.38962*z^(0)

Stage : 5
Dual Lift
Coefficients : 0.5 -0.125
Laurent Polynomial : 0.5*z^(0)-0.125*z^(-1)

--------------------------
 K : 1.9182
 Approximation :
0.0443938 0.9017 1.1909 1.39608
 Detail :
-0.066988 -1.22228 -2.09606 0.711298 -0.775945 -1.26932 -1.23474 -2.10261 -0.291
774 -1.29618 -1.43258 -0.4876
 Lengths Of Detail Vectors :
4 8
 Reconstructed :
0.9501 0.2311 0.6068 0.486 0.8913 0.7621 0.4565 0.0185 0.8214 0.4447 0.6154 0.79
19 0.9218 0.7382 0.1763 0.4057

Press any key to continue.


```

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

## Laurent Polynomial Class ##

Initialization
```

Laurent<double> poly1;

```

**Associated Functions**

```

void 	setPoly (const vector< T > &coef_i, int hdeg)
void 	getPoly (vector< T > &vec)
void 	dispPoly ()
void 	printPoly ()
int 	degree ()
int 	highdeg ()
void 	LaurentAdd (Laurent &A, Laurent &B)
void 	LaurentSub (Laurent &A, Laurent &B)
void 	LaurentMult (Laurent &A, Laurent &B)
void 	One ()
void 	Zero ()
int 	isZero ()
void 	scale (T s)
void 	zinv (Laurent &A)
void 	merge (Laurent &X, Laurent &Y)

```

setPoly is used to set the values of the Laurent Polynomial. Example usage is

```

Laurent<double> poly1;
int mp=2;
vector<double> coeff;
coeff.push_back(1.0);
coeff.push_back(-0.5);
poly1.setPoly(coeff,mp);
poly1.dispPoly();

```

setPoly accepts an input vector that corresponds to the coefficients of the Poynomial and a maximum degree integer that corresponds to the maximum power of the polynomial. The code above uses dispPoly() to output the following polynomial.

```

1*z^(2)-0.5*z^(1)


```

getPoly returns the coefficient vector from a Laurent class object.

```

vector<double> get_coeff;
poly1.getPoly(get_coeff);

```

The two functions degree() and highdeg() return the degree of the Laurent Polynomial( size of coefficient vector - 1) and the highest power of the polynomial. In this case, the degree is 1 while the highest power is 2.

One() and Zero() set the value of Laurent Polynomial to one( `1*z^(0)`) and zero ( `0*z^(0)`).

LaurentAdd, LaurentSub and LaurentMult add subtract and multiply two Laurent Polynomials respectively and store the value in a third polynomial.

```

        double re_array[]= {-0.125,0.75,-0.125};
	double re_array2[]= {0.25,0.25};

	vector<double> a(re_array, re_array + sizeof(re_array)/sizeof(double));
	vector<double> b(re_array2, re_array2 + sizeof(re_array2)/sizeof(double));

        int low=1;
	int low2=1;
	Laurent<double> lp1,lp2,lp3,lp4,lp5,lp6;
	lp1.setPoly(a,low);
	lp2.setPoly(b,low2);
        cout << lp1.degree()+1 << " " << lp2.degree()+1 << endl; // prints Laurent Test

        vector<double> newvec;
        lp1.getPoly(newvec);
        cout << newvec.size() << endl;

        cout << "A : ";
	lp1.dispPoly();
	cout << "B : ";
	lp2.dispPoly();
	lp3.LaurentAdd(lp1,lp2);
	cout << "A+B : ";
	lp3.dispPoly();
	lp3.LaurentSub(lp1,lp2);
	cout << "A-B : ";
        lp3.dispPoly();

        lp4.LaurentMult(lp1,lp2);
        cout << "A*B : ";
        lp4.dispPoly();


```

This code has the following output :

```

3 2
3
A : -0.125*z^(1)+0.75*z^(0)-0.125*z^(-1)
B : 0.25*z^(1)+0.25*z^(0)
A+B : 0.125*z^(1)+1*z^(0)-0.125*z^(-1)
A-B : -0.375*z^(1)+0.5*z^(0)-0.125*z^(-1)
A*B : -0.03125*z^(2)+0.15625*z^(1)+0.15625*z^(0)-0.03125*z^(-1)



```

zinv inverts the power of the polynomial while scale(T s) scales the coefficients by a scalar s.

**Long Division Using Div**

The function Div is not part of the class. It is a stand alone function that divides two Laurent Polynomials and stores the values in a vector of Laurent Polynomials such that the every even term (starting from index zero) contains the quotient while every odd term contains the remainder polynomial. This is a very basic long division algorithm (as the solution is non-unique) and may not return all quotient/remainder combinations for very large polynomials. Improving this function is on my TO-DO list. For more information see the Sweldens/Daubechies paper as well as [Mladen Victor Wickerhauser's Survey Of Wavelet Algorithms 2001/2002 ](http://www.math.wustl.edu/~victor/papers/) and Wavelet Toolbox user's guide (Michel Misiti, Yves Misiti, Georges Oppenheim and Jean-Michel Poggi) .

```

void Div(Laurent<T> &A, Laurent<T> &B, vector<Laurent<T> > &lcont) 

```

A is divided by B and the results are stored in a Container lcont.

```

    vector<Laurent<double> > lout;
    Div(lp1,lp2,lout);

    for (unsigned int i=0; i < lout.size()/2; i++) {
        cout << "Q" << i << ": ";
        lout[2*i].dispPoly();
        cout << endl;
        cout << "R" << i << ": " ;
        lout[2*i+1].dispPoly();
        cout << endl;

    }


```

The Output is

```

Q0: -0.5*z^(0)+3.5*z^(-1)

R0: -1*z^(-1)

Q1: -0.5*z^(0)-0.5*z^(-1)

R1: 1*z^(0)

Q2: 3.5*z^(0)-0.5*z^(-1)

R2: -1*z^(1)

Q3: -0.5*z^(0)-0.5*z^(-1)

R3: 1*z^(0)


```

**Splitting A Laurent Polynomial Into Polyphase Components**

Only single level splitting (Even and Odd) is available in this implementation.

```

void EvenOdd(Laurent<T> &A,Laurent<T> &even,Laurent<T> &odd)

```

Example : In the following example you will have to include "filter.h" header file.

```

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include "lwave.h"
#include "filter.h"


using namespace std;

int main()
{
        string name="db2";
	Laurent<double> lpd,hpd,lpr,hpr;
	lpoly(name,lpd,hpd,lpr,hpr);
	Laurent<double> leven,lodd;
	EvenOdd(lpr,leven,lodd);
	cout << "Polynomial 1 : ";
	lpr.dispPoly();
	cout << "Polynomial 1 Even Component : ";
	leven.dispPoly();
	cout << "Polynomial 1 Odd Component : ";
	lodd.dispPoly();
	
	Laurent<double> out;
	out.merge(leven,lodd);
	cout << "Merging Even and Odd Components : ";
	out.dispPoly();
	
	return 0;
}

```


The Output is

```

Polynomial 1 : 0.482963*z^(0)+0.836516*z^(-1)+0.224144*z^(-2)-0.12941*z^(-3)
Polynomial 1 Even Component : 0.482963*z^(0)+0.224144*z^(-1)
Polynomial 1 Odd Component : 0.836516*z^(0)-0.12941*z^(-1)
Merging Even and Odd Components : 0.482963*z^(0)+0.836516*z^(-1)+0.224144*z^(-2)
-0.12941*z^(-3)

Press any key to continue.


```

## LaurentMat Class {2 X 2 Matrices} ##

Initialization
```

LaurentMat<double> matrix;

```

**Associated Functions**

```

void 	setMat (Laurent< T > &AA, Laurent< T > &BB, Laurent< T > &CC, Laurent< T > &DD)
void 	Det (Laurent< T > &oup)
void 	MatAdd (LaurentMat &X, LaurentMat &Y)
void 	MatSub (LaurentMat &X, LaurentMat &Y)
void 	MatMult (LaurentMat &X, LaurentMat &Y)
void 	TZ (Laurent< T > &t)
void 	SZ (Laurent< T > &s)
void 	dispMat ()
void 	scale (T s)
void 	MatInv (LaurentMat &Inv)
void 	getLpoly (Laurent< T > &P, int N)

```

setMat sets the matrix. The Laurent Polynomials are entered as (1,1), (1,2),(2,1) and (2,2).

```

        Laurent<double> lpd,hpd,lpr,hpr;
	lpoly(name,lpd,hpd,lpr,hpr);
	
	LaurentMat<double> matrix;
	
	matrix.setMat(lpd,lpr,hpd,hpr);

```

Det finds the determinant of the matrix while you can use dispMat() to display the matrix.

```

        Laurent<double> determinant;
	matrix.Det(determinant);
	
	cout << "The Matrix : " << endl;
	matrix.dispMat();
        cout << endl;
	cout << " The Determinant : ";
	determinant.dispPoly();

```

The Output is

```

The Matrix :
 Laurent Matrix
(1,1) : -0.176777*z^(1)+0.353553*z^(0)+1.06066*z^(-1)+0.353553*z^(-2)-0.176777*z
^(-3)
(1,2) : 0.353553*z^(0)+0.707107*z^(-1)+0.353553*z^(-2)
(2,1) : 0.353553*z^(1)-0.707107*z^(0)+0.353553*z^(-1)
(2,2) : 0.176777*z^(2)+0.353553*z^(1)-1.06066*z^(0)+0.353553*z^(-1)+0.176777*z^(
-2)

 The Determinant : -0.03125*z^(3)+0*z^(2)+0.375*z^(1)+1.38778e-017*z^(0)-0.6875*
z^(-1)-1.38778e-017*z^(-2)+0.375*z^(-3)+0*z^(-4)-0.03125*z^(-5)



```

TZ and SZ functions set the T(Z) and S(Z) matrices (see the Sweldens/Daubechies paper).

```

        LaurentMat<double> T1,S1;
	T1.TZ(lpd);
	S1.SZ(hpd);
	cout << "T(Z) matrix : " << endl;
	T1.dispMat();
	cout << "S(Z) matrix : " << endl;
	S1.dispMat();

```

The Output

```


T(Z) matrix :
 Laurent Matrix
(1,1) : 1*z^(0)
(1,2) : 0*z^(0)
(2,1) : -0.176777*z^(1)+0.353553*z^(0)+1.06066*z^(-1)+0.353553*z^(-2)-0.176777*z
^(-3)
(2,2) : 1*z^(0)
S(Z) matrix :
 Laurent Matrix
(1,1) : 1*z^(0)
(1,2) : 0.353553*z^(1)-0.707107*z^(0)+0.353553*z^(-1)
(2,1) : 0*z^(0)
(2,2) : 1*z^(0)


```

**Scaling and The Inverse Of a Matrix**

I have used the most basic and very restrictive algorithm to invert a 2X2 matrix. It works only if the determinant is a mononomial. Otherwise it returns all zeros. Scaling by a scalar is straightforward as the name implies.

```

        T1.scale(2.2);
	cout << "T(Z) matrix Scaled by 2.2 : " << endl;
	T1.dispMat();
	
	LaurentMat<double> IS;
	
	S1.MatInv(IS);
	cout << "Inverse of S(Z) matrix  : " << endl;
	IS.dispMat();

```

The Output

```


T(Z) matrix Scaled by 2.2 :
 Laurent Matrix
(1,1) : 2.2*z^(0)
(1,2) : 0*z^(0)
(2,1) : -0.388909*z^(1)+0.777817*z^(0)+2.33345*z^(-1)+0.777817*z^(-2)-0.388909*z
^(-3)
(2,2) : 2.2*z^(0)
Inverse of S(Z) matrix  :
 Laurent Matrix
(1,1) : 1*z^(0)
(1,2) : -0.353553*z^(1)+0.707107*z^(0)-0.353553*z^(-1)
(2,1) : 0*z^(0)
(2,2) : 1*z^(0)

Press any key to continue.


```

**Matrix Addition, Subtraction and Multiplication**

MatAdd, MatSub and MatMult add, subtract and multiply two matrices respectively.

```

        LaurentMat<double> addm,subm,multm;
	
	addm.MatAdd(T1,S1);
	subm.MatSub(T1,S1);
	multm.MatMult(T1,S1);
	
	cout << " T(Z)+S(Z) = " << endl;
	addm.dispMat();
	cout << endl;
	
	cout << " T(Z)-S(Z) = " << endl;
	subm.dispMat();
	cout <<endl;
	
	cout << " T(Z)*S(Z) = " << endl;
	multm.dispMat();
	cout <<endl;

```

The Output

```

 T(Z)+S(Z) =
 Laurent Matrix
(1,1) : 3.2*z^(0)
(1,2) : 0.353553*z^(1)-0.707107*z^(0)+0.353553*z^(-1)
(2,1) : -0.388909*z^(1)+0.777817*z^(0)+2.33345*z^(-1)+0.777817*z^(-2)-0.388909*z
^(-3)
(2,2) : 3.2*z^(0)

 T(Z)-S(Z) =
 Laurent Matrix
(1,1) : 1.2*z^(0)
(1,2) : -0.353553*z^(1)+0.707107*z^(0)-0.353553*z^(-1)
(2,1) : -0.388909*z^(1)+0.777817*z^(0)+2.33345*z^(-1)+0.777817*z^(-2)-0.388909*z
^(-3)
(2,2) : 1.2*z^(0)

 T(Z)*S(Z) =
 Laurent Matrix
(1,1) : 2.2*z^(0)
(1,2) : 0.777817*z^(1)-1.55563*z^(0)+0.777817*z^(-1)
(2,1) : -0.388909*z^(1)+0.777817*z^(0)+2.33345*z^(-1)+0.777817*z^(-2)-0.388909*z
^(-3)
(2,2) : -0.1375*z^(2)+0.55*z^(1)+2.3375*z^(0)-1.1*z^(-1)+0.1375*z^(-2)+0.55*z^(-
3)-0.1375*z^(-4)


Press any key to continue.



```

**LaurentMat Full Example Code**

_This code also includes "filter.h" only because I am using a biorthogonal filter to set the matrix. You may not need to include "filter.h" usually if you are setting up matrices on your own._

```

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include "lwave.h"
#include "filter.h"


using namespace std;

int main()
{
        string name="bior2.2";
	Laurent<double> lpd,hpd,lpr,hpr;
	lpoly(name,lpd,hpd,lpr,hpr);
	
	LaurentMat<double> matrix;
	
	matrix.setMat(lpd,lpr,hpd,hpr);
	Laurent<double> determinant;
	matrix.Det(determinant);
	
	cout << "The Matrix : " << endl;
	matrix.dispMat();
	cout << endl;
	cout << " The Determinant : ";
	determinant.dispPoly();
	
	LaurentMat<double> T1,S1;
	T1.TZ(lpd);
	S1.SZ(hpd);
	cout << "T(Z) matrix : " << endl;
	T1.dispMat();
	cout << "S(Z) matrix : " << endl;
	S1.dispMat();
	
	T1.scale(2.2);
	cout << "T(Z) matrix Scaled by 2.2 : " << endl;
	T1.dispMat();
	
	LaurentMat<double> IS;
	
	S1.MatInv(IS);
	cout << "Inverse of S(Z) matrix  : " << endl;
	IS.dispMat();
	
	LaurentMat<double> addm,subm,multm;
	
	addm.MatAdd(T1,S1);
	subm.MatSub(T1,S1);
	multm.MatMult(T1,S1);
	
	cout << " T(Z)+S(Z) = " << endl;
	addm.dispMat();
	cout << endl;
	
	cout << " T(Z)-S(Z) = " << endl;
	subm.dispMat();
	cout <<endl;
	
	cout << " T(Z)*S(Z) = " << endl;
	multm.dispMat();
	cout <<endl;
	
	
	return 0;
}

```

The Output

```

The Matrix :
 Laurent Matrix
(1,1) : -0.176777*z^(1)+0.353553*z^(0)+1.06066*z^(-1)+0.353553*z^(-2)-0.176777*z
^(-3)
(1,2) : 0.353553*z^(0)+0.707107*z^(-1)+0.353553*z^(-2)
(2,1) : 0.353553*z^(1)-0.707107*z^(0)+0.353553*z^(-1)
(2,2) : 0.176777*z^(2)+0.353553*z^(1)-1.06066*z^(0)+0.353553*z^(-1)+0.176777*z^(
-2)

 The Determinant : -0.03125*z^(3)+0*z^(2)+0.375*z^(1)+1.38778e-017*z^(0)-0.6875*
z^(-1)-1.38778e-017*z^(-2)+0.375*z^(-3)+0*z^(-4)-0.03125*z^(-5)
T(Z) matrix :
 Laurent Matrix
(1,1) : 1*z^(0)
(1,2) : 0*z^(0)
(2,1) : -0.176777*z^(1)+0.353553*z^(0)+1.06066*z^(-1)+0.353553*z^(-2)-0.176777*z
^(-3)
(2,2) : 1*z^(0)
S(Z) matrix :
 Laurent Matrix
(1,1) : 1*z^(0)
(1,2) : 0.353553*z^(1)-0.707107*z^(0)+0.353553*z^(-1)
(2,1) : 0*z^(0)
(2,2) : 1*z^(0)
T(Z) matrix Scaled by 2.2 :
 Laurent Matrix
(1,1) : 2.2*z^(0)
(1,2) : 0*z^(0)
(2,1) : -0.388909*z^(1)+0.777817*z^(0)+2.33345*z^(-1)+0.777817*z^(-2)-0.388909*z
^(-3)
(2,2) : 2.2*z^(0)
Inverse of S(Z) matrix  :
 Laurent Matrix
(1,1) : 1*z^(0)
(1,2) : -0.353553*z^(1)+0.707107*z^(0)-0.353553*z^(-1)
(2,1) : 0*z^(0)
(2,2) : 1*z^(0)
 T(Z)+S(Z) =
 Laurent Matrix
(1,1) : 3.2*z^(0)
(1,2) : 0.353553*z^(1)-0.707107*z^(0)+0.353553*z^(-1)
(2,1) : -0.388909*z^(1)+0.777817*z^(0)+2.33345*z^(-1)+0.777817*z^(-2)-0.388909*z
^(-3)
(2,2) : 3.2*z^(0)

 T(Z)-S(Z) =
 Laurent Matrix
(1,1) : 1.2*z^(0)
(1,2) : -0.353553*z^(1)+0.707107*z^(0)-0.353553*z^(-1)
(2,1) : -0.388909*z^(1)+0.777817*z^(0)+2.33345*z^(-1)+0.777817*z^(-2)-0.388909*z
^(-3)
(2,2) : 1.2*z^(0)

 T(Z)*S(Z) =
 Laurent Matrix
(1,1) : 2.2*z^(0)
(1,2) : 0.777817*z^(1)-1.55563*z^(0)+0.777817*z^(-1)
(2,1) : -0.388909*z^(1)+0.777817*z^(0)+2.33345*z^(-1)+0.777817*z^(-2)-0.388909*z
^(-3)
(2,2) : -0.1375*z^(2)+0.55*z^(1)+2.3375*z^(0)-1.1*z^(-1)+0.1375*z^(-2)+0.55*z^(-
3)-0.1375*z^(-4)


Press any key to continue.


```