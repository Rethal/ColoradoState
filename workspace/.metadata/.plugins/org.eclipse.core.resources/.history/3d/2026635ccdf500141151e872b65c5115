// This is a starter sketch of the Equation class
// In its current form this code does not compile
// Tree, BST, TokenIter, Exceptions, are missing


public class Equation {

	private boolean debug;

	private String nextToken;	
	private TokenIter itTokens;

	Tree exprTree;

	public Equation(TokenIter iter, boolean debug){
		itTokens = iter;
		this.debug = debug;
		// put the first token from iter in nextToken
		// initial indent ""
		nextTok("");
	}

	private void error(String errMess) throws ParseException{
		throw new ParseException(errMess);

	}
	private void nextTok(String indent){
		if(itTokens.hasNext())
			nextToken = itTokens.next();
		else 
			nextToken = null;
		if(debug)
			System.out.println(indent+"next token: " + nextToken);
	}
	// line parses a line: LHS "=" expr
	// lhs = identifier
	// and returns a Symbol (identifier + value) and stores it in the symbol table
	public Symbol line(BST symbolTable) throws BSTException, ParseException{
		String expression = null;
		TreeNode root;
		exprTree = null;
		Symbol lhsVal = null; // Symbol to be returned
		if(nextToken==null)
			return null;
		else {
			if(debug)
				System.out.println("line");				
			// scan left hand side String lhs
			// if it is not an identifier
			// call	error("Identifier expected");
			String lhs = nextToken;

			// if no next token
			// call	error("unexpected end of line");
			if(!itTokens.hasNext())
				error("unexpected end of line");
			// scan "="
			// if not "=" call error("= expected");
			nextTok("");
			String eq = nextToken;
			if(!eq.equals("="))
				error("= expected");
			// parse expression and create expression tree
			nextTok("");
			//if(!itTokens.hasNext()){
				root = expr("");
				exprTree=new Tree(root);
			//}
			// evaluate Expression tree
			int value = exprTree.postorderEval("m", symbolTable);
			// create lhsVal Symbol (lhs, value)
			lhsVal=new Symbol(lhs,value);
			// insert lhsVal in symbolTable
			symbolTable.insertItem(lhsVal);
			if(debug)
				System.out.println("retrieving " + lhs + ": " + symbolTable.retrieveItem(lhs));
			if(nextToken!=null){
				error("end of line expected");
				return null; 
			} else 
			return lhsVal;
		}
	}
	private TreeNode expr(String indent) throws ParseException{
		if(debug)
			System.out.println(indent+"expr");

		TreeNode left = term(indent+" ");
		while(nextToken != null&& (nextToken.equals("+")||nextToken.equals("-")) ){
			String op = nextToken;
			if (debug)
				System.out.println(indent+"addOp: true");
			nextTok(indent+" ");
			TreeNode right = term(indent+" ");
			if ( (right.getItem().equals("+")||right.getItem().equals("-") ) && right.getLeft() == null && right.getRight() == null ) throw new ParseException();
			left = new TreeNode(op,left, right);
		}
		return left;
	}
	private TreeNode factor(String indent) throws ParseException{
		if(debug)
			System.out.println(indent + "factor");
		if (nextToken == null ) throw new ParseException();
		if(nextToken.equals("(")){
			nextTok(indent+" ");
			TreeNode E = expr(indent+" ");
			if(nextToken.equals(")") )
				nextTok(indent+" ");
			else
				error(") expected");
			return E;
		}
		else if(Character.isDigit(nextToken.charAt(0)))
			return number(indent+" ");
		else
			return identifier(indent+" ");
	}
	private TreeNode term(String indent) throws ParseException{
		if(debug)
			System.out.println(indent+ "term");
		TreeNode left = factor(indent+" ");
		while(nextToken != null&& (nextToken.equals("*")||nextToken.equals("/")) ){
			String op = nextToken;
			if (debug)
			   System.out.println(indent+"mulOp: true");
			nextTok(indent+" ");
			TreeNode right = factor(indent+" ");
			left = new TreeNode(op,left, right);
		}
		return left;
	}
	private TreeNode identifier(String indent) throws ParseException{
		if(debug)
			System.out.println(indent+"identifier");
		String id = nextToken;
		nextTok(indent);
		return new TreeNode (id);
	}
	private TreeNode number(String indent) throws ParseException{
		if(debug)
			System.out.println(indent + "number");
		if(Character.isDigit(nextToken.charAt(0))){
			String num = nextToken;
			nextTok(indent);
			return new TreeNode(num);
		}
		else {
			error("number expected");
			return null; //not
		}
	}
}