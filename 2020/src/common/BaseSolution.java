package common;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class BaseSolution {

    protected InputType getInputType() {
        return InputType.NONE;
    }

    public String getInputFilename() {
        return "input.txt";
    }

    public enum InputType {
        NONE,
        STRINGS,
        INTS,
        LONGS
    }

    protected List<String> inputStrs;
    protected List<Integer> inputInts;
    protected List<Long> inputLongs;

    public BaseSolution() {
        if (getInputType() == InputType.STRINGS) {
            inputStrs = getInputStrings();
        } else if (getInputType() == InputType.INTS) {
            inputInts = getInputInts();
        } else if (getInputType() == InputType.LONGS) {
            inputLongs = getInputLongs();
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

    protected String getInputFilenamePath() {
        return getCurrentDir() + "/src/" + getDayName() + "/" + getInputFilename();
    }

    protected InputReader getInputReader() {
        return new InputReader(getInputFilenamePath());
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

    protected List<Long> getInputLongs() {
        return getInputStrings().stream()
                .map(s -> Long.parseLong(s))
                .collect(Collectors.toList());
    }

    public Integer part1Int() throws Exception {
        return null;
    }

    public Long part1Long() throws Exception {
        return null;
    }

    public String part1() throws Exception {
        Integer valueInt = part1Int();
        if (valueInt != null) {
            return String.valueOf(valueInt);
        }
        Long valueLong = part1Long();
        if (valueLong != null) {
            return String.valueOf(valueLong);
        }
        return null;
    }

    public Integer part2Int() throws Exception {
        return null;
    }

    public Long part2Long() throws Exception {
        return null;
    }

    public String part2() throws Exception {
        Integer valueInt = part2Int();
        if (valueInt != null) {
            return String.valueOf(valueInt);
        }
        Long valueLong = part2Long();
        if (valueLong != null) {
            return String.valueOf(valueLong);
        }
        return null;
    }
}
