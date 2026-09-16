class Solution {
public:
    long long modPow(long long a, long long b, long long mod) {
        long long res = 1;

        while (b > 0) {
            if (b & 1)
                res = res * a % mod;

            a = a * a % mod;
            b >>= 1;
        }

        return res;
    }

    int numberOfSets(int n, int k) {
        const long long MOD = 1e9 + 7;

        int N = n + k - 1;
        int R = 2 * k;

        vector<long long> fact(N + 1);

        fact[0] = 1;

        for (int i = 1; i <= N; i++)
            fact[i] = fact[i - 1] * i % MOD;

        // C(N, R) = fact[N] / (fact[R] * fact[N-R])
        long long numerator = fact[N];

        long long denominator =
            fact[R] * fact[N - R] % MOD;

        // Modular inverse of denominator
        long long inverse =
            modPow(denominator, MOD - 2, MOD);

        return numerator * inverse % MOD;
    }
};