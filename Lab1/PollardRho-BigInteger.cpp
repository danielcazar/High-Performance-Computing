#include <stdio.h>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

//Inputs alpha: a generator of G, beta: an element of G
//Output An integer x such that alpha^x = beta, or failure

//ZZ q(1018), alpha(2), beta(5);
//ZZ p(1019);

ZZ q(5915587276), alpha(5), beta(5);
ZZ p(5915587277);

new_xab( ZZ& x, ZZ& a, ZZ& b ) {
    switch( x%3 ) {
    case 0: x = x*x     % p;
            a =  a*2  % q;
            b =  b*2  % q;
            break;
    case 1: x = x*alpha % p;
            a = (a+1) % q;
            break;
    case 2: x = x*beta  % p;
            b = (b+1) % q;
            break;
    }
}

int main() {
ZZ x(1), a(0), b(0);
ZZ X(x), A(a), B(b);

for(long i = 1; i < q; ++i ) {
    new_xab( x, a, b );
    new_xab( X, A, B );
    new_xab( X, A, B );
    cout << i <<" "<< x <<" "<< a<<" "<< b <<" "<< X <<" "<< A<<" " << B << "\n";
    if( x == X )
    break;
}
return 0;
}
