package day02;

import common.BaseSolution;

public class Solution02 extends BaseSolution {

    public static void main(String[] args) throws Exception {
        new Solution02().run();
    }

    protected InputType getInputType() {
        return InputType.STRINGS;
    }

    @Override
    public Integer part1Int() throws Exception {
        int numValid = 0;
        for (String input : inputStrs) {
            if (isValidCount(input)) {
                numValid++;
            }
        }
        return numValid;
    }

    @Override
    public Integer part2Int() {
        int numValid = 0;
        for (String input : inputStrs) {
            if (isValidPositions(input)) {
                numValid++;
            }
        }
        return numValid;
    }

    protected boolean isValidCount(String input) {
        String[] pieces = input.split(" ");
        int lowest = Integer.valueOf(pieces[0].split("-")[0]);
        int highest = Integer.valueOf(pieces[0].split("-")[1]);
        char letter = pieces[1].charAt(0);
        String password = pieces[2];

        int letterCount = 0;
        for (int i = 0; i < password.length(); i++) {
            char passwordLetter = password.charAt(i);
            if (passwordLetter == letter) {
                letterCount++;
            }
        }
        return lowest <= letterCount && letterCount <= highest;
    }

    /**
     * TODO: Not copy/pasta
     * @param input
     * @return
     */
    protected boolean isValidPositions(String input) {
        String[] pieces = input.split(" ");
        int first = Integer.valueOf(pieces[0].split("-")[0]);
        int second = Integer.valueOf(pieces[0].split("-")[1]);
        char letter = pieces[1].charAt(0);
        String password = pieces[2];
        boolean firstMatch = letter == password.charAt(first - 1);
        boolean secondMatch = letter == password.charAt(second - 1);
        return firstMatch ^ secondMatch;
    }
}
