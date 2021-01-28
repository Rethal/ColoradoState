
public class BSTNode<T> {

	private T item;
	private BSTNode<T> left;
	private BSTNode<T> right;
	
	// one node, empty children
	public BSTNode(T item){
		this.item = item;
		left = null;
		right = null;
	}
	
	public T getItem(){
		return item;
	}

	public BSTNode<T> getLeft(){
		return left;
	}
	public void setLeft(BSTNode<T> newLeft){
		left = newLeft;
	}
	
	public BSTNode<T> getRight(){
		return right;
	}
	public void setRight(BSTNode<T> newRight){
		right = newRight;
	}
	
	public String toString(){
		if(left==null && right == null)
			return "BST leaf: " + item;
		else
			return "BST internal: " + item;
	}	

	
}

