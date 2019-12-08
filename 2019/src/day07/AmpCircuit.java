package day07;

import day05.IntcodeComputer;

import java.util.Arrays;
import java.util.List;

public class AmpCircuit {
    protected int[] ampControllerSoftware;
    protected IntcodeComputer ampA, ampB, ampC, ampD, ampE;

    public AmpCircuit(int[] ampControllerSoftware) {
        this.ampControllerSoftware = ampControllerSoftware;
    }

    public int findLargestOutputSignal() throws day02.IntcodeComputer.IntcodeException {
        int outputSignal;
        int maxOutputSignal = -1;
        List<int[]> phaseSettingSequences = Permutations.getPermutations(5);
        for (int[] phaseSettingSequence : phaseSettingSequences) {
            System.out.println(Arrays.toString(phaseSettingSequence));
            outputSignal = getOutputSignal(phaseSettingSequence);
            System.out.println(outputSignal);
            if (outputSignal > maxOutputSignal) {
                maxOutputSignal = outputSignal;
            }
        }
        return maxOutputSignal;
    }

    protected int getOutputSignal(int[] phaseSettingSequence) throws day02.IntcodeComputer.IntcodeException {
        int inputSignal = 0;
        int[] inputs;

        ampA = new IntcodeComputer(ampControllerSoftware.clone());
        inputs = new int[] {phaseSettingSequence[0], inputSignal};
        inputSignal = ampA.process(inputs);

        ampB = new IntcodeComputer(ampControllerSoftware.clone());
        inputs = new int[] {phaseSettingSequence[1], inputSignal};
        inputSignal = ampB.process(inputs);

        ampC = new IntcodeComputer(ampControllerSoftware.clone());
        inputs = new int[] {phaseSettingSequence[2], inputSignal};
        inputSignal = ampC.process(inputs);

        ampD = new IntcodeComputer(ampControllerSoftware.clone());
        inputs = new int[] {phaseSettingSequence[3], inputSignal};
        inputSignal = ampD.process(inputs);

        ampE = new IntcodeComputer(ampControllerSoftware.clone());
        inputs = new int[] {phaseSettingSequence[4], inputSignal};
        return ampE.process(inputs);
    }
}
