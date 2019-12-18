package day16;

public class FFTPatternGenerator {
    protected int[] pattern;
    protected int index;

    public FFTPatternGenerator(int[] inputPattern, int position) {
        pattern = new int[inputPattern.length * position];
        index = 0;
        for (int value : inputPattern) {
            for (int i = 0; i < position; i++) {
                pattern[index] = value;
                index++;
            }
        }
        index = 1;
    }

    public int next() {
        int result = pattern[index];
        index++;
        if (index == pattern.length) {
            index = 0;
        }
        return result;
    }

    public static void main(String[] args) {
        FFTPatternGenerator generator;
        for (int position = 1; position <= 8; position++) {
            generator = new FFTPatternGenerator(new int[] {0, 1, 0, -1}, position);
            for (int i = 0; i < 8; i++) {
                System.out.print(generator.next() + " ");
            }
            System.out.println();
        }
    }
}
