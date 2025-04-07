/**
 *
 * @author Yazar adı ve mail
 * @since 2025-04-07
 * <p>
 * Simülasyon zamanlayıcısına tepki veren sınıflar için arayüz tanımı olan IEventListener arayüzü.
 * </p>
 */


public interface IEventListener
{
    public void SimulationTick(int time);
}
