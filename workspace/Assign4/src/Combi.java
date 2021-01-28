import java.util.Arrays;
import java.util.Scanner;

public class Combi {

	private long[] subset;

	/**
	 * Recursive computation of n choose k
	 * @param n >= 0
	 * @param k <= n
	 * @return the number of possible combinations of
	 * k out of n
	 */
	public long combRec(long n, long k){
		// pre: 0 <= k <= n
		// post:  return the number of possible combinations of
		// k out of n
		if (n==k || k==0) return 1;
		else // n>k and k>0
			return combRec(n-1,k-1) + combRec(n-1,k);

	}

	/*
	 * Fast Spock
	 */
	public long combFast(int n, int k, long[][] A) {
		long r;
		if (n==k || k==0) {
			A[n][k]=1;
			return 1;
		}
		else if (A[n][k] == 0) {
			r = combFast(n-1,k-1,A) + combFast(n-1,k,A);
			A[n][k] = r;
			return r;
		}
		else {
			r = A[n][k];
			return r;
		}
	}
	/**
	 * Iterative computation of n choose k
	 * @param n >= 0
	 * @param k <= n
	 * @return n! / ((n-k)! * k!)
	 */
	public long combIter(long n, long k){
		long nComb = 1;
		long i;
		// n choose k
		for(i=n;i>n-k;i--)  nComb *= i;
		for(i=2;i<=k;i++)  nComb /= i;
		return nComb;
	}

	/**
	 * print all possible subsets of k out of n
	 * @param n >= 1
	 * @param k <= n
	 * @param p: position to fill 0 .. k-1 
	 * @param lo: first digit to pick
	 */
	void forwardC(int n, int k, int p, int lo) {
		int i;
		// n-k+p is last digit to pick in position p
		// for (i = lo; i <= n-1; i++) { // works like assign 1
		for (i = lo; i <= n-k + p; i++) {
			subset[p] = i;
			if (p < k-1)
				forwardC(n, k, p+1, i+1);
			else {
				// BASE CASE: we have placed k digits
				// print them:
				for(int j=0;j<k;j++) System.out.print(subset[j]+" ");
				System.out.println();
			}
		}
	}

	/**
	 * print all possible subsets of k out of n
	 * @param n >= 1
	 * @param p: position to fill
	 */
	void backwardC(int n, int p) {
		// all elements placed
		if(p<0) {
			System.out.print(Arrays.toString(subset));
			System.out.println();
		}
		else{
			// include n-1
			subset[p] = n-1;
			backwardC(n-1,p-1);

			// exclude n-1 if possible
			if(n-1>p)
				backwardC(n-1,p);	
		}
	}


	void subsets(int n) {
		for (int size = 1; size <= n; size++) {
			System.out.println("\nSubsets size " + size +
					" out of " + n);
			subset = new long[size];

			System.out.println("forward:");
			forwardC(n, size, 0, 0);
			System.out.println("\nbackward:");			
			backwardC(n,size-1);
		}
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner Input = new Scanner(System.in);
		int n;
		long start, finish, res;
		Combi S = new Combi();
		do{
			System.out.println("Enter set size n>0  (0 to finish)");
			n = Input.nextInt();

			if(n>0) {
				long[][] A = new long[n+1][n+1];
				for(int k = 0; k<=n; k++){ 
					start = System.currentTimeMillis();
					res = S.combRec(n, k);
					finish = System.currentTimeMillis();
					System.out.println("Number of combinations (slow): (" +
							n + " choose " +k+ ")  =  " + res + ", time = " + (finish-start) + "  milliseconds");
					//			   long[][] A = new long[n+1][k+1];
					start = System.currentTimeMillis();
					res = S.combFast(n, k, A);
					finish = System.currentTimeMillis();
					System.out.println("Number of combinations (fast): (" +
							n + " choose " +k+ ")  =  " + res + " time = " + (finish-start) + "  milliseconds\n");
				}
			}
		} while (n>0);
		System.out.println("Enter subset size n>0");
		n=Input.nextInt();
		if(n>0){
		System.out.println("Combinations");
		S.subsets(n);
		}
	}

}
