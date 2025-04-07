/**
 *
 * @author Yazar adı ve mail
 * @since 2025-04-07
 * <p>
 * Uzay gemilerini, bunların durumlarını, hareketlerini ve mürettebatlarını yöneten SpaceShip sınıfı.
 * </p>
 */


import java.util.ArrayList;
import java.util.List;

public class SpaceShip implements ISearchable, IEventListener {

    public enum State {
        WAITING, ON_ROAD, REACHED, SELF_DESTRUCT
    }

    private final String name;
    private final Planet from;
    private final Planet to;
    private final Time departureDate;
    private final Time desiredArrivalDate;

    private int timeRemaining;
    private State state;
    private final List<Person> crew;

    public SpaceShip(Planet from, Planet to, String name, Time departureDate, int timeRemaining) {
        this.name = name;
        this.from = from;
        this.to = to;
        this.departureDate = departureDate;
        this.timeRemaining = timeRemaining;
        this.state = State.WAITING;
        this.crew = new ArrayList<>();
        this.desiredArrivalDate = calculateDesiredArrivalDate();

        Simulation.addListener(this);
    }

    private Time calculateDesiredArrivalDate() {
        return to.GetFutureTime(timeRemaining);
    }

    public String getName() {
        return name;
    }

    public String getStateDescription() {
        return switch (state) {
            case ON_ROAD -> "Yolda";
            case REACHED -> "Vardı";
            case WAITING -> "Bekliyor";
            case SELF_DESTRUCT -> "IMHA!!";
        };
    }

    public String getRemainingTime() {
        return String.valueOf(timeRemaining);
    }

    public String getArrivalDate() {
        return desiredArrivalDate.toString();
    }

    public Planet getStartPlanet() {
        return from;
    }

    public Planet getDestination() {
        return to;
    }

    public void addToCrew(Person person) {
        crew.add(person);
    }

    public void checkSelfDestruct() {
        boolean allAlive = crew.stream().allMatch(p -> p.getState() != Person.State.Dead);
        if (!allAlive) {
            triggerSelfDestruct();
        }
    }

    @Override
    public void SimulationTick(int time) {
        if (shouldDepart()) {
            depart();
        }

        if (state == State.ON_ROAD) {
            timeRemaining -= time;

            if (timeRemaining <= 0) {
                timeRemaining = 0;
                reachDestination();
            }
        }
    }

    private boolean shouldDepart() {
        return state == State.WAITING &&
                from.getTime().timeDifferenceInHours(departureDate) >= 0;
    }

    private void depart() {
        state = State.ON_ROAD;
        crew.forEach(Person::departure);
    }

    private void reachDestination() {
        state = State.REACHED;
        try {
            for (Person person : crew) {
                person.reachDestination();
            }
        } catch (Exception e) {
            System.err.println("Error during reaching destination: " + e.getMessage());
        }
    }

    private void triggerSelfDestruct() {
        state = State.SELF_DESTRUCT;
    }

    @Override
    public String toString() {
        return String.format(
                "SpaceShip{name='%s', state=%s, from='%s', to='%s', timeRemaining=%d, crewSize=%d, departureTime=%s}",
                name, state, from.getName(), to.getName(), timeRemaining, crew.size(), departureDate
        );
    }
}
