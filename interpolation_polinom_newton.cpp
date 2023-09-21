#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double* splitFunction(double a, double b, int n){            //function for dividing a segment into N equal segments
   auto* s = new double [n];                                 //creating an array to record points
   s[0] = a;                                                 //the starting and ending point of the constant
   double step = (b - a)/n;                                  //counting the step
   for(int i = 1; i <= n; i++){                              //we go through the cycle and add a step to the previous point
       s[i] = s[i-1] + step;
   }
   return s;                                                  //returning an array of interpolation nodes
}

double* myFunction(double* x, int n){                        //function for counting the function in the interpolation nodes
   auto* f = new double [n];                                  //array for writing functions
   for(int i = 0; i <= n; i++){                               //we go through the cycle and count the functions in the interpolation nodes
       f[i] = (x[i]*x[i]+2) + sin(sqrt(x[i]*x[i]+2));         // variante 19
   }
   return f;                                                  //returning an array of functions
}

double NewtPol(const double *x, const double *y, int n, double xx){//function for counting a polynomial at a point
   double omg, newt = y[0], a;
   for(int i = 1; i < n; i++) {                               //we go through the cycle and consider the polynomial
       a = 0.0;                                               //setting the initial value of a
       for(int j = 0; j <= i; j++) {                          //we go through the cycle and count a
           omg = 1.0;                                         //setting the initial value of omega
           for(int k = 0; k <= i; k++) {                      //we go through the cycle and count the value of omega
               if (k != j) {
                   omg *= (x[j] - x[k]);                      //multiply the previous omega value with the difference between the split points
               }
           }
           a +=  (y[j] / omg);                               //we add the previous value of a to the quotient of the jth element of the function and the value of omega
       }
       for (int j = 0; j < i; j++) {                         //we go through the cycle and count the new values of a for the polynomial
           a *= (xx - x[j]);
       }
       newt += a;                                            //adding the value of a with the previous value of the polynomial
   }
   return newt;                                             //returning the value of the polynomial
}

double* PolNewtAll(double* x, double* y, int n){           //function for counting the polynomial at each point
   auto* newton = new double [n];                          //creating an array to write a polynomial at each point
   for(int i = 0; i <= n; i++){                            //we go through the cycle and at each point we count the values of the polynomial and write it to the array
       newton[i] = NewtPol(x, y, n, x[i]);
   }
   return newton;                                         //returning the array
}

void print(double* pol, int n, double* x, double* y){    //function for convenient, readable output
   cout << "Dividing a segment into " << n << " parts: " << endl;
   for(int i = 0; i <= n; i++){                         //we use the setprecision method to set the floating point precision
       cout << setprecision(4) << x[i] << setw(20);
       cout << y[i] << setw(20);
       cout << pol[i] << setw(20);
       cout << abs(y[i] - pol[i]) << setprecision(20) << endl;
   }
}

int main() {
   cout << "Enter N: "<< endl;
   int n;
   cin >> n;
   int m = 3*n;
   double a = -1, b= 1;
   double *x = splitFunction(a, b, n);
   double *y = myFunction(x, n);
   double *x1 = splitFunction(a, b, m);
   double *y1 = myFunction(x1, m);
   double* ne = PolNewtAll(x, y, n);
   print(ne, n, x, y);
   cout << endl;
   double* ne1 = PolNewtAll(x1, y1, m);
   print(ne1, m, x1, y1);
   return 0;
}
