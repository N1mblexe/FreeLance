public class PlantingSpot
{
    GameObject gameObject;
    private int currentStep;
    private int end;

    public boolean gameFinished;

    PlantingSpot()
    {
        gameFinished = false;
        currentStep = 0;
        end = 4;
        gameObject = new GameObject();
    }

    public void next()
    {
        if(++currentStep == end)
            gameFinished = true;
    }

}
