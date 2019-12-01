package day01;

import common.BaseSolution;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Solution extends BaseSolution {

    public static void main(String[] args) {
        System.out.println("Part1: " + Solution.part1());
        System.out.println("Part2: " + Solution.part2());
    }

    private static int part1() {
        BufferedReader reader;
        int mass, totalFuel = 0;
        try {
            reader = new BufferedReader(new FileReader(getInputFilename("day01")));
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

    private static int part2() {
        BufferedReader reader;
        int mass, totalFuel = 0;
        try {
            reader = new BufferedReader(new FileReader(getInputFilename("day01")));
            String line = reader.readLine();
            while (line != null) {
                mass = Integer.valueOf(line);
                totalFuel += Solution.getFuelWithResiduals(mass);
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

    private static int getFuelWithResiduals(int mass) {
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
