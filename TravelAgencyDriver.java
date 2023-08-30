import java.sql.*;
import java.util.Scanner;
import java.util.ArrayList;
//some codes are referenced from TestJDBC.java
//javac hw10.java java TravelAgencyDriver
class TravelAgencyDriver {
 public static void main( String args[] ) {
 OurTravelAgency ota = new OurTravelAgency();
ota.openConnection();
ota.createTrigger();
ota.createList();
ota.menu();
//
ota.closeConnection();
 }
}
class OurTravelAgency {
 private String database;
 private String username;
 private String password;
 private static final String JDBC_DRIVER = "org.mysql.jdbc.Driver";
 private static final String LOCAL_HOST = "jdbc:mariadb://localhost:3306/";
 private PreparedStatement preparedStatement;
 private Connection connection;
 ArrayList<Integer> travelerList = new ArrayList<Integer>();
 
 public OurTravelAgency() {
 database = "TravelAgencyDB";
 username = "root";
 password = "root";
 }
 public OurTravelAgency( String database, String username, String
password ) {
 this.database = database;
 this.username = username;
 this.password = password;
 }
 public void menu() {
 // implement your menu
 ResultSet rs;
 ResultSetMetaData rsmd;
 int columnsNumber ;
 Scanner myScanner = new Scanner(System.in);
 String userInput= "5";
 while(!userInput.equals("c"))
 {
     System.out.println("*******Main menu*******");
     System.out.println("a. Execute a query\nb. View Tables\nc.Quit\nd.Book Trip");
     System.out.print("Enter :");
     userInput= myScanner.nextLine();userInput=userInput.toLowerCase();
     String sql="";
     if(userInput.equals("a"))
     {
         System.out.print("Enter a complete SQL command:");
         sql =myScanner.nextLine();
         rs = query( sql, null ); 
         try {
             rsmd= rs.getMetaData(); columnsNumber = rsmd.getColumnCount();
             System.out.print("(");
             for(int i = 1; i <= columnsNumber; i++)
             {
                 System.out.print(rsmd.getColumnName(i)+"  ");
              }System.out.print(")");
              System.out.println();
              while ( rs.next() ) {
                  System.out.print("(");
                  for (int i = 1; i <= columnsNumber; i++){
                      if (i > 1) System.out.print(",  ");
                      String columnValue = rs.getString(i);
                      System.out.print(columnValue + " ");
                      }System.out.print(")");System.out.println();
                }
                   System.out.println( "That's all!" );
                }
    catch ( SQLException sqle ) {System.out.println("hi");}
           
      }else if(userInput.equals("b"))
      {
          tableMenu();
      }else if(userInput.equals("d"))
      {
          System.out.println( "***Booking***" );
          System.out.print( "Please enter your ssn :" );
          int ssn =Integer.parseInt(myScanner.nextLine());
          if(travelerList.contains(ssn))
          {
              //
          }else
          {
              addTraveler(ssn); 
          }
          printTrips();
          System.out.print( "Please enter a trip id :" );
          int id =Integer.parseInt(myScanner.nextLine());
          System.out.println();
          System.out.print( "Please enter an agent's name :" );
          String agent =myScanner.nextLine();
          System.out.println();
          String sql2 ="INSERT INTO booking (agent, traveler_ssn, trip_id) " +
          "VALUES " +
          "('"+agent+ "' ," + ssn +" ,"+ id +");";
          //update relation
          update( sql2 );
          String sql3="INSERT INTO GoesOn(traveler_ssn, trip_id) " +
          "VALUES " +
          "(" +ssn +" ,"+ id +");";
          update( sql3 );
    }
      else{
          //userInput !=a or userInput !=b
          closeConnection();
      }
  }
 
 }
 // implement other methods as needed
 public void openConnection() {
    try {
      connection = DriverManager.getConnection( LOCAL_HOST + database, username, password );
      System.out.println( database + " connected." );
      System.out.println();
      }
    catch ( SQLException sqle ) {
      sqle.printStackTrace();
    }
  }
  public void closeConnection() {
    try {
	System.out.println("close connection!");
      if ( connection != null ) {
        connection.close();
      }
    }
    catch ( SQLException sqle ) {
      sqle.printStackTrace();
    }
  }
  
  public ResultSet query( String sql, String args[] ) {
    ResultSet rs = null;
    int i;

    try {
      // rs = statement.executeQuery( sql );
      
      preparedStatement = connection.prepareStatement( sql );
      
      if ( args != null ) {
        for ( i = 0; i < args.length; i++ ) {
          preparedStatement.setString( ( i + 1 ), args[i] );
	    }
	  }
      
      rs = preparedStatement.executeQuery();
    }
    catch ( SQLException sqle ) {
      sqle.printStackTrace();
    }

    return rs;
  }
    public void update( String sql ) {
    int result = 0;

    try {
      // result = statement.executeUpdate( sql );
      
      preparedStatement = connection.prepareStatement( sql );
      result = preparedStatement.executeUpdate();
    }
    catch ( SQLException sqle ) {
      sqle.printStackTrace();
    }
  }
  
