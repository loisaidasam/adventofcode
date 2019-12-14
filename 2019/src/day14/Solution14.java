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
        inputFilename = "input-test-2.txt";
    }

    @Override
    public String part1() throws Exception {
        List<Reaction> reactionList = Reaction.parseReactionStrings(getInputStrings());
        for (int numOreNeeded = 0; true; numOreNeeded++) {
            NanoFactory nanoFactory = new NanoFactory(reactionList);
            nanoFactory.addIngredient(new Ingredient(numOreNeeded, Ingredient.INGREDIENT_ORE));
            System.out.println("Trying " + nanoFactory + " ...");
            if (nanoFactory.canMakeOneFuel()) {
                return String.valueOf(numOreNeeded);
            }
        }
    }

    @Override
    public String part2() throws Exception {
        return null;
    }
}
