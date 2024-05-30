package Game;

import Map.MapData;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class FileManager
{
    public static FileManager instance;

    private String settingsFile , displayFile;
    public FileManager(String settingsFile , String displayFile)
    {
        if(instance == null)
            instance = this;


        this.settingsFile = settingsFile;
        this.displayFile = displayFile;
    }

    public MapData.DisplaySettings GetDisplaySettings() throws Exception
    {
        BufferedReader br = new BufferedReader(new FileReader(displayFile));

        String line = br.readLine();

        String[] vals = line.split(",");

        MapData.DisplaySettings ds = new MapData.DisplaySettings();

        ds.setSettings(vals);

        return ds;
    }

    public InputManager.InputSettings GetInputSettings() throws Exception
    {
        BufferedReader br = new BufferedReader(new FileReader(settingsFile));

        char[] vals = br.readLine().toCharArray();

        InputManager.InputSettings inputSettings = new InputManager.InputSettings();

        inputSettings.setSettings(vals);

        return inputSettings;
    }

    public int[][] readMapFromFile(String filename)
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
}
