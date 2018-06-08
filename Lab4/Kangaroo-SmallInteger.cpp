#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <omp.h>

using namespace std;

long Jfunction ( long X, long c, long d)
{
  int k, elevado, variable;
  k=floor(log2(d-c))/2;
  variable= (X % k);
  elevado=pow(2,variable);
  return(elevado);
  //RETURN(2^(X mod k))
}

long F ( long X, long c, long d, long g, long p)
{
  long J,elevado,variable;
  J = Jfunction(X, c, d);
  elevado=powf(g, J);
  variable=X * elevado;
  return((variable) % p);
  //RETURN((X*(g&^J)) mod p)
}

//This function solves DLP if we know that discrete log belongs to some interval [a,b].
//It solves with good probability  when b-a is smaller than sqrt(p).
long Kangaroo (long b,long g,long p,long c,long d)
{
//To solve: g^x=b mod p in [c,d]
//Initial value of tame kangaroo  in [c,d]

  long Wzero, Tzero, W, T, Told, powerT, powerTold, powerW, variable, j;
  variable=powf(g, c);
  Tzero = variable % p;
  T = Tzero;
  powerT = c;
  cout << "Working on the tame kangaroo: " << endl;

  for (j = 1; j <= d - c + 1; j++)
  {
    Told = T;
    powerTold = powerT;
    powerT = powerT + Jfunction(T, c, d);
    T = F(T, c, d, g, p);
    printf("T=%ld\n",T);
    if (d < powerT)
    {
      powerT = powerTold;
      T = Told;
      printf("\nEnd of tame kangaroo: T=%ld, powerT=%ld, j = %ld\n", T, powerT, j);
      break;
    }
  }

  Wzero = b;
  W = Wzero;
  powerW = 0;
  cout << "Working on the wild kangaroo: " << endl;

  for (j = 1; j <= d - c + 1; j++)
  {
    powerW = powerW + Jfunction(W, c, d);
    W = F(W, c, d, g, p);
    printf("W=%ld\n",W);
    if (W == T)
      return((powerT - powerW) % (p - 1));
  }
  printf("The kangaroo doesn't work. Try increasing the upperbound on the interval.\n");
}

int main() {
    long p, g, b, c, d, x;
    p=29;
    g=3;
    b=2;
    c=4;
    d=19;
    x=Kangaroo(b,g,p,c,d);
    cout << "The result of the Discrete Logarithm is:" << endl;
    cout << "x="<< x << endl;
    //In order to verify, compute b=g^x mod p. If this b is equal to b written in the input then Kangaroo succeeded.
}