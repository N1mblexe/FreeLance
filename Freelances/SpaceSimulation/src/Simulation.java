/**
 *
 * @author Yazar adı ve mail
 * @since 2025-04-07
 * <p>
 * Simülasyonu başlatan, güncelleyen ve kullanıcı etkileşimini yöneten Simulation sınıfı.
 * </p>
 */


import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Simulation {
	//in needed
    private static List<Person> persons;
    private static List<SpaceShip> spaceShips;
    private static List<Planet> planets;

    private static List<IEventListener> listeners;

    static public void addListener(IEventListener listener) {
        listeners.add(listener);
    }

    static public void removeListener(IEventListener listener) {
        listeners.remove(listener);
    }

    static private void PrintStatus()
    {
        PrintHelper.printPlanets(planets);
        System.out.println();
        PrintHelper.printSpaceShips(spaceShips);
    }

    static private void initSimulation()
    {
        listeners = new ArrayList<IEventListener>();

        // Read files
        try {
            planets = FileReader.readPlanets("Gezegenler.txt");
            spaceShips = FileReader.readSpaceShips("Araclar.txt", planets);
            persons = FileReader.readPersons("Kisiler.txt", spaceShips);

            System.out.println("Dosyalar başarıyla okundu.");
        } catch (Exception e) {
            System.out.println("Unable to read file: " + e.getMessage());
            System.exit(0);
        }

        System.out.println("Simulasyon başlatıldı");
    }

    static public void updateSimulation(int hours) {
        if(listeners.isEmpty())
            return;

        for(IEventListener listener : listeners)
            listener.SimulationTick(hours);
    }

    public void RunSimulation()
    {
        Scanner s = new Scanner(System.in);
        int input = 1;
        do {
            PrintHelper.printMenu();

            input = s.nextInt();
            if (input < 0)
                break;
            if (input == 0)
                PrintHelper.clearScreen();

            updateSimulation(input);
            PrintStatus();
        }while (input >= 0);
        s.close();
    }

    public static void main(String[] args) {
        Simulation simulation = new Simulation();
        initSimulation();
        simulation.RunSimulation();
    }
}
