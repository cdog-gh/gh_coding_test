import java.util.*;
import java.lang.*;
import java.io.*;
class JoFileSystem{
    private static final Set<String> fileExtensionSet = new HashSet<>();
    
    public static void addSupportExtension(String extension){
        fileExtensionSet.add(extension);
    }
    
    public static boolean getIsSupportedExtension(String extension){
        return fileExtensionSet.contains(extension);
    }
}

class JoFileUtil{
    public static String getName(String filename)
    {
        return filename.substring(
            filename.lastIndexOf('.') + 1
        );
    }
    
    public static String getExtension(String filename)
    {
        if(filename.lastIndexOf('.') == -1)
            return "";
        return filename.substring(
            0, filename.lastIndexOf('.')
        );
    }
}

class JoFile implements Comparable<JoFile>{
    private final String name;
    private final String extension;
    private final String filename;
    
    JoFile(String filename){
        this.filename = filename;
        this.name = JoFileUtil.getName(filename);
        this.extension = JoFileUtil.getExtension(filename);
    }
    
    public String getFileName(){
        return this.filename;
    }
    
    public String getName(){
        return this.name;
    }
    
    public String getExtension(){
        return this.extension;
    }
    
    public String toString(){
        return this.filename;
    }
    
    @Override
    public int compareTo(JoFile another) {
        boolean thisExtensionSupported = JoFileSystem.getIsSupportedExtension(this.extension);
        boolean anotherExtensionSupported = JoFileSystem.getIsSupportedExtension(another.getExtension());
        if(this.name.compareTo(another.getName()) != 0)
            return this.name.compareTo(another.getName());
        if(thisExtensionSupported != anotherExtensionSupported)
            return Boolean.compare(anotherExtensionSupported, thisExtensionSupported);
        return this.extension.compareTo(another.getExtension());
    }
}

public class Main {
    public static void main(String []args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        String []parse;
        List <JoFile> files = new ArrayList<>();
        parse = bf.readLine().split(" ");
        int n = Integer.parseInt(parse[0]);
        int m = Integer.parseInt(parse[1]);
        for(int i=0;i<n;i++)
            files.add(new JoFile(bf.readLine()));
        for(int i=0;i<m;i++)
            JoFileSystem.addSupportExtension(bf.readLine());
        Collections.sort(files);
        StringBuilder sb = new StringBuilder();
        for(JoFile file : files)
            sb.append(file.getFileName() + "\n");
        System.out.println(sb);
    }
}