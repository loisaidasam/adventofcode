package day05;

import common.BaseSolution;
import common.InputReader;
import day02.IntcodeComputer;

public class Solution05 extends BaseSolution implements common.Solution {

    protected day05.IntcodeComputer computer;

    public static void main(String[] args) throws Exception {
        new Solution05().run();
    }

    protected int[] getInputPositions() {
        InputReader reader = getInputReader();
        String line = reader.next();
        return IntcodeComputer.buildInputPositions(line);
    }

    @Override
    public String part1() throws IntcodeComputer.IntcodeException {
        computer = new day05.IntcodeComputer(getInputPositions());
        int[] inputs = {1};
        return String.valueOf(computer.process(inputs));
    }

    @Override
    public String part2() throws IntcodeComputer.IntcodeException {
        // inputFilename = "input-test.txt";
        computer = new day05.IntcodeComputer(getInputPositions());
        int[] inputs = {5};
        return String.valueOf(computer.process(inputs));
    }
}
