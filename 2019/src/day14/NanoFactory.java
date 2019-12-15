package day14;

import java.util.*;

public class NanoFactory {

    protected List<Reaction> reactionList, reactionListOre, reactionListNonOre;

    protected Map<String, Ingredient> availableIngredients;

    protected List<Reaction> reactionHistory;

    protected Set<String> finalOreIngredients;

    protected final boolean verbose = false;

    public class InvalidReactionException extends Exception {};

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

    public NanoFactory(List<Reaction> reactionList) {
        this.reactionList = reactionList;
        splitReactionList();
        availableIngredients = new HashMap<>();
        reactionHistory = new ArrayList<>();
        setFinalOreIngredients();
    }

    protected void splitReactionList() {
        reactionListOre = new ArrayList<>();
        reactionListNonOre = new ArrayList<>();
        for (Reaction reaction : reactionList) {
            if (reaction.isOreReaction()) {
                reactionListOre.add(reaction);
            } else {
                reactionListNonOre.add(reaction);
            }
        }
        Collections.sort(reactionListOre, new Reaction());
    }

    protected void setFinalOreIngredients() {
        finalOreIngredients = new HashSet<>();
        for (Reaction reaction : reactionListOre) {
            finalOreIngredients.add(reaction.output.name);
        }
    }

    public void setReactionHistory(List<Reaction> reactionHistory) {
        this.reactionHistory = reactionHistory;
    }

    public int getReactionHistorySize() {
        return reactionHistory.size();
    }

    protected List<Reaction> copyReactionHistory() {
        List<Reaction> reactionHistory = new ArrayList<>();
        for (Reaction reaction : this.reactionHistory) {
            reactionHistory.add(reaction);
        }
        return reactionHistory;
    }

    public NanoFactory clone() {
        NanoFactory factory = new NanoFactory(reactionList);
        for (Ingredient ingredient : availableIngredients.values()) {
            factory.addIngredient(ingredient.clone());
        }
        factory.setReactionHistory(copyReactionHistory());
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
    public void executeReaction(Reaction reaction) throws InvalidReactionException {
        for (Ingredient ingredient : reaction.inputs) {
            removeIngredient(ingredient);
        }
        addIngredient(reaction.output);
        reactionHistory.add(reaction);
    }

    /**
     * For going from 1 AB => 3 A, 4 B
     * @param reaction
     * @throws InvalidReactionException
     */
    public void executeReactionReverse(Reaction reaction) throws InvalidReactionException {
        // Don't allow ORE reactions:
        // removeIngredient(reaction.output);
        // Allow ORE reactions:
        try {
            removeIngredient(reaction.output);
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
     * DFS, recursive
     * @return
     */
//    public boolean canMakeOneFuel() {
////        logVerbose(this);
//        if (containsExactlyOneFuel()) {
//            return true;
//        }
//        NanoFactory factory;
//        for (Reaction reaction : reactionList) {
//            factory = clone();
//            try {
//                factory.executeReaction(reaction);
//            } catch (InvalidReactionException e) {
//                continue;
//            }
//            if (factory.canMakeOneFuel()) {
//                return true;
//            }
//        }
//        return false;
//    }

//    public boolean containsExactlyOneFuel() {
//        return availableIngredients.containsKey(Ingredient.INGREDIENT_FUEL) &&
//                availableIngredients.get(Ingredient.INGREDIENT_FUEL).quantity == 1;
//    }

    /**
     * BFS/DFS, iterative using stack
     * @return
     */
    public Integer numOreNeededForOneFuel() {
        printReactionLists();
        printFinalOreIngredients();
        Integer minOreNeeded = null;
        Stack<NanoFactory> stack = new Stack<>();
//        Queue<NanoFactory> queue = new LinkedList<>();
        Stack<NanoFactory> stackOreOnly = new Stack<>();
        addIngredient(new Ingredient(1, Ingredient.INGREDIENT_FUEL));
        stack.push(this);
//        queue.add(this);
        NanoFactory factory, clone;
        int hash;
        Set<Integer> factoryStatesSeen = new HashSet<>();
        int maxDepth = 0;
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
            boolean executedReaction = false;
//            for (Reaction reaction : reactionList) {
            for (Reaction reaction : reactionListNonOre) {
                clone = factory.clone();
                logVerbose(clone.getReactionSizeBuffer() + "?" + reaction);
                try {
                    clone.executeReactionReverse(reaction);
                } catch (InvalidReactionException e) {
                    logVerbose(clone.getReactionSizeBuffer() + "->" + e);
                    continue;
                }
                executedReaction = true;
                logVerbose(clone.getReactionSizeBuffer(-1) + "->Y");
                stack.push(clone);
//                queue.add(clone);
            }
            if (! executedReaction) {
                stackOreOnly.push(factory);
            }
        }
        logInfo("Checking stackOreOnly (size=" + stackOreOnly.size() + ")");
        logInfo(stackOreOnly.peek().toString());
        while (! stackOreOnly.isEmpty()) {
            factory = stackOreOnly.pop();
//            hash = factory.hashCode();
//            if (factoryStatesSeen.contains(hash)) {
//                continue;
//            }
//            factoryStatesSeen.add(hash);
//            logVerbose(stack.size());
            logVerbose(factory.getReactionSizeBuffer() + factory);
            if (factory.getReactionHistorySize() > maxDepth) {
                maxDepth = factory.getReactionHistorySize();
                logInfo("maxDepth=" + maxDepth + " stackOreOnly.size()=" + stackOreOnly.size());
            }
            int numOre = factory.getNumOre();
            if (minOreNeeded != null && numOre > minOreNeeded) {
                continue;
            }
            if (factory.hasOnlyOre()) {
                logVerbose("HAS ONLY ORE!!! " + numOre + " of 'em!");
                if (minOreNeeded == null || numOre < minOreNeeded) {
                    minOreNeeded = numOre;
                }
            }
//            for (Reaction reaction : reactionList) {
            for (Reaction reaction : reactionListOre) {
                clone = factory.clone();
                logVerbose(clone.getReactionSizeBuffer() + "?" + reaction);
                try {
                    clone.executeReactionReverse(reaction);
                } catch (InvalidReactionException e) {
                    logVerbose(clone.getReactionSizeBuffer() + "->" + e);
                    continue;
                }
                logVerbose(clone.getReactionSizeBuffer() + "->Y");
                stackOreOnly.push(clone);
            }
        }
        return minOreNeeded;
    }

    public boolean hasOnlyOre() {
        return availableIngredients.size() == 1 && availableIngredients.containsKey(Ingredient.INGREDIENT_ORE);
    }

    protected boolean hasOnlyFinalOreIngredients() {
        for (String ingredientName : availableIngredients.keySet()) {
            if (! finalOreIngredients.contains(ingredientName)) {
                return false;
            }
        }
        return true;
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

    public void printReactionLists() {
        logVerbose("reactionListOre:");
        for (Reaction reaction : reactionListOre) {
            logVerbose("\t" + reaction);
        }
        logVerbose("reactionListNonOre:");
        for (Reaction reaction : reactionListNonOre) {
            logVerbose("\t" + reaction);
        }
    }

    public void printFinalOreIngredients() {
        logVerbose("finalOreIngredients:");
        for (String ingredientName : finalOreIngredients) {
            logVerbose("\t" + ingredientName);
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
