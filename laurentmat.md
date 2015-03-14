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