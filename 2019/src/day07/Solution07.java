package day07;

import common.BaseSolution;
import common.InputReader;
import day05.IntcodeComputer;

public class Solution07 extends BaseSolution implements common.Solution {

    public static void main(String[] args) throws Exception {
        new Solution07().run();
    }

    // public Solution07() {
    //     super();
    //     buildOrbitObjectMap();
    // }

    protected int[] getInputPositions() {
        InputReader reader = getInputReader();
        String line = reader.next();
        return IntcodeComputer.buildInputPositions(line);
    }

    @Override
    public String part1() throws day02.IntcodeComputer.IntcodeException {
        int outputSignal = new AmpCircuit(getInputPositions()).findLargestOutputSignal();
        return String.valueOf(outputSignal);
    }

    @Override
    public String part2() {
        return null;
    }
}
