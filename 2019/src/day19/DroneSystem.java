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
                // System.out.println("x=" + x + " y=" + y);
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
            // if (y % 100 == 0) {
            //     System.out.println("y=" + y);
            // }
            x = findMinXforY(x, y);
            point = new Point(x, y);
            if (check100x100Square(point)) {
                return point;
            }
        }
    }

    protected int findMinXforY(int x, int y) throws IntcodeComputer.IntcodeException {
        while (true) {
            int result = getResultAtPosition(x, y);
            // System.out.println("getResultAtPosition(" + x + ", " + y + ")=" + result);
            if (result == RESULT_PULLED) {
                return x;
            }
            x++;
        }
    }

    protected boolean check100x100Square(Point point) throws IntcodeComputer.IntcodeException {
        System.out.println("check100x100Square(" + point + ")");
        // scanForTractorBeam(point.x, point.y, 100);
        for (int y = point.y; y > point.y - 100; y--) {
            for (int x = point.x; x < point.x + 100; x++) {
                // System.out.println("x=" + x + " y=" + y);
                int result = getResultAtPosition(x, y);
                // System.out.println("result=" + result);
                if (result != RESULT_PULLED) {
                    System.out.println("x=" + x + " point.x=" + point.x + " width=" + (x - point.x));
                    return false;
                }
            }
        }
        return true;
    }
}
