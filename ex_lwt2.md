# 2D Lifting Wavelet Transform Example #

[sample code](http://code.google.com/p/liftwave/source/browse/examples/ex_lwt2.cpp)

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

This Program

1) Uses an 11X8 matrix as input.

2) Defines a Lifting Scheme (bior3.3)

3) Performs a 2 level 2D Lifting Wavelet Transform.

4) Performs a corresponding Inverse LWT.

The Output

![https://lh3.googleusercontent.com/-32YSAvipPNo/UFPmIdSGbCI/AAAAAAAAAPA/xf5TQFYPPQw/s912/lwt2.png](https://lh3.googleusercontent.com/-32YSAvipPNo/UFPmIdSGbCI/AAAAAAAAAPA/xf5TQFYPPQw/s912/lwt2.png)