## 1D LWT/ILWT Classes and Functions ##

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