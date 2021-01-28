
public class XcelStudent extends Student {
	String projectGrade = "";
	int totalGrades;
	int id;
	String name;
	public XcelStudent(String name, int id, int totalGrades, String projectGrade){
		super(name, id, totalGrades);
		this.projectGrade = projectGrade;
		this.totalGrades = totalGrades;
		this.name = name;
		this.id = id;
	}

	public double computeScore(){
		double total = super.computeScore();
		if(projectGrade.equals("A")){
			return total+4;
		}
		else if(projectGrade.equals("B")){
			return total+2;
		}
		else if(projectGrade.equals("C")){
			return total+1;
		}
		else return total;
	}
	public String toString(){
		String string = super.toString()+" project: "+projectGrade;
		return string;
	}
}
