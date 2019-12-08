package day05;

import common.BaseSolution;
import common.InputReader;
import common.IntcodeComputer;

public class Solution05 extends BaseSolution implements common.Solution {

    protected common.IntcodeComputer computer;

    public static void main(String[] args) throws Exception {
        new Solution05().run();
    }

    @Override
    public String part1() throws IntcodeComputer.IntcodeException {
        computer = new common.IntcodeComputer(getInputPositions());
        int[] inputs = {1};
        return String.valueOf(computer.processAndReturnLastOutput(inputs));
    }

    @Override
    public String part2() throws IntcodeComputer.IntcodeException {
        // inputFilename = "input-test.txt";
        computer = new common.IntcodeComputer(getInputPositions());
        int[] inputs = {5};
        return String.valueOf(computer.processAndReturnLastOutput(inputs));
    }
}
