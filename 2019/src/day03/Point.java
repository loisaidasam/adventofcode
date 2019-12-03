package day03;

public class Point {
    public int x;
    public int y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

//    @Override
//    public boolean equals(Object point) {
//        return ((Point) point).x == x && ((Point) point).y == y;
//    }

    public String toString() {
        return "x=" + x + " y=" + y;
    }

//    public int[] toXY() {
//        int[] xy = new int[2];
//        xy[0] = x;
//        xy[1] = y;
//        return xy;
//    }

//    public static Point fromXY(int[] xy) {
//        return new Point(xy[0], xy[1]);
//    }

    public int manhattanDistanceFromCentralPort() {
        return Math.abs(x) + Math.abs(y);
    }
}
