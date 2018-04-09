#include <bits/stdc++.h>
using namespace std;

int clearBits(int n, int i, int j) {
	int mask = 0;
	for(int k=i; k<=j; k++) mask += 1 << k;
	mask = ~mask;
	return n & mask;
}

int main() {
	int n, m;
	cin >> n >> m;

	int i, j;
	cin >> i >> j;

	n = clearBits(n, i, j);	
	int res = n | (m << i);
	cout << "Result: " << res << endl;
	
	return 0;
}
