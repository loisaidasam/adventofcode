package day07;

import java.util.ArrayList;
import java.util.List;

/**
 * Inspired by https://www.baeldung.com/java-array-permutations
 *
 * - https://github.com/eugenp/tutorials/blob/master/algorithms-miscellaneous-4/src/main/java/com/baeldung/algorithms/permutation/Permutation.java
 * - https://github.com/eugenp/tutorials/blob/ac4de4e809fd22dbd9eb533490a9bb57c8b26c1c/algorithms-miscellaneous-4/src/main/java/com/baeldung/algorithms/permutation/Permutation.java
 */
public class Permutations {
    public static List<int[]> getPermutations(int n) {
        List<int[]> permutations = new ArrayList<>();

        int[] indexes = new int[n];
        int[] elements = new int[n];
        for (int i = 0; i < n; i++) {
            indexes[i] = 0;
            elements[i] = i;
        }

        permutations.add(elements.clone());

        int i = 0;
        while (i < n) {
            if (indexes[i] < i) {
                swap(elements, i % 2 == 0 ?  0: indexes[i], i);
                permutations.add(elements.clone());
                indexes[i]++;
                i = 0;
            }
            else {
                indexes[i] = 0;
                i++;
            }
        }
        return permutations;
    }

    private static void swap(int[] input, int a, int b) {
        int tmp = input[a];
        input[a] = input[b];
        input[b] = tmp;
    }

    public static void main(String[] args) {
        List<int[]> permutations = getPermutations(5);
        for (int[] permutation : permutations) {
            printArray(permutation);
        }
    }

    private static void printArray(int[] input) {
        for(int i = 0; i < input.length; i++) {
            System.out.print(input[i]);
        }
        System.out.println();
    }
}
