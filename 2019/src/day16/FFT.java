package day16;

public class FFT {

    protected final int[] pattern;

    protected String signal;

    public FFT(int[] pattern, String signal) {
        this.pattern = pattern;
        this.signal = signal;
    }

    public String executePhase() {
        String outputSignal = "";
        // System.out.println("Preprocessing ...");
        int[] signalArray = new int[signal.length()];
        for (int i = 0; i < signal.length(); i++) {
            signalArray[i] = Integer.parseInt(signal.substring(i, i+1));
        }
        // System.out.println("OK. Running ...");
        FFTPatternGenerator generator;
        int signalPositionValue, nextGeneratorValue, total;
        String totalStr;
        long last = System.currentTimeMillis();
        for (int position = 1; position <= signalArray.length; position++) {
            if (position % 10000 == 0) {
                System.out.println((System.currentTimeMillis() - last) + " position=" + position);
                last = System.currentTimeMillis();
            }
            generator = new FFTPatternGenerator(pattern, position);
            total = 0;
            for (int digit = 0; digit < signalArray.length; digit++) {
                nextGeneratorValue = generator.next();
                if (nextGeneratorValue == 0) {
                    continue;
                }
                // signalPositionValue = Integer.parseInt(signal.substring(digit, digit + 1));
                // System.out.print(signalPositionValue + "*" + nextGeneratorValue + " + ");
                // total += signalPositionValue * nextGeneratorValue;
                if (nextGeneratorValue == 1) {
                    total += signalArray[digit];
                } else {
                    total -= signalArray[digit];
                }
            }
            if (total < 0) {
                total = Math.abs(total);
            }
            outputSignal += total % 10;
        }
        return outputSignal;
    }

    public String executeNPhases(int n) {
        for (int phase = 1; phase <= n; phase++) {
            System.out.println(System.currentTimeMillis() + " Starting phase " + phase);
            signal = executePhase();
        }
        return signal;
    }
}
