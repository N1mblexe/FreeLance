import Game.BomberMan;

public class Main {
    public static void main(String[] args)
    {
        //Oyunu oynamak için gerekenler sadece 1 adet BomberMan.BomberMan sınıfından obje oluşturma ve run fonksiyonunu çağırmaktır

        BomberMan game = new BomberMan();
        game.run();
    }
}