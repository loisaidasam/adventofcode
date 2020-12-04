package common;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
 * Helper class for reading from the current directory's input.txt file
 */
public class InputReader {
    private BufferedReader reader;
    private boolean reading = true;

    public InputReader(String filename) {
        try {
            reader = new BufferedReader(new FileReader(filename));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public String next() {
        if (reader == null || ! reading) {
            return null;
        }
        String line = null;
        try {
            line = reader.readLine();
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
        if (line == null) {
            reading = false;
            try {
                reader.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return line;
    }
}
