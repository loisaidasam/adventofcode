package day06;

import java.util.HashSet;
import java.util.Set;

public class OrbitObject {
    protected String code;

    protected OrbitObject parent;

    public OrbitObject(String code) {
        this.code = code;
    }

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public OrbitObject getParent() {
        return parent;
    }

    public void setParent(OrbitObject parent) {
        this.parent = parent;
    }

    public int getOrbitCount() {
        int count = 0;
        OrbitObject parent = this.parent;
        while (parent != null) {
            parent = parent.getParent();
            count++;
        }
        return count;
    }

    public Set<String> getAllParentCodes() {
        Set<String> parentCodes = new HashSet<>();
        OrbitObject parent = this.parent;
        while (parent != null) {
            parentCodes.add(parent.getCode());
            parent = parent.getParent();
        }
        return parentCodes;
    }

    public OrbitObject findFirstCommonParent(OrbitObject obj) {
        Set<String> commonParentCodes = getCommonParentCodes(obj);
        OrbitObject parent = this.parent;
        while (parent != null) {
            if (commonParentCodes.contains(parent.getCode())) {
                return parent;
            }
            parent = parent.getParent();
        }
        return null;
    }

    protected Set<String> getCommonParentCodes(OrbitObject obj) {
        Set<String> thisParents = getAllParentCodes();
        Set<String> objParents = obj.getAllParentCodes();
        Set<String> commonParents = new HashSet<>();
        for (String parent : thisParents) {
            if (objParents.contains(parent)) {
                commonParents.add(parent);
            }
        }
        return commonParents;
    }

    public int distanceToParentCode(String code) {
        int distance = 0;
        OrbitObject parent = this.parent;
        while (parent != null) {
            distance++;
            if (code.equals(parent.getCode())) {
                return distance;
            }
            parent = parent.getParent();
        }
        return -1;
    }
}
