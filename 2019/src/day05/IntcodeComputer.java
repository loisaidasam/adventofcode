package day05;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class IntcodeComputer extends day02.IntcodeComputer {

    public final static int OPCODE_INPUT = 3;
    public final static int OPCODE_OUTPUT = 4;
    public final static int OPCODE_JUMP_IF_TRUE = 5;
    public final static int OPCODE_JUMP_IF_FALSE = 6;
    public final static int OPCODE_LESS_THAN = 7;
    public final static int OPCODE_EQUALS = 8;

    protected Queue<Integer> inputs;
    protected List<Integer> outputs;

    public class InvalidImmediateException extends IntcodeException {}

    public IntcodeComputer(int[] positions) {
        super(positions);
    }

    public int process(int[] inputs) throws IntcodeException {
        this.inputs = new LinkedList<>();
        for (int input : inputs) {
            this.inputs.add(input);
        }
        outputs = new ArrayList<>();

        int opcode = positions[instructionPointer];
        while (opcode != OPCODE_HALT) {
            handleOpcode(opcode);
            opcode = positions[instructionPointer];
        }
        // Return the last output
        return outputs.get(outputs.size() - 1);
    }

    protected void handleOpcode(int opcode) throws IntcodeException {
        Instruction instruction = new Instruction(opcode);
        int param1 = positions[instructionPointer + 1];
        int item1 = instruction.modeParam1 == Instruction.PARAMETER_MODE_POSITION ? positions[param1] : param1;
        switch (instruction.opcode) {
            case OPCODE_INPUT:
                // System.out.println(opcode + " " + param1);
                positions[param1] = inputs.remove();
                instructionPointer += 2;
                return;
            case OPCODE_OUTPUT:
                // System.out.println(opcode + " " + param1);
                outputs.add(item1);
                // System.out.println("OUTPUT " + item1 + "\n");
                instructionPointer += 2;
                return;
        }

        int param2 = positions[instructionPointer + 2];
        int item2 = instruction.modeParam2 == Instruction.PARAMETER_MODE_POSITION ? positions[param2] : param2;

        switch (instruction.opcode) {
            case OPCODE_JUMP_IF_TRUE:
                // System.out.println(opcode + " " + param1 + " " + param2);
                if (item1 != 0) {
                    instructionPointer = item2;
                } else {
                    instructionPointer += 3;
                }
                return;
            case OPCODE_JUMP_IF_FALSE:
                // System.out.println(opcode + " " + param1 + " " + param2);
                if (item1 == 0) {
                    instructionPointer = item2;
                } else {
                    instructionPointer += 3;
                }
                return;
        }

        int param3 = positions[instructionPointer + 3];
        // Confirm that param 3 can never be in immediate mode
        if (instruction.modeParam3 == Instruction.PARAMETER_MODE_IMMEDIATE) {
            throw new InvalidImmediateException();
        }

        // System.out.println(opcode + " " + param1 + " " + param2 + " " + param3);

        switch (instruction.opcode) {
            case OPCODE_ADD:
                positions[param3] = item1 + item2;
                break;
            case OPCODE_MULTIPLY:
                positions[param3] = item1 * item2;
                break;
            case OPCODE_LESS_THAN:
                positions[param3] = item1 < item2 ? 1 : 0;
                break;
            case OPCODE_EQUALS:
                positions[param3] = item1 == item2 ? 1 : 0;
                break;
            default:
                throw new UnknownOpcodeException();
        }
        instructionPointer += 4;
    }
}
