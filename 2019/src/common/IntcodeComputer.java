package common;

import java.math.BigInteger;
import java.util.*;

public class IntcodeComputer {

    public final static int OPCODE_ADD = 1;
    public final static int OPCODE_MULTIPLY = 2;
    public final static int OPCODE_INPUT = 3;
    public final static int OPCODE_OUTPUT = 4;
    public final static int OPCODE_JUMP_IF_TRUE = 5;
    public final static int OPCODE_JUMP_IF_FALSE = 6;
    public final static int OPCODE_LESS_THAN = 7;
    public final static int OPCODE_EQUALS = 8;
    public final static int OPCODE_ADJUST_RELATIVE_BASE = 9;
    public final static int OPCODE_HALT = 99;

    protected int instructionPointer = 0;
    protected int relativeBase = 0;
    protected Map<Integer, BigInteger> positions;

    protected Queue<BigInteger> inputs;
    protected Queue<BigInteger> outputs;
    protected BigInteger lastOutput = null;

    protected boolean halted = false;

    protected boolean verbose = false;

    protected boolean interruptOnOutput = false;

    public class IntcodeException extends Exception {}

    public class UnknownOpcodeException extends IntcodeException {}

    public class InvalidImmediateException extends IntcodeException {}

    public class WaitingOnInputInterrupt extends IntcodeException {}

    public class OutputInterrupt extends IntcodeException {}

    public class UnknownParameterModeException extends IntcodeException {}

    public IntcodeComputer(int[] positions) {
        setup();
        setPositions(positions);
    }

    public IntcodeComputer(BigInteger[] positions) {
        setup();
        setPositions(positions);
    }

    protected void setup() {
        this.positions = new HashMap<>();
        inputs = new LinkedList<>();
        outputs = new LinkedList<>();
    }

    public static int[] buildInputPositions(String input) {
        String[] values = input.split(",");
        return Arrays.stream(values).mapToInt(Integer::parseInt).toArray();
    }

    public static BigInteger[] buildInputPositionsBigInteger(String input) {
        String[] values = input.split(",");
        BigInteger[] inputPositions = new BigInteger[values.length];
        for (int i = 0; i < values.length; i++) {
            inputPositions[i] = new BigInteger(values[i]);
        }
        return inputPositions;
    }

    public boolean isHalted() {
        return halted;
    }

    public void setVerbose(boolean verbose) {
        this.verbose = verbose;
    }

    public void setInterruptOnOutput(boolean interruptOnOutput) {
        this.interruptOnOutput = interruptOnOutput;
    }

    public void pushOntoInputs(BigInteger input) {
        inputs.add(input);
    }

    public void pushOntoInputs(int input) {
        pushOntoInputs(BigInteger.valueOf(input));
    }

    public void pushOntoInputs(int[] inputs) {
        for (int input : inputs) {
            pushOntoInputs(input);
        }
    }

    public void pushOntoInputs(Queue<BigInteger> inputs) {
        for (BigInteger input : inputs) {
            pushOntoInputs(input);
        }
    }

    protected void setPositions(int[] positions) {
        BigInteger[] positionsBigInteger =
                (BigInteger[]) Arrays.stream(positions).mapToObj(BigInteger::valueOf).toArray();
        setPositions(positionsBigInteger);
    }

    protected void setPositions(BigInteger[] positions) {
        for (int i = 0; i < positions.length; i++) {
            setPosition(i, positions[i]);
        }
    }

    public void setPosition(int position, BigInteger value) {
        this.positions.put(position, value);
    }

    public int processDay02() throws IntcodeException {
        process();
        return outputs.peek().intValue();
    }

    public int processAndReturnLastOutput(int[] inputs) throws IntcodeException {
        process(inputs);
        return getLastOutput().intValue();
    }

    public Queue<BigInteger> process(int[] inputs) throws IntcodeException {
        pushOntoInputs(inputs);
        return process();
    }

