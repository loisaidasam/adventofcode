package day16;

import common.BaseSolution;
import common.Solution;

public class Solution16 extends BaseSolution implements Solution {

    protected final int[] pattern = {0, 1, 0, -1};

    public static void main(String[] args) throws Exception {
        new Solution16().run();
    }

   public Solution16() {
       super();
       inputFilename = "input-test-5.txt";
   }

    // @Override
    // public String part1() throws Exception {
    //     FFT fft = new FFT(pattern, getInputReader().next());
    //     return fft.executeNPhases(100).substring(0, 8);
    // }

    @Override
    public String part2() throws Exception {
        String input = getInputReader().next();
        int offset = Integer.parseInt(input.substring(0, 7));
        String fftInput = "";
        for (int i = 0; i < 10000; i++) {
            fftInput += input;
        }
        System.out.println("Input size: " + fftInput.length());
        FFT fft = new FFT(pattern, fftInput);
        String result = fft.executeNPhases(100);
        return result.substring(offset, offset+8);
    }
}
