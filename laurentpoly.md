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

**A Simple Example demonstrating the Laurent class**

```

//============================================================================
// Name        : Laurent.cpp
// Author      : Rafat Hussain
// Version     :
// Copyright   :
// Description : 
//============================================================================

#include <iostream>
#include <vector>
#include "lwave.h"

using namespace std;

int main() {
//    double re_array[]= {5.0,2.0,4.0,3.0};
//	double re_array2[]= {2.0,2.0,-1.0,9.0};
    double re_array[]= {-0.125,0.75,-0.125};
	double re_array2[]= {0.25,0.25};

	vector<double> a(re_array, re_array + sizeof(re_array)/sizeof(double));
	vector<double> b(re_array2, re_array2 + sizeof(re_array2)/sizeof(double));
//	int low=-2;
//	int low2=2;
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

    lp5.zinv(lp1);
    cout << "A(1/z) : ";
    lp5.dispPoly();

    //cout << lp5.isMono() << endl;

    LaurentMat<double> Mat1;
    Mat1.setMat(lp1,lp1,lp2,lp2);
    Laurent<double> det1;
    Mat1.Det(det1);
    cout << "Determinant : ";
    det1.dispPoly();

    cout << "Mono : " << det1.isMono() << endl;
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
	
	return 0;
}



```


The Output

```

3 2
3
A : -0.125*z^(1)+0.75*z^(0)-0.125*z^(-1)
B : 0.25*z^(1)+0.25*z^(0)
A+B : 0.125*z^(1)+1*z^(0)-0.125*z^(-1)
A-B : -0.375*z^(1)+0.5*z^(0)-0.125*z^(-1)
A*B : -0.03125*z^(2)+0.15625*z^(1)+0.15625*z^(0)-0.03125*z^(-1)
A(1/z) : -0.125*z^(1)+0.75*z^(0)-0.125*z^(-1)
Determinant : 0*z^(-1)
Mono : 1
Q0: -0.5*z^(0)+3.5*z^(-1)

R0: -1*z^(-1)

Q1: -0.5*z^(0)-0.5*z^(-1)

R1: 1*z^(0)

Q2: 3.5*z^(0)-0.5*z^(-1)

R2: -1*z^(1)

Q3: -0.5*z^(0)-0.5*z^(-1)

R3: 1*z^(0)


Press any key to continue.


```