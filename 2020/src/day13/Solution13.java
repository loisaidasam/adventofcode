package day13;

import common.BaseSolution;
import common.LongSolution;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
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

    @Override
    public Long part2Long() throws Exception {
        String[] departures = inputStrs.get(1).split(",");
        DepartureFinder df = new DepartureFinder(departures);
        return df.findEarliestDeparture();
    }

    public class DepartureFinder {
        private String[] departures;
        private Map<Long, Long> rules;

        public DepartureFinder(String[] departures) {
            this.departures = departures;
            rules = new HashMap<>();
            for (int offset = 0; offset < departures.length; offset++) {
                if (! departures[offset].equals("x")) {
                    rules.put((long) offset, Long.parseLong(departures[offset]));
                }
            }
            System.out.println("rules=" + rules);
            // List<Long> busIds = Arrays.stream(departures)
            //         .filter(busId -> ! busId.equals("x"))
            //         .map(Long::parseLong)
            //         // Sort in reverse order here
            //         .sorted((busId1, busId2) -> Long.compare(busId2, busId1))
            //         .collect(Collectors.toList());
        }

        public Long findEarliestDeparture() {
            // Long firstBus = rules.get(0L);
            // Long highestIdBus = rules.values().stream()
            //         .sorted((busId1, busId2) -> Long.compare(busId2, busId1))
            //         .findFirst()
            //         .get();
            // System.out.println("Highest ID bus: " + highestIdBus);
            // for (Long offset : rules.keySet()) {
            //     if (rules.get(offset).equals(highestIdBus)) {
            //         break;
            //     }
            // }
            // TODO: Got this with my eyes, do it programatically somehow
            Long period = null;
            for (int offset = 0; offset < departures.length; offset++) {
                if (departures[offset].equals("853")) {
                    period = 853L - (long) offset;
                    break;
                }
            }
            System.out.println("Period=" + period);
            // Long timestamp = 0L;
            Long timestamp = period;

            // timestamp % busId == offset
            // (offset - timestamp) % busId
            int tries = 0;
            while (true) {
                if (tries % 10000000 == 0) {
                    System.out.println("timestamp=" + timestamp + " (" + tries + " tries)");
                }
                if (departureIsValid(timestamp)) {
                    return timestamp;
                }
                // timestamp += firstBus;
                timestamp += period;
                tries++;
            }

            // rules={0=19, 9=41, 19=523, 36=17, 37=13, 48=29, 50=853, 56=37, 73=23}
            // timestamp % 19 = 0
            // timestamp % 41 = 9
            //

            // Bus Ids: 7,13,x,x,59,x,31,19
            // timestamp % 7 = 0 (0, 7, 21, ...)
            // timestamp % 13 = 1 (14, 27, 40, ...)
        }

        // https://introcs.cs.princeton.edu/java/23recursion/Euclid.java.html
        // // recursive implementation
        // public static int gcd(int p, int q) {
        //     if (q == 0) return p;
        //     else return gcd(q, p % q);
        // }
        //
        // // non-recursive implementation
        // public static int gcd2(int p, int q) {
        //     while (q != 0) {
        //         int temp = q;
        //         q = p % q;
        //         p = temp;
        //     }
        //     return p;
        // }

        private boolean departureIsValid(Long timestamp) {
            for (Long offset : rules.keySet()) {
                Long busId = rules.get(offset);
                if (timestamp % busId != offset) {
                    return false;
                }
            }
            return true;
        }
    }
}