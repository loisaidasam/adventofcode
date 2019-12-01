package day01;

import common.BaseSolution;
import common.InputReader;

public class Solution extends BaseSolution implements common.Solution {

    public static void main(String[] args) {
        new Solution().run();
    }

    public String part1() {
        int mass, totalFuel = 0;
        InputReader reader = getInputReader();
        String line = reader.next();
        while (line != null) {
            mass = Integer.parseInt(line);
            totalFuel += getFuel(mass);
            line = reader.next();
        }
        return String.valueOf(totalFuel);
    }

    private int getFuel(int mass) {
        return mass / 3 - 2;
    }

    public String part2() {
        int mass, totalFuel = 0;
        InputReader reader = getInputReader();
        String line = reader.next();
        while (line != null) {
            mass = Integer.parseInt(line);
            totalFuel += getFuelWithResiduals(mass);
            line = reader.next();
        }
        return String.valueOf(totalFuel);
    }

    private int getFuelWithResiduals(int mass) {
        int fuel = 0;
        int fuelPiece = mass;
        do {
            fuelPiece = getFuel(fuelPiece);
            if (fuelPiece > 0) {
                fuel += fuelPiece;
            }
        } while (fuelPiece > 0);
        return fuel;
    }
}
