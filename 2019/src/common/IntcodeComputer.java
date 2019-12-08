package common;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class IntcodeComputer {

    public final static int OPCODE_ADD = 1;
    public final static int OPCODE_MULTIPLY = 2;
    public final static int OPCODE_INPUT = 3;
    public final static int OPCODE_OUTPUT = 4;
    public final static int OPCODE_JUMP_IF_TRUE = 5;
    public final static int OPCODE_JUMP_IF_FALSE = 6;
    public final static int OPCODE_LESS_THAN = 7;
    public final static int OPCODE_EQUALS = 8;
    public final static int OPCODE_HALT = 99;

    protected int instructionPointer = 0;
    protected int[] positions;

    protected Queue<Integer> inputs;
    protected Queue<Integer> outputs;
    protected Integer lastOutput = null;

    protected boolean halted = false;

    protected boolean verbose = false;

    protected boolean interruptOnOutput = false;

    public class IntcodeException extends Exception {}

    public class UnknownOpcodeException extends IntcodeException {}

    public class InvalidImmediateException extends IntcodeException {}

    public class WaitingOnInputInterrupt extends IntcodeException {
        public Queue<Integer> outputs;

        public WaitingOnInputInterrupt(Queue<Integer> outputs) {
            this.outputs = outputs;
        }
    }

    public class OutputInterrupt extends IntcodeException {
        public int output;

        public OutputInterrupt(int output) {
            this.output = output;
        }
    }

    public IntcodeComputer(int[] positions) {
        this.positions = positions;
        inputs = new LinkedList<>();
        outputs = new LinkedList<>();
    }

    public static int[] buildInputPositions(String input) {
        String[] values = input.split(",");
        return Arrays.stream(values).mapToInt(Integer::parseInt).toArray();
    }

    public boolean isHalted() {
        return halted;
    }

    public void setVerbose(boolean verbose) {
        this.verbose = verbose;
    }

    public void pushOntoInputs(int input) {
        inputs.add(input);
    }

    public void pushOntoInputs(int[] inputs) {
        for (int input : inputs) {
            this.inputs.add(input);
        }
    }

    public void pushOntoInputs(Queue<Integer> inputs) {
        for (int input : inputs) {
            this.inputs.add(input);
        }
    }

    public int processDay02() throws IntcodeException {
        instructionPointer = 0;
        int opcode = positions[instructionPointer];
        while (opcode != OPCODE_HALT) {
            handleOpcode(opcode);
            opcode = positions[instructionPointer];
        }
        return positions[0];
    }

    public Integer processAndReturnLastOutput(int[] inputs) throws IntcodeException {
        process(inputs);
        return getLastOutput();
    }

    public Queue<Integer> process(int[] inputs) throws IntcodeException {
        pushOntoInputs(inputs);
        return process();
    }

    public Integer processWithFeedback(IntcodeComputer nextComputer) throws IntcodeException {
        interruptOnOutput = true;
        try {
            process();
        }
        catch (IntcodeComputer.WaitingOnInputInterrupt exception) {
            nextComputer.pushOntoInputs(outputs);
            outputs.clear();
            return null;
        }
        catch (OutputInterrupt exception) {
            nextComputer.pushOntoInputs(outputs);
            outputs.clear();
            return null;
        }
        return getLastOutput();
    }

    public Queue<Integer> process() throws IntcodeException {
        int opcode = positions[instructionPointer];
        while (opcode != OPCODE_HALT) {
            handleOpcode(opcode);
            opcode = positions[instructionPointer];
        }
        halted = true;
        // Return all outputs
        return outputs;
    }

    public Integer getLastOutput() {
        return lastOutput;
    }

    protected void logVerbose(String instruction) {
        if (verbose) {
            System.out.println(instruction);
        }
    }

    protected void handleOpcode(int opcode) throws IntcodeException {
        Instruction instruction = new Instruction(opcode);
        int param1 = positions[instructionPointer + 1];
        int item1 = instruction.modeParam1 == Instruction.PARAMETER_MODE_POSITION ? positions[param1] : param1;
        switch (instruction.opcode) {
            case OPCODE_INPUT:
                logVerbose(opcode + " " + param1);
                if (inputs.isEmpty()) {
                    logVerbose("WaitingOnInputInterrupt!");
                    throw new WaitingOnInputInterrupt(outputs);
                }
                positions[param1] = inputs.remove();
                instructionPointer += 2;
                return;
            case OPCODE_OUTPUT:
                logVerbose(opcode + " " + param1);
                outputs.add(item1);
                lastOutput = item1;
                logVerbose("OUTPUT " + item1 + "\n");
                instructionPointer += 2;
                if (interruptOnOutput) {
                    logVerbose("OutputInterrupt!)");
                    throw new OutputInterrupt(item1);
                }
                return;
        }

        int param2 = positions[instructionPointer + 2];
        int item2 = instruction.modeParam2 == Instruction.PARAMETER_MODE_POSITION ? positions[param2] : param2;

        switch (instruction.opcode) {
            case OPCODE_JUMP_IF_TRUE:
                logVerbose(opcode + " " + param1 + " " + param2);
                if (item1 != 0) {
                    instructionPointer = item2;
                } else {
                    instructionPointer += 3;
                }
                return;
            case OPCODE_JUMP_IF_FALSE:
                logVerbose(opcode + " " + param1 + " " + param2);
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

        logVerbose(opcode + " " + param1 + " " + param2 + " " + param3);

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
