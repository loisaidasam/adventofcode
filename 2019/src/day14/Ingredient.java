package day14;

import java.util.Objects;

public class Ingredient {
    public static final String INGREDIENT_FUEL = "FUEL";
    public static final String INGREDIENT_ORE = "ORE";

    public final int quantity;
    public final String name;

    public Ingredient(int quantity, String name) {
        this.quantity = quantity;
        this.name = name;
    }

    public Ingredient clone() {
        return new Ingredient(quantity, name);
    }

    @Override
    public String toString() {
        return "Ingredient{" +
                "quantity=" + quantity +
                ", name='" + name + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Ingredient that = (Ingredient) o;
        return quantity == that.quantity &&
                name.equals(that.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(quantity, name);
    }
}
