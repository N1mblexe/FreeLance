package Analyzer;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


/**
*
* @author Yazar adı ve mail
* @since 12.03.2024
* <p>
* Dosyaların analizi ve işlenmesine yarar
* </p>
*/
public class JavaFileAnalyzer {

	/***
	 * Girilen dosya konumundaki dosyayı analiz edip bilgilerini ekrana yazdırır
	 * @param filePath Analiz edilecek dosyanın konumu
	 */
    public static void analyzeFile(String filePath) {
        String code = FileToString(filePath);
        
        int javadocLines = CountJavadocLines(code);
        int otherCommentsLines = CountOtherCommentsLines(code);
        int codeLines = CountCodeLines(code);            
        int functions = CountFunctions(code);
        int LOC = CountLines(code);

        double yorumSapmaYuzdesiHesabi = CalculateMetrics(javadocLines, otherCommentsLines, codeLines, functions);
        DecimalFormat df = new DecimalFormat("#." + "0".repeat(2));
        
        // Çıktıyı ekrana yazdır
        System.out.println("Sınıf: " + filePath);
        System.out.println("Javadoc Satır Sayısı: " + javadocLines);
        System.out.println("Yorum Satır Sayısı: " + otherCommentsLines);
        System.out.println("Kod Satır Sayısı: " + codeLines);
        System.out.println("LOC: " + (LOC));
        System.out.println("Fonksiyon Sayısı: " + functions);
        System.out.println("Yorum Sapma Yüzdesi: % " + df.format(yorumSapmaYuzdesiHesabi));
        System.out.println("----------------------------------------");
    }
    
