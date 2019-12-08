package common;


public class Instruction {
    public final static int PARAMETER_MODE_POSITION = 0;
    public final static int PARAMETER_MODE_IMMEDIATE = 1;

    public final static int PARAMETER_MODE_DEFAULT = PARAMETER_MODE_POSITION;

    public int opcode;

    public int modeParam1 = PARAMETER_MODE_DEFAULT;
    public int modeParam2 = PARAMETER_MODE_DEFAULT;
    public int modeParam3 = PARAMETER_MODE_DEFAULT;

    public Instruction(int value) {
        parseValue(value);
    }

    public String toString() {
        return "opcode=" + opcode +
                " modeParam1=" + modeParam1 +
                " modeParam2=" + modeParam2 +
                " modeParam3=" + modeParam3;
    }

    protected void parseValue(int value) {
        String valueStr = String.valueOf(value);
        if (valueStr.length() == 1 || valueStr.length() == 2) {
            opcode = value;
            return;
        }
        opcode = Integer.parseInt(valueStr.substring(valueStr.length() - 2));
        modeParam1 = Integer.parseInt(valueStr.substring(valueStr.length() - 3, valueStr.length() - 2));
        if (valueStr.length() == 3) {
            return;
        }
        modeParam2 = Integer.parseInt(valueStr.substring(valueStr.length() - 4, valueStr.length() - 3));
        if (valueStr.length() == 4) {
            return;
        }
        modeParam3 = Integer.parseInt(valueStr.substring(valueStr.length() - 5, valueStr.length() - 4));
    }

    public static void main(String[] args) {
        System.out.println(new Instruction(Integer.parseInt(args[0])));
    }
}
