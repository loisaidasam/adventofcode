package day11;

import common.IntcodeComputer;
import common.Point;

import java.math.BigInteger;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

public class EmergencyHullPaintingRobot {

    public static final int COLOR_BLACK = 0;
    public static final int COLOR_WHITE = 1;

    public static final int DIRECTION_UP = 0;
    public static final int DIRECTION_RIGHT = 1;
    public static final int DIRECTION_DOWN = 2;
    public static final int DIRECTION_LEFT = 3;

    protected IntcodeComputer brain;

    protected Point location;
    protected int direction;

    protected HashMap<Point, Integer> panelColors;
    protected Set<Point> panelsPainted;

    protected int xMin = 0;
    protected int xMax = 0;
    protected int yMin = 0;
    protected int yMax = 0;

    public EmergencyHullPaintingRobot(BigInteger[] paintingInstructions) {
        brain = new IntcodeComputer(paintingInstructions);
//        brain.setVerbose(true);
        brain.setInterruptOnOutput(true);
        location = new Point(0, 0);
        direction = DIRECTION_UP;
        panelsPainted = new HashSet<>();
        panelColors = new HashMap<>();
    }

    public void paint() throws Exception {

        Integer color;
        int paintColor, turnDirection;
        while (true) {
            color = panelColors.containsKey(location) ? panelColors.get(location) : COLOR_BLACK;
            brain.pushOntoInputs(color);
            try {
                brain.process();
                return;
            } catch (IntcodeComputer.OutputInterrupt exception) {
                paintColor = brain.getLastOutput().intValue();
            }
            try {
                brain.process();
                throw new Exception("Process with no output");
            } catch (IntcodeComputer.OutputInterrupt exception) {
                turnDirection = brain.getLastOutput().intValue();
            }
            panelColors.put(location, paintColor);
            panelsPainted.add(location);
            location = location.clone();
            turn(turnDirection);
            move();
        }
    }

    public int findNumPanelsPaintedAtLeastOnce() {
        return panelsPainted.size();
    }

    protected void turn(int turnDirection) throws Exception {
        switch (turnDirection) {
            case 0:
                direction--;
                if (direction == -1) {
                    direction = 3;
                }
                break;
            case 1:
                direction++;
                if (direction == 4) {
                    direction = 0;
                }
                break;
            default:
                throw new Exception("Unknown direction!");
        }
    }

    protected void move() {
        switch (direction) {
            case DIRECTION_UP:
                location.y--;
                if (location.y < yMin) {
                    yMin = location.y;
                }
                break;
            case DIRECTION_RIGHT:
                location.x++;
                if (location.x > xMax) {
                    xMax = location.x;
                }
                break;
            case DIRECTION_DOWN:
                location.y++;
                if (location.y > yMax) {
                    yMax = location.y;
                }
                break;
            case DIRECTION_LEFT:
                location.x--;
                if (location.x < xMin) {
                    xMin = location.x;
                }
                break;
        }
    }

    public void setStartingPanelWhite() {
        panelColors.put(new Point(0, 0), COLOR_WHITE);
    }

    public void printHull() {
        Point point;
        int color;
        for (int y = yMin; y <= yMax; y++) {
            for (int x = xMin; x <= xMax; x++) {
                point = new Point(x, y);
                color = panelColors.containsKey(point) ? panelColors.get(point) : COLOR_BLACK;
                System.out.print(color);
            }
            System.out.println();
        }
    }
}
