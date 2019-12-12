package day11;

import common.BaseSolution;
import common.Solution;

public class Solution11 extends BaseSolution implements Solution {

    public static void main(String[] args) throws Exception {
        new Solution11().run();
    }

    @Override
    public String part1() throws Exception {
        EmergencyHullPaintingRobot robot = new EmergencyHullPaintingRobot(getInputPositionsBigInteger());
        robot.paint();
        return String.valueOf(robot.findNumPanelsPaintedAtLeastOnce());
    }

    @Override
    public String part2() throws Exception {
        EmergencyHullPaintingRobot robot = new EmergencyHullPaintingRobot(getInputPositionsBigInteger());
        robot.setStartingPanelWhite();
        robot.paint();
        robot.printHull();
        return null;
    }
}
