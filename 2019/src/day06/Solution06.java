package day06;

import common.BaseSolution;
import common.InputReader;

import java.util.HashMap;
import java.util.Map;

public class Solution06 extends BaseSolution implements common.Solution {

    protected Map<String, OrbitObject> orbitObjectMap;

    public static void main(String[] args) throws Exception {
        new Solution06().run();
    }

    public Solution06() {
        super();
        buildOrbitObjectMap();
    }

    protected void buildOrbitObjectMap() {
        orbitObjectMap = new HashMap<>();
        InputReader reader = getInputReader();
        while (true) {
            String line = reader.next();
            if (line == null) {
                break;
            }
            String[] values = line.split("\\)");
            OrbitObject parent = getOrCreateOrbitObject(values[0]);
            OrbitObject child = getOrCreateOrbitObject(values[1]);
            child.setParent(parent);
        }
    }

    protected OrbitObject getOrCreateOrbitObject(String code) {
        if (! orbitObjectMap.containsKey(code)) {
            orbitObjectMap.put(code, new OrbitObject(code));
        }
        return orbitObjectMap.get(code);
    }

    @Override
    public String part1() {
        int orbitCount = 0;
        for (OrbitObject obj : orbitObjectMap.values()) {
            orbitCount += obj.getOrbitCount();
        }
        return String.valueOf(orbitCount);
    }

    @Override
    public String part2() {
        OrbitObject you = orbitObjectMap.get("YOU");
        OrbitObject santa = orbitObjectMap.get("SAN");
        OrbitObject common = you.findFirstCommonParent(santa);
        int distance = you.distanceToParentCode(common.getCode()) + santa.distanceToParentCode(common.getCode()) - 2;
        return String.valueOf(distance);
    }
}
