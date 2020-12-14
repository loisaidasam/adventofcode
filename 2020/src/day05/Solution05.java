package day05;

import common.BaseSolution;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

public class Solution05 extends BaseSolution {


    public static void main(String[] args) throws Exception {
        new Solution05().run();
    }

    protected InputType getInputType() {
        return InputType.STRINGS;
    }

    @Override
    public Integer part1Int() {
        int maxSeatId = 0;
        for (String input : inputStrs) {
            int seatId = getSeatId(input);
            if (seatId > maxSeatId) {
                maxSeatId = seatId;
            }
        }
        return maxSeatId;
    }

    @Override
    public Integer part2Int() {
        List<Integer> seatIds = new ArrayList<>();
        for (String input : inputStrs) {
            seatIds.add(getSeatId(input));
        }
        Collections.sort(seatIds);
        int last = 0;
        for (int seatId : seatIds) {
            if (last != 0 && seatId - last > 1) {
                // System.out.println("Last: " + last + " seatId: " + seatId);
                return seatId - 1;
            }
            last = seatId;
        }
        return 0;
    }

    private int getSeatId(String bspString) {
        int row = getRow(bspString.substring(0, 7));
        int col = getCol(bspString.substring(7, 10));
        return row * 8 + col;
    }

    /**
     *
     * 0/15
     * 0/7 8/15
     * 0/3 4/7 8/11 12/15
     * 0/1 2/3 4/5 6/7 8/9 10/11 12/13 14/15
     *
     * @param bspString
     * @return
     */
    private int getRow(String bspString) {
        int min, max;
        min = 0;
        max = 127;
        for (int i = 0; i < bspString.length(); i++) {
            int delta = (max - min) / 2 + 1;
            if (bspString.charAt(i) == 'F') {
                max -= delta;
            } else {
                min += delta;
            }
        }
        return min;
    }

    private int getCol(String bspString) {
        int min, max;
        min = 0;
        max = 7;
        for (int i = 0; i < bspString.length(); i++) {
            int delta = (max - min) / 2 + 1;
            if (bspString.charAt(i) == 'L') {
                max -= delta;
            } else {
                min += delta;
            }
        }
        return min;
    }
}