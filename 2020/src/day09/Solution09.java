package day09;

import common.BaseSolution;
import common.LongSolution;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;

public class Solution09 extends BaseSolution implements LongSolution {

    private Long firstInvalidNumber;

    protected BaseSolution.InputType getInputType() {
        return InputType.LONGS;
    }

    public static void main(String[] args) throws Exception {
        new Solution09().run();
    }

    public Solution09() {
        super();
        firstInvalidNumber = findFirstInvalidNumber();
    }

    public class XMASCipher {
        private int preambleSize;
        private Set<Long> set;
        private Queue<Long> queue;

        public XMASCipher(int preambleSize) {
            this.preambleSize = preambleSize;
            set = new HashSet<>();
            queue = new LinkedList<>();
        }

        public void insert(Long value) {
            if (queue.size() >= preambleSize) {
                set.remove(queue.poll());
            }
            queue.offer(value);
            set.add(value);
        }

        public boolean isValid(Long value) {
            for (long part1 : queue) {
                long part2 = value - part1;
                if (part1 != part2 && set.contains(part2)) {
                    return true;
                }
            }
            return false;
        }
    }

    private Long findFirstInvalidNumber() {
        XMASCipher cipher = new XMASCipher(25);
        for (int i = 0; i < inputLongs.size(); i++) {
            long input = inputLongs.get(i);
            if (i < 25) {
                cipher.insert(input);
                continue;
            }
            if (! cipher.isValid(input)) {
                return input;
            }
            cipher.insert(input);
        }
        return null;
    }

    @Override
    public Long part1Long() throws Exception {
        return firstInvalidNumber;
    }

    @Override
    public Long part2Long() throws Exception {
        for (int i = 0; i < inputLongs.size(); i++) {
            for (int j = i + 1; j < inputLongs.size(); j++) {
                long sum = 0;
                long smallest = inputLongs.get(i);
                long largest = inputLongs.get(i);
                for (int k = i; k <= j; k++) {
                    sum += inputLongs.get(k);
                    if (inputLongs.get(k) < smallest) {
                        smallest = inputLongs.get(k);
                    }
                    if (inputLongs.get(k) > largest) {
                        largest = inputLongs.get(k);
                    }
                }
                // System.out.println("==> i=" + i + " j=" + j + " sum=" + sum);
                if (sum == firstInvalidNumber) {
                    return smallest + largest;
                }
            }
        }
        return null;
    }
}
