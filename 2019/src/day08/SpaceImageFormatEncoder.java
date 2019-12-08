package day08;

import java.util.ArrayList;
import java.util.List;

public class SpaceImageFormatEncoder {

    public static final char DIGIT_BLACK = '0';
    public static final char DIGIT_WHITE = '1';
    public static final char DIGIT_TRANSPARENT = '2';

    protected int width, height;
    protected String imageData;
    protected List<String> layers;

    public SpaceImageFormatEncoder(int width, int height, String imageData) {
        this.width = width;
        this.height = height;
        this.imageData = imageData;
        buildLayers();
    }

    protected void buildLayers() {
        layers = new ArrayList<>();
        int layerSize = width * height;
        for (int position = 0; position < imageData.length(); position += layerSize) {
            String layer = imageData.substring(position, position + layerSize);
            layers.add(layer);
        }
    }

    public int findLayerWithFewestOfDigit(char digit) {
        int layerWithFewestOfDigit = 0;
        int digitCount;
        Integer minDigitCount = null;
        for (int layerNum = 0; layerNum < layers.size(); layerNum++) {
            digitCount = findDigitCount(layers.get(layerNum), digit);
            if (minDigitCount == null || digitCount < minDigitCount) {
                layerWithFewestOfDigit = layerNum;
                minDigitCount = digitCount;
            }
        }
        return layerWithFewestOfDigit;
    }

    public int findLayerDigitCount(int layerNum, char digit) {
        return findDigitCount(layers.get(layerNum), digit);
    }

    protected int findDigitCount(String layer, char digit) {
        int count = 0;
        for (int i = 0; i < layer.length(); i++) {
            if (layer.charAt(i) == digit) {
                count++;
            }
        }
        return count;
    }

    public String decode() {
        String result = "";
        for (int i = 0; i < width * height; i++) {
            result += determineDigitAtPosition(i);
            if ((i + 1) % width == 0) {
                result += "\n";
            }
        }
        return result;
    }

    protected char determineDigitAtPosition(int position) {
        for (String layer : layers) {
            if (layer.charAt(position) == DIGIT_TRANSPARENT) {
                continue;
            }
            return layer.charAt(position);
        }
        return DIGIT_TRANSPARENT;
    }

    public String toString() {
        String result = "";
        for (int layerNum = 0; layerNum < layers.size(); layerNum++) {
            result += "Layer " + layerNum + 1 + "\n";
            String layer = layers.get(layerNum);
            for (int i = 0; i < layer.length(); i++) {
                result += layer.charAt(i);
                if ((i + 1) % width == 0) {
                    result += "\n";
                }
            }
            result += "\n";
        }
        return result;
    }

    public static void main(String[] args) {
        System.out.println(new SpaceImageFormatEncoder(3, 2, "123456789012"));
    }
}
