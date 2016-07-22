Mike is an orphan.  He was lost from his parents when he was 2. Now he wants to find his biological parents.
Many evidence points to a man called Mr. Smith. Is Mr. Smith Mike's biological father?

DNA

A strand of DNA can be expressed as a string of {A, C, G, T}

Mike:
X = ACCGGGTTACCGTTTAAAACCCGGGTAACCT

Mr. Smith:
Y = CCAGGACCAGGGACCGTTTACCAGCCTTAAACCA


Algorithm #1:
N = X.size() -1
For i = [N..1]:
   Find all subsequence of length i in X and see if there exist same subsequence in Y

   N!/(i!)(N-i)!

   N!/1*(N-1)! + N!/2!*(N-2)! + ... + N!/(N-1)!*1 = pow(2, N)





Algorithm #2:

Define:
C[i][j] -- Length of LCS of sequecne X[0..i] and Y[0..j]

if (i==0 || j==0) 
   C[i][j] = 0;
else if (X[i] == Y[j])
   C[i][j] = C[i-1][j-1] + 1;
else
   C[i][j] = max( C[i][j-1], C[i-1][j] );




//////////////////////////////////////////
code:


template<typename T>
void prtM(vector< vector<T> >& arr, string msg = "") {
	cout << msg << " " << endl;
	for  (auto i: arr) {
		for (auto j: i) {
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename T>
void prt(vector<T>& arr, string msg = "") {
	cout << msg << " ";
	for  (auto i: arr) {
		cout << i << " ";
	}
	cout << endl;
}


void prt_LCS(vector< vector<char> >& S, string& X, int i, int j) {
	//cout << "i=" << i << " j=" << j << "  " << S[i][j] << endl;
	if (i==0 || j == 0)
		return;
	if ('s' == S[i][j]) {
		prt_LCS(S, X, i-1, j-1);
		cout << X[i];
	} else if ('j' == S[i][j])  {
		prt_LCS(S, X, i, j-1);
	} else {
		prt_LCS(S, X, i-1, j);
	}
}


void calc_LCS(string& X,  string& Y) {
	cout << "X: " << X << endl;
	cout << "Y: " << Y << endl;

	vector< vector<int> > C;  // Length of LCS of sequecne X[0..i] and Y[0..j]
	vector< vector<char> > S;
	for (int i=0; i<X.size(); i++) {
		C.push_back( vector<int>(Y.size()) );
		S.push_back( vector<char>(Y.size()) );
	}

	for (int i=0; i<X.size(); i++) 
		C[i][0] = 0;
	for (int j=0; j<Y.size(); j++) 
		C[0][j] = 0;

	for (int i=1; i<X.size(); i++)
		for (int j=1; j<Y.size(); j++) {
			if (X[i] == Y[j]) {
			   C[i][j] = C[i-1][j-1] + 1;
			   S[i][j] = 's';  // same
			} else if ( C[i][j-1] > C[i-1][j] ) {
				C[i][j] = C[i][j-1];
				S[i][j] = 'j';
			} else {
			    C[i][j] = C[i-1][j] ;
				S[i][j] = 'i';
			}
		}

	prtM(C);
	prtM(S);
	prt_LCS(S, X, X.size()-1, Y.size()-1);
	cout<< endl;
}

int main() {

	string S1 = " ACCGGGTTAC";  // To simplify notation, first char will be ignored.
	string S2 = " AGGACCA";

	calc_LCS(S1, S2);

	return 0;
}


