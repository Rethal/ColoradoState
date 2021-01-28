

public class BST {
	// this Binary Search Tree is used for the implementation of the 
	// symbol tables containing Symbols: (key,value) pairs
	// A Symbol is a Comparable object containing a String Identifier key  
	// and an Integer value 
	private BSTNode<Symbol> root;

	//empty tree
	public BST(){
		this.root = null;
	}

	public boolean isEmpty(){
		return root==null;
	}

	public void insertItem(Symbol item) throws BSTException{
		root = insertItem(root, item);
	}

	private BSTNode<Symbol> insertItem(BSTNode<Symbol> node, Symbol item) throws BSTException{
		BSTNode<Symbol> start = new BSTNode<Symbol>(item);
		if(isEmpty()){
			return start;
		}
		else{
			String itemsKey =item.getKey();
			String nodesKey= node.getItem().getKey();
			int compare = itemsKey.compareTo(nodesKey);
			if(compare<0){
				BSTNode<Symbol> left = node.getLeft();
				if(left==null){
					node.setLeft(start);
				}
				else{
					insertItem(left,item);
				}
				//else if(node.getRight()==null){
				//	insertItem(node.getRight(),item);
				//}
				//node.setLeft(start);
				return root;
			}
			else if(compare>0){
				//insertItem(node,item);
				//node.setRight(insertItem(node.getRight(),item));
				if(node.getRight()==null){
					node.setRight(start);
				}
				else{
					insertItem(node.getRight(),item);
				}
				return root;
			}

			else return null;}
	}

	public Symbol retrieveItem(String key){
		return retrieveItem(root,key);
	}

	private Symbol retrieveItem(BSTNode<Symbol> node, String key){
		if(isEmpty()){
			return null;
		}
		else{
			Symbol nodesItem = node.getItem();
			String nodesKey = nodesItem.getKey();
			int compare = key.compareTo(nodesKey);
			if(compare==0){
				return nodesItem;
			}
			else if(compare<0){
				BSTNode <Symbol> left = node.getLeft();
				if(left==null){
				}
				else{
				return retrieveItem(left,key);
				}
			}
			else{
				BSTNode <Symbol> right = node.getRight();
				if(right==null){
				}
				else{
				return retrieveItem(right,key);
				}
			}
		}
		return null;
	}


	public void preorderTraverse(){
		if (!isEmpty())
			preorderTraverse(root,"");
		else
			System.out.println("root is null");
	}

	public void preorderTraverse(BSTNode<Symbol> node, String indent){
		System.out.println(indent+node.getItem());		
		if(node.getLeft()!=null) {
			System.out.println(indent+"left");
			preorderTraverse(node.getLeft(),indent+" ");
		}

		if(node.getRight()!=null) {
			System.out.println(indent+"right");
			preorderTraverse(node.getRight(),indent+" ");
		}
	}



}
