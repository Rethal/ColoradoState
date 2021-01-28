
public class Vehicle {
	protected String color;


	public Vehicle(String color) {
		this.color = color;
	}

  public String getColor(){
    return this.color;
  }

	public String toString() {
		return "color: " + color;
	}

	public boolean equals(Object other) {
		if (other instanceof Vehicle) {
			return equals((Vehicle)other);
		}
		return false;
	}

	public boolean equals(Vehicle other) {
		return other != null && color.equals(other.color);
	}
	
	public void move() {
		System.out.println("Vehicle: how do I move...?");
	}
}
