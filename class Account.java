/*assignment number: HW #1
* assigned date: January 25
*/
public class Account
{
//declaration
private double balance;
//default constructor
public Account (){
balance = 0;
}
//initialization constructor
public Account (double b){
balance = b;
}
//sets Balance
public void setBalance (double b)
{
balance = b;
}
//get Balance
public double getBalance()
{
return balance;
}
//increases the balance by a specified amount
public void deposit(double amount)
{
balance = balance + amount;
}
//decreases the balance by a user specified amount returning the
amount withdrawn
public double withdraw(double amount)
{
double withdrawnMoney = amount;
balance = balance - withdrawnMoney;
return withdrawnMoney;
}
//other method
public String toString()
{
String data = "balance :" + balance;
return data;
}
//prints Information
public void printInfo()
{
String data = toString();
System.out.println("Account Information...");
System.out.println(data);
}