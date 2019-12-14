package day14;

import java.util.ArrayList;
import java.util.List;

public class Reaction {
    public final List<Ingredient> inputs;
    public final Ingredient output;

    public Reaction(List<Ingredient> inputs, Ingredient output) {
        this.inputs = inputs;
        this.output = output;
    }

    public static Reaction parseReactionString(String reactionString) throws Exception {
        String[] pieces = reactionString.split(" ");
        List<Ingredient> inputs = new ArrayList<>();
        Ingredient output;
        for (int i = 0; i < pieces.length; i++) {
            if (pieces[i].equals("=>")) {
                output = new Ingredient(Integer.parseInt(pieces[i + 1]), pieces[i + 2]);
                return new Reaction(inputs, output);
            }
            inputs.add(new Ingredient(Integer.parseInt(pieces[i]), pieces[i + 1].replace(",", "")));
            i++;
        }
        throw new Exception("Invalid reaction string");
    }

    public static List<Reaction> parseReactionStrings(List<String> reactionStrings) throws Exception {
        List<Reaction> reactionList = new ArrayList<>();
        for (String reactionString : reactionStrings) {
            reactionList.add(parseReactionString(reactionString));
        }
        return reactionList;
    }

    public static void main(String[] args) throws Exception {
        String[] reactionStrings = new String[] {
                "10 ORE => 10 A",
                "1 ORE => 1 B",
                "7 A, 1 B => 1 C",
                "7 A, 1 C => 1 D",
                "7 A, 1 D => 1 E",
                "7 A, 1 E => 1 FUEL",
        };
        for (String reactionString : reactionStrings) {
            System.out.println(parseReactionString(reactionString));
        }
    }

    @Override
    public String toString() {
        return "Reaction{" +
                "inputs=" + inputs +
                ", output='" + output + '\'' +
                '}';
    }
}
