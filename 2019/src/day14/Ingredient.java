package day14;

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
}
