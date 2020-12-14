package day04;

import common.BaseSolution;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Solution04 extends BaseSolution {

    public static void main(String[] args) throws Exception {
        new Solution04().run();
        // new Solution04().test();
    }

    protected InputType getInputType() {
        return InputType.STRINGS;
    }

    /**
     *
     * byr (Birth Year)
     * iyr (Issue Year)
     * eyr (Expiration Year)
     * hgt (Height)
     * hcl (Hair Color)
     * ecl (Eye Color)
     * pid (Passport ID)
     * cid (Country ID)
     */
    public class Passport {
        private final String[] FIELDS_REQUIRED = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
        String[] eye_colors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        private final Set<String> VALID_EYE_COLORS = new HashSet<>(Arrays.asList(eye_colors));

        private Map<String, String> fields;

        public Passport(List<String> buffer) throws Exception {
            fields = new HashMap<>();
            for (String input : buffer) {
                String[] pieces = input.split(" ");
                for (String piece : pieces) {
                    if (piece.trim().length() == 0) {
                        continue;
                    }
                    String field = piece.split(":")[0];
                    if (field.trim().length() == 0) {
                        throw new Exception("Invalid field: " + field);
                    }
                    String value = piece.split(":")[1];
                    if (value.trim().length() == 0) {
                        throw new Exception("Invalid field " + field + " value:" + value);
                    }
                    // System.out.println("Field: " + field);
                    fields.put(field, value);
                }
            }
            // System.out.println("Fields: " + fields);
        }

        public boolean isValid(boolean strictCheck) {
            for (String field : FIELDS_REQUIRED) {
                if (! fields.containsKey(field)) {
                    return false;
                }
            }
            if (! strictCheck) {
                return true;
            }
            // byr (Birth Year) - four digits; at least 1920 and at most 2002.
            if (! validateYear("byr", 1920, 2002)) {
                return false;
            }
            // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
            if (! validateYear("iyr", 2010, 2020)) {
                return false;
            }
            // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
            if (! validateYear("eyr", 2020, 2030)) {
                return false;
            }
            // hgt (Height) - a number followed by either cm or in:
            //   If cm, the number must be at least 150 and at most 193.
            //   If in, the number must be at least 59 and at most 76.
            String hgt = fields.get("hgt");
            int pos = hgt.indexOf("cm");
            if (pos != -1) {
                int hgtValue = Integer.valueOf(hgt.substring(0, pos));
                if (hgtValue < 150 || hgtValue > 193) {
                    return false;
                }
            } else {
                pos = hgt.indexOf("in");
                if (pos == -1) {
                    // Missing "cm" or "in"
                    return false;
                }
                int hgtValue = Integer.valueOf(hgt.substring(0, pos));
                if (hgtValue < 59 || hgtValue > 76) {
                    return false;
                }
            }
            // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
            String hcl = fields.get("hcl");
            if (hcl.charAt(0) != '#') {
                return false;
            }
            hcl = hcl.substring(1);
            if (hcl.length() != 6) {
                return false;
            }
            for (int i = 0; i < hcl.length(); i++) {
                char hclChar = hcl.charAt(i);
                if (! ((hclChar >= '0' && hclChar <= '9') || (hclChar >= 'a' && hclChar <= 'f'))) {
                    return false;
                }
            }
            // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
            if (! VALID_EYE_COLORS.contains(fields.get("ecl"))) {
                return false;
            }
            // pid (Passport ID) - a nine-digit number, including leading zeroes.
            String pid = fields.get("pid");
            if (pid.length() != 9) {
                return false;
            }
            for (int i = 0; i < pid.length(); i++) {
                char pidChar = pid.charAt(i);
                if (pidChar < '0' || pidChar > '9') {
                    return false;
                }
            }
            // cid (Country ID) - ignored, missing or not.
            return true;
        }

        private boolean validateYear(String key, int min, int max) {
            int value = Integer.valueOf(fields.get(key));
            return min <= value && value <= max;
        }
    }

    @Override
    public Integer part1Int() {
        return runCheck(false);
    }

    @Override
    public Integer part2Int() {
        return runCheck(true);
    }

    private int runCheck(boolean strictCheck) {
        int numPassports = 0;
        int numValid = 0;
        int numInvalid = 0;
        List<String> buffer = new ArrayList<>();
        for (String input : inputStrs) {
            if (input.length() == 0) {
                if (buffer.size() > 0) {
                    Passport passport = null;
                    try {
                        passport = new Passport(buffer);
                        if (passport.isValid(strictCheck)) {
                            numValid++;
                        } else {
                            numInvalid++;
                        }
                        numPassports++;
                    } catch (Exception e) {
                        System.err.println(e);
                        numInvalid++;
                    }
                    buffer.clear();
                }
            }
            buffer.add(input);
        }
        System.out.println(numPassports + " passports / numValid=" + numValid + " numInvalid=" + numInvalid);
        return numValid;
    }

    /**
     * valid:
     * ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
     * byr:1937 iyr:2017 cid:147 hgt:183cm
     *
     * invalid:
     * iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884
     * hcl:#cfa07d byr:1929
     *
     * valid:
     * hcl:#ae17e1 iyr:2013
     * eyr:2024
     * ecl:brn pid:760753108 byr:1931
     * hgt:179cm
     *
     * invalid:
     * hcl:#cfa07d eyr:2025 pid:166559648
     * iyr:2011 ecl:brn hgt:59in
     */
    public void test() throws Exception {
        // First, valid
        // String[] buffer = {
        //         "ecl:gry pid:860033327 eyr:2020 hcl:#fffffd",
        //         "byr:1937 iyr:2017 cid:147 hgt:183cm"
        // };


        // Second, invalid
        // String[] buffer = {
        //         "iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884",
        //         "hcl:#cfa07d byr:1929"
        // };

        // Third, valid
        // String[] buffer = {
        //         "hcl:#ae17e1 iyr:2013",
        //         "eyr:2024",
        //         "ecl:brn pid:760753108 byr:1931",
        //         "hgt:179cm"
        // };

        // Fourth, invalid
        // String[] buffer = {
        //         "hcl:#cfa07d eyr:2025 pid:166559648",
        //         "iyr:2011 ecl:brn hgt:59in"
        // };

        // String[] buffer = new String[] {
        //         "pid:#850e8b eyr:2025 hgt:163in",
        //         "ecl:#71e9e2",
        //         "hcl:#623a2f"
        // };

        String[] buffer = new String[] {
                "iyr:2021 hcl:#ceb3a1 ecl:#d6db5a pid:185cm eyr:2020 cid:130 byr:2009"
        };
        System.out.println("Valid: " + new Passport(Arrays.asList(buffer)).isValid(false));
    }
}