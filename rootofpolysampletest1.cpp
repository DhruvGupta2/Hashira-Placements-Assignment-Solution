#include <bits/stdc++.h>
using namespace std;

// Convert string in base 'b' to decimal (for large numbers, using long long)
long long toDecimal(const string &s, int base) {
    long long num = 0;
    for (char c : s) {
        int digit = isdigit(c) ? (c - '0') : (tolower(c) - 'a' + 10);
        num = num * base + digit;
    }
    return num;
}

int main() {
    // Example JSON input (Sample Test 2)
    struct Root { int base; string value; };
    vector<Root> roots = {
        {10, "4"},
        {2, "111"},
        {10, "12"},
        {4, "213"} // extra root, can ignore if k=3
    };

    int k = 3; // minimum roots required = degree + 1
    int m = k - 1; // degree of polynomial

    // Step 1: Convert roots to decimal
    vector<long long> X;
    for (int i = 0; i < k; i++) {
        X.push_back(toDecimal(roots[i].value, roots[i].base));
    }

    // Step 2: Build Vandermonde matrix
    vector<vector<long long>> A(k, vector<long long>(k));
    for (int i = 0; i < k; i++) {
        long long val = 1;
        for (int j = 0; j < k; j++) {
            A[i][j] = val;
            val *= X[i];
        }
    }

    // Step 3: Solve homogeneous system Ax=0
    vector<long long> c(k);
    c[k-1] = 1; // fix highest degree coefficient = 1

    // Back-substitute to find other coefficients
    for (int i = k-2; i >= 0; i--) {
        long long sum = 0;
        for (int j = i+1; j < k; j++) sum += A[i][j] * c[j];
        c[i] = -sum / A[i][i]; // integer division
    }

    // Step 4: Print coefficients
    cout << "Polynomial coefficients: ";
    for (long long coef : c) cout << coef << " ";
    cout << endl;

    return 0;
}
