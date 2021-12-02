package day15;

import common.BaseSolution;
import common.IntSolution;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Solution15 extends BaseSolution implements IntSolution {
    public class RecentlySpoken {
        // [0] is most recent, [1] is oldest
        Integer[] turns;

        public RecentlySpoken() {
            turns = new Integer[2];
        }

        public int speak(int turn) {
            // Empty (first turn)
            if (turns[0] == null) {
                turns[0] = turn;
                return 0;
            }
            // At least the second turn, push back value of [0] to [1], set [0] to current turn
            turns[1] = turns[0];
            turns[0] = turn;
            return turns[0] - turns[1];
        }
    }

    public class NumberStatus {

    }

    public class Game {
        int turns = 0;
        int lastNumber;

        Map<Integer, Integer> numberSeenCount;
        Map<Integer, Integer> numberLastSeenTurn;

        // private void addNumberToGame()

        public Game(int[] startingNumbers) {
            numberSeenCount = new HashMap<>();
            numberLastSeenTurn = new HashMap<>();
            for (int number : startingNumbers) {
                turns++;
                numberSeenCount.put(number, numberSeenCount.getOrDefault(number, 0) + 1);
                numberLastSeenTurn.put(number, turns);
                lastNumber = number;
            }
        }

        public int getTurns() {
            return turns;
        }

        public int speak() {
            int number;
            turns++;
            if (numberSeenCount.get(lastNumber) == 1) {
                number = 0;
            } else {
                number = numberLastSeenTurn.get(lastNumber);
            }
            return 0;
        }
    }

    @Override
    public Integer part1Int() {
        int[] startingNumbers = new int[]{6,3,15,13,1,0};
        Game game = new Game(startingNumbers);
        Integer number = null;
        while (game.getTurns() != 2020) {
            number = game.speak();
        }
        return number;
    }
}
