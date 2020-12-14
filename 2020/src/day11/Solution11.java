package day11;

import common.BaseSolution;
import common.IntSolution;
import common.StringSolution;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution11 extends BaseSolution implements IntSolution {

    public class SeatingSystem {
        private List<String> layout;

        public SeatingSystem(List<String> layout) {
            this.layout = layout;
        }

        public String toString() {
            String result = "";
            for (String row : layout) {
                result += row + "\n";
            }
            return result;
        }

        private Character getSeatStatus(int row, int col) {
            if (row < 0 || col < 0 || row >= layout.size() || col >= layout.get(0).length()) {
                return null;
            }
            return layout.get(row).charAt(col);
        }

        private Character[] getSurroundingSeats(int row, int col) {
            return new Character[] {
                    getSeatStatus(row - 1, col - 1),
                    getSeatStatus(row - 1, col),
                    getSeatStatus(row - 1, col + 1),
                    getSeatStatus(row, col + 1),
                    getSeatStatus(row + 1, col + 1),
                    getSeatStatus(row + 1, col),
                    getSeatStatus(row + 1, col - 1),
                    getSeatStatus(row, col - 1),
            };
        }

        private long getNumOccupiedAdjacentSeats(int row, int col) {
            return Arrays.asList(getSurroundingSeats(row, col)).stream()
                    .filter(status -> status != null && status == '#')
                    .count();
        }

        private char getNewSeatStatus(int row, int col) {
            char status = getSeatStatus(row, col);
            if (status == '.') {
                return '.';
            }
            if (status == 'L' && getNumOccupiedAdjacentSeats(row, col) == 0) {
                return '#';
            }
            if (status == '#' && getNumOccupiedAdjacentSeats(row, col) >= 4) {
                return 'L';
            }
            return status;
        }

        public int applySeatingRules() {
            int numChanged = 0;
            List<String> newLayout = new ArrayList<>();
            for (int row = 0; row < layout.size(); row++) {
                String newRow = "";
                for (int col = 0; col < layout.get(0).length(); col++) {
                    newRow += getNewSeatStatus(row, col);
                    if (getSeatStatus(row, col) != newRow.charAt(col)) {
                        numChanged++;
                    }
                }
                newLayout.add(newRow);
            }
            layout = newLayout;
            return numChanged;
        }

        public int getNumOccupiedSeats() {
            int numOccupied = 0;
            for (int row = 0; row < layout.size(); row++) {
                String rowStr = layout.get(row);
                for (int col = 0; col < rowStr.length(); col++) {
                    if (rowStr.charAt(col) == '#') {
                        numOccupied++;
                    }
                }
            }
            return numOccupied;
        }
    }
    public static void main(String[] args) throws Exception {
        new Solution11().run();
    }

    protected InputType getInputType() {
        return InputType.STRINGS;
    }

    @Override
    public Integer part1Int() {
        SeatingSystem seatingSystem = new SeatingSystem(inputStrs);
        while (true) {
            if (seatingSystem.applySeatingRules() == 0) {
                break;
            }
        }
        return seatingSystem.getNumOccupiedSeats();
    }

    @Override
    public String part2() {
        return null;
    }
}