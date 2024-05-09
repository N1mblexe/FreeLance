import java.util.Objects;

public class Bus extends Vehicle 
{
    private int capacity;
    private int ageOfBus;

    //Constructer
    public Bus() {
        super();
        this.capacity = 0;
        this.ageOfBus = 0;
    }

    //Constructer
    public Bus(String brand, String licencePlate, Person owner, int capacity, int ageOfBus) {
        super(brand, licencePlate, owner);
        this.capacity = capacity;
        this.ageOfBus = ageOfBus;
    }

    //Constructer
    public Bus(Bus bus) {
        super(bus);
        this.capacity = bus.capacity;
        this.ageOfBus = bus.ageOfBus;
    }

    //Leak olmaması için get ve setler
    public int getCapacity() {
        return capacity;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    public int getAgeOfBus() {
        return ageOfBus;
    }

    public void setAgeOfBus(int ageOfBus) {
        this.ageOfBus = ageOfBus;
    }

    //Vergi hesaplaması
    @Override
    public int calculateTax() {
        if (ageOfBus < 5) {
            return 4000;
        } else if (ageOfBus >= 5 && ageOfBus <= 10) {
            return 3000;
        } else {
            return 2000;
        }
    }

    //Stringe çevirme
    @Override
    public String toString() {
        return "Marka: " + getBrand() + "\nPlakasi: " + getLicencePlate() + "\nSahibi: " + getOwner()
                + "\nKapasitesi: " + capacity + "\nOtobusun yasi: " + ageOfBus;
    }

    //Eşit olup olmadığını kontrol etme
    @Override
    public boolean equals(Object otherObject) 
    {
    if (this == otherObject)
        return true;
    if (!(otherObject instanceof Bus)) 
        return false;
    Bus otherBus = (Bus) otherObject; 

    return Objects.equals(getBrand(), otherBus.getBrand())
            && Objects.equals(getLicencePlate(), otherBus.getLicencePlate())
            && Objects.equals(getOwner(), otherBus.getOwner())
            && getCapacity() == otherBus.getCapacity()
            && getAgeOfBus() == otherBus.getAgeOfBus();
}

}
