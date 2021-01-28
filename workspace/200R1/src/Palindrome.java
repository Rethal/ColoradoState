// Palindrome.java
// Class: cs200

public class Palindrome extends Stack {

//	private void generatePalindromeRecursive(String s,int index)
//	{
//		// first print the character, then recurse on the next character index
////		System.out.print(s.charAt(index));
////		if(index<s.length()-1)
////		{
////			// question: will index++ or ++index work on the method call below?
////			generatePalindromeRecursive(s,index+1);
////		}
////		System.out.print(s.charAt(index));
//		
//		
//	}
	
	public void generatePalindrome(String s) {
		// generate palindrome by concatenating the reverse of s to s
		//generatePalindromeRecursive(s,0);
		generatePalindromeStack(s,0);
		System.out.println();
		
	}
	public void generatePalindromeStack(String s,int index){
		while(index<s.length()){
			this.push(s.charAt(index));
			System.out.print(s.charAt(index));
			index++;
		}
		while(index>0){
		System.out.print(this.pop());
		index--;
		}
	}
	
	public static void main(String[] args) {
	    Palindrome p = new Palindrome();
		p.generatePalindrome("evolve");

	}

	

}
