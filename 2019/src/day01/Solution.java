package day01;

import common.BaseSolution;
import common.InputReader;

public class Solution extends BaseSolution implements common.Solution {

    public static void main(String[] args) {
        new Solution().run();
    }

    class BaseFuelCalculator {
        public int calculateFuel() {
            int mass, totalFuel = 0;
            InputReader reader = getInputReader();
            String line = reader.next();
            while (line != null) {
                mass = Integer.parseInt(line);
                totalFuel += getFuel(mass);
                line = reader.next();
            }
            return totalFuel;
        }

        protected int getFuelForMass(int mass) {
            return mass / 3 - 2;
        }

        protected int getFuel(int mass) {
            return 0;
        }
    }

    class Part1FuelCalculator extends BaseFuelCalculator {
        protected int getFuel(int mass) {
            return getFuelForMass(mass);
        }
    }

    class Part2FuelCalculator extends BaseFuelCalculator {
        protected int getFuel(int mass) {
            int fuel = 0;
            int fuelPiece = getFuelForMass(mass);
            while (fuelPiece > 0) {
                fuel += fuelPiece;
                fuelPiece = getFuelForMass(fuelPiece);
            }
            return fuel;
        }
    }

    public String part1() {
        return String.valueOf(new Part1FuelCalculator().calculateFuel());
    }

    public String part2() {
        return String.valueOf(new Part2FuelCalculator().calculateFuel());
    }
}
