package day13;

import common.BaseSolution;
import common.LongSolution;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Solution13 extends BaseSolution implements LongSolution {

    public static void main(String[] args) throws Exception {
        new Solution13().run();
    }

    protected InputType getInputType() {
        return InputType.STRINGS;
    }

    @Override
    public Long part1Long() throws Exception {
        Long earliestDeparture = Long.parseLong(inputStrs.get(0));
        List<Long> busIds = Arrays.stream(inputStrs.get(1).split(","))
                .filter(busId -> ! busId.equals("x"))
                .map(Long::parseLong)
                .collect(Collectors.toList());
        Long bestBus = null, shortestWaitTime = null;
        for (Long busId : busIds) {
            Long waitTime = earliestDeparture % busId;
            if (waitTime > 0) {
                waitTime = busId - waitTime;
            }
            if (shortestWaitTime == null || waitTime < shortestWaitTime) {
                bestBus = busId;
                shortestWaitTime = waitTime;
            }
        }
        return shortestWaitTime * bestBus;
    }
}