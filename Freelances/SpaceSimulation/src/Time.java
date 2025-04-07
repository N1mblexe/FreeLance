/**
 *
 * @author Yazar adı ve mail
 * @since 2025-04-07
 * <p>
 * Zaman hesaplamalarını, saat ilerletmelerini ve tarih farklarını yöneten Time sınıfı.
 * </p>
 */

public class Time implements IEventListener
{
    private int year;
    private int month;
    private int day;
    private int hour;
    private int dailyHours;  // Represents the number of hours in a day

    private boolean constTime = false;

    // Constructor accepting year, month, day, and dailyHours
    public Time(int year, int month, int day, int dailyHours)
    {
        this.year = year;
        this.month = month;
        this.day = day;
        this.hour = 0;  // Start at midnight (00:00)
        this.dailyHours = dailyHours;

        if(dailyHours > 0);
            Simulation.addListener(this);
    }

    // Method to advance the time
    public void advanceHours(int hours)
    {
        if(constTime)
            return;

        int totalHours = this.hour + hours;
        int daysToAdd = totalHours / this.dailyHours;
        this.hour = totalHours % this.dailyHours;

        if (daysToAdd > 0) {
            this.day += daysToAdd;

            while (this.day > getDaysInMonth(this.month, this.year)) {
                this.day -= getDaysInMonth(this.month, this.year);
                this.month++;

                if (this.month > 12) {
                    this.month = 1;
                    this.year++;
                }
            }
        }

    }


    private int getDaysInMonth(int month, int year) {
        return switch (month) {
            case 1, 3, 5, 7, 8, 10, 12 -> 31;
            case 4, 6, 9, 11 -> 30;
            case 2 -> 28; // No leap year handling for simplicity
            default -> 0;
        };
    }

    @Override
    public String toString() {
        return this.day +"." +this.month +"." +this.year;
    }

    public int getDailyHours() {
        return this.dailyHours;
    }

    public long timeDifferenceInHours(Time otherTime) {
        int diffInDays = this.calculateTotalDays() - otherTime.calculateTotalDays();
        return diffInDays * this.dailyHours;
    }

    public Time getFutureTime(int hoursToAdvance) {
        Time futureTime = new Time(this.year, this.month, this.day, this.dailyHours);
        futureTime.hour = this.hour;
        futureTime.advanceHours(hoursToAdvance);
        futureTime.constTime = true;
        return futureTime;
    }

    private int calculateTotalDays() {
        return this.year * 365 + this.month * 30 + this.day;
    }

    @Override
    public void SimulationTick(int time) {
        advanceHours(time);
    }
}
