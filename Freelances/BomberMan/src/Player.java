//Bu sınıf Oyuncuyu temsil eder ve temel özelliklerini ve metodlarını taşır
public class Player extends MonoBehaviour
{
    //Karakterin : konumu , mape başlama konumunu , baktığı yönü , kaç adım attığını , bomba patlatma yarıçapını tutar
    private Vector2 position;
    private Vector2 SpawnPos;
    private Vector2 dir;
    private int stepAmount = 0;
    private int  bombRadius = 2;

    public int maxStep;

    Bomb currBomb = null;
    //Constructor ile player'in konumu başlangıç pozisyonu gibi değerleri doldur
    Player(int maxStep)
    {
        this.maxStep = maxStep;
        this.position = new Vector2();
        SpawnPos = new Vector2(5,5);
        dir = new Vector2(1 , 0);
    }

    //Karkateri map'in spawn konumuna göre spawn eden fonksiyon
    boolean SpawnPlayer(MapData mapData) throws Exception
    {
        SpawnPos = mapData.playerSpawnPos;

        if (mapData.getDataAtPosition(SpawnPos) != ID.spawnPos.ordinal())
            return false;

        position = SpawnPos;
        mapData.setDataToPosition(SpawnPos , ID.player.ordinal());

        return true;
    }

    //Karakterin haraketini ve bomba kurmasını sağlayan fonksiyon
    protected boolean Move(MapData mapData) throws Exception {
        if(maxStep <= 0)
            BomberMan.Instance.LoseGame("Out of steps!!");

        Vector2 in = new Vector2();

        //InputManager'dan inputu al
        try {in = InputManager.getInput();}
        catch (Exception bomb)
        {
            //Eğer exception yakalanırsa (bu da bomba tuşuna basıldığı anlamına geliyor) bomba kurma fonksiyonunu çağır
            PlaceBomb();
            maxStep--;
            return false;
        }
        //Baktığı yönü güncelle
        dir = in;
        Vector2 temp = Vector2.Addition(position ,in);

        try {
            //karakterin sonraki adımını atmaya çalıştığı yer boşsa karakteri oraya götür
            if (mapData.isPositionValid(temp) && mapData.getDataAtPosition(temp) != ID.wall.ordinal())
            {
                maxStep--;
                int nextPos = mapData.getDataAtPosition(temp);
                //Eğer sonraki konum çıkışsa oyunu kazandır
                if(nextPos == ID.exit.ordinal())
                    return true;
                if(nextPos == ID.empty.ordinal())
                    Step(mapData , temp);
            }
        }
        catch (Exception ignored) {}
        return false;
    }
    //Karakterin baktığı yöne doğru 1 birim ileri bomba kuran fonksiyon
    private void PlaceBomb() throws Exception
    {
        //konumu hesapla ve boş mu kontrol et
        Vector2 bombPos = Vector2.Addition(position , dir);
        if (MapManager.Instance.getCurrentMap().getDataAtPosition(bombPos) != ID.empty.ordinal())
            return;

        //Yeni bir bomba oluşturuyor
        Bomb bomb = new Bomb(bombPos , bombRadius);

        //Bombayı map verisine ekliyor
        MapManager.Instance.getCurrentMap().setDataToPosition(bombPos , ID.bomb.ordinal());
    }
    //Karakteri istenilen konuma taşır
    private void Step(MapData mapData , Vector2 temp)
    {
        //Önceki pozisyonunu temizliyor
        mapData.setDataToPosition(position , ID.empty.ordinal());

        //Yeni konumu ayarlıyor ve konumunu güncelliyor
        position = temp;
        mapData.setDataToPosition(temp , ID.player.ordinal());

        stepAmount++;
    }
}
