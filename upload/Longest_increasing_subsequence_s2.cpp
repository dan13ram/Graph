Problem:
  For a sequence of data: a[0], a[1], ..., a[N], find longest increasing subsequence.
Example: a[] = {3, 2, 6, 4, 5, 1}
   Increasing Subsequcne: {3, 6}, {2,6}, {2, 4, 5}, {1}

Algorithm:
For i = 0..N:
  For sequence: { a[0], a[1], ..., a[i] },  
    calculate M[0..j], which contains the index of the smallest tail of all increasing subsequences of length (j+1)
    P[i] records the predecessor of M[j]

Note: 
  M[0] < M[1] < ... < M[j] 

Pseudocode:
1. M[0] = 0

2. for i = 0..N:
M[0..J] is already calculated for {a[0] ... a[i]}
if a[i+1] > M[j]:
    M[j+1] = a[i+1]
    P[i+1] = M[j]
else:
   binary search M for a[i+1], get position p (p is the first position where: a[p] >= a[i+1])
   M[p] = a[i+1]
   P[i+1] = M[p-1] (if p>0)

3. Result:   ..., a[P[P[M[j]]]], a[P[M[j]]], a[M[j]]


Example: a[] = {3, 2, 6, 4, 5, 1}
init:              M[0] = 0
i=0: a[i+1] is 2,  M[0] = 1                         P[1] =
i=1: a[i+1] is 6,  M[0] = 1, M[1] = 2               P[2] = 1
i=2: a[i+1] is 4,  M[0] = 1, M[1] = 3               P[3] = 1
i=3: a[i+1] is 5,  M[0] = 1, M[1] = 3, M[2] = 4,    P[4] = 3
i=4: a[i+1] is 1,  M[0] = 5, M[1] = 3, M[2] = 4,    P[5] = 

Results:
Index: 1, 3, 4
Data:  2, 4, 5


using namespace std;

void prt(vector<int>& arr, string msg = "") {
	cout << msg << " ";
	for  (auto i: arr) {
		cout << i << " ";
	}
	cout << endl;
}

void calc_LIS(vector<int>& din, vector<int>& dout) {
	vector<int> M;  // M[j] store the index of the smallest tail of all LIS of length (j+1)
	M.push_back(0);  // M[0]  
	vector<int> P(din.size());  // Predecessor of M[j]

	for (int i=0; i<din.size()-1; i++) {  // Calculate M for {din[0]..din[i]}
		if (din[M.back()] < din[i+1]) {
			M.push_back(i+1);
			P[i+1] = M[M.size()-2];
			prt(M, "M: ");
			continue;
		}

		vector<int>::iterator pos = lower_bound(M.begin(), M.end(), din[i+1], [&](int m, int val){return (din[m] < val);});
		if ( din[*pos] > din[i+1] ) {
			*pos = i+1;
			if (pos != M.begin()) 
				P[i+1] = *(pos - 1);
		}

		prt(M, "M: ");
	}

	int v = M.back();
	dout.resize(M.size());
	for (int u = M.size(); u!=0; u--) {
		dout[u-1] = din[v];
		v = P[v];
	}
}

int main() {

	int a[] = {3, 2, 6, 4, 5, 1};
	vector<int> arr(a, a + sizeof(a)/sizeof(a[0]));
	vector<int> res;

	prt(arr, "Data In:");
	calc_LIS(arr, res);
	prt(res, "Data out:");

	return 0;
}

