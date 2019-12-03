package day03;

import common.BaseSolution;
import common.InputReader;
import common.Solution;

public class Solution03 extends BaseSolution implements Solution {

    public static void main(String[] args) throws Exception {
        new Solution03().run();
    }

    @Override
    public String part1() throws FrontPanel.UnknownDirectionException {
        FrontPanel panel = new FrontPanel();
        System.out.println(panel);
        InputReader reader = getInputReader();
        // 'r' for red
        panel.handleInstructions('r', reader.next().split(","));
        // 'b' for blue
        panel.handleInstructions('b', reader.next().split(","));
        return String.valueOf(panel.findClosestIntersectionDistance());
    }
}
