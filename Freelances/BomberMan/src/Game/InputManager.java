package Game;

import PlayerPackage.EPlayerAction;

import java.io.File;
import java.util.Scanner;

//input'u daha anlaşılır ve rahat almak için bu sınıf kullanılır
public class InputManager
{
    public static class InputSettings
    { char[] moveKeys;
        char bombPlaceKey;
        char abilityKey;

        static public InputSettings DefaultInputSettings()
        {
            InputSettings inputSettings = new InputSettings();

            inputSettings.moveKeys = new char[]{'A', 'D', 'W', 'S'};
            inputSettings.bombPlaceKey = 'E';
            inputSettings.abilityKey = 'Q';

            return inputSettings;
        }

        public void setSettings(char[] keys)
        {
            this.moveKeys = new char[]{keys[0] , keys[1] , keys[2] , keys[3]};
            this.bombPlaceKey = keys[4];
            this.abilityKey = keys[5];
        }
    }

    static private InputSettings inputSettings = new InputSettings();

    public InputManager()
    {
        try
        {
            inputSettings = FileManager.instance.GetInputSettings();
        }catch (Exception e)
        {
            inputSettings = InputSettings.DefaultInputSettings();
        }
    }

    static private Vector2 playerVelocity = new Vector2();
    static public EPlayerAction getInput()
    {
        Scanner console = new Scanner(System.in);
        String inputStr = console.next();

        char in = inputStr.charAt(0);

        char[] mKeys = inputSettings.moveKeys;
        char bKey = inputSettings.bombPlaceKey;
        char aKey = inputSettings.abilityKey;

        if(CheckMoveKeys(in))
        {
            playerVelocity = new Vector2();

            if(in == mKeys[0] || in == Character.toUpperCase(mKeys[0])) playerVelocity.y = -1;   //A
            if(in == mKeys[1] || in == Character.toUpperCase(mKeys[1])) playerVelocity.y = 1;    //D
            if(in == mKeys[2] || in == Character.toUpperCase(mKeys[2])) playerVelocity.x = -1;   //W
            if(in == mKeys[3] || in == Character.toUpperCase(mKeys[3])) playerVelocity.x = 1;    //S

            return EPlayerAction.move;
        }
            else if(in == bKey || in == Character.toUpperCase(bKey))
            return EPlayerAction.setBomb;
        else if(in == aKey || in == Character.toUpperCase(aKey))
            return  EPlayerAction.useAbility;
        else
            return EPlayerAction.undefinedInput;
    }
    static private boolean CheckMoveKeys(char in)
    {
        char[] mKeys = inputSettings.moveKeys;

        return in == mKeys[0] || in == mKeys[1] || in == mKeys[2] || in == mKeys[3] ||
                in == Character.toUpperCase(mKeys[0]) ||
                in == Character.toUpperCase(mKeys[1]) ||
                in == Character.toUpperCase(mKeys[2]) ||
                in == Character.toUpperCase(mKeys[3]);
    }

    /**
     * Bu fonksiyondan hemen önce getInput fonksiyonu kullanılmalıdır
     * DIKKAT: bu fonksyion sorumluluk alarak kullanılmalı ve edge case'leri iyi kontrol edilmelidir
     * @return playerVelocity
     */
    public static Vector2 GetVelocity(){
        return playerVelocity;
    }

}
