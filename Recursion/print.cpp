#include <bits/stdc++.h>
using namespace std;

void print(int ind, int n) {
	if(ind == n) { 
		cout << n << endl;
		return;
	}

	cout << ind << " ";
	print(ind+1, n);
}

int main() {
	int n;
	cin >> n;
	print(1,n);
}
