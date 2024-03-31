package Analyzer;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

/**
*
* @author Yazar adı ve mail
* @since 12.03.2024
* <p>
* Git kullanarak github linki üzerinden dosya klonlamak
* </p>
*/
public class GithubAnalyzer {

    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        try {
            // Kullanıcıdan GitHub deposu URL'sini al
            System.out.print("GitHub Repository URL: ");
            String repositoryURL = reader.readLine();

            // GitHub deposunu klonla
            String targetDirectory = "cloned_repo";
            cloneRepository(repositoryURL, targetDirectory);

            // Klonlanan repo içindeki Java dosyalarını bul ve analiz et
            analyzeJavaFiles(targetDirectory);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Repo'yu git kullanarak hedef dizine clonelamak
     * @param repositoryURL Repo'nun bulunduğu link
     * @param targetDirectory Bilgisayarda kaydedilmesi istenen hedef konum
     */
    private static void cloneRepository(String repositoryURL, String targetDirectory) {
        try {
            String gitCommand = "git clone " + repositoryURL + " " + targetDirectory;
            Process process = Runtime.getRuntime().exec(gitCommand);

            // Git çıktılarını oku ve ekrana yazdır
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            // Hata çıktısını oku ve ekrana yazdır
            BufferedReader errorReader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
            while ((line = errorReader.readLine()) != null) {
                System.out.println(line);
            }

            // Prosesi bekle
            int exitCode = process.waitFor();
            System.out.println("Klonlama işlemi tamamlandı. Çıkış kodu: " + exitCode);

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    /***
     * hedef dizindeki dosyaları analiz etme
     * @param targetDirectory Analiz edilecek dosyaların konumu
     */
    private static void analyzeJavaFiles(String targetDirectory) {
        File directory = new File(targetDirectory);
        File[] javaFiles = directory.listFiles((dir, name) -> name.endsWith(".java"));

        if (javaFiles != null) {
            for (File javaFile : javaFiles) {
                JavaFileAnalyzer.analyzeFile(javaFile.getAbsolutePath());
            }
        } else {
            System.out.println("Belirtilen dizinde (.java) dosyası bulunamadı.");
        }
    }
}
