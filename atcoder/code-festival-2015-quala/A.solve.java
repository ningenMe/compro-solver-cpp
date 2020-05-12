import java.util.Scanner;
 
public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
        String s = sc.next();
		System.out.println(s.substring(0, s.length()-1)+"5");
	}
}