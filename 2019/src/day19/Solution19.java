package day19;

import common.BaseSolution;
import common.Point;
import common.Solution;

public class Solution19 extends BaseSolution implements Solution {

    public static void main(String[] args) throws Exception {
        new Solution19().run();
    }

    @Override
    public String part1() throws Exception {
        DroneSystem drone = new DroneSystem(getInputPositionsBigInteger());
        return String.valueOf(drone.scanForTractorBeam(0, 0, 50));
    }

    @Override
    public String part2() throws Exception {
        DroneSystem drone = new DroneSystem(getInputPositionsBigInteger());
        Point point = drone.find100x100Square();
        return String.valueOf(point.x * 10000 + point.y);
    }
}
