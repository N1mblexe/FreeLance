/**
 *
 * @author Yazar adı ve mail
 * @since 2025-04-07
 * <p>
 * Gezegen bilgilerini, zamanını ve nüfus durumunu yöneten Planet sınıfı.
 * </p>
 */


public class Planet implements ISearchable
{
    private final String name;
    private final Time time;
    private int population;

    @Override
    public String getName() { return name; }
    public String getTimestr() { return time.toString(); }
    public Time getTime() { return time; }
    public int getPopulation() { return population; }

    public Time GetFutureTime(int hoursToAdvance) { return time.getFutureTime(hoursToAdvance); }

    public void UpdatePopulation(int amount) { population += (population + amount <= 0) ? -population : amount; }

    public Planet(String name, Time time)
    {
        this.name = name;
        this.time = time;
    }

    @Override
    public String toString() {
        return "Planet{name='" + name +
                "', population=" + population +
                ", time=" + time +"}";
    }
}