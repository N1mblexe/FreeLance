package Game;

import Behaviour.MonoBehaviour;
import Map.ID;
import Map.MapData;
import Map.MapManager;
import PlayerPackage.Player;

import java.util.Random;

//Bu sınıf bomba oluşturmak için kullanılır
public class Bomb extends MonoBehaviour
{
    //Yarıçap , patlama süresi ve bombanın konumunu içerir
    private int radius;
    private int lifeTime;
    public Vector2 currPos;

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

    public void setPosition(MapData map , Vector2 newPos)
    {
        try
        {
            if(     map.getDataAtPosition(currPos) == ID.bomb.ordinal() &&
                    map.getDataAtPosition(newPos) == ID.empty.ordinal())
            {
                map.setDataToPosition(currPos , ID.empty.ordinal());

                currPos = newPos;
                map.setDataToPosition(currPos , ID.bomb.ordinal());
            }
        } catch (Exception e) {return;}
    }

    //Bu fonksiyonu bombanın konumuna bağlı olarak bombanın patlamasına yarar
    private void Explode()
    {
        //Şu an oynanan mapin verilerini Map.MapManager'dan al
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
                    BreakWall(map , px);
                if(map.getDataAtPosition(py) == ID.breakableWall.ordinal())
                    BreakWall(map , py);
                if(map.getDataAtPosition(px) == ID.player.ordinal() || map.getDataAtPosition(py) == ID.player.ordinal())
                    BomberMan.Instance.LoseGame("You died to a bomb");

            }catch (Exception ignored){}
        }

        //Bombanın olduğu konumuda boş olarak ayarla (bomba patladığı için orası boş olması gerekiyor)
        map.setDataToPosition(currPos , ID.empty.ordinal());

        Player.instance.deleteBomb();
    }

    private void BreakWall(MapData mapData , Vector2 pos)
    {
        Random random = new Random();
        int min = ID.runPower.ordinal();
        int max = ID.shieldPower.ordinal();

        ID data = ID.empty;

        if(random.nextInt(4) == 2)
        {
            ID randomAbility = ID.fromInteger(random.nextInt((max - min) + 1) + min);

            data = randomAbility;
        }

        mapData.setDataToPosition(pos , data.ordinal());
    }
}
