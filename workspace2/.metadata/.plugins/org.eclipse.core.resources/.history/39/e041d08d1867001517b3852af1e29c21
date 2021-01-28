import java.util.ArrayList;
import java.util.Scanner;

public class In2Post {

	// This class implements the infix to postfix translation

	// Use expQueu to create the postfix expression
	// enque at the end of the queue
	// deque at the front of the queue
	private Queue expQueue;

	// opStack maintains operators
	private Stack opStack;

	// when scanning a next Token, put it in nextToken
	private String nextToken;

	// scLine is the scanner that gets the input line in the constructor
	private TokenIter tokIt;

	public In2Post(String line, boolean debug){
		tokIt = new TokenIter(line);
		opStack  = new Stack(debug);
		expQueue = new Queue(debug);
		//System.out.println("line: " + line);
	}


	// Convert infix to a String postfix, using expQueue and opStack.
	// The workings of In2Post are described in the Queue (L4) lecture notes,
	// and in Prichard Section 7.4 
	public String convertIn2Post() throws StackException, QueueException{
		while(tokIt.hasNext()){
			nextToken=tokIt.next();
			if(nextToken.equals("(")){
				opStack.push("(");
			}
			else if(nextToken.equals(")")){
				while(opStack.peek()!="("){
					expQueue.enqueue(opStack.pop());
				}
				opStack.pop();
			}
			else if(nextToken.equals("*")||nextToken.equals("/")){
				if(opStack.isEmpty()){
					opStack.push(nextToken);
				}
				else{
					while(!opStack.isEmpty()&&!opStack.peek().equals("+")&&!opStack.peek().equals("-")&&!opStack.peek().equals("(")){
						//if(!opStack.isEmpty()&&opStack.peek()!="+"&&opStack.peek()!="-"&&opStack.peek()!="("){
						expQueue.enqueue(opStack.pop());
						//}
						//expQueue.enqueue(nextToken);
					}
					opStack.push(nextToken);
				}
			}
			else if(nextToken.equals("+")||nextToken.equals("-")){
				if(opStack.isEmpty()){
					opStack.push(nextToken);
				}				
				else{
					while(!opStack.isEmpty()&&!opStack.peek().equals("(")){
						//if(!opStack.isEmpty()&&opStack.peek()!="("){
						expQueue.enqueue(opStack.pop());
						//}
						//expQueue.enqueue(nextToken);
					}
					opStack.push(nextToken);
				}	
			}
			else{
				expQueue.enqueue(nextToken);
			}
		}
		while(!opStack.isEmpty()){
			expQueue.enqueue(opStack.pop());
		}
		String go = "";
		while(expQueue.size()!=0){
			go=go+expQueue.dequeue()+" ";
		}
		return go;
	}


	public static void main(String[] args) throws StackException, QueueException{
		// exercise with increasingly complex expressions
		boolean db = false;
		In2Post ex1 = new In2Post("1", db);
		System.out.println(ex1.convertIn2Post());
		In2Post ex2 = new In2Post("1+2", db);
		System.out.println(ex2.convertIn2Post());
	}
}
