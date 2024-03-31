import javax.crypto.*;
import javax.crypto.spec.*;

import java.io.*;
import java.security.*;

public class AESDecryptiom 
{
    public static void main(String[] args) throws Exception 
    {
        // Define the key and IV
        byte[] keyBytes = "0123456789012345".getBytes("UTF-8");
        byte[] ivBytes = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};

        SecretKeySpec secretKeySpec = new SecretKeySpec(keyBytes, "AES");
        IvParameterSpec ivSpec = new IvParameterSpec(ivBytes);
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        cipher.init(Cipher.DECRYPT_MODE, secretKeySpec, ivSpec);

        File directory = new File("Klasör konumu");
        File[] files = directory.listFiles();
        for (File file : files) 
        {
            if (file.isFile() && file.getName().endsWith(".dat")) 
            {
                FileInputStream inputStream = new FileInputStream(file);
                inputStream.skip(4);
                byte[] inputBytes = new byte[(int) (file.length() - 4)];
                inputStream.read(inputBytes);

                int blockSize = cipher.getBlockSize();
                int inputLength = inputBytes.length;
                int paddingLength = blockSize - (inputLength % blockSize);
                byte[] paddedInputBytes = new byte[inputLength + paddingLength];
                System.arraycopy(inputBytes, 0, paddedInputBytes, 0, inputLength);
                for (int i = inputLength; i < paddedInputBytes.length; i++) 
                {
                    paddedInputBytes[i] = (byte) paddingLength;
                }

                byte[] outputBytes = cipher.doFinal(paddedInputBytes);
                int paddingCount = outputBytes[outputBytes.length - 1];
                int unpaddedLength = outputBytes.length - paddingCount;
                byte[] unpaddedBytes = new byte[unpaddedLength];
                System.arraycopy(outputBytes, 0, unpaddedBytes, 0, unpaddedLength);

                String fileName = file.getName().replace(".dat", ".txt");
                FileOutputStream outputStream = new FileOutputStream("Klasör konumu" + fileName);
                outputStream.write(unpaddedBytes);

                inputStream.close();
                outputStream.close();
            }
        }
    }
}
