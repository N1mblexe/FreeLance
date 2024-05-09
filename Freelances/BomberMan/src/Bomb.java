//Bu sınıf bomba oluşturmak için kullanılır
public class Bomb extends MonoBehaviour
{
    //Yarıçap , patlama süresi ve bombanın konumunu içerir
    private int radius;
    private int lifeTime;
    private Vector2 currPos;

    //Constructor (yapıcı metot) ile gerekli atamalar yapılır
    public Bomb(Vector2 pos , int radius)
    {
        // super(); kodu kalıtım aldığı (Monobehaviour) sınıfının constructor'unu çağırır  (Tip : ctrl'ye basılı tutarak super();'e tıklarsanız sizi o fonksiyona götürür)
        super();

        lifeTime = 4;
        currPos = pos;
        this.radius = radius;
    }

    //Monobehaviuour'dan kalıtım aldığımız Update sınıfı
    @Override
    public void Update()
    {
        //Her bir tur geçtiğinde patlama süresini bir azalt (0 olduğunda patlama (Exlpode()) fonksiyonunu çağır)
        if(lifeTime-- == 0)
            Explode();
    }

    //Bu fonksiyonu bombanın konumuna bağlı olarak bombanın patlamasına yarar
    private void Explode()
    {
        //Şu an oynanan mapin verilerini MapManager'dan al
        MapData map = MapManager.Instance.getCurrentMap();

        //Yarıçapı kadar döngüye al
        for(int i = -radius;i < radius;i++)
        {
            //Hem x ekseni hemde y ekseni için patlayacak konumu hesapla
            Vector2 px = Vector2.Addition(currPos , new Vector2(i,0));
            Vector2 py = Vector2.Addition(currPos , new Vector2(0,i));
            try {

                //Patlayacak konumda kırılabilir duvar varsa orayı boş olarak ayarla
                if(map.getDataAtPosition(px) == ID.breakableWall.ordinal())
                    map.setDataToPosition(px , ID.empty.ordinal());
                if(map.getDataAtPosition(py) == ID.breakableWall.ordinal())
                    map.setDataToPosition(py , ID.empty.ordinal());
                if(map.getDataAtPosition(px) == ID.player.ordinal() || map.getDataAtPosition(py) == ID.player.ordinal())
                    BomberMan.Instance.LoseGame("You died to a bomb");

            }catch (Exception ignored){}
        }

        //Bombanın olduğu konumuda boş olarak ayarla (bomba patladığı için orası boş olması gerekiyor)
        map.setDataToPosition(currPos , ID.empty.ordinal());
    }
}
