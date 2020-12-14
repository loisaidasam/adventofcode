package day03;

import common.BaseSolution;

import java.util.ArrayList;
import java.util.List;

public class Solution03 extends BaseSolution {

    public static void main(String[] args) throws Exception {
        new Solution03().run();
    }

    protected InputType getInputType() {
        return InputType.STRINGS;
    }

    @Override
    public Integer part1Int() throws Exception {
        return tobogganRun(3, 1);
    }

    @Override
    public Integer part2Int() {
        List<Integer> results = new ArrayList<>();
        results.add(tobogganRun(1, 1));
        results.add(tobogganRun(3, 1));
        results.add(tobogganRun(5, 1));
        results.add(tobogganRun(7, 1));
        results.add(tobogganRun(1, 2));
        return results.stream()
                .reduce(1, (a, b) -> a * b);
    }

    private int tobogganRun(int right, int down) {
        int numTrees = 0;
        int row = 0;
        int col = 0;
        final int WIDTH = inputStrs.get(0).length();
        while (row < inputStrs.size()) {
            if (isTree(row, col)) {
                numTrees++;
            }
            col += right;
            row += down;
            if (col >= WIDTH) {
                col -= WIDTH;
            }
        }
        return numTrees;
    }

    private boolean isTree(int row, int col) {
        return inputStrs.get(row).charAt(col) == '#';
    }
}