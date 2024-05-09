public abstract class Vehicle 
{
    private String brand;
    private String licencePlate;
    private Person owner;

    //Constructer
    public Vehicle() 
    {
        this.brand = null;
        this.licencePlate = null;
        this.owner = null;
    }

    //Constructer
    public Vehicle(String brand, String licencePlate, Person owner) 
    {
        this.brand = brand;
        this.licencePlate = licencePlate;
        this.owner = new Person(owner);
    }

    //Constructer
    public Vehicle(Vehicle other)
    {
        this.brand = other.brand;
        this.licencePlate = other.licencePlate;
        this.owner = new Person(other.owner); 
    }

    //Leak olmaması için get ve setler
    public String getBrand() {
        return brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }

    public String getLicencePlate() {
        return licencePlate;
    }

    public void setLicencePlate(String licencePlate) {
        this.licencePlate = licencePlate;
    }

    public Person getOwner() {
        return new Person(owner); 
    }

    public void setOwner(Person owner) {
        this.owner = new Person(owner);
    }

    //Vergi hesaplaması için abstract(soyut) metod 
    public abstract int calculateTax();

    //Stringe çevirme
    @Override
    public String toString() 
    {
        return "Marka: " + brand + ", Plaka: " + licencePlate + ", Sahibi: " + owner;
    }

    //Eşit olup olmadığını kontrol etme
    @Override
    public boolean equals(Object otherObject) 
    {
        if (otherObject == null)
            return false;
        else if (getClass() != otherObject.getClass())
            return false;
        else {
            Vehicle otherVehicle = (Vehicle) otherObject;
            return (brand.equals(otherVehicle.brand) && licencePlate.equals(otherVehicle.licencePlate) && owner.equals(otherVehicle.owner));
        }
    }
}
