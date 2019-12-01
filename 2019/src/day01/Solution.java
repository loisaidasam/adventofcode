package day01;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Solution {

    public static void main(String[] args) {
        System.out.println("Part1: " + Solution.part1());
    }

    /**
     * via https://stackoverflow.com/a/7603444
     */
    protected static String getCurrentDir() {
        return System.getProperty("user.dir");
    }

    private static int part1() {
        BufferedReader reader;
        int mass, totalFuel = 0;
        try {
            reader = new BufferedReader(new FileReader( getCurrentDir() + "/src/day01/input.txt"));
            String line = reader.readLine();
            while (line != null) {
                mass = Integer.valueOf(line);
                totalFuel += Solution.getFuel(mass);
                line = reader.readLine();
            }
            reader.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return totalFuel;
    }

    private static int getFuel(int mass) {
        return mass / 3 - 2;
    }
}
