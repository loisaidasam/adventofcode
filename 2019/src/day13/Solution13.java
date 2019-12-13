package day13;

import common.BaseSolution;
import common.IntcodeComputer;
import common.Solution;

public class Solution13 extends BaseSolution implements Solution {

    public static void main(String[] args) throws Exception {
        new Solution13().run();
    }

    @Override
    public String part1() throws Exception {
        ArcadeGame game = new ArcadeGame(getInputPositionsBigInteger());
        game.start();
        return String.valueOf(game.countByTileId(ArcadeGame.TILE_ID_BLOCK));
    }

    @Override
    public String part2() throws IntcodeComputer.IntcodeException {
        ArcadeGame game = new ArcadeGame(getInputPositionsBigInteger());
        game.setToFreeMode();
        game.startUntilAwaitingInput();
        System.out.println(game);
        // for (int i = 0; i < 50; i++) {
        //     game.move();
        //     System.out.println(game);
        // }
        game.moveUntilDone();
        System.out.println(game);
        return String.valueOf(game.getScore());
    }
}
