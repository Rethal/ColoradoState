// IdVal is a String KeyItem 
// Strings are Comparable
public class IdVal extends KeyItem<String> {
	
	private boolean val;
	
	public IdVal(String id, boolean val){
		super(id);
		this.val = val;
	}

	public String toString(){
		return "[" + getKey() + ": " + val+ "]"; 
	}
	
	public boolean getVal(){
		return val;
	}
	
	public static void main(String[] args){
		IdVal iv1 = new IdVal("abc", true);
		IdVal iv2 = new IdVal("bcd", false);
		IdVal iv3 = new IdVal("cde", false);	
		if(iv1.getKey().compareTo(iv2.getKey())<0)
			System.out.println(iv1 + " < " + iv2);
	}
}
