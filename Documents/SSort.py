def SS(A):
	SSAux(A,0,len(A)-1)

def SSAux(A,i,j):
	if j-i <= 1:
		if (A[i]>A[j]):
			A[j],A[i] = A[i],A[j]
	else:
		k = (j-i+1)/3
		SSAux(A,i,j-k)
		SSAux(A,i+k,j)
		SSAux(A,i,j-k)

A = [5,3,9,6,14,2,7]