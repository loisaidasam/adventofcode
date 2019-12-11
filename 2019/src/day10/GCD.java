package day10;

public class GCD {
    /**
     * via https://stackoverflow.com/a/4202033/1406873
     */
    public static int gcd(int a, int b) {
        if (b == 0) return a;
        if (a == 0) return b;
        return gcd(b, a % b);
    }

    public static void main(String[] args) {
        System.out.println(gcd(Integer.parseInt(args[0]), Integer.parseInt(args[1])));
    }
}
