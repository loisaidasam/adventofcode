package day04;

public class PasswordChecker {

    protected int min, max;

    public int getMin() {
        return min;
    }

    public int getMax() {
        return max;
    }

    public PasswordChecker(String input) {
        String[] inputs = input.split("-");
        min = Integer.parseInt(inputs[0]);
        max = Integer.parseInt(inputs[1]);
    }

    public boolean isValidPart1(int password) {
        String passwordStr = String.valueOf(password);
        if (passwordStr.length() != 6) {
            return false;
        }
        if (password < min || password > max) {
            return false;
        }
        boolean foundDupe = false;
        for (int index = 1; index < passwordStr.length(); index++) {
            if (passwordStr.charAt(index - 1) > passwordStr.charAt(index)) {
                return false;
            }
            if (passwordStr.charAt(index - 1) == passwordStr.charAt(index)) {
                foundDupe = true;
            }
        }
        return foundDupe;
    }

    public boolean isValidPart2(int password) {
        if (! isValidPart1(password)) {
            return false;
        }
        String passwordStr = String.valueOf(password);
        char letter = passwordStr.charAt(0);
        char nextLetter;
        int runLength = 1;
        for (int index = 1; index < passwordStr.length(); index++) {
            nextLetter = passwordStr.charAt(index);
            if (letter == nextLetter) {
                runLength++;
            } else {
                if (runLength == 2) {
                    return true;
                }
                runLength = 1;
            }
            letter = nextLetter;
        }
        return runLength == 2;
    }
}
