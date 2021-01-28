
public class Manager extends Engineer {
	
	public Manager(String empName, int empId, int managerID) {
		super(empName, empId, managerID);
	}
	public void handleCrisis(){
		System.out.println("I'm handling a crisis");
	}
	public boolean work(){
		System.out.println("I'm programming");
		return true;
	}
	public String toString() {
		return "Manager "+super.toString();
	}
}
