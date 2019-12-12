package day12;

import common.BaseSolution;
import common.InputReader;
import common.IntcodeComputer;
import common.Solution;
import javafx.geometry.Pos;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

public class Solution12 extends BaseSolution implements Solution {

    public static void main(String[] args) throws Exception {
        new Solution12().run();
    }

    public Solution12() {
        super();
        inputFilename = "input-test-2.txt";
    }

    @Override
    public String part1() throws Exception {
        JupiterSystem system = new JupiterSystem(readPositions());
        system.step(1000);
        return String.valueOf(system.getTotalEnergy());
    }

    @Override
    public String part2() {
        JupiterSystem system = new JupiterSystem(readPositions());
        return system.getNumStepsUntilRepeat().toString();
    }

    protected List<Position> readPositions() {
        List<Position> positions = new ArrayList<>();
        InputReader reader = getInputReader();
        String line;
        for (int i = 0; i < 4; i++) {
            line = reader.next();
            int[] intPositions = IntcodeComputer.buildInputPositions(line);
            Position position = new Position(intPositions[0], intPositions[1], intPositions[2]);
            positions.add(position);
        }
        return positions;
    }
}
