Problem:
  For a sequence of data: a[0], a[1], ..., a[N], find longest increasing subsequence.
Example: a[] = {3, 2, 6, 4, 5, 1}
   Increasing Subsequcne: {3, 6}, {2,6}, {2, 4, 5}, {1}

Simple Algorithm:
for i=[N..1]:
   1. Find all combination of i numbers;   (N!)/(i!)(N-i)!    O(exp(N))
   2. See if there is one sorted increasingly.


Algorithm 1:
   for i=[0..N], calculate LIS[i], which is the longest increasing subsequence that ends with a[i]

LIS[0]:  3
LIS[1]:  2
LIS[2]:  2,6
LIS[3]:  2,4
LIS[4]:  2,4,5
LIS[5]:  1

using namespace std;

void prt(vector<int>& arr, string msg = "") {
	cout << msg << " ";
	for  (auto i: arr) {
		cout << i << " ";
	}
	cout << endl;
}


void calc_LIS(vector<int>& D) {
	vector< vector<int> > L(D.size());  // The longest increasing subsequence ends with D[i]

   L[0].push_back(D[0]);

	for (int i=1; i<D.size(); i++) {
		for(int j=0; j<i; j++) {
			if ( (D[j] < D[i]) && ( L[i].size() < L[j].size() ) ) {
				L[i] = L[j];  				
			}         
		}
      L[i].push_back(D[i]);
	}

	for (auto x: L) {
		prt(x);
	}
}

int main() {
	int a[] = {3, 2, 6, 4, 5, 1};
	vector<int> arr(a, a + sizeof(a)/sizeof(a[0]));

	prt(arr, "Data In:");
	calc_LIS(arr);

	return 0;
}



