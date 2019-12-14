package day14;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class NanoFactory {

    protected List<Reaction> reactionList;

    protected Map<String, Ingredient> availableIngredients;

    public class InvalidReactionException extends Exception {};

    public class MissingIngredient extends InvalidReactionException {};

    public class NotEnoughIngredient extends InvalidReactionException {};

    public NanoFactory(List<Reaction> reactionList) {
        this.reactionList = reactionList;
        availableIngredients = new HashMap<>();
    }

    public NanoFactory clone() {
        NanoFactory factory = new NanoFactory(reactionList);
        for (Ingredient ingredient : availableIngredients.values()) {
            factory.addIngredient(ingredient.clone());
        }
        return factory;
    }

    public void addIngredient(Ingredient ingredient) {
        if (! availableIngredients.containsKey(ingredient.name)) {
            availableIngredients.put(ingredient.name, ingredient);
            return;
        }
        int quantity = availableIngredients.get(ingredient.name).quantity + ingredient.quantity;
        availableIngredients.put(ingredient.name, new Ingredient(quantity, ingredient.name));
    }

    public void executeReaction(Reaction reaction) throws InvalidReactionException {
        int quantityAvailable, quantityRemaining;
        for (Ingredient ingredient : reaction.inputs) {
            if (! availableIngredients.containsKey(ingredient.name)) {
                throw new MissingIngredient();
            }
            quantityAvailable = availableIngredients.get(ingredient.name).quantity;
            quantityRemaining = quantityAvailable - ingredient.quantity;
            if (quantityRemaining < 0) {
                throw new NotEnoughIngredient();
            }
            if (quantityRemaining == 0) {
                availableIngredients.remove(ingredient.name);
            } else {
                availableIngredients.put(ingredient.name, new Ingredient(quantityRemaining, ingredient.name));
            }
        }
        Ingredient output = reaction.output;
        if (availableIngredients.containsKey(output.name)) {
            quantityAvailable = availableIngredients.get(output.name).quantity;
            quantityAvailable += output.quantity;
            availableIngredients.put(output.name, new Ingredient(quantityAvailable, output.name));
        } else {
            availableIngredients.put(output.name, output);
        }
    }

    public boolean canMakeFuel() {
//        System.out.println(this);
        if (containsFuel()) {
            return true;
        }
        NanoFactory factory;
        for (Reaction reaction : reactionList) {
            factory = clone();
            try {
                factory.executeReaction(reaction);
            } catch (InvalidReactionException e) {
                continue;
            }
            if (factory.canMakeFuel()) {
                return true;
            }
        }
        return false;
    }

    public boolean containsFuel() {
        return availableIngredients.containsKey(Ingredient.INGREDIENT_FUEL);
    }

    @Override
    public String toString() {
        return "NanoFactory{" +
                "availableIngredients=" + availableIngredients +
                '}';
    }
}
