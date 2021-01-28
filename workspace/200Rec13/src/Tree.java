import java.util.Hashtable;

public class Tree {
	private TreeNode root;


	//empty tree
	public Tree(){
		this.root = null;
	}

	// rootItem, empty children
	public Tree(TreeNode root){
		this.root = root;
	}

	public boolean isEmpty(){
		return root==null;
	}

	public void preorderTraverse(){
		if (!isEmpty())
			preorderTraverse(root,"");
		else
			System.out.println("root is null");
	}

	public void preorderTraverse(TreeNode node, String indent){
		System.out.println(indent+node.getItem());
		if(node.getLeft()!=null) preorderTraverse(node.getLeft(),indent+" ");
		if(node.getRight()!=null) preorderTraverse(node.getRight(),indent+" ");

	}
	// if tree empty return null
	// else evaluate the tree by postorder traversal 
	// and return its value
	public Integer postorderEval(){
		Integer res = null;
		if(!isEmpty()){
			res = postorderEval(root);
		}
		return res;
	}
	public Integer postorderEval(String indent, Hashtable<String,Integer> symTab){
		Integer res = null;
		if(!isEmpty()){
			res = postorderEval(root,indent,symTab);
		}
		return res;
	}
	public Integer postorderEval(TreeNode node, String indent, Hashtable<String,Integer> symTab){
		String rootItem = node.getItem();
		Integer sym = symTab.get(rootItem);

		Integer val;
		if(rootItem.equals("+")||rootItem.equals("-")||rootItem.equals("*")||rootItem.equals("/")){
			int left = postorderEval(node.getLeft(),indent,symTab);
			int right = postorderEval(node.getRight(),indent,symTab);
			if (rootItem.equals("+")){
				return left+right;
			}
			if (rootItem.equals("-")){
				return left-right;
			}
			if(rootItem.equals("*")){
				return left*right;
			}
			if(rootItem.equals("/")){
				return left/right;
			}
			return null;
		}
		else if(Character.isLetter(rootItem.charAt(0))){
			return symTab.get(rootItem.charAt(0));
		}
		else 
		{
			try {
				val = Integer.valueOf(rootItem);
				return val;
			} catch ( NumberFormatException nfe )
			{
				return 0;
			}
		}
	}
	private Integer postorderEval(TreeNode root) {
		// TODO Auto-generated method stub
		if(root.getItem().equals("+")||root.getItem().equals("-")||root.getItem().equals("*")||root.getItem().equals("/")){
			int left = postorderEval(root.getLeft());
			int right = postorderEval(root.getRight());
			if (root.getItem().equals("+")){
				return left+right;
			}
			if (root.getItem().equals("-")){
				return left-right;
			}
			if(root.getItem().equals("*")){
				return left*right;
			}
			else{
				return left/right;
			}
		}
		else return Integer.valueOf(root.getItem());
	}
}
