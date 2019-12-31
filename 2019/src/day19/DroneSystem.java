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
    }

    public void scanArea(int minX, int minY, int n) throws IntcodeComputer.IntcodeException {
        for (int y = minY; y < minY + n; y++) {
            for (int x = minX; x < minX + n; x++) {
                int result = getResultAtPosition(x, y);
                tractorBeamMap.put(new Point(x, y), result);
            }
        }
    }

    public void printArea(int minX, int minY, int n) {
        for (int y = minY; y < minY + n; y++) {
            for (int x = minX; x < minX + n; x++) {
                System.out.print(tractorBeamMap.get(new Point(x, y)));
            }
            System.out.println();
        }
    }

    protected int getResultAtPosition(int x, int y) throws IntcodeComputer.IntcodeException {
        IntcodeComputer computer = new IntcodeComputer(instructions.clone());
        computer.pushOntoInputs(new int[] {x, y});
        Queue<BigInteger> outputs = computer.processUntilNOutputs(1);
        // System.out.println("outputs:" + outputs);
        return outputs.poll().intValue();
    }

    public int scanForTractorBeam(int minX, int minY, int n) throws IntcodeComputer.IntcodeException {
        tractorBeamMap = new HashMap<>();
        scanArea(minX, minY, n);
        printArea(minX, minY, n);
        int count = 0;
        for (int y = minY; y < minY + n; y++) {
            for (int x = minX; x < minX + n; x++) {
                if (tractorBeamMap.get(new Point(x, y)) == RESULT_PULLED) {
                    count++;
                }
            }
        }
        return count;
    }

    public Point find100x100Square() throws IntcodeComputer.IntcodeException {
        Point point;
        int x = 0;
        for (int y = 837; true; y++) {
            x = findMaxXforY(x, y);
            point = new Point(x - 99, y);
            if (check100x100Square(point)) {
                return point;
            }
        }
    }

    protected int findMaxXforY(int x, int y) throws IntcodeComputer.IntcodeException {
        int result = getResultAtPosition(x, y);
        while (result == RESULT_STATIONARY) {
            x++;
            result = getResultAtPosition(x, y);
        }
        while (result == RESULT_PULLED) {
            x++;
            result = getResultAtPosition(x, y);
        }
        return x - 1;
    }

    protected boolean check100x100Square(Point point) throws IntcodeComputer.IntcodeException {
        System.out.println("check100x100Square(" + point + ")");
        // scanForTractorBeam(point.x, point.y, 100);
        return getResultAtPosition(point.x, point.y) == RESULT_PULLED &&
                getResultAtPosition(point.x + 99, point.y) == RESULT_PULLED &&
                getResultAtPosition(point.x, point.y + 99) == RESULT_PULLED;
    }
}
