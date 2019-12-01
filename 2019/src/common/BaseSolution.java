package common;

public class BaseSolution {

    /**
     * via https://stackoverflow.com/a/7603444
     */
    protected static String getCurrentDir() {
        return System.getProperty("user.dir");
    }

    protected static String getInputFilename(String dayName) {
        return getCurrentDir() + "/src/" + dayName + "/input.txt";
    }
}
