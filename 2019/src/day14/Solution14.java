package day14;

import common.BaseSolution;
import common.Solution;

import java.util.List;

public class Solution14 extends BaseSolution implements Solution {

    public static void main(String[] args) throws Exception {
        new Solution14().run();
    }

    public Solution14() {
        super();
        inputFilename = "input-test-3.txt";
    }

    @Override
    public String part1() throws Exception {
        List<Reaction> reactionList = Reaction.parseReactionStrings(getInputStrings());
        NanoFactory nanoFactory = new NanoFactory(reactionList);
        return String.valueOf(nanoFactory.numOreNeededForOneFuel());
    }

    @Override
    public String part2() throws Exception {
        return null;
    }
}
