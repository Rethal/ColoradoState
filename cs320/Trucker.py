'''  This is about the problem of a trucker who shows up at a loading dock
     and has a set A of n packages to choose from.  Each package weighs
     an integer number of pounds, and he can't put more than t pounds
     in the truck without getting fined at the truck weigh station.  He 
     gets paid by the pound, so he wants to select a set of items that gets 
     as close to t without going over.   '''

'''  Compute the closest sum to t that does not exceed it, over all
     subsets of elements of A '''
def TruckRecursive(A, t):
    return TruckRecursive_aux([-1] + A, len(A), t)  #prepend a dummy value pos 0

'''  Compute the closest sum to t that does not exceed it, for all subsets
     of elements of A[1..n]  '''
def TruckRecursive_aux(A, n, t):
    if n == 0 or n == 0:
        return 0
    else:
        opt1 = TruckRecursive_aux(A, n-1, t)  # one option, don't use A[n]
        if A[n] <= t:    #another option:  use A[n] if it doesn't exceend t
           opt2 = TruckRecursive_aux(A, n-1, t-A[n]) + A[n] 
        else:
           opt2 = 0
    return max(opt1, opt2)  # return the best of these two options

'''  Solve the problem of TruckRecursive using dynamic programming.  Instead
     of returning the best you can do, return the whole dynamic programming
     table '''
def TruckDP(A, t):
    return TruckDP_aux([-1] + A, len(A), t)

'''  Solve the problem of TruckRecursive_Aux, returning the whole n by t 
     dynamic programming table instead of a value ''';
def TruckDP_aux(A, n, t):  
	 DPTable = [[0]*(t+1) for i in range(n+1)]
	 for k in range(0,n+1):
		for j in range(0,t+1):
			#opt1 = DPTable[k][j-1]#don't use A[n]
			#if DPTable[k][j-1] + A[k] <= t:
			#	opt2 = DPTable[k][j-1] + A[k]#use A[n] if it doesn't exceed t
			#DPTable[k][j] = TruckRecursive_aux(A, k, j)
			#DPTable[k][j] = TruckDPSolve_aux(A,k,j,DPTable)
			#DPTable[k][j] = max(opt1,opt2);
			if k == 0 or j == 0:
				DPTable[k][j] = 0
			elif A[k] <= j:
				opt1 = DPTable[k-1][j-A[k]] + A[k]
				opt2 = DPTable[k-1][j]
				DPTable[k][j] = max(opt1,opt2)
			else:
				DPTable[k][j] = DPTable[k-1][j]
    # fill in code here
	 return DPTable
	 
'''  Tell how the sum in DPTable[n][t] is achieved.  That is, give a subset 
     of elements of A whose sum is equal to the optimum value '''
def TruckDPSolve(A, t, DPTable):
    return TruckDPSolve_aux([-1] + A, len(A), t, DPTable)

def TruckDPSolve_aux(A, n, t, DPTable):
    print n, t
    if n == 0 or t == 0:
        return []
    elif DPTable[n][t] == DPTable[n-1][t]:
        return TruckDPSolve_aux(A,n-1, t, DPTable)
    else:
        L = TruckDPSolve_aux(A, n-1, t-A[n], DPTable)
        L.append(A[n])
        return L

'''  Find a solution to the problem of TruckDP, but use memoization and a
     hash table, filling on only those elements of the table that are 
     relevant to solving the problem.  '''
def TruckMemoized(A, t):
    MemoTable = {}
    TruckMemoized_aux([-1] + A, len(A), t, MemoTable)
    return MemoTable

def TruckMemoized_aux(A, i, j, MemoTable):
    hashKey = str(i) + ',' + str(j)
    if MemoTable.get(hashKey) == None:
		pass
		if i == 0 or j == 0:
			MemoTable[hashKey] = 0
		else:
			opt1 = TruckMemoized_aux(A, i-1, j, MemoTable)  # one option, don't use A[n]
			if A[i] <= j:    #another option:  use A[n] if it doesn't exceend t
				opt2 = TruckMemoized_aux(A, i-1, j-A[i], MemoTable) + A[i] 
			else:
				opt2 = 0
			MemoTable[hashKey] = max(opt1,opt2)	

		'''for n in range(1,i+1):
			for t in range (1,j+1):
				hashKey = str(n) + ',' + str(t)'''
      # fill in code from here to the return statement
    else:
		pass
    return MemoTable[hashKey]

'''  Solve the problem of TruckDPSolve, but on a hash table produced
     by the memoized approach, rather than a full dynamic programming
     table. '''
def TruckMemoSolve(A, t, MemoTable):
    return TruckMemoSolve_aux([-1] + A, len(A), t, MemoTable)

def TruckMemoSolve_aux(A, n, t, MemoTable):
     # fill in code here
	print n, t
	hashKey = str(n) + ',' + str(t)
	hashKey2 = str(n-1) + ',' + str(t)
	if MemoTable.get(hashKey) == None:
		return []
	elif MemoTable.get(hashKey) == MemoTable.get(hashKey2):
		return TruckMemoSolve_aux(A,n-1,t,MemoTable)
	else:
		L = TruckMemoSolve_aux(A,n-1,t-A[n],MemoTable)
		L.append(A[n])
		return L

