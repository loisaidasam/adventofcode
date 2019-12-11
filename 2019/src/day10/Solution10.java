package day10;

import common.BaseSolution;
import common.InputReader;
import common.Solution;

import java.util.ArrayList;
import java.util.List;

public class Solution10 extends BaseSolution implements Solution {

    public static void main(String[] args) throws Exception {
        new Solution10().run();
    }

//    public Solution10() {
//        super();
//        inputFilename = "input-test-5.txt";
//    }

    @Override
    public String part1() throws Exception {
        AstroidMap astroidMap = new AstroidMap(getRows());
        int numVisible = astroidMap.findNumVisibleFromBestMonitoringStation();
        return String.valueOf(numVisible);
    }

    @Override
    public String part2() {
        return null;
    }

    protected List<String> getRows() {
        InputReader reader = getInputReader();
        List<String> rows = new ArrayList<>();
        String row = reader.next();
        while (row != null) {
            rows.add(row);
            row = reader.next();
        }
        return rows;
    }
}
