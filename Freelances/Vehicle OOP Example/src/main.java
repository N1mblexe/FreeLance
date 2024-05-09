public class main {
    public static void main(String[] args) 
    {
        ContactInfo contactInfo = new ContactInfo("London", "123 456 789", "cemyilmaz@example.com");
        Person person = new Person("Cem",  contactInfo);
        Bus bus = new Bus("Ferrari", "06 ABC 123", person, 50, 7);

        System.out.println("Otobusun bilgileri:\n " + bus.toString());
        System.out.println("Motorlu tasit vergisi: " + bus.calculateTax());

        Bus busCopy = new Bus(bus);
        System.out.println("Iki otobus ayni mi? " + bus.equals(busCopy));
    }
}
