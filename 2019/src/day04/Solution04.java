package day04;

import common.BaseSolution;
import common.InputReader;

public class Solution04 extends BaseSolution implements common.Solution {

    protected String input;

    public static void main(String[] args) throws Exception {
        new Solution04().run();
    }

    public Solution04() {
        super();
        readInput();
    }

    protected void readInput() {
        InputReader reader = getInputReader();
        input = reader.next();
    }

    @Override
    public String part1() {
        return String.valueOf(checkIsValid(1));
    }

    @Override
    public String part2() {
        return String.valueOf(checkIsValid(2));
    }

    protected int checkIsValid(int part) {
        int count = 0;
        PasswordChecker checker = new PasswordChecker(input);
        for (int password = checker.getMin(); password <= checker.getMax(); password++) {
            if ((part == 1 && checker.isValidPart1(password)) || (part == 2 && checker.isValidPart2(password))) {
                // System.out.println(password);
                count++;
            }
        }
        return count;
    }
}