    public BigInteger processWithFeedback(IntcodeComputer nextComputer) throws IntcodeException {
        setInterruptOnOutput(true);
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

    public Queue<BigInteger> process() throws IntcodeException {
        int opcode = getPositionValue().intValue();
        while (opcode != OPCODE_HALT) {
            handleOpcode(opcode);
            opcode = getPositionValue().intValue();
        }
        halted = true;
        // Return all outputs
        return outputs;
    }

    public Queue<BigInteger> processUntilNOutputs(int numOutputs) throws IntcodeException {
        setInterruptOnOutput(true);
        for (int i = 0; i < numOutputs; i++) {
            try {
                process();
                // System.out.println("Processed with no OutputInterrupt, returning outputs: " + outputs);
                return outputs;
            } catch (OutputInterrupt exception) {
                // System.out.println("Caught OutputInterrupt on i=" + i + " " + exception);
            }
        }
        return outputs;
    }

    public BigInteger getLastOutput() {
        return lastOutput;
    }

    protected BigInteger getPositionValue() {
        return getPositionValue(instructionPointer);
    }

    protected BigInteger getPositionValue(int position) {
        // Default to 0
        if (! positions.containsKey(position)) {
            return BigInteger.valueOf(0);
        }
        return positions.get(position);
    }

    protected void logVerbose(String message) {
        if (verbose) {
            System.out.println(message);
//            logPositions();
        }
    }

    protected void logPositions() {
        String message = "\t";
        for (int position : positions.keySet()) {
            message += position + "=" + positions.get(position) + " ";
        }
        System.out.println(message);
    }

    protected BigInteger getItemValue(int mode, BigInteger param) throws UnknownParameterModeException {
        switch (mode) {
            case Instruction.PARAMETER_MODE_POSITION:
                return getPositionValue(param.intValue());
            case Instruction.PARAMETER_MODE_IMMEDIATE:
                return param;
            case Instruction.PARAMETER_MODE_RELATIVE:
                return getPositionValue(relativeBase + param.intValue());
        }
        throw new UnknownParameterModeException();
    }

    protected int getDestinationPosition(int mode, BigInteger param)
            throws InvalidImmediateException, UnknownParameterModeException {
        switch (mode) {
            case Instruction.PARAMETER_MODE_POSITION:
                return param.intValue();
            case Instruction.PARAMETER_MODE_IMMEDIATE:
                // Confirm that destination param can never be in immediate mode
                throw new InvalidImmediateException();
            case Instruction.PARAMETER_MODE_RELATIVE:
                return relativeBase + param.intValue();
        }
        throw new UnknownParameterModeException();
    }

    protected void handleOpcode(int opcode) throws IntcodeException {
        Instruction instruction = new Instruction(opcode);
        int destination;
        BigInteger result;

        BigInteger param1 = getPositionValue(instructionPointer + 1);
        BigInteger item1 = getItemValue(instruction.modeParam1, param1);
        switch (instruction.opcode) {
            case OPCODE_INPUT:
                if (inputs.isEmpty()) {
                    logVerbose("WaitingOnInputInterrupt!");
                    throw new WaitingOnInputInterrupt();
                }
                destination = getDestinationPosition(instruction.modeParam1, param1);
                result = inputs.remove();
                logVerbose("INPUT\t" + opcode + " " + param1 +
                        " (" + result + " -> " + destination + ")");
                positions.put(destination, result);
                instructionPointer += 2;
                return;
            case OPCODE_OUTPUT:
                logVerbose("OUTPUT\t" + opcode + " " + param1 + " (" + item1 + ")");
                outputs.add(item1);
                lastOutput = item1;
                logVerbose("output=" + item1 + "\n");
                instructionPointer += 2;
                if (interruptOnOutput) {
                    logVerbose("OutputInterrupt!)");
                    throw new OutputInterrupt();
                }
                return;
            case OPCODE_ADJUST_RELATIVE_BASE:
                relativeBase += item1.intValue();
                logVerbose("ADJUST_RELATIVE_BASE\t" + opcode + " " + param1 +
                        " (+ " + item1 + ", " + relativeBase + ")");
                instructionPointer += 2;
                return;
        }

        BigInteger param2 = getPositionValue(instructionPointer + 2);
        BigInteger item2 = getItemValue(instruction.modeParam2, param2);

        boolean jump;
        switch (instruction.opcode) {
            case OPCODE_JUMP_IF_TRUE:
                jump = ! item1.equals(BigInteger.valueOf(0));
                logVerbose("JUMP_IF_TRUE\t" + opcode + " " + param1 + " " + param2 +
                        " (" + item1 + " != 0, " + jump + ")");
                if (jump) {
                    instructionPointer = item2.intValue();
                } else {
                    instructionPointer += 3;
                }
                return;
            case OPCODE_JUMP_IF_FALSE:
                jump = item1.equals(BigInteger.valueOf(0));
                logVerbose("JUMP_IF_FALSE\t" + opcode + " " + param1 + " " + param2 +
                        " (" + item1 + " == 0, " + jump + ")");
                if (jump) {
                    instructionPointer = item2.intValue();
                } else {
                    instructionPointer += 3;
                }
                return;
        }

        BigInteger param3 = getPositionValue(instructionPointer + 3);
        destination = getDestinationPosition(instruction.modeParam3, param3);
        switch (instruction.opcode) {
            case OPCODE_ADD:
                result = item1.add(item2);
                logVerbose("ADD\t" + opcode + " " + param1 + " " + param2 + " " + param3 +
                        " (" + item1 + " + " + item2 + " -> " + destination + ", " + result + ")");
                positions.put(destination, result);
                break;
            case OPCODE_MULTIPLY:
                result = item1.multiply(item2);
                logVerbose("MULTIPLY\t" + opcode + " " + param1 + " " + param2 + " " + param3 +
                        " (" + item1 + " * " + item2 + " -> " + destination + ", " + result + ")");
                positions.put(destination, result);
                break;
            case OPCODE_LESS_THAN:
                result = BigInteger.valueOf(item1.compareTo(item2) < 0 ? 1 : 0);
                logVerbose("LESS_THAN\t" + opcode + " " + param1 + " " + param2 + " " + param3 +
                        " (" + item1 + " < " + item2 + " -> " + destination + ", " + result + ")");
                positions.put(destination, result);
                break;
            case OPCODE_EQUALS:
                result = BigInteger.valueOf(item1.equals(item2) ? 1 : 0);
                logVerbose("EQUALS\t" + opcode + " " + param1 + " " + param2 + " " + param3 +
                        " (" + item1 + " == " + item2 + " -> " + destination + ", " + result + ")");
                positions.put(destination, result);
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
        positions.put(1, BigInteger.valueOf(noun));
        positions.put(2, BigInteger.valueOf(verb));
    }
}
