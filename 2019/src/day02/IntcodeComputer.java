package day02;

import java.util.Arrays;

public class IntcodeComputer {
    public static int OPCODE_ADD = 1;
    public static int OPCODE_MULTIPLY = 2;
    public static int OPCODE_HALT = 99;

    protected int position;
    protected int[] positions;

    public class UnknownOpcodeException extends Exception {
    }

    public IntcodeComputer(int[] positions) {
        this.positions = positions;
    }

    public String toString() {
        String[] positionsStrings4 = Arrays.stream(Arrays.copyOfRange(positions, position, position + 4))
                .mapToObj(String::valueOf)
                .toArray(String[]::new);
        String[] positionsStrings = Arrays.stream(positions)
                .mapToObj(String::valueOf)
                .toArray(String[]::new);
        String positionsStr4 = String.join(",", positionsStrings4);
        String positionsStr = String.join(",", positionsStrings);
        return "Position " + position + " / " + positionsStr4 + " / " + positionsStr;
    }

    public int process() throws UnknownOpcodeException {
        position = 0;
        int opcode = positions[position];
        while (opcode != OPCODE_HALT) {
            if (opcode == OPCODE_ADD) {
                positions[positions[position + 3]] = positions[positions[position + 1]] +
                        positions[positions[position + 2]];
            } else if (opcode == OPCODE_MULTIPLY) {
                positions[positions[position + 3]] = positions[positions[position + 1]] *
                        positions[positions[position + 2]];
            } else {
                throw new UnknownOpcodeException();
            }
            position += 4;
            opcode = positions[position];
        }
        return positions[0];
    }

    /**
     * https://www.hq.nasa.gov/alsj/a11/a11.landing.html#1023832
     */
    public void restoreTo1202ProgramAlarmState() {
        restoreToState(12, 2);
    }

    public void restoreToState(int noun, int verb) {
        positions[1] = noun;
        positions[2] = verb;
    }
}
