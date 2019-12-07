package day02;

import java.util.Arrays;

public class IntcodeComputer {
    public final static int OPCODE_ADD = 1;
    public final static int OPCODE_MULTIPLY = 2;
    public final static int OPCODE_HALT = 99;

    protected int instructionPointer = 0;
    protected int[] positions;

    public class IntcodeException extends Exception {}

    public class UnknownOpcodeException extends IntcodeException {}

    public IntcodeComputer(int[] positions) {
        this.positions = positions;
    }

    public static int[] buildInputPositions(String input) {
        String[] values = input.split(",");
        return Arrays.stream(values).mapToInt(Integer::parseInt).toArray();
    }

    public String toString() {
        String[] positionsStrings4 = Arrays.stream(Arrays.copyOfRange(positions, instructionPointer, instructionPointer + 4))
                .mapToObj(String::valueOf)
                .toArray(String[]::new);
        String[] positionsStrings = Arrays.stream(positions)
                .mapToObj(String::valueOf)
                .toArray(String[]::new);
        String positionsStr4 = String.join(",", positionsStrings4);
        String positionsStr = String.join(",", positionsStrings);
        return "Position " + instructionPointer + " / " + positionsStr4 + " / " + positionsStr;
    }

    public int process() throws IntcodeException {
        instructionPointer = 0;
        int opcode = positions[instructionPointer];
        while (opcode != OPCODE_HALT) {
            handleOpcode(opcode);
            opcode = positions[instructionPointer];
        }
        return positions[0];
    }

    protected void handleOpcode(int opcode) throws IntcodeException {
        if (opcode == OPCODE_ADD) {
            positions[positions[instructionPointer + 3]] = positions[positions[instructionPointer + 1]] +
                    positions[positions[instructionPointer + 2]];
        } else if (opcode == OPCODE_MULTIPLY) {
            positions[positions[instructionPointer + 3]] = positions[positions[instructionPointer + 1]] *
                    positions[positions[instructionPointer + 2]];
        } else {
            throw new UnknownOpcodeException();
        }
        instructionPointer += 4;
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
