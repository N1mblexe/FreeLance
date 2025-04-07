/**
 *
 * @author Yazar adı ve mail
 * @since 2025-04-07
 * <p>
 * Bir kişiyi ve simülasyondaki davranışlarını temsil eden Person sınıfı.
 * </p>
 */

public class Person implements IEventListener, ISearchable {
    @Override
    public void SimulationTick(int time)
    {
        lifeTime -= time;

        if (lifeTime <= 0) {
            die();
        }
    }

    public enum State {OnPlanet, OnShip, Dead }

    private String name;
    private int age;
    private int lifeTime;
    private SpaceShip spaceShip;
    private Planet currentPlanet;
    private State state;

    public Person(String name, int age, int lifeTime, SpaceShip spaceShip) {
        this.name = name;
        this.age = age;
        this.lifeTime = lifeTime;
        this.spaceShip = spaceShip;

        spaceShip.addToCrew(this); // Updated method name for consistency

        state = State.OnPlanet;

        currentPlanet = spaceShip.getStartPlanet();
        currentPlanet.UpdatePopulation(1);

        Simulation.addListener(this);
    }

    public State getState() {
        return state;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "Person{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", lifeTime=" + lifeTime +
                ", spaceShip=" + (spaceShip != null ? spaceShip.getName() : "None") +
                ", currentPlanet=" + (currentPlanet != null ? currentPlanet.getName() : "None") +
                ", state=" + state +
                '}';
    }


    private void die() {
        if (currentPlanet != null && state == State.OnPlanet) {
            currentPlanet.UpdatePopulation(-1);
        }

        state = State.Dead;
        spaceShip.checkSelfDestruct();
    }

    public void departure() {
        if (state == State.OnPlanet) {
            state = State.OnShip;
            currentPlanet.UpdatePopulation(-1);
            currentPlanet = spaceShip.getDestination();
        }
    }

    public void reachDestination() throws Exception {
        if (state == State.OnShip) {
            state = State.OnPlanet;
            currentPlanet.UpdatePopulation(1);
        } else {
            throw new Exception("Invalid state transition: Person is not on a ship.");
        }
    }
}
