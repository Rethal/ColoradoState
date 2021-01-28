import java.io.File;
import java.io.FileNotFoundException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class StudentRecords {

	public static String readString(Scanner scan) throws NoSuchElementException {
		return scan.next();	
	}

	public static int readInt(Scanner scan) throws NoSuchElementException {
		return scan.nextInt();	
	}

	/**
	 * @param args: coursefile #grades
	 * @throws FileNotFoundException 
	 */
	public static void main(String[] args) throws FileNotFoundException {
		String course=args[0];	
		int totGrades=Integer.parseInt(args[1]);

		System.out.println("Course " + course + ": " + 
				totGrades   + " grades");


		Scanner scan = new Scanner( new File (course));	
		String name;
		int id;
		String NorX;
		StudentCollectionIF sDB = new StudentLL(course,false);
		int grade;
		while(scan.hasNext()) { 
			name = readString(scan);
			id =   readInt(scan);
			NorX = readString(scan);
			StudentIF s;
			if (NorX.equals("N"))
				s = new Student(name,id,totGrades);
			else
				s = new XcelStudent(name,id,totGrades,NorX);
			for(int j=0;j<totGrades;j++){
					grade = scan.nextInt();
					s.addGrade(grade);
			}
			sDB.insort(s);
		}
		System.out.println("Top Score: " + sDB.classTopScore());
		System.out.println("Avg Score: " + sDB.classAvg());
        System.out.println(sDB);
	}
}
