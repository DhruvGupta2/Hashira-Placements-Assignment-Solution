#include <bits/stdc++.h>
using namespace std;

// Multiply string number by integer
string multiplyStringByInt(const string &num, long long x) {
    long long carry = 0;
    string result = "";
    for (int i = num.size()-1; i >= 0; i--) {
        long long val = (num[i]-'0')*x + carry;
        result.push_back((val % 10) + '0');
        carry = val / 10;
    }
    while (carry) {
        result.push_back((carry % 10) + '0');
        carry /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

// Add integer to string number
string addIntToString(const string &num, long long x) {
    long long carry = x;
    string result = num;
    for (int i = result.size()-1; i >=0 && carry; i--) {
        long long val = (result[i]-'0') + carry;
        result[i] = (val % 10) + '0';
        carry = val / 10;
    }
    if (carry) result.insert(result.begin(), carry+'0');
    return result;
}

// Convert from base b string to decimal string
string toDecimal(const string &s, int base) {
    string num = "0";
    for (char c : s) {
        int digit = isdigit(c) ? (c-'0') : (tolower(c)-'a'+10);
        num = multiplyStringByInt(num, base);
        num = addIntToString(num, digit);
    }
    return num;
}

// Compare two string numbers (a < b)
bool lessThan(const string &a, const string &b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

// Subtract b from a (a >= b)
string subtractString(const string &a, const string &b) {
    string res = a;
    int n = a.size(), m = b.size();
    int carry = 0;
    for (int i=0; i<m; i++) {
        int ai = res[n-1-i]-'0';
        int bi = b[m-1-i]-'0';
        int sub = ai - bi - carry;
        if (sub < 0) { sub += 10; carry = 1; }
        else carry = 0;
        res[n-1-i] = sub+'0';
    }
    for (int i=m; i<n && carry; i++) {
        int ai = res[n-1-i]-'0';
        int sub = ai - carry;
        if (sub < 0) { sub += 10; carry = 1; }
        else carry = 0;
        res[n-1-i] = sub+'0';
    }
    // Remove leading zeros
    int pos = 0; while (pos+1 < (int)res.size() && res[pos]=='0') pos++;
    return res.substr(pos);
}

int main() {
    // Sample Test 2 roots
    vector<pair<int,string>> roots = {
        {6, "13444211440455345511"},
        {15, "aed7015a346d635"},
        {15, "6aeeb69631c227c"},
        {16, "e1b5e05623d881f"},
        {8, "316034514573652620673"},
        {3, "2122212201122002221120200210011020220200"},
        {3, "20120221122211000100210021102001201112121"},
        {6, "20220554335330240002224253"},
        {12, "45153788322a1255483"},
        {7, "1101613130313526312514143"}
    };

    int k = 7; // min roots required
    vector<string> X;
    for(int i=0; i<k; i++)
        X.push_back(toDecimal(roots[i].second, roots[i].first));

    // Polynomial degree = k-1
    int m = k-1;

    // Vandermonde matrix as strings
    vector<vector<string>> A(k, vector<string>(k,"0"));
    for(int i=0;i<k;i++){
        A[i][0]="1";
        for(int j=1;j<k;j++)
            A[i][j] = multiplyStringByInt(A[i][j-1], stoll(X[i])); // string*decimal
    }

    // Solve Ax=0 (homogeneous system)
    vector<long long> c(k);
    c[k-1]=1; // fix highest degree coefficient

    // Back-substitution (integer approximation)
    for(int i=k-2;i>=0;i--){
        long long sum=0;
        for(int j=i+1;j<k;j++){
            sum += stoll(A[i][j])*c[j];
        }
        c[i] = -sum / stoll(A[i][i]);
    }

    // Print coefficients
    cout<<"Polynomial coefficients: ";
    for(auto x:c) cout<<x<<" ";
    cout<<endl;

    return 0;
}
