#include <bits/stdc++.h>
using namespace std;

int main() {
	unsigned int A;
	cin >> A;


	unsigned int res = 0;
	
	for(int i=0; i<32; i++) {
		int ibit = ((A & 1<<i) != 0);
		if(ibit) res += 1<<(32-i-1);

		bitset<32> x(res);
		cout << "res: " << x << endl;
	}
    
    return res;
}
