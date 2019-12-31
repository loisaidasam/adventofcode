package day19;

import common.IntcodeComputer;
import common.Point;

import java.math.BigInteger;
import java.util.HashMap;
import java.util.Map;
import java.util.Queue;

public class DroneSystem {

    public static final int RESULT_STATIONARY = 0;
    public static final int RESULT_PULLED = 1;

    protected BigInteger[] instructions;

    protected Map<Point, Integer> tractorBeamMap;

    public DroneSystem(BigInteger[] instructions) {
        this.instructions = instructions;
        tractorBeamMap = new HashMap<>();
    }

    public void scanArea(int n) throws IntcodeComputer.IntcodeException {
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                // System.out.println("x=" + x + " y=" + y);
                int result = getResultAtPosition(x, y);
                tractorBeamMap.put(new Point(x, y), result);
            }
        }
    }

    protected int getResultAtPosition(int x, int y) throws IntcodeComputer.IntcodeException {
        IntcodeComputer computer = new IntcodeComputer(instructions.clone());
        computer.pushOntoInputs(new int[] {x, y});
        Queue<BigInteger> outputs = computer.processUntilNOutputs(1);
        // System.out.println("outputs:" + outputs);
        return outputs.poll().intValue();
    }

    public int scanForTractorBeam(int n) {
        int count = 0;
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                if (tractorBeamMap.get(new Point(x, y)) == RESULT_PULLED) {
                    count++;
                }
            }
        }
        return count;
    }
}
