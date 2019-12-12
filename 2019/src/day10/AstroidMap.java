package day10;

import common.Point;

import java.util.*;

public class AstroidMap {

    protected int width, height;
    protected Set<Point> astroids;

    public AstroidMap(List<String> rows) {
        astroids = new HashSet<>();
        height = rows.size();
        width = rows.get(0).length();
        for (int y = 0; y < height; y++) {
            String row = rows.get(y);
            for (int x = 0; x < width; x++) {
                if (row.charAt(x) == '#') {
                    Point asteroid = new Point(x, y);
                    astroids.add(asteroid);
//                     System.out.println("Asteroid #" + astroids.size() + ": " + asteroid);
                }
            }
        }
//        System.out.println("width=" + width + " height=" + height);
    }

    public int findNumVisibleFromBestMonitoringStation() throws Exception {
        Point bestPoint = null;
        int numVisible = -1;
        for (Point astroid : astroids) {
            Set<Point> visibleAstroids = findVisibleAstroidsFromLocation(astroid);
            if (bestPoint == null || visibleAstroids.size() > numVisible) {
                bestPoint = astroid;
                numVisible = visibleAstroids.size();
            }
        }
//        System.out.println("Chose " + bestPoint + " with " + numVisible + " visible");
        return numVisible;
    }

    public Set<Point> findVisibleAstroidsFromLocation(Point location) throws Exception {
//        System.out.println("findVisibleAstroidsFromLocation(" + location + ")");
        Set<Point> visible = new HashSet<>();
        Set<Point> notVisible = new HashSet<>();
        for (Point astroid : astroids) {
//            System.out.println("astroid=" + astroid);
            if (astroid.equals(location)) {
                continue;
            }
            if (visible.contains(astroid) || notVisible.contains(astroid)) {
                continue;
            }
            int xDelta = astroid.x - location.x;
            int yDelta = astroid.y - location.y;
            int xDeltaMin, yDeltaMin;
            if (xDelta == 0) {
                xDeltaMin = 0;
                yDeltaMin = yDelta / Math.abs(yDelta);
            } else if (yDelta == 0) {
                xDeltaMin = xDelta / Math.abs(xDelta);
                yDeltaMin = 0;
            } else {
                int gcd = GCD.gcd(Math.abs(xDelta), Math.abs(yDelta));
                if (gcd == 0) {
                    throw new Exception("Invalid GCD " + gcd);
                }
                xDeltaMin = xDelta / gcd;
                yDeltaMin = yDelta / gcd;
            }
//            System.out.println("xDeltaMin=" + xDeltaMin + " yDeltaMin=" + yDeltaMin);
            Point point = new Point(location.x + xDeltaMin, location.y + yDeltaMin);
            boolean hit = false;
            while (point.x >= 0 && point.x < width && point.y >= 0 && point.y < height) {
                if (astroids.contains(point)) {
//                    System.out.print("\t" + point);
                    if (hit) {
                        notVisible.add(point);
//                        System.out.println(" (not visible)");
                    } else {
                        visible.add(point);
//                        System.out.println(" (visible)");
                        hit = true;
                    }
                }
                point = point.cloneWithDelta(xDeltaMin, yDeltaMin);
            }
        }
//        System.out.println("Got " + visible.size() + " visible");
        return visible;
    }
}
