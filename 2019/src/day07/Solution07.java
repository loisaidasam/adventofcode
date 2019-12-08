package day07;

import common.BaseSolution;
import common.IntcodeComputer;

public class Solution07 extends BaseSolution implements common.Solution {

    public static void main(String[] args) throws Exception {
        new Solution07().run();
    }

    @Override
    public String part1() throws IntcodeComputer.IntcodeException {
        int outputSignal = new AmpCircuit(getInputPositions()).findLargestOutputSignal();
        return String.valueOf(outputSignal);
    }

    @Override
    public String part2() throws IntcodeComputer.IntcodeException {
        int outputSignal = new AmpCircuit(getInputPositions()).findLargestOutputSignalWithFeedback();
        return String.valueOf(outputSignal);
    }
}
