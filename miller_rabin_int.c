#include <gmp.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

int ipow(int base, int exp)
{
    int result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

int randR(int lower, int upper) {
  int r = (rand() % (upper - lower + 1)) + lower;
  return r; 
}

int mexp(int base, int exponent, int modulus) {
  if (modulus == 1) return 0;
  int c = 1;
  for (int i=0; i<exponent; i++) {
    c = (c*base) % modulus;
  }
  return c;
}


bool trial_composite(int n, int d, int r, int a) {
  int x = mexp(a, d, n);
  if ((x==1) || (x==n-1)) {
    return false;
  }
  for (int i=0; i<r; i++) {
    x = mexp(a, d*ipow(2,i), n);
    if (x==n-1) {
      return false;
    }
  }
  return true;
}

bool mr_test_int(int n, int numtests) {
  if (n % 2 == 0) {
    printf("Error: %d is even\n", n);
    return -1;
  }
  if (n < 3) {
    printf("Error: Value of %d is expected to be > 3.\n", n);
    return -1;
  }


  int d = n-1;
  int r = 0;

  // Decompose into d*2^r + 1 = n
  while (d % 2 == 0) {
    d >>= 1;
    r++;
  }

  int a;
  for (int k=0; k<numtests; k++) {
    a = randR(2,n-2);
    if (trial_composite(n,d,r,a)) {
      return false;
    }
    
  }
  return true;
}



int main(){
  srand(time(NULL));


  //  b = 4, e = 13, and m = 497 
  int t = mexp(4, 13, 497);
  //printf("Mexp %d\n", t);

  bool p;
  for (int i=10001; i<10040;i+=2) {
    p = mr_test_int(i, 10);
    if (p) {
      printf("  %d is Prime\n", i);
    }
    else {
      printf("  %d is Not prime\n", i);
    }
  }
	return 0;
}



