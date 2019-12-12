package day12;

import java.util.ArrayList;
import java.util.List;

public class JupiterSystem {

    protected JupiterMoon io, europa, ganymede, callisto;

    public JupiterSystem(List<Position> positions) {
        this.io = new JupiterMoon(positions.get(0));
        this.europa = new JupiterMoon(positions.get(1));
        this.ganymede = new JupiterMoon(positions.get(2));
        this.callisto = new JupiterMoon(positions.get(3));
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
}
