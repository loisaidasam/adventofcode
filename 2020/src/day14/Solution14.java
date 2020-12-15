package day14;

import common.BaseSolution;
import common.LongSolution;

import java.util.HashMap;
import java.util.Map;

public class Solution14 extends BaseSolution implements LongSolution {

    public static void main(String[] args) throws Exception {
        new Solution14().run();
    }

    @Override
    public InputType getInputType() {
        return InputType.STRINGS;
    }

    @Override
    public String getInputFilename() {
        return "input-wrangled.txt";
    }

    @Override
    public Long part1Long() throws Exception {
        try {
            testMask();
        } catch (Exception e) {
            e.printStackTrace();
        }
        Mask mask = new Mask();
        Map<Long, Long> memory = new HashMap<>();
        for (String input : inputStrs) {
            String[] pieces = input.split(",");
            if (pieces[0].equals("mask")) {
                mask = new Mask(pieces[1]);
                // System.out.println(mask);
            } else if (pieces[0].equals("mem")) {
                Long key = Long.parseLong(pieces[1]);
                Long value = Long.parseLong(pieces[2]);
                // System.out.print("mem[" + key + "] = " + value + " -> ");
                value = mask.applyMask(value);
                // System.out.println(value);
                memory.put(key, value);
            } else {
                System.err.println("Unknown input: " + input);
            }
        }
        Long result = 0L;
        for (Long value : memory.values()) {
            result += value;
        }
        return result;
    }

    public void testMask() throws Exception {
        System.out.println("Running tests ...");

        // Silly tests
        Mask mask = new Mask("0");
        assert Long.toBinaryString(mask.getMaskAND()).equals("0");
        assert Long.toBinaryString(mask.getMaskOR()).equals("0");
        assert mask.applyMask(1L) == 0;
        assert mask.applyMask(0L) == 0;
        mask = new Mask("1");
        assert Long.toBinaryString(mask.getMaskAND()).equals("1");
        assert Long.toBinaryString(mask.getMaskOR()).equals("1");
        assert mask.applyMask(1L) == 1;
        assert mask.applyMask(0L) == 1;
        mask = new Mask("X");
        assert Long.toBinaryString(mask.getMaskAND()).equals("1");
        assert Long.toBinaryString(mask.getMaskOR()).equals("0");
        assert mask.applyMask(1L) == 1;
        assert mask.applyMask(0L) == 0;

        // Basic test
        mask = new Mask("1X0X");

        assert mask.getMaskAND() == Long.parseLong("1101", 2);
        assert mask.getMaskAND() == 13L;
        assert mask.getMaskOR() == Long.parseLong("1000", 2);
        assert mask.getMaskOR() == 8L;

        // Sanity
        assert Long.parseLong("0000", 2) == 0L;
        assert Long.parseLong("1111", 2) == 15L;
        assert Long.parseLong("0100", 2) == 4L;

        assert mask.applyMask(0L) == 8L;
        assert mask.applyMask(15L) == 13L;
        assert mask.applyMask(4L) == 12L;

        // Actual test (beginning of input)
        // 1 mask,01100101XX0010111010X010X10001010111
        // 2 mem,59869,296403277
        // 3 mem,50029,14565
        // 4 mem,52488,627950233
        // 5 mem,48318,113982010
        // 6 mem,22257,82
        // 7 mem,27870,17795
        // 8 mem,55511,4594118

        // Line 1, mask:
        mask = new Mask("01100101XX0010111010X010X10001010111");
        assert Long.toBinaryString(mask.getMaskAND()).equals("11001011100101110101010110001010111");
        assert Long.toBinaryString(mask.getMaskOR()).equals("11001010000101110100010010001010111");

        // Line 2, do actual AND/OR:
        assert Long.toBinaryString(296403277L).equals("10001101010101100000101001101");

        // 11001011100101110101010110001010111 AND
        //       10001101010101100000101001101
        // 00000010000101010101000000001000101 =

        // 00000010000101010101000000001000101 OR
        // 11001010000101110100010010001010111
        // 11001010000101110101010010001010111 =

        // 296,403,277 becomes 27,124,212,823
        assert mask.applyMask(296403277L) == 27124212823L;
        assert Long.toBinaryString(mask.applyMask(296403277L)).equals("11001010000101110101010010001010111");

        // Skip ahead to line 6, small value like 82:
        assert Long.toBinaryString(82L).equals("1010010");

        // 11001011100101110101010110001010111 AND
        //                             1010010
        //                             1010010 =

        // 11001010000101110100010010001010111 OR
        // 00000000000000000000000000001010010
        // 11001010000101110100010010001010111 =

        assert mask.applyMask(82L) == 27124180055L;
        assert Long.toBinaryString(mask.applyMask(82L)).equals("11001010000101110100010010001010111");

        System.out.println("OK");
    }

    public class Mask {
        // // Put zeros in this mask, will do bitwise AND. Start with all 1's
        // Long maskAND = (long) Math.pow(2, 36) - 1;
        Long maskAND;
        // // Put ones in this mask, will do bitwise OR. Start with all 0's
        // Long maskOR = 0L;
        Long maskOR;

        public Mask() {}

        public Mask(String mask) throws Exception {
            // Put zeros in this mask, will do bitwise AND. Start with all 1's
            String maskAND = "";
            // Put ones in this mask, will do bitwise OR. Start with all 0's
            String maskOR = "";
            for (int i = 0; i < mask.length(); i++) {
                switch (mask.charAt(i)) {
                    case 'X':
                        maskAND += "1";
                        maskOR += "0";
                        break;
                    case '1':
                        maskAND += "1";
                        maskOR += "1";
                        break;
                    case '0':
                        maskAND += "0";
                        maskOR += "0";
                        break;
                    default:
                        throw new Exception("Unknown char at pos " + i + ": " + mask.charAt(i));
                }
            }
            // System.out.println("maskAND=" + maskAND);
            // System.out.println("maskOR =" + maskOR);
            this.maskAND = Long.parseLong(maskAND, 2);
            this.maskOR = Long.parseLong(maskOR, 2);
        }

        public Long applyMask(Long value) {
            return (value & maskAND) | maskOR;
        }

        public String toString() {
            return "maskAND=" + Long.toBinaryString(maskAND) + " maskOR=" + Long.toBinaryString(maskOR);
        }

        public Long getMaskAND() {
            return maskAND;
        }

        public Long getMaskOR() {
            return maskOR;
        }
    }
}
