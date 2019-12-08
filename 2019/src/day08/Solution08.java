package day08;

import common.BaseSolution;

public class Solution08 extends BaseSolution implements common.Solution {

    protected SpaceImageFormatEncoder encoder;

    public Solution08() {
        super();
        String imageData = getInputReader().next();
        encoder = new SpaceImageFormatEncoder(25, 6, imageData);
    }

    public static void main(String[] args) throws Exception {
        new Solution08().run();
    }

    @Override
    public String part1() throws Exception {
        // return encoder.toString();
        int layerWithFewestZeros = encoder.findLayerWithFewestOfDigit('0');
        int result = encoder.findLayerDigitCount(layerWithFewestZeros, '1') *
                encoder.findLayerDigitCount(layerWithFewestZeros, '2');
        return String.valueOf(result);
    }

    @Override
    public String part2() throws Exception {
        System.out.println(encoder.decode());
        return null;
    }
}
