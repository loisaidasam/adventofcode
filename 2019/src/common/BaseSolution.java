package common;

public class BaseSolution implements Solution {

    protected String inputFilename = "input.txt";

    public void run() {
        System.out.println("Solution for " + getDayName());
        System.out.println("Part1: " + part1());
        System.out.println("Part2: " + part2());
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

    @Override
    public String part1() {
        return null;
    }

    @Override
    public String part2() {
        return null;
    }
}
