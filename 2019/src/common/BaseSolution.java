package common;

import java.math.BigInteger;

public class BaseSolution implements Solution {

    protected String inputFilename = "input.txt";

    public Solution run() throws Exception {
        System.out.println("Solution for " + getDayName());
        System.out.println("Part1: " + part1());
        System.out.println("Part2: " + part2());
        return this;
    }

    protected String getDayName() {
        // Something like "day01.Solution"
        String packageName = getClass().getName();
        // What we're after is the "day01" piece
        String[] bits = packageName.split("\\.");
        return bits[bits.length - 2];
    }

    /**
     * via https://stackoverflow.com/a/7603444
     */
    protected String getCurrentDir() {
        return System.getProperty("user.dir");
    }

    protected String getInputFilename() {
        return getCurrentDir() + "/src/" + getDayName() + "/" + inputFilename;
    }

    protected InputReader getInputReader() {
        return new InputReader(getInputFilename());
    }

    protected int[] getInputPositions() {
        InputReader reader = getInputReader();
        String line = reader.next();
        return IntcodeComputer.buildInputPositions(line);
    }

    protected BigInteger[] getInputPositionsBigInteger() {
        InputReader reader = getInputReader();
        String line = reader.next();
        return IntcodeComputer.buildInputPositionsBigInteger(line);
    }

    @Override
    public String part1() throws Exception {
        return null;
    }

    @Override
    public String part2() throws Exception {
        return null;
    }
}
