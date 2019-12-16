package day14;

import java.util.*;

public class NanoFactory {

    public final Map<String, Reaction> ingredientReactionMap;

    protected Map<String, Ingredient> availableIngredients;

    protected List<Reaction> reactionHistory;

    protected final boolean verbose = true;

    public class InvalidReactionException extends Exception {}

    public class MissingIngredient extends InvalidReactionException {
        public final String name;

        public MissingIngredient(String name) {
            this.name = name;
        }

        @Override
        public String toString() {
            return "MissingIngredient{" +
                    "name='" + name + '\'' +
                    '}';
        }
    };

    public class NotEnoughIngredient extends InvalidReactionException {
        public final String name;
        public final int quantityRequired;
        public final int quantityAvailable;

        public NotEnoughIngredient(String name, int quantityRequired, int quantityAvailable) {
            this.name = name;
            this.quantityRequired = quantityRequired;
            this.quantityAvailable = quantityAvailable;
        }

        @Override
        public String toString() {
            return "NotEnoughIngredient{" +
                    "name='" + name + '\'' +
                    ", quantityRequired=" + quantityRequired +
                    ", quantityAvailable=" + quantityAvailable +
                    '}';
        }
    };

    public NanoFactory(List<Reaction> reactionList) throws Exception {
        this(buildIngredientReactionMap(reactionList));
    }

    public NanoFactory(Map<String, Reaction> ingredientReactionMap) {
        this.ingredientReactionMap = ingredientReactionMap;
        availableIngredients = new HashMap<>();
        reactionHistory = new ArrayList<>();
    }

    public static Map<String, Reaction> buildIngredientReactionMap(List<Reaction> reactionList) throws Exception {
        Map<String, Reaction> ingredientReactionMap = new HashMap<>();
        for (Reaction reaction : reactionList) {
            if (ingredientReactionMap.containsKey(reaction.output.name)) {
                throw new Exception("ingredientReactionMap already contains output key!");
            }
            ingredientReactionMap.put(reaction.output.name, reaction);
        }
        return ingredientReactionMap;
    }

    public void setReactionHistory(List<Reaction> reactionHistory) {
        this.reactionHistory = reactionHistory;
    }

    public int getReactionHistorySize() {
        return reactionHistory.size();
    }

    public Map<String, Ingredient> getAvailableIngredients() {
        return availableIngredients;
    }

    public static List<Reaction> copyReactionList(List<Reaction> reactionList) {
        List<Reaction> result = new ArrayList<>();
        for (Reaction reaction : reactionList) {
            result.add(reaction);
        }
        return result;
    }

