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


public class application {
	static Integer binarySearch(Integer[] x, Integer key, Integer size) {
		int pos = Arrays.binarySearch(x, 0, size, key);
		//System.out.println("  Search " + Arrays.toString(x) + " length(" + size + ") for " + key +" get " + pos);
		if (pos < 0) {
			pos = 0-pos-1;
		}
		return pos;
	}
	
	static void LIS(Integer[] din) {
		System.out.println("Data in:" + Arrays.toString(din));
		Integer size = din.length;
		
		Integer[] M= new Integer[size+1];  // M[j] store the index of the smallest tail of all LIS of length j+1. 
		M[0] = 0;
		Integer Length = 1;
		Integer[] P = new Integer[size+1];
		
		for (Integer i=0; i<size-1; i++){   // O(N)
			if (din[M[Length-1]] < din[i+1]) {
				Length++;
				M[Length-1] = i+1;
				P[i+1] = M[Length-2];
				continue;
			}
			
			Integer pos = bSearch(din, M, din[i+1], Length);  // O(log N)
						
			//System.out.println("i = " + i + "    M = " + Arrays.toString(M) + "  pos = " + pos + "  Length = " + Length);
			if ( din[M[pos]] > din[i+1] ) {
				if (pos > 0) 
					P[i+1] = M[pos - 1];
				M[pos] = i+1;
			}
		}
		
		for (int i = 0; i < M.length; i++) {
			if (M[i] != null)  System.out.print("["+M[i]+"]"+din[M[i]] + " ");
		}

		System.out.println("\nP: " + Arrays.toString(P));
		System.out.println("Length: " + Length);
		
		Integer v = M[Length-1];
		Integer[] res = new Integer[Length];
		for (Integer u = Length; u!=0; u--) {
			//System.out.println("v = " + v);
			res[u-1] = din[v];
			v = P[v];
		}
		System.out.println("Final Result: " + Arrays.toString(res));
	}
	
	static Integer bSearch(Integer[] data, Integer[] index, Integer key, Integer size) {
		Integer start = 0;
		Integer end = size -1;
		if (key > data[index[size-1]])
			return size;
		
		while (start < end) {
			//System.out.println("start: " + start + "   end: "+ end);
			Integer middle = (end + start)/2 ;
			if (data[index[middle]] < key) 
				start = middle + 1;
			else
				end = middle;
		}		
		return start;
	}
	
	public static void main(String[] args) {
		Integer[] arr = {3, 5, 4, 9, 2, 1, 4, 8, 9, 1};
		//Integer[] arr = {7, 9,2,6,4,5,1};
		LIS(arr);
		
		//Integer[] s = { 1, 2, 3,  4, 5, 6, 8, 10};
		//Integer[] ids = {0, 2, 4, 6, 7};
		//System.out.println(bSearch(s, ids, 7));
	}
}

