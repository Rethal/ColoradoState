#  Print out the moves for an instance of towers of Hanoi.
#  Preconditions:  n >= 0, The set {source, target, spare} = {1,2,3}.
#  Postcondtion:  The set of moves to move a stack of n disks from
#   peg number source to peg number target using peg number spare
#   as a parking spot have been printed out.
def Hanoi(n, source, target, spare):
   if n == 0:  
	return
   else:
	Hanoi(n-1, source, target, spare)
	print ('move disk ', n, ' from peg ', source, ' to peg ', spare)
	Hanoi(n-1, target, source, spare)
       	print ('move disk ', n, ' from peg ', spare, ' to peg ', target)
      	Hanoi(n-1, source, target, spare)
	


