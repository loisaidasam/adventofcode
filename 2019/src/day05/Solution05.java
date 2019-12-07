package day05;

import common.BaseSolution;
import common.InputReader;
import day02.IntcodeComputer;

public class Solution05 extends BaseSolution implements common.Solution {

    protected day05.IntcodeComputer computer;

    public static void main(String[] args) throws Exception {
        new Solution05().run();
    }

    public Solution05() {
        super();
        computer = new day05.IntcodeComputer(getInputPositions());
    }

    protected int[] getInputPositions() {
        InputReader reader = getInputReader();
        String line = reader.next();
        return IntcodeComputer.buildInputPositions(line);
    }

    @Override
    public String part1() throws IntcodeComputer.IntcodeException {
        int[] inputs = {1};
        computer.process(inputs);
        return null;
    }

    @Override
    public String part2() {
        return null;
    }
}
