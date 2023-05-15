package SD_Frame;
import java.sql.Connection;
import java.sql.DriverManager;

public class DBConnector {
    static Connection conn;
    
    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost/uas_sd";
    static final String USER = "root";
    static final String PASSWORD = "";
    
    public static void initDBConnection(){
        try {
            Class.forName(JDBC_DRIVER);
            
            conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);
            if (conn != null){
                System.out.println("Connection established");
            }
        }
        catch(Exception e) {
            System.out.println(e);
        }
    }
    
    
}
