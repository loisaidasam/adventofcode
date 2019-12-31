package day19;

import common.BaseSolution;
import common.Solution;

public class Solution19 extends BaseSolution implements Solution {

    public static void main(String[] args) throws Exception {
        new Solution19().run();
    }

    @Override
    public String part1() throws Exception {
        DroneSystem drone = new DroneSystem(getInputPositionsBigInteger());
        drone.scanArea(50);
        return String.valueOf(drone.scanForTractorBeam(50));
    }

    @Override
    public String part2() throws Exception {
        return null;
    }
}
