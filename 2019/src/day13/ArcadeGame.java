package day13;

import common.IntcodeComputer;
import common.Point;

import java.math.BigInteger;
import java.util.HashMap;
import java.util.Map;
import java.util.Queue;


public class ArcadeGame {
    // 0 is an empty tile. No game object appears in this tile.
    public static final int TILE_ID_EMPTY = 0;
    // 1 is a wall tile. Walls are indestructible barriers.
    public static final int TILE_ID_WALL = 1;
    // 2 is a block tile. Blocks can be broken by the ball.
    public static final int TILE_ID_BLOCK = 2;
    // 3 is a horizontal paddle tile. The paddle is indestructible.
    public static final int TILE_ID_HORIZONTAL_PADDLE = 3;
    // 4 is a ball tile. The ball moves diagonally and bounces off objects.
    public static final int TILE_ID_BALL = 4;

    public static final int JOYSTICK_LEFT = -1;
    public static final int JOYSTICK_NEUTRAL = 0;
    public static final int JOYSTICK_RIGHT = 1;

    public static Map<Integer, Character> TILE_ID_CHAR_MAP;

    protected IntcodeComputer computer;

    protected Map<Point, Integer> board;

    protected Integer xMin, xMax, yMin, yMax;

    protected int ballX, paddleX;

    protected BigInteger score;

    public ArcadeGame(BigInteger[] software) {
        computer = new IntcodeComputer(software);
        board = new HashMap<>();
        TILE_ID_CHAR_MAP = new HashMap<>();
        TILE_ID_CHAR_MAP.put(TILE_ID_EMPTY, ' ');
        TILE_ID_CHAR_MAP.put(TILE_ID_WALL, 'O');
        TILE_ID_CHAR_MAP.put(TILE_ID_BLOCK, 'b');
        TILE_ID_CHAR_MAP.put(TILE_ID_HORIZONTAL_PADDLE, '-');
        TILE_ID_CHAR_MAP.put(TILE_ID_BALL, '@');
    }

    public BigInteger getScore() {
        return score;
    }


    public void start() throws IntcodeComputer.IntcodeException {
        Queue<BigInteger> outputs;
        int x, y, tile_id;
        while (! computer.isHalted()) {
            outputs = computer.processUntilNOutputs(3);
            if (outputs.isEmpty()) {
                continue;
            }
            x = outputs.poll().intValue();
            y = outputs.poll().intValue();
            if (x == -1 && y == 0) {
                score = outputs.poll();
            } else {
                tile_id = outputs.poll().intValue();
                board.put(new Point(x, y), tile_id);
                setMinMax(x, y);
                switch (tile_id) {
                    case TILE_ID_BALL:
                        ballX = x;
                        break;
                    case TILE_ID_HORIZONTAL_PADDLE:
                        paddleX = x;
                        break;
                }
            }
        }
    }

    /**
     * Returns whether or not it is waiting on input
     *
     * @return
     * @throws IntcodeComputer.IntcodeException
     */
    public boolean startUntilAwaitingInput() throws IntcodeComputer.IntcodeException {
        try {
            start();
            return false;
        } catch (IntcodeComputer.WaitingOnInputInterrupt exception) {
            return true;
        }
    }

    protected void setMinMax(int x, int y) {
        if (xMin == null || x < xMin) {
            xMin = x;
        }
        if (xMax == null || x > xMax) {
            xMax = x;
        }
        if (yMin == null || y < yMin) {
            yMin = y;
        }
        if (yMax == null || y > yMax) {
            yMax = y;
        }
    }

    public int countByTileId(int tile_id) {
        int count = 0;
        for (int tile_id_spot : board.values()) {
            if (tile_id_spot == tile_id) {
                count++;
            }
        }
        return count;
    }

    @Override
    public String toString() {
        Point point;
        int tile_id;
        String result = "ArcadeGame | score: " + score + "\n\n";
        for (int y = yMin; y <= yMax; y++) {
            for (int x = xMin; x <= xMax; x++) {
                point = new Point(x, y);
                tile_id = board.containsKey(point) ? board.get(point) : TILE_ID_EMPTY;
                result += TILE_ID_CHAR_MAP.get(tile_id);
            }
            result += "\n";
        }
        return result;
    }

    public void setToFreeMode() {
        computer.setPosition(0, BigInteger.valueOf(2));
    }

    public boolean move() throws IntcodeComputer.IntcodeException {
        if (ballX < paddleX) {
            return setJoystickLeft();
        }
        if (ballX > paddleX) {
            return setJoystickRight();
        }
        return setJoystickNeutral();
    }

    public boolean setJoystickLeft() throws IntcodeComputer.IntcodeException {
        // System.out.println("LEFT");
        return setJoystickPosition(JOYSTICK_LEFT);
    }

    public boolean setJoystickNeutral() throws IntcodeComputer.IntcodeException {
        // System.out.println("NEUTRAL");
        return setJoystickPosition(JOYSTICK_NEUTRAL);
    }

    public boolean setJoystickRight() throws IntcodeComputer.IntcodeException {
        // System.out.println("RIGHT");
        return setJoystickPosition(JOYSTICK_RIGHT);
    }

    protected boolean setJoystickPosition(int position) throws IntcodeComputer.IntcodeException {
        computer.pushOntoInputs(position);
        return startUntilAwaitingInput();
    }

    public void moveUntilDone() throws IntcodeComputer.IntcodeException {
        boolean awaitingInput = true;
        while (awaitingInput) {
            awaitingInput = move();
        }
    }
}
