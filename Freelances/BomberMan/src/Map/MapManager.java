package Map;

import Behaviour.MonoBehaviour;
import Game.FileManager;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class MapManager extends MonoBehaviour
{
    //Burdaki Instance yapısı çok önemlidir
    //Bir sınıftan sadece 1 tane obje üretileceği zaman kullanılır
    //Erişim kolaylığı sağlar (Herhangi bir şekilde statik değişkeni çağırarak tek olan objeye erişebilirim)
    //Daha fazla bilgi için "singleton" yapısını araştırabilirsiniz
    public static MapManager Instance;

    //Dosyaların adı burda saklanır
    private String[] mapFileNames;
    private int currentMapId;


    //Constructor metod ile hem Instance doldururlur hemde mapler için dosya adları alınır
    public MapManager(String[] mapFileNames)
    {
        this.mapFileNames = mapFileNames;

        if(Instance == null)
            Instance = this;
    }

    //Maplar HashMap'de saklanır <Dosya adı, Map verisi>
    private HashMap<String , MapData> mapPool;
    //Şu an oynanan map currentMap ile tutulur
    private MapData currentMap;

    //Encapsulation
    public MapData getCurrentMap()
    {
        return currentMap;
    }


    public boolean NextMap()
    {
        try {
            var v = mapFileNames[++currentMapId];

            currentMap = mapPool.get(v);
            return true;
        }catch (Exception ignored){
            currentMapId--;
            return false;
        }
    }

    //Girilen map adı varsa şu an oynanan mapi günceller
    //eğer yoksa false döndürür
    public boolean setCurrentMap(String mapName)
    {
        currentMap = mapPool.get(mapName);

        if(currentMap == null || currentMap.data == null)
            return false;

        return  true;
    }

    //Girilen dosya adında bir dosya varsa içerisindeki veriyi okuyup iki boyutlu bir diziye atan fonksiyon


    //Monobehaviour'dan kalıtım alınan Init sınıfı kullanılarak map verilerini dosyadan çekip hashMap'a atıyor
    @Override
    public void Init()
    {
        mapPool = new HashMap<>();

        currentMap = new MapData();
        //currentMap.setTestData();

        for(var mapName : mapFileNames)
        {
            MapData temp = new MapData();
            var v = FileManager.instance.readMapFromFile(mapName);
            if(v == null)
                System.out.println("Couldn't find file: " + mapName);
            temp.setData(FileManager.instance.readMapFromFile(mapName));
            mapPool.put(mapName , temp);
        }

        currentMapId = 0;
        currentMap = mapPool.get(mapFileNames[currentMapId]);
    }

    //HashMap'de bulunan mapleri key değerlerine göre ekrana yazdırır
    public void ListMaps()
    {
        Set<String> keys = mapPool.keySet();

        int id = 0;
        Iterator<String> iterator = keys.iterator();
        while (iterator.hasNext()) {
            String key = iterator.next();
            System.out.println(id++ + " : " + key);
        }
    }
}
