package day02;

import common.BaseSolution;
import common.InputReader;

import java.util.Arrays;

public class Solution02 extends BaseSolution implements common.Solution {

    public static void main(String[] args) throws Exception {
        new Solution02().run();
    }

    @Override
    public String part1() throws IntcodeComputer.UnknownOpcodeException {
        InputReader reader = getInputReader();
        String line = reader.next();
        String[] values = line.split(",");
        int[] positions = Arrays.stream(values).mapToInt(Integer::parseInt).toArray();
        IntcodeComputer computer = new IntcodeComputer(positions);
        computer.process();
        return String.valueOf(computer.getPosition(0));
    }
}
