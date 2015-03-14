# C++ Discrete Wavelet Transform Using Lifting Method #

### Lifting Implementation ###

This library implements lifting scheme based on Sweldens/Daubechies paper.
_I. Daubechies, W. Sweldens, Factoring wavelets transforms into lifting steps, J. Fourier Anal. Appl. 4 (3) (1998) 247-269._
> It is highly recommended that you download a copy of the paper from either the website of the Journal or from http://cm.bell-labs.com/who/wim/papers/factor/index.html (See Figure 7 and 8 for implementation details)

![https://lh4.googleusercontent.com/-BODCEXcVn4I/UFWbNHwCsnI/AAAAAAAAAPQ/Vgj58HAuIeo/s851/lift1.png](https://lh4.googleusercontent.com/-BODCEXcVn4I/UFWbNHwCsnI/AAAAAAAAAPQ/Vgj58HAuIeo/s851/lift1.png)

![https://lh6.googleusercontent.com/-HSTO2rWj1NM/UFWbNGT4mMI/AAAAAAAAAPU/5CfOBms0JnI/s844/lift2.png](https://lh6.googleusercontent.com/-HSTO2rWj1NM/UFWbNGT4mMI/AAAAAAAAAPU/5CfOBms0JnI/s844/lift2.png)

**Installation** No Installation is necessary. The package consists of a bunch of header files. For most applications it will be sufficient to include "lwave.h" in your program. Just make sure that all header files are contained in one folder.

**Download** Downloads are available at "Downloads" and the git repository can be accessed using "Source" tab.

|**List of Classes and Functions**| Lists all Classes/Functions available in the liftwave Library|
|:--------------------------------|:-------------------------------------------------------------|
|**[Lifting Scheme Class and Functions](http://code.google.com/p/liftwave/wiki/liftscheme)**| liftscheme class and associated functions|
|**[1D LWT/ILWT Classes and Functions](http://code.google.com/p/liftwave/wiki/1dlwt)**| lwt, ilwt classes and associated functions|
|**[2D LWT/ILWT Classes and Functions](http://code.google.com/p/liftwave/wiki/2dlwt)**| lwt2, ilwt2 classes and associated functions|
|**[Laurent Polynomial Class and Functions](http://code.google.com/p/liftwave/wiki/laurentpoly)**| Laurent class and associated functions|
|**[LaurentMat Class {2 X 2 Matrices} and Functions](http://code.google.com/p/liftwave/wiki/laurentmat)**| LaurentMat class and associated functions|

**A few Simple Examples**

|**[Lifting Scheme Example](http://code.google.com/p/liftwave/wiki/ex1_liftscheme)**| A Simple Demonstration Of liftscheme class|
|:----------------------------------------------------------------------------------|:------------------------------------------|
|**[1D LWT/ILWT Example](http://code.google.com/p/liftwave/wiki/ex1_lwt)**| 1D Lifting DWT/IDWT Demo Code|
|**[2D LWT/ILWT Example](http://code.google.com/p/liftwave/wiki/ex_lwt2)**| 2D Lifting DWT/IDWT Demo Code|