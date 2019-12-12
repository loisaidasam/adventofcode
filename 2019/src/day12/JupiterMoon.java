package day12;

public class JupiterMoon {
    public Position position;
    public Position velocity;

    public JupiterMoon(Position position) {
        this.position = position;
        velocity = new Position(0, 0, 0);
    }

    public void applyGravity(JupiterMoon otherMoon) {
        if (position.x < otherMoon.position.x) {
            velocity.x++;
        } else if (position.x > otherMoon.position.x) {
            velocity.x--;
        }
        if (position.y < otherMoon.position.y) {
            velocity.y++;
        } else if (position.y > otherMoon.position.y) {
            velocity.y--;
        }
        if (position.z < otherMoon.position.z) {
            velocity.z++;
        } else if (position.z > otherMoon.position.z) {
            velocity.z--;
        }
    }

    public void applyVelocity() {
        position.x += velocity.x;
        position.y += velocity.y;
        position.z += velocity.z;
    }

    public int getTotalEnergy() {
        return getPotentialEnergy() * getKineticEnergy();
    }

    protected int getPotentialEnergy() {
        return Math.abs(position.x) + Math.abs(position.y) + Math.abs(position.z);
    }

    protected int getKineticEnergy() {
        return Math.abs(velocity.x) + Math.abs(velocity.y) + Math.abs(velocity.z);
    }

    @Override
    public String toString() {
        return "JupiterMoon{" +
                "position=" + position +
                ", velocity=" + velocity +
                '}';
    }
}