    /***
     * 
     * @param path dosyanın konumu
     * @return Dosyanın içindeki kodu döndürür
     */
    private static String FileToString(String path)
    {
    	try (BufferedReader reader = new BufferedReader(new FileReader(path))) 
        {
        	String line;
        	StringBuilder code = new StringBuilder();
        	
        	while((line = reader.readLine()) != null)
        	{
        		code.append(line).append("\n");
        	}
        	
        	reader.close();
        	
        	String codeStr = code.toString();
        	
        	return codeStr;
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    	
    	return null;
    }
    
    /**
     * 
     * @param code Kod parçası
     * @return JavaDoc satır sayısı
     */
    private static int CountJavadocLines(String code) {
        int count = 0;
        
        Pattern pattern = Pattern.compile("/\\*\\*.*?\\*/", Pattern.DOTALL);
        Matcher matcher = pattern.matcher(code);

        while (matcher.find()) {
            count += matcher.group().split("\n").length;
        }

        return count - CountFakeJavaDoc(code);
    }
    /**
     * 
     * @param code Kod parçası
     * @return Sahte JavaDoc satır sayısı
     */
    private static int CountFakeJavaDoc(String code)
    {
    	String[] lines = code.split("\n");
    	int fakeCommentCount = 0;
    	boolean inBlockComment = false;
    	
    	for(String line : lines)
    	{
    		if (inBlockComment) 
            {
                if (line.contains("*/")) 
                {
                    inBlockComment = false;
                }
                fakeCommentCount++; 
            } 
            else 
            {
                if (line.contains("\"/**")) 
                {
                    inBlockComment = true;
                    fakeCommentCount++; 
                }

                if (line.contains("*/")) 
                {
                    inBlockComment = false;
                }
            }
    	}
    	return fakeCommentCount;
    }
    
    /**
     * 
     * @param code Kod parçası
     * @return Javadoc harici yorum satırları
     */
    private static int CountOtherCommentsLines(String code)
    {
    	return (CountMultiLineComments(code) + CountSingleLineComments(code) - (CountJavadocLines(code) + CountFakeJavaDoc(code)+ CountFakeComments(code)));
    }
    
    /**
     * 
     * @param code Kod parçası
     * @return Sahte yorum satırı sayısı
     */
    public static int CountFakeComments(String code) 
    {
        String[] lines = code.split("\n");
        int fakeCommentCount = 0;
        boolean inBlockComment = false;

        for (String line : lines) 
        {
            if (inBlockComment) 
            {
                if (line.contains("*/")) 
                {
                    inBlockComment = false;
                }
                fakeCommentCount++; 
            } 
            else 
            {
                if (line.contains("\"/*") && !line.contains("\"/**")) 
                {
                    inBlockComment = true;
                    fakeCommentCount++; 
                }

                if (line.contains("*/")) 
                {
                    inBlockComment = false;
                }

                if (line.contains("\"//")) 
                {
                    fakeCommentCount++;
                }
            }
        }

        return fakeCommentCount;
    }
    /**
     * 
     * @param code Kod parçası
     * @return // ile başlayan yorum satırlarının sayısı
     */
    private static int CountSingleLineComments(String code) 
    {
        int count = 0;
        String[] lines = code.split("\n");

        for (String line : lines) 
        {
            if (line.matches(".*//.*")) 
            {
                count++;
            }
        }

        return count;
    }
    /**
     * 
     * @param code Kod parçası
     * @return /* ile başlayan yorum satırlarının sayısı
     */
    private static int CountMultiLineComments(String code) 
    {
        int count = 0;

        Pattern pattern = Pattern.compile("/\\*.*?\\*/", Pattern.DOTALL);
        Matcher matcher = pattern.matcher(code);

        while (matcher.find()) 
        {
            count += matcher.group().split("\n").length;
        }

        return count;
    }
    
    /**
     * 
     * @param code Kod parçası
     * @return Koddaki tüm satır sayısı
     */
    private static int CountLines(String code)
    {
    	return code.split("\n").length;
    }

    /**
     * Bu metodun amacı, verilen bir kod parçasındaki gerçek işle ilgili satır sayısını bulmaktır.
     * Yorum satırları, boş satırlar ve sadece * karakteri içeren satırlar sayılmaz.
     *
     * @param code Kod parçası
     * @return Gerçek işle ilgili satır sayısı
     */
    private static int CountCodeLines(String code)
    {
    	String[] lines = code.split("\n");
    	int counter = 0;
    	
    	for(String line : lines)
    	{
    		if(!(line.trim().startsWith("/*") || line.trim().startsWith("/**") || line.trim().startsWith("//") || line.trim().isEmpty() || line.trim().startsWith("*")))
    			counter++;
    	}
    	
    	return counter;
    }
    
    /**
     * Bu metodun amacı, verilen bir kod parçasındaki fonksiyon sayısını bulmaktır.
     * Sadece private, public veya protected başlangıcı olan ve parantez içeren satırlar sayılır.
     *
     * @param code Kod parçası
     * @return Kod parçasındaki fonksiyon sayısı
     */
    private static int CountFunctions(String code)
    {
    	String[] lines = code.split("\n");
    	int counter = 0;
    	
    	for(String line : lines)
    	{
    		if((line.trim().startsWith("private") || line.trim().startsWith("public") || line.trim().startsWith("protected")) && line.contains("("))
    			counter++;
    	}
    	return counter;
    }
    /**
     * Bu metodun amacı, belirli metrikleri hesaplamak için kullanılmaktadır.
     * Yorum satırları, diğer yorum türleri, kod satırları ve fonksiyon sayısı parametre olarak alınır.
     * YG ve YH değerleri hesaplanarak sonuç döndürülür.
     *
     * @param javadocLines        Javadoc yorum satırları sayısı
     * @param otherCommentsLines Diğer yorum türleri satırları sayısı
     * @param codeLines           Kod satırları sayısı
     * @param functions           Fonksiyon sayısı
     * @return Hesaplanan metrik değeri
     */
    private static double CalculateMetrics(int javadocLines, int otherCommentsLines, int codeLines, int functions) {
        double YG = ((javadocLines + otherCommentsLines) * 0.8) / functions;
        double YH = (codeLines / (double) functions) * 0.3;
        return ((100 * YG) / YH) - 100;
    }
}
