package day07;

import common.BaseSolution;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class Solution07 extends BaseSolution {

    public String getInputFilename() {
        return "input-wrangled.txt";
    }

    Map<String, Set<String>> bagMap;

    protected InputType getInputType() {
        return InputType.STRINGS;
    }

    public static void main(String[] args) throws Exception {
        new Solution07().run();
    }

    public Solution07() {
        super();
        buildBagMap();
    }

    @Override
    protected Integer part1Int() {
        Set<String> validBags = new HashSet();
        validBags.addAll(bagMap.get("shiny gold"));
        int lastNum = 0;
        while (validBags.size() > lastNum) {
            lastNum = validBags.size();
            System.out.println("Valid bags: " + validBags);
            for (String bag : validBags.toArray(new String[0])) {
                if (! bagMap.containsKey(bag)) {
                    continue;
                }
                // System.out.println(bag);
                validBags.addAll(bagMap.get(bag));
            }
        }
        return validBags.size();
    }

    private void buildBagMap() {
        bagMap = new HashMap<>();
        for (String input : inputStrs) {
            // light violet,2 striped magenta,5 light lime,5 posh cyan
            String[] pieces = input.split(",");
            String outerBag = "";
            for (int i = 0; i < pieces.length; i++) {
                if (i == 0) {
                    outerBag = pieces[0];
                    continue;
                }
                String bag = pieces[i];
                // Discard the first part (the number)
                bag = bag.substring(bag.indexOf(" ") + 1);
                if (! bagMap.containsKey(bag)) {
                    bagMap.put(bag, new HashSet<>());
                }
                bagMap.get(bag).add(outerBag);
            }
        }
        // System.out.println(bagMap);
    }
}