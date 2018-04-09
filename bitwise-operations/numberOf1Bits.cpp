#include <bits/stdc++.h>
using namespace std;

int main() {
	int A;
	cin >> A;
	int res = 0;
	for(int i=0; i<32; i++) {
		if(((A & (1 << i)) != 0) == 1) res++;
    	}
	cout << "result: " << res << endl;
}
