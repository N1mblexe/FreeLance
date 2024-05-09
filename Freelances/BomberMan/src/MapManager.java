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
    private  MapData currentMap;

    //Encapsulation
    public  MapData getCurrentMap()
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
    private int[][] readArrayFromFile(String filename)
    {
        List<int[]> rows = new ArrayList<>();
        int maxCols = 0;

        try (BufferedReader br = new BufferedReader(new FileReader(filename)))
        {
            String line;
            while ((line = br.readLine()) != null)
            {
                String[] values = line.trim().split(",\\s*");
                int[] row = new int[values.length];
                for (int col = 0; col < values.length; col++)
                {
                    row[col] = Integer.parseInt(values[col]);
                }
                rows.add(row);
                if (values.length > maxCols)
                {
                    maxCols = values.length;
                }
            }
        } catch (IOException ignored) {
            return null;
        }

        int[][] array = new int[rows.size()][maxCols];
        for (int i = 0; i < rows.size(); i++) {
            array[i] = rows.get(i);
        }

        return array;
    }

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
            var v = readArrayFromFile(mapName);
            if(v == null)
                System.out.println("Couldn't find file: " + mapName);
            temp.setData(readArrayFromFile(mapName));
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
