import java.math.BigDecimal;
import java.util.Scanner;

public class test {
        public static void main(String args[]) {
                Scanner input = new Scanner(System.in);
                while (input.hasNext()) {
                        BigDecimal r = input.nextBigDecimal();
                        BigDecimal res = new BigDecimal(1);
                        int n = input.nextInt();
                        while (n > 0) {
                                res = res.multiply(r);
                                n = n - 1;
                        }
                        String out = res.stripTrailingZeros().toPlainString();
                        if (out.length() >= 2 && out.substring(0, 1).equals(new String("0")))
                                System.out.println(out.substring(1));
                        else System.out.println(out);
                }
        }
}