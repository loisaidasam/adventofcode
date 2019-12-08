package day02;

import common.BaseSolution;
import common.InputReader;
import common.IntcodeComputer;

public class Solution02 extends BaseSolution implements common.Solution {

    protected int[] positions;

    public static void main(String[] args) throws Exception {
        new Solution02().run();
    }

    public Solution02() {
        super();
        positions = getInputPositions();
    }

    @Override
    public String part1() throws IntcodeComputer.IntcodeException {
        IntcodeComputer computer = new IntcodeComputer(positions.clone());
        computer.restoreTo1202ProgramAlarmState();
        return String.valueOf(computer.processDay02());
    }

    @Override
    public String part2() {
        int targetOutput = 19690720;
        IntcodeComputer computer;
        int output;
        for (int noun = 0; noun <= 99; noun++) {
            for (int verb = 0; verb <= 99; verb++) {
                computer = new IntcodeComputer(positions.clone());
                computer.restoreToState(noun, verb);
                try {
                    output = computer.processDay02();
                } catch (IntcodeComputer.IntcodeException exception) {
                    continue;
                }
                if (output == targetOutput) {
                    return String.valueOf(100 * noun + verb);
                }
            }
        }
        return null;
    }
}