    public NanoFactory cloneFactory() {
        NanoFactory factory = new NanoFactory(ingredientReactionMap);
        for (Ingredient ingredient : availableIngredients.values()) {
            factory.addIngredient(ingredient.clone());
        }
        factory.setReactionHistory(copyReactionList(reactionHistory));
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

    public void removeIngredient(Ingredient ingredient) throws InvalidReactionException {
        int quantityAvailable, quantityRemaining;
        if (! availableIngredients.containsKey(ingredient.name)) {
            throw new MissingIngredient(ingredient.name);
        }
        quantityAvailable = availableIngredients.get(ingredient.name).quantity;
        quantityRemaining = quantityAvailable - ingredient.quantity;
        if (quantityRemaining < 0) {
            throw new NotEnoughIngredient(ingredient.name, ingredient.quantity,
                    availableIngredients.get(ingredient.name).quantity);
        }
        if (quantityRemaining == 0) {
            availableIngredients.remove(ingredient.name);
            return;
        }
        availableIngredients.put(ingredient.name, new Ingredient(quantityRemaining, ingredient.name));
    }

    /**
     * For going from 3 A, 4 B => 1 AB
     * @param reaction
     * @throws InvalidReactionException
     */
    // public void executeReaction(Reaction reaction) throws InvalidReactionException {
    //     for (Ingredient ingredient : reaction.inputs) {
    //         removeIngredient(ingredient);
    //     }
    //     addIngredient(reaction.output);
    //     reactionHistory.add(reaction);
    // }

    /**
     * For going from 1 AB => 3 A, 4 B
     * @param reaction
     * @throws InvalidReactionException
     */
    public void executeReactionReverse(Reaction reaction) throws InvalidReactionException {
        // Don't allow ORE reactions:
        // removeIngredient(reaction.output);
        // Allow ORE reactions:
        Ingredient output = reaction.output;
        try {
            removeIngredient(output);
        } catch (NotEnoughIngredient exception) {
            // If it's *just* ore, this is OK
            if (reaction.isOreReaction()) {
                availableIngredients.remove(reaction.output.name);
            } else {
                throw exception;
            }
        }
        for (Ingredient ingredient : reaction.inputs) {
            addIngredient(ingredient);
        }
        reactionHistory.add(reaction);
    }

    /**
     * BFS/DFS, iterative using stack
     * @return
     */
    public Integer numOreNeededForOneFuel() throws Exception {
        printIngredientReactionMap();
        Integer minOreNeeded = null;
        Stack<NanoFactory> stack = new Stack<>();
//        Queue<NanoFactory> queue = new LinkedList<>();
        addIngredient(new Ingredient(1, Ingredient.INGREDIENT_FUEL));
        stack.push(this);
//        queue.add(this);
        NanoFactory factory, clone;
        int hash;
        Set<Integer> factoryStatesSeen = new HashSet<>();
        int maxDepth = 0;
        Reaction reaction;
        while (! stack.isEmpty()) {
//        while (!queue.isEmpty()) {
            factory = stack.pop();
//            factory = queue.poll();
            hash = factory.hashCode();
            if (factoryStatesSeen.contains(hash)) {
                continue;
            }
            factoryStatesSeen.add(hash);
//            logVerbose(stack.size());
            logVerbose(factory.getReactionSizeBuffer() + factory);
            if (factory.getReactionHistorySize() > maxDepth) {
                maxDepth = factory.getReactionHistorySize();
                logInfo("maxDepth=" + maxDepth + " stack.size()=" + stack.size());
            }
            if (factory.hasOnlyOre()) {
//                logVerbose("HAS ONLY ORE!!!");
                if (minOreNeeded == null || factory.getNumOre() < minOreNeeded) {
                    minOreNeeded = factory.getNumOre();
                }
            }
            boolean didPerformReaction = false;
            // TODO: We want to go in order from "farthest from ore" to "closest to ore"
            for (String ingredientName : factory.getAvailableIngredients().keySet()) {
                if (ingredientName.equals(Ingredient.INGREDIENT_ORE)) {
                    // Not cashing ore in for anything
                    continue;
                }
                reaction = ingredientReactionMap.get(ingredientName);
                logVerbose(factory.getReactionSizeBuffer() + "?" + reaction);
                try {
                    factory.executeReactionReverse(reaction);
                } catch (InvalidReactionException e) {
                    logVerbose(factory.getReactionSizeBuffer() + "->" + e);
                    continue;
                }
                logVerbose(factory.getReactionSizeBuffer(-1) + "->Y");
                didPerformReaction = true;
                break;
                // clone = factory.cloneFactory();
                // logVerbose(clone.getReactionSizeBuffer() + "?" + reaction);
                // try {
                //     clone.executeReactionReverse(reaction);
                // } catch (InvalidReactionException e) {
                //     logVerbose(clone.getReactionSizeBuffer() + "->" + e);
                //     continue;
                // }
                // logVerbose(clone.getReactionSizeBuffer(-1) + "->Y");
                // stack.push(clone);
                // // queue.add(clone);
            }
            if (didPerformReaction) {
                stack.push(factory);
            }
        }
        return minOreNeeded;
    }

    public boolean hasOnlyOre() {
        return availableIngredients.size() == 1 && availableIngredients.containsKey(Ingredient.INGREDIENT_ORE);
    }

    public int getNumOre() {
        return availableIngredients.containsKey(Ingredient.INGREDIENT_ORE) ?
                availableIngredients.get(Ingredient.INGREDIENT_ORE).quantity : 0;
    }

    @Override
    public String toString() {
        return "NanoFactory{" +
                "availableIngredients=" + getAvailableIngredientsString() +
                ", reactionHistory.size()=" + getReactionHistorySize() +
                '}';
    }

    protected String getAvailableIngredientsString() {
        String result = "{";
        boolean leadingComma = false;
        for (String name : availableIngredients.keySet()) {
            if (leadingComma) {
                result += ", ";
            }
            result += name + "=" + availableIngredients.get(name).quantity;
            leadingComma = true;
        }
        return result + "}";
    }

    public String getReactionSizeBuffer() {
        return getReactionSizeBuffer(0);
    }

    public String getReactionSizeBuffer(int plusMinus) {
        String buffer = "";
        for (int i = 0; i < getReactionHistorySize() + plusMinus; i++) {
            buffer += "  ";
        }
        return buffer;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        NanoFactory that = (NanoFactory) o;
        return availableIngredients.equals(that.availableIngredients);
    }

    @Override
    public int hashCode() {
        // TODO: Look into why this doesn't work for input-test-2.txt
//        return Objects.hash(availableIngredients);
        return getAvailableIngredientsString().hashCode();
    }

    public void printIngredientReactionMap() {
        logVerbose("ingredientReactionMap:");
        for (String ingredientName : ingredientReactionMap.keySet()) {
            logVerbose("\t" + ingredientName + ": " + ingredientReactionMap.get(ingredientName));
        }
    }

    protected void logInfo(String message) {
        System.out.println(message);
    }

    protected void logVerbose(String message) {
        if (! verbose) {
            return;
        }
        System.out.println(message);
    }
}
