
public class StudentLLNode{

	private StudentIF std;
	private StudentLLNode next;
	
	public StudentLLNode (StudentIF newStd){
		std = newStd;
		next = null;
	}
	
	public StudentLLNode (StudentIF newStd, StudentLLNode nextNode){
		std = newStd;
		next = nextNode;
	}
	
	public StudentIF getStd(){
		return std;
	}
	
	public StudentLLNode getNext(){
		return next;
	}
	
	
	public void setStd(StudentIF newStd){
		std = newStd;
	}
	
	public void setNext(StudentLLNode nextNode){
		next = nextNode;
	}
	
	public String toString(){
		return std.toString();
	}
	
	public static void main(String[] args) {
	 // TODO Auto-generated method stub
         StudentLLNode jess = new StudentLLNode(new Student("Jess",123,4));
         StudentLLNode john = new StudentLLNode(new Student("John",234,4), jess);
         StudentLLNode jane = new StudentLLNode(new Student("Jane",345,4), john);
         
         System.out.println("First sweep:");
         for(StudentLLNode curr = jane; curr != null; curr = curr.next)
        	 System.out.println(curr);
         
         jane.setNext(jess);
         
         System.out.println("\n\nSecond sweep:");
         for(StudentLLNode curr = jane; curr != null; curr = curr.next)
        	 System.out.println(curr);
         
         System.out.println("\n\nThird sweep:");
         for(StudentLLNode curr = john; curr != null; curr = curr.next)
        	 System.out.println(curr);
	}

}
