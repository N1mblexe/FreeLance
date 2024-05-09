public class Person 
{
    private String name;
    private ContactInfo contactInformation;

    //Parametresiz yapıcı
    public Person() 
    {
        this.name = null;
        this.contactInformation = null;
    }

    //İki parametreli yapıcı
    public Person(String name, ContactInfo contactInformation) 
    {
        this.name = name;
        this.contactInformation = new ContactInfo(contactInformation);
    }

    //Kopyalama constructor
    public Person(Person other) 
    {
        this.name = other.name;
        this.contactInformation = new ContactInfo(other.contactInformation);
    }

    //Leak olmaması için get ve setler
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public ContactInfo getContactInformation() {
        return new ContactInfo(contactInformation);
    }

    public void setContactInformation(ContactInfo contactInformation) {
        this.contactInformation = new ContactInfo(contactInformation);
    }

    //Stringe çevirme
    @Override
    public String toString() 
    {
        return "Adi: " + name + ", Ulasim bilgileri: " + contactInformation.toString();
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
            Person otherPerson = (Person) otherObject;
            return (name.equals(otherPerson.name) && contactInformation.equals(otherPerson.contactInformation));
        }
    }
}
