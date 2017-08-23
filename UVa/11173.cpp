#include <bits/stdc++.h>
using namespace std;

#define INF 1e9
#define pb push_back
#define mp make_pair

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef pair<int,int> pii;

int pot2(int k) {
  int b = 1;
  for(int i=0; i<k; i++) b*=2;

  return b;
}

int bit(int n, int k) {
  if(n == 1) {
    if(k == 0) return 0;
    else return 1;
  } else {
    if(k < pot2(n-1)) return bit(n-1,k);
    else return (1<<(n-1)) + bit(n-1,pot2(n)-k-1);
  }
}

int main(){
  int cases;
  cin >> cases;

  for(int i=0;i<cases;i++) {
    int n, k;
    cin >> n >> k;
    cout << bit(n,k) << endl;
  }

  return 0;
}
