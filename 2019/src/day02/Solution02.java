package day02;

import common.BaseSolution;
import common.InputReader;

import java.util.Arrays;

public class Solution02 extends BaseSolution implements common.Solution {

    protected int[] positions;

    public static void main(String[] args) throws Exception {
        new Solution02().run();
    }

    public Solution02() {
        super();
        positions = getInputPositions();
    }

    protected int[] getInputPositions() {
        InputReader reader = getInputReader();
        String line = reader.next();
        String[] values = line.split(",");
        return Arrays.stream(values).mapToInt(Integer::parseInt).toArray();
    }

    @Override
    public String part1() throws IntcodeComputer.UnknownOpcodeException {
        IntcodeComputer computer = new IntcodeComputer(positions.clone());
        computer.restoreTo1202ProgramAlarmState();
        return String.valueOf(computer.process());
    }
}
