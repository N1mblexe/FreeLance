public class ContactInfo 
{
    private String homeAddress;
    private String telNumber;
    private String eMail;
    
    //Constructer
    public ContactInfo() 
    {
        this.homeAddress = null;
        this.telNumber = null;
        this.eMail = null;
    }
    
    //Constructer
    public ContactInfo(String homeAddress, String telNumber, String eMail) 
    {
        this.homeAddress = homeAddress;
        this.telNumber = telNumber;
        this.eMail = eMail;
    }
    
    //Constructer
    public ContactInfo(ContactInfo other) 
    {
        this.homeAddress = other.homeAddress;
        this.telNumber = other.telNumber;
        this.eMail = other.eMail;
    }
    
    //Leak olmaması için get ve setler
    public String getHomeAddress() {
        return homeAddress;
    }
    
    public void setHomeAddress(String homeAddress) {
        this.homeAddress = homeAddress;
    }
    
    public String getTelNumber() {
        return telNumber;
    }
    
    public void setTelNumber(String telNumber) {
        this.telNumber = telNumber;
    }
    
    public String getEMail() {
        return eMail;
    }
    
    public void setEMail(String eMail) {
        this.eMail = eMail;
    }
    
    //Stringe çevirme
    @Override
    public String toString() 
    {
        return "Ev adresi: " + homeAddress + "\n" +
                "Telefon numarasi: " + telNumber + "\n" +
                "E-Mail: " + eMail;
    }
   
    //Eşit olup olmadığını kontrol etme
    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
    
        if (obj == null || getClass() != obj.getClass())
            return false;
    
        ContactInfo other = (ContactInfo) obj;
    
        if (homeAddress != null ? !homeAddress.equals(other.homeAddress) : other.homeAddress != null)
            return false;
    
        if (telNumber != null ? !telNumber.equals(other.telNumber) : other.telNumber != null)
            return false;
    
        return !(eMail != null ? !eMail.equals(other.eMail) : other.eMail != null);
}

}
