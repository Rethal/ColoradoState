
public class SignThenDriveEvent {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Vehicle v = new Vehicle("Red");
		System.out.println(v);
		
		Vehicle car = new Aveo("Black", 43234);
		System.out.println(car);
		
		if (v.equals(car)) {
			System.out.println("v == car");
		} else {
			System.out.println("v != car");
		}
		
    v.move();
		car.move();

		SR71 blackBird = new SR71(20000);
		if (car.equals(blackBird)) {
			System.out.println("car == blackBird");
		} else {
			System.out.println("car != blackBird");
		}

    blackBird.move();	
    System.out.println(car.getColor());	

	}

}
