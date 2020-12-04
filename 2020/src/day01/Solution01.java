package day01;

import common.BaseSolution;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Solution01 extends BaseSolution {

    private final List<Integer> inputs;

    public static void main(String[] args) throws Exception {
        new Solution01().run();
    }

   public Solution01() {
        inputs = getInputInts();
   }

    @Override
    public Integer part1Int() throws Exception {
        return find2020NumsOnePass(inputs);
    }

    /**
     * O(N) approach that only does one pass. O(N) storage.
     *
     * O(N^2) approach would be checking all values against all values, but would only require O(1) storage.
     *
     * @param inputs
     * @return
     */
    private Integer find2020NumsOnePass(List<Integer> inputs) {
        Set<Integer> seenEntries = new HashSet();
        for (Integer input : inputs) {
            int otherValue = 2020 - input;
            if (seenEntries.contains(otherValue)) {
                return input * otherValue;
            }
            seenEntries.add(input);
        }
        return null;
    }

    @Override
    public Integer part2Int() throws Exception {
        return findThree2020NumsBruteForce(inputs);
    }

    /**
     * O(N^3) approach
     *
     * TODO: Come up with a faster solution
     *
     * @param inputs
     * @return
     */
    private Integer findThree2020NumsBruteForce(List<Integer> inputs) {
        for (int i = 0; i < inputs.size(); i++) {
            for (int j = 0; j < inputs.size(); j++) {
                for (int k = 0; k < inputs.size(); k++) {
                    if (i == j || i == k || i == k) {
                        continue;
                    }
                    if (inputs.get(i) + inputs.get(j) + inputs.get(k) == 2020) {
                        return inputs.get(i) * inputs.get(j) * inputs.get(k);
                    }
                }
            }
        }
        return null;
    }
}
