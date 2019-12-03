package day03;

import org.apache.commons.collections4.map.MultiKeyMap;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

public class FrontPanel {
    // {x: {y: {'r', 'b'}}}
    protected HashMap<Integer, HashMap<Integer, Set<Character>>> pointWires;
    // {'r': {x: {y, ...}}}
    protected HashMap<Character, HashMap<Integer, Set<Integer>>> wirePoints;

    public class UnknownDirectionException extends Exception {}

    public FrontPanel() {
        pointWires = new HashMap<>();
        wirePoints = new HashMap<>();
    }

    public String toString() {
        String result = "";
        for (int x : pointWires.keySet()) {
            for (int y : pointWires.get(x).keySet()) {
                result += "x=" + x + " y=" + y + " : " + pointWires.get(x).get(y) + "\n";
            }
        }
        return result;
    }

    public String summary() {
        String result = "";
        String pointsStr;
        int numPoints;
        for (char wire : wirePoints.keySet()) {
            numPoints = 0;
            pointsStr = "";
            for (int x : wirePoints.get(wire).keySet()) {
                for (int y : wirePoints.get(wire).get(x)) {
                    numPoints += 1;
                    pointsStr += "/ x=" + x + " y=" + y;
                }
            }
            result += wire + ": (" + numPoints + ") " + pointsStr + "\n";
        }
        return result;
    }

    public void handleInstructions(char wire, String[] instructions) throws UnknownDirectionException {
        Point point = new Point(0, 0);
        addPointWire(point, wire);
        for (String instruction : instructions) {
            handleInstruction(wire, point, instruction);
        }
    }

    public void handleInstruction(char wire, Point point, String instruction) throws UnknownDirectionException {
        char direction = instruction.charAt(0);
        int distance = Integer.parseInt(instruction.substring(1));
        for (int i = 0; i < distance; i++) {
            switch (direction) {
                case 'U':
                    point.y++;
                    break;
                case 'R':
                    point.x++;
                    break;
                case 'D':
                    point.y--;
                    break;
                case 'L':
                    point.x--;
                    break;
                default:
                    throw new UnknownDirectionException();
            }
            addPointWire(point, wire);
        }
    }

    public void addPointWire(Point point, char wire) {
        // Point Wires:
        if (! pointWires.containsKey(point.x)) {
            pointWires.put(point.x, new HashMap<>());
        }
        if (! pointWires.get(point.x).containsKey(point.y)) {
            pointWires.get(point.x).put(point.y, new HashSet<>());
        }
        pointWires.get(point.x).get(point.y).add(wire);

        // Wire Points:
        if (! wirePoints.containsKey(wire)) {
            wirePoints.put(wire, new HashMap<>());
        }
        if (! wirePoints.get(wire).containsKey(point.x)) {
            wirePoints.get(wire).put(point.x, new HashSet<>());
        }
        wirePoints.get(wire).get(point.x).add(point.y);
    }

    public int findClosestIntersectionDistance() {
        int distance;
        Point point;
        int minDistance = -1;
        for (int x : pointWires.keySet()) {
            for (int y : pointWires.get(x).keySet()) {
                if (pointWires.get(x).get(y).size() == 1) {
                    continue;
                }
                point = new Point(x, y);
                distance = point.manhattanDistanceFromCentralPort();
                if (distance != 0 && (minDistance == -1 || distance < minDistance)) {
                    minDistance = distance;
                }
            }
        }
        return minDistance;
    }
}
