package common;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class BaseSolution {

    public enum InputType {
        NONE,
        STRINGS,
        INTS,
    }

    protected List<String> inputStrs;
    protected List<Integer> inputInts;

    protected String inputFilename = "input.txt";

    public BaseSolution() {
        if (getInputType() == InputType.STRINGS) {
            inputStrs = getInputStrings();
        } else if (getInputType() == InputType.INTS) {
            inputInts = getInputInts();
        }
    }

    public BaseSolution run() throws Exception {
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

    protected List<String> getInputStrings() {
        List<String> inputStrings = new ArrayList<>();
        InputReader reader = getInputReader();
        String line = reader.next();
        while (line != null) {
            inputStrings.add(line);
            line = reader.next();
        }
        return inputStrings;
    }

    protected List<Integer> getInputInts() {
        return getInputStrings().stream()
                .map(s -> Integer.parseInt(s))
                .collect(Collectors.toList());
    }

    protected InputType getInputType() {
        return InputType.NONE;
    }

    protected Integer part1Int() throws Exception {
        return null;
    }

    public String part1() throws Exception {
        Integer value = part1Int();
        return value == null ? null : String.valueOf(value);
    }

    protected Integer part2Int() throws Exception {
        return null;
    }

    public String part2() throws Exception {
        Integer value = part2Int();
        return value == null ? null : String.valueOf(value);
    }
}
