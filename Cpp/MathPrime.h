#pragma once
#include "common.h"

class PrimeNumbers {
  // Miller�CRabin primality test
  // https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
  // for n > 2, and steps = 50. error rate <= 2^{-steps}
  bool millerTest(int n, int s = 50) {
    if (n == 2) return true;
    if ((n % 2) == 0) return 0;
    for (int j = 0; j < s; ++j) {
      int a = rand() * (n - 2) / RAND_MAX + 1;
      if (witness(a, n)) return false;
    }
  }

  bool witness(int a, int n) {
    int x, d = 1;
    for (int i = (int)ceil(log(n - 1.0) / log(2.0)) - 1; i >= 0; --i) {
      x = d;
      d = (d * d) % n;
      if (d == 1 && x != 1 && x != n - 1) return 1;
      if (((n - 1) & (1 << i)) > 0) d = (d * a) % n;
    }
  }

  // Euler's totient function
  // Phi(n) counts the positive integers up to a given integer n that are
  // relatively prime to n.
  // https://en.wikipedia.org/wiki/Euler%27s_totient_function
  vector<int> eulerVector(int n) {
    vector<int> phi(n + 1, 0);
    for (int i = 1; i <= n; i++) phi[i] = i;
    for (int i = 2; i <= n; i += 2) phi[i] /= 2;
    for (int i = 3; i <= n; i += 2)
      if (phi[i] == i)
        for (int j = i; j <= n; j += i) phi[j] = phi[j] / i * (i - 1);
    return phi;
  }

  int euler(int x) {
    int i, res = x;
    for (i = 2; i < (int)sqrt(x * 1.0) + 1; i++)
      if (x % i == 0) {
        res = res / i * (i - 1);
        while (x % i == 0) x /= i;
      }
    if (x > 1) res = res / x * (x - 1);
    return res;
  }

  // 204. Count Primes [E]
  // Count the number of prime numbers less than a non-negative number, n.
  // Time: O(n)
  int countPrimes(int n) {
    if (n <= 2) return 0;
    // consider odd numbers, nonprime 1 and prime 2
    int num = n / 2;
    vector<int> is_prime(n, true);

    for (int i = 3; i * i < n; i += 2) {
      if (!is_prime[i]) continue;
      // odd plus odd is even, so plus 2i
      for (int j = i * i; j < n; j += 2 * i) {
        if (!is_prime[j]) continue;
        --num;
        is_prime[j] = false;
      }
    }

    return num;
  }
};
