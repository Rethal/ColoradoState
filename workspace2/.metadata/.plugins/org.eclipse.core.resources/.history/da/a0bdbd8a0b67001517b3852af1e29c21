
import java.util.Iterator;


public class TokenIter implements Iterator<String>{

	// This class builds a Token Iterator, that produces 
	// Strings containing numbers (sequences of digits) and 
	// special characters: "(" ")" "+" "-"  "*" "/"


	//input line to be tokenized
	private String line;

	// the next Token, null if no next Token
	private String nextToken = " ";
	int loc = 0;
	
	// scLine is the scanner that gets the input line
	//Scanner scLine = new Scanner(line);
			
	public TokenIter(String line){
		line = line.replaceAll("\\s", "");
		this.line = line;
	}

	@Override
	public void remove() {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException();
	}

	@Override
	public boolean hasNext() {
		// TODO Auto-generated method stub
		if(loc<line.length()){
			return true;
		}
		return false;
	}

	@Override
	public String next() {
		// TODO Auto-generated method stub
		// if(scLine.hasNextInt())nextToken=Integer.toString(scLine.nextInt());
		// if token nextToken=scLine.next();
		String digit = "";
		String operator = "";
		if(loc<line.length()&&Character.isDigit(line.charAt(loc))){
			while(loc<line.length()&&Character.isDigit(line.charAt(loc))){
				digit = digit+line.charAt(loc);
				loc++;
			}
			nextToken = digit;
		}
		else{
			operator = operator+line.charAt(loc);
			loc++;
			nextToken = operator;
		}
		return nextToken;
		
//		while(scLine.next()==" "){
//			scLine.next();
//		}
//		nextToken=line.
//		System.out.println(nextToken);
//		System.out.println(scLine.next());
//		return nextToken;
	}
	
	public static void main(String[] args){
		String line = "  15*(26+37) - 489/5*61 - (723-8456789)   ";
		System.out.println("line: [" + line + "]");
		TokenIter tokIt = new TokenIter(line);
		// print tokens in square brackets to check absence of white space
		//System.out.println(tokIt.line);
		while(tokIt.hasNext()){
			System.out.println("next token: [" + tokIt.next() + "]");
		}
	}

}
