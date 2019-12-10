package day09;

import common.BaseSolution;
import common.IntcodeComputer;
import common.Solution;
import day07.AmpCircuit;

import java.math.BigInteger;
import java.util.Queue;

public class Solution09 extends BaseSolution implements common.Solution {

    public static void main(String[] args) throws Exception {
        new Solution09().run();
    }

//    public Solution09() {
//        super();
//        inputFilename = "input-test-3.txt";
//    }

    @Override
    public String part1() throws IntcodeComputer.IntcodeException {
        IntcodeComputer computer = new IntcodeComputer(getInputPositionsBigInteger());
        computer.process(new int[] {1});
        return String.valueOf(computer.getLastOutput());
    }

    @Override
    public String part2() throws IntcodeComputer.IntcodeException {
        IntcodeComputer computer = new IntcodeComputer(getInputPositionsBigInteger());
        computer.process(new int[] {2});
        return String.valueOf(computer.getLastOutput());
    }
}
