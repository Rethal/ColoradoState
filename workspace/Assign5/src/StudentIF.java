
public interface StudentIF extends Comparable<StudentIF> {
	
	// The extends here specifies that a class that implements StudentIF
	// both implements the methods below and the compareTo method from
	// the Comparable interface
	
	
	// The constructor (which is not in the interface)
	//    initializes the instance variables  
	//    name, id, totalGrades, grades = new int[totalGrades], 
        //    and numGrades = 0;
	// Constructors cannot appear in interfaces because they are class specific.
	// Interfaces collect methods that represent similar functionality across 
        // classes, while different class constructors behave in different ways.
	
	
	// get name
	public String getName();
	
	// get id
	public int getId();
		
	// compute and return the score: score total / totalGrades
	public double computeScore();
	
	// if grades not full, add newGrade to the next slot in grades and return true
	// else return false
	// update numGrades 
	public boolean addGrade (int newGrade);

	
	
	// compareTo public int compareTo(Student other) 
	// is defined in the Comparable Interface
        // and should compare the student ID's  (they are positive integers).
	// Must be able to handle null "other" students. A null student should be
	// ordered before any student s so the s.compareTo(null) should be positive.
	
	
	
	
	
	// Two students are equal if their IDs are equal (names are not unique)
	// Must be able to handle null "other" students (i.e. not equal to the current student).
	public boolean equals(StudentIF other);
	
}
