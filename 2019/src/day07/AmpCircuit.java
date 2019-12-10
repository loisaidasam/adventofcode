package day07;

import common.IntcodeComputer;

import java.util.List;

public class AmpCircuit {
    protected int[] ampControllerSoftware;
    protected IntcodeComputer ampA, ampB, ampC, ampD, ampE;

    public AmpCircuit(int[] ampControllerSoftware) {
        this.ampControllerSoftware = ampControllerSoftware;
    }

    public int findLargestOutputSignal() throws IntcodeComputer.IntcodeException {
        int outputSignal;
        int maxOutputSignal = -1;
        List<int[]> phaseSettingSequences = Permutations.getPermutations(5);
        for (int[] phaseSettingSequence : phaseSettingSequences) {
            // System.out.println(Arrays.toString(phaseSettingSequence));
            outputSignal = getOutputSignal(phaseSettingSequence);
            // System.out.println(outputSignal);
            if (outputSignal > maxOutputSignal) {
                maxOutputSignal = outputSignal;
            }
        }
        return maxOutputSignal;
    }

    protected int getOutputSignal(int[] phaseSettingSequence) throws IntcodeComputer.IntcodeException {
        int inputSignal = 0;
        int[] inputs;

        ampA = new IntcodeComputer(ampControllerSoftware.clone());
        inputs = new int[] {phaseSettingSequence[0], inputSignal};
        inputSignal = ampA.processAndReturnLastOutput(inputs);

        ampB = new IntcodeComputer(ampControllerSoftware.clone());
        inputs = new int[] {phaseSettingSequence[1], inputSignal};
        inputSignal = ampB.processAndReturnLastOutput(inputs);

        ampC = new IntcodeComputer(ampControllerSoftware.clone());
        inputs = new int[] {phaseSettingSequence[2], inputSignal};
        inputSignal = ampC.processAndReturnLastOutput(inputs);

        ampD = new IntcodeComputer(ampControllerSoftware.clone());
        inputs = new int[] {phaseSettingSequence[3], inputSignal};
        inputSignal = ampD.processAndReturnLastOutput(inputs);

        ampE = new IntcodeComputer(ampControllerSoftware.clone());
        inputs = new int[] {phaseSettingSequence[4], inputSignal};
        return ampE.processAndReturnLastOutput(inputs);
    }

    public int findLargestOutputSignalWithFeedback() throws IntcodeComputer.IntcodeException {
        int outputSignal;
        int maxOutputSignal = -1;

        List<int[]> phaseSettingSequences = Permutations.getPermutations(new int[] {5, 6, 7, 8, 9});
        for (int[] phaseSettingSequence : phaseSettingSequences) {
            // System.out.println(Arrays.toString(phaseSettingSequence));
            outputSignal = getOutputSignalFeedback(phaseSettingSequence);
            // System.out.println(outputSignal);
            if (outputSignal > maxOutputSignal) {
                maxOutputSignal = outputSignal;
            }
        }
        return maxOutputSignal;
    }

    protected int getOutputSignalFeedback(int[] phaseSettingSequence) throws IntcodeComputer.IntcodeException {
        ampA = new IntcodeComputer(ampControllerSoftware.clone());
        ampA.pushOntoInputs(new int[]{phaseSettingSequence[0], 0});
        ampB = new IntcodeComputer(ampControllerSoftware.clone());
        ampB.pushOntoInputs(phaseSettingSequence[1]);
        ampC = new IntcodeComputer(ampControllerSoftware.clone());
        ampC.pushOntoInputs(phaseSettingSequence[2]);
        ampD = new IntcodeComputer(ampControllerSoftware.clone());
        ampD.pushOntoInputs(phaseSettingSequence[3]);
        ampE = new IntcodeComputer(ampControllerSoftware.clone());
        ampE.pushOntoInputs(phaseSettingSequence[4]);

        while (true) {
            // System.out.println("ampA...");
            ampA.processWithFeedback(ampB);
            // System.out.println("ampB...");
            ampB.processWithFeedback(ampC);
            // System.out.println("ampC...");
            ampC.processWithFeedback(ampD);
            // System.out.println("ampD...");
            ampD.processWithFeedback(ampE);
            // System.out.println("ampE...");
            ampE.processWithFeedback(ampA);

            if (ampA.isHalted() && ampB.isHalted() && ampC.isHalted() && ampD.isHalted() && ampE.isHalted()) {
                return ampE.getLastOutput().intValue();
            }
        }
    }

    // public static void main(String[] args) throws IntcodeComputer.IntcodeException {
    //     // This one should result in 139629729
    //     int[] software = {3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5};
    //     int[] phaseSettingSequence = {9,8,7,6,5};
    //
    //     // This one should result in 18216
    //     // int[] software = {3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,-5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10};
    //     // int[] phaseSettingSequence = {9,7,8,5,6};
    //
    //     int outputSignal = new AmpCircuit(software).getOutputSignalFeedback(phaseSettingSequence);
    //     System.out.println(outputSignal);
    // }
}
