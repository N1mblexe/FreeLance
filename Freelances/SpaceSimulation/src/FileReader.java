/**
 *
 * @author Yazar adı ve mail
 * @since 2025-04-07
 * <p>
 * Dosyalardan gezegen, uzay gemisi ve kişi verilerini okuyarak uygun nesne listeleri oluşturan FileReader sınıfı.
 * </p>
 */


import java.io.*;
import java.util.*;

class FileReader {

    public static List<Person> readPersons(String filePath, List<SpaceShip> ships) throws Exception
    {
        List<Person> kisiler = new ArrayList<>();

        BufferedReader br = new BufferedReader(new java.io.FileReader(filePath));

            String line;
            while ((line = br.readLine()) != null)
            {

                String[] data = line.split("#");
                String name = data[0];

                int age = Integer.parseInt(data[1]);
                int lifeTime = Integer.parseInt(data[2]);

                SpaceShip spaceShip = ISearchable.SearchInList(ships , data[3]);

                if (spaceShip != null)
                    kisiler.add(new Person(name, age, lifeTime, spaceShip));

            }
            br.close();
        return kisiler;
    }

    public static List<SpaceShip> readSpaceShips(String filePath, List<Planet> planets) throws Exception
    {
        List<SpaceShip> araclar = new ArrayList<>();
        BufferedReader br = new BufferedReader(new java.io.FileReader(filePath));
            String line;
            while ((line = br.readLine()) != null)
            {
                String[] data = line.split("#");
                String name = data[0];
                Planet from = ISearchable.SearchInList(planets , data[1]);
                Planet to =   ISearchable.SearchInList(planets , data[2]);

                String[] date = data[3].split("\\.");

                Time departureDate = new Time(  Integer.parseInt(date[2]),
                                                Integer.parseInt(date[1]),
                                                Integer.parseInt(date[0]),
                                                -1);

                int timeRemaining = Integer.parseInt(data[4]);

                if (from != null && to != null) {
                    araclar.add(new SpaceShip(from, to, name, departureDate, timeRemaining));
                }
            }
            br.close();
        return araclar;
    }

    public static List<Planet> readPlanets(String filePath)throws Exception
    {
        List<Planet> gezegenler = new ArrayList<>();
        BufferedReader br = new BufferedReader(new java.io.FileReader(filePath));
            String line;
            while ((line = br.readLine()) != null)
            {
                String[] data = line.split("#");
                String name = data[0];
                int hoursPerDay = Integer.parseInt(data[1]);

                String[] date = data[2].split("\\.");

                Time time = new Time(   Integer.parseInt(date[2]),
                                        Integer.parseInt(date[1]),
                                        Integer.parseInt(date[0]),
                                        hoursPerDay);

                gezegenler.add(new Planet(name, time));
            }
            br.close();
            
        return gezegenler;
    }
}
