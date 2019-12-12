package day10;

import common.Point;

import java.util.*;

public class AstroidMap {

    public static final int QUADRANT_UP = 0;
    public static final int QUADRANT_UP_RIGHT = 1;
    public static final int QUADRANT_RIGHT = 2;
    public static final int QUADRANT_RIGHT_DOWN = 3;
    public static final int QUADRANT_DOWN = 4;
    public static final int QUADRANT_DOWN_LEFT = 5;
    public static final int QUADRANT_LEFT = 6;
    public static final int QUADRANT_LEFT_UP = 7;

    protected int width, height;
    protected Set<Point> astroids;

    protected Point monitoringStation;

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
        monitoringStation = bestPoint;
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

    public Point vaporizeUntilAstroidN(int n) throws Exception {
        int quadrant = QUADRANT_UP;
        Set<Point> visible = new HashSet<>();
        int astroidNum = 0;
        while (true) {
            if (visible.isEmpty()) {
                visible = findVisibleAstroidsFromLocation(monitoringStation);
            }
            Set<Point> astroidsInQuadrant = findAstroidsInQuadrant(visible, quadrant);
            List<Point> astroidsSorted = sortAstroids(astroidsInQuadrant, quadrant);
            for (Point astroid : astroidsSorted) {
                astroidNum++;
//                System.out.println("Vaporize #" + astroidNum + " - " + astroid);
                visible.remove(astroid);
                astroids.remove(astroid);
                if (astroidNum == n) {
                    return astroid;
                }
            }
            quadrant++;
            if (quadrant == 8) {
                quadrant = QUADRANT_UP;
            }
        }
    }

    protected Set<Point> findAstroidsInQuadrant(Set<Point> astroids, int quadrant) throws Exception {
        Set<Point> validAstroids = new HashSet<>();
        for (Point astroid : astroids) {
            if (isAstroidInQuadrant(astroid, quadrant)) {
                validAstroids.add(astroid);
            }
        }
        return validAstroids;
    }

    protected boolean isAstroidInQuadrant(Point astroid, int quadrant) throws Exception {
        switch (quadrant) {
            case QUADRANT_UP:
                return astroid.x == monitoringStation.x && astroid.y < monitoringStation.y;
            case QUADRANT_UP_RIGHT:
                return astroid.x > monitoringStation.x && astroid.y < monitoringStation.y;
            case QUADRANT_RIGHT:
                return astroid.x > monitoringStation.x && astroid.y == monitoringStation.y;
            case QUADRANT_RIGHT_DOWN:
                return astroid.x > monitoringStation.x && astroid.y > monitoringStation.y;
            case QUADRANT_DOWN:
                return astroid.x == monitoringStation.x && astroid.y > monitoringStation.y;
            case QUADRANT_DOWN_LEFT:
                return astroid.x < monitoringStation.x && astroid.y > monitoringStation.y;
            case QUADRANT_LEFT:
                return astroid.x < monitoringStation.x && astroid.y == monitoringStation.y;
            case QUADRANT_LEFT_UP:
                return astroid.x < monitoringStation.x && astroid.y < monitoringStation.y;
            default:
                throw new Exception("Unknown quadrant!");
        }
    }

    protected List<Point> sortAstroids(Set<Point> astroidsUnsorted, int quadrant) throws Exception {
        List<Point> astroidsSorted = new ArrayList<>();
        if (astroidsUnsorted.size() == 0) {
            return astroidsSorted;
        }
        if (astroidsUnsorted.size() == 1) {
            for (Point astroid : astroidsUnsorted) {
                astroidsSorted.add(astroid);
            }
            return astroidsSorted;
        }
        Map<Point, Float> astroidSlopes = getAstroidSlopes(astroidsUnsorted, quadrant);
        return sortAstroidSlopes(astroidSlopes);
    }

    protected Map<Point, Float> getAstroidSlopes(Set<Point> astroids, int quadrant) throws Exception {
        Map<Point, Float> astroidSlopes = new HashMap<>();
        int xDelta, yDelta;
        float slope;
        for (Point astroid : astroids) {
            xDelta = astroid.x - monitoringStation.x;
            yDelta = astroid.y - monitoringStation.y;
            switch (quadrant) {
                case QUADRANT_UP_RIGHT:
                    slope = (float) xDelta / -yDelta;
                    break;
                case QUADRANT_RIGHT_DOWN:
                    slope = (float) yDelta / xDelta;
                    break;
                case QUADRANT_DOWN_LEFT:
                    slope = (float) -xDelta / yDelta;
                    break;
                case QUADRANT_LEFT_UP:
                    slope = (float) -yDelta / -xDelta;
                    break;
                default:
                    throw new Exception("Unexpected quadrant!");
            }
            astroidSlopes.put(astroid, slope);
        }
        return astroidSlopes;
    }

    protected List<Point> sortAstroidSlopes(Map<Point, Float> astroidSlopes) {
        List<Point> sortedAstroids = new ArrayList<>();
        while (astroidSlopes.size() > 0) {
            Point astroid = getMinAstroidSlope(astroidSlopes);
            sortedAstroids.add(astroid);
            astroidSlopes.remove(astroid);
        }
        return sortedAstroids;
    }

    protected Point getMinAstroidSlope(Map<Point, Float> astroidSlopes) {
        Point minAstroid = null;
        float minSlope = 0;
        for (Point astroid : astroidSlopes.keySet()) {
            if (minAstroid == null || astroidSlopes.get(astroid) < minSlope) {
                minAstroid = astroid;
                minSlope = astroidSlopes.get(astroid);
            }
        }
        return minAstroid;
    }
}
