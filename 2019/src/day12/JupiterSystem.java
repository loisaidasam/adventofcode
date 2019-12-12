package day12;

import java.math.BigInteger;
import java.util.*;

public class JupiterSystem {

    protected JupiterMoon io, europa, ganymede, callisto;

    public JupiterSystem() {}

    public JupiterSystem(List<Position> positions) {
        this.io = new JupiterMoon(positions.get(0));
        this.europa = new JupiterMoon(positions.get(1));
        this.ganymede = new JupiterMoon(positions.get(2));
        this.callisto = new JupiterMoon(positions.get(3));
    }

    public JupiterSystem clone() {
        JupiterSystem system = new JupiterSystem();
        system.io = io.clone();
        system.europa = europa.clone();
        system.ganymede = ganymede.clone();
        system.callisto = callisto.clone();
        return system;
    }

    protected JupiterMoon[] getMoons() {
        return new JupiterMoon[] {io, europa, ganymede, callisto};
    }

    public void step(int n) {
        for (int i = 0; i < n; i++) {
            step();
        }
    }

    public void step() {
        JupiterMoon[] moons = getMoons();
        for (int i = 0; i < moons.length; i++) {
            for (int j = 0; j < moons.length; j++) {
                if (i == j) {
                    continue;
                }
                moons[i].applyGravity(moons[j]);
            }
        }
        for (JupiterMoon moon : moons) {
            moon.applyVelocity();
        }
    }

    public int getTotalEnergy() {
        int energy = 0;
        for (JupiterMoon moon : getMoons()) {
            energy += moon.getTotalEnergy();
        }
        return energy;
    }

    public BigInteger getNumStepsUntilRepeat() {
        Set<Integer> systemHashes = new HashSet<>();
        int hash = hashCode();
        System.out.println(hash);
        systemHashes.add(hash);
        BigInteger numSteps = BigInteger.valueOf(0);
        while (true) {
            step();
            numSteps = numSteps.add(BigInteger.ONE);
            hash = hashCode();
            System.out.println(numSteps + " - " + hash);
            if (systemHashes.contains(hash)) {
                return numSteps;
            }
            systemHashes.add(hash);
        }
    }

    @Override
    public String toString() {
        return "JupiterSystem{" +
                "io=" + io +
                ", europa=" + europa +
                ", ganymede=" + ganymede +
                ", callisto=" + callisto +
                '}';
    }

    public static void main(String args[]) {
        List<Position> positions = new ArrayList<>();
        positions.add(new Position(-1,0,2));
        positions.add(new Position(2,-10,-7));
        positions.add(new Position(4,-8,8));
        positions.add(new Position(3,5,-1));
        JupiterSystem system = new JupiterSystem(positions);
        System.out.println("Initial State: " + system.toString());
        for (int step = 1; step <= 10; step++) {
            system.step();
            System.out.println("Step #" + step + ": " + system.toString());
        }
        System.out.println("Total energy: " + system.getTotalEnergy());
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        JupiterSystem that = (JupiterSystem) o;
        return io.equals(that.io) &&
                europa.equals(that.europa) &&
                ganymede.equals(that.ganymede) &&
                callisto.equals(that.callisto);
    }

    @Override
    public int hashCode() {
        // Default
        // return Objects.hash(io, europa, ganymede, callisto);
        // Better
        return Arrays.hashCode(new int[] {
                io.position.x,
                io.position.y,
                io.position.z,
                io.velocity.x,
                io.velocity.y,
                io.velocity.z,

                europa.position.x,
                europa.position.y,
                europa.position.z,
                europa.velocity.x,
                europa.velocity.y,
                europa.velocity.z,

                ganymede.position.x,
                ganymede.position.y,
                ganymede.position.z,
                ganymede.velocity.x,
                ganymede.velocity.y,
                ganymede.velocity.z,

                callisto.position.x,
                callisto.position.y,
                callisto.position.z,
                callisto.velocity.x,
                callisto.velocity.y,
                callisto.velocity.z,
        });
    }
}