  public void createTrigger() 
  {
      String sql ="CREATE TRIGGER new_agent "+
"AFTER INSERT ON booking "+
"FOR EACH ROW "+
"BEGIN "+
    "IF NEW.agent NOT IN "+
        "(SELECT name FROM TravelAgent) THEN "+
          "INSERT INTO TravelAgent(name, years_experience, phone) "+
          "VALUES( NEW.agent, 0, NULL ) ; "+
    "END IF; "+
"END;";
 update( sql );
 }
   public void printTrips() 
  {
      String sql ="SELECT * FROM trip";
      ResultSet rs;
      rs = query( sql, null ); 
      ResultSetMetaData rsmd; int columnsNumber ;
      try {
              rsmd= rs.getMetaData(); columnsNumber = rsmd.getColumnCount();
              System.out.print("(");
              for(int i = 1; i <= columnsNumber; i++)
              {
                  System.out.print(rsmd.getColumnName(i)+"  ");
              }System.out.print(")");
              System.out.println();
              while ( rs.next() ) {
                  System.out.print("(");
                  for (int i = 1; i <= columnsNumber; i++){
                      if (i > 1) System.out.print(",  ");
                      String columnValue = rs.getString(i);
                      System.out.print(columnValue + " ");
                      }System.out.print(")");System.out.println();
                }
                   System.out.println( "That's all!" );
                }
    catch ( SQLException sqle ) {System.out.println("hi");}
  }
  
  public void createList() 
  {
      String sql ="SELECT ssn FROM traveler";
      ResultSet rs;
      rs = query( sql, null ); 
      try {
      while ( rs.next() ) {
          travelerList.add(rs.getInt( "ssn" ));
        //System.out.println( rs.getString( "ssn" ) );
      }
      }
    catch ( SQLException sqle ) {}
  }
  
  public void addTraveler(int ssn) 
  {
      Scanner myScanner = new Scanner(System.in);
      
      System.out.print( "Please enter your name :" );
      String name =myScanner.nextLine();
      System.out.print( "Please enter your date of birth yyyy-mm-dd [dash separated] :" );
      String dob =myScanner.nextLine();
      String sql ="INSERT INTO traveler(name, ssn, dob) " +
          "VALUES " +
          "('"+ name +"', "+ssn +", '"+ dob +"');";
      update( sql );
      travelerList.add(ssn);
      System.out.println();
  }
  
  public void tableMenu() 
  { ArrayList<String> tableNameList = new ArrayList<String>();
  int j =1;
  tableNameList.add("none");
     try{
    DatabaseMetaData dbmd=connection.getMetaData();
    ResultSet resultSet = dbmd.getTables(null, null, null, new String[]{"TABLE"});
    System.out.println("*******Table menu*******");
    System.out.print("0. Retun to Main menu,\n");
    
    
    while(resultSet.next()){
    //Print
    String tableName=resultSet.getString("TABLE_NAME");
    tableNameList.add(tableName);
    System.out.print (j + ". "+ tableName+"\n");
    j++;
    }
    
    //System.out.println("test: "+tableNameList.get(1));
     }catch ( SQLException sqle ) {System.out.println("Exception!");}
    
    Scanner myScanner = new Scanner(System.in);Scanner myScanner2 = new Scanner(System.in);
    System.out.println();
    
    System.out.print("Enter a selection  :");
    int userInput= myScanner.nextInt();
    String tableName ="";
    if(userInput>=j){
        System.out.println("Invaild selection!");userInput=0;
        tableMenu();
    }else{
        tableName = tableNameList.get(userInput);
        System.out.println("Selected table  :" +tableName);
    }
    if (userInput !=0){
    System.out.println();
    System.out.print("Enter Attributes[comma separated]  :");
    String attributes =myScanner2.nextLine();
    String sql="SELECT "+attributes+" FROM "+  tableName +";";
    //System.out.println(sql);
    ResultSet rs = query( sql, null );  
    ResultSetMetaData rsmd;
//printTable(rs);
     int columnsNumber ;
      try {
              rsmd= rs.getMetaData(); columnsNumber = rsmd.getColumnCount();
              System.out.print("(");
              for(int i = 1; i <= columnsNumber; i++)
              {
                  System.out.print(rsmd.getColumnName(i)+"  ");
              }System.out.print(")");
              System.out.println();
              while ( rs.next() ) {
                  System.out.print("(");
                  for (int i = 1; i <= columnsNumber; i++){
                      if (i > 1) System.out.print(",  ");
                      String columnValue = rs.getString(i);
                      System.out.print(columnValue + " ");
                      }System.out.print(")");System.out.println();
                }
                   System.out.println( "That's all!" );
                }
    catch ( SQLException sqle ) {System.out.println("hi");}
    
  }
  }
 }
// implement other classes as needed