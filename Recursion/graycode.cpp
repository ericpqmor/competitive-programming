#include <bits/stdc++.h>
using namespace std;

#define vs vector<string>
#define pb push_back

vs gray(int n) {
	vs ans;
	if(n == 1) {
		ans.pb("0");
		ans.pb("1");
		return ans;
	}
	vs last = gray(n-1);
	
	for(int i=0; i<last.size(); i++)
		ans.pb("0" + last[i]);
	for(int i=last.size()-1; i>=0; i--)
		ans.pb("1" + last[i]);

	return ans;
}

int main() {
	int n;
	cin >> n;

	vs g = gray(n);
	for(int i=0; i<g.size(); i++) cout << g[i] << " ";

	return 0;
}
