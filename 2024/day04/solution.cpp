
#include <iostream>
#include <vector>
#include <string>

using namespace std;


int countSubstringOccurrences(const vector<string>& strings, const string& substring) {
    int count = 0;

    // Iterate through each string in the vector
    for (const auto& str : strings) {
        size_t pos = str.find(substring); // Find the first occurrence of substring
        while (pos != string::npos) {    // Keep finding until no more occurrences
            // cout << pos << " - " << str << endl;
            count++;
            pos = str.find(substring, pos + 1); // Move to the next position
        }
    }

    return count;
}

int solution1() {
    vector<string> inputStrings;
    vector<string> allStrings;
    string line;

    string substring = "XMAS";
    int occurrences = 0;

    while (getline(cin, line)) {
        inputStrings.push_back(line);
        // Get all forward strings while we're here
        allStrings.push_back(line);
        // And the backwards strings
        // Note we can do this because line is mutable, and the value of line
        // put into those vectors above was copied, so not "by reference"
        reverse(line.begin(), line.end());
        allStrings.push_back(line);
    }
    int sectionOccurrences = countSubstringOccurrences(allStrings, substring);
    if (sectionOccurrences > 0) {
        // cout << "forwards or backwards" << endl;
        // cout << sectionOccurrences << endl << endl;
        allStrings.clear();
        occurrences += sectionOccurrences;
    }

    // Find the maximum number of columns (length of the longest string)
    int maxCols = 0;
    for (const auto& str : inputStrings) {
        maxCols = max(maxCols, static_cast<int>(str.size()));
    }

    // Create a 2D char array
    vector<vector<char>> charArray(inputStrings.size(), vector<char>(maxCols, '\0'));

    // Fill the 2D array with the input strings
    for (size_t i = 0; i < inputStrings.size(); ++i) {
        for (size_t j = 0; j < inputStrings[i].size(); ++j) {
            charArray[i][j] = inputStrings[i][j];
        }
    }

    int numRows = charArray.size();
    // Going to assume this is > 0
    int numCols = charArray[0].size();

    // Get all columns
    for (size_t col = 0; col < numCols; ++col) {
        string colString;
        for (size_t row = 0; row < numRows; ++row) {
            colString += charArray[row][col];
        }
        allStrings.push_back(colString);
        // Down to up also
        reverse(colString.begin(), colString.end());
        allStrings.push_back(colString);
    }
    sectionOccurrences = countSubstringOccurrences(allStrings, substring);
    if (sectionOccurrences > 0) {
        // cout << "cols" << endl;
        // cout << sectionOccurrences << endl << endl;
        allStrings.clear();
        occurrences += sectionOccurrences;
    }

    // Get all diagonals going down-right or up-left

    // Step 1: Traverse the left-most column from bottom to top
    for (int row = numRows - 1; row >= 0; --row) {
        string diagString;
        int diagRow = row;
        int diagCol = 0;
        while (diagRow < numRows && diagCol < numCols) {
            diagString += charArray[diagRow][diagCol];
            diagRow++;
            diagCol++;
        }
        allStrings.push_back(diagString);
        // Down to up also
        if (diagString.size() > 1) {
            reverse(diagString.begin(), diagString.end());
            allStrings.push_back(diagString);
        }
    }
    sectionOccurrences = countSubstringOccurrences(allStrings, substring);
    if (sectionOccurrences > 0) {
        // cout << "diags pointing down and to the right, left col" << endl;
        // cout << sectionOccurrences << endl << endl;
        allStrings.clear();
        occurrences += sectionOccurrences;
    }

    // Step 2: Traverse the top row (top-left to top-right)
    for (int col = 1; col < numCols; col++) {
        string diagString;
        int diagRow = 0;
        int diagCol = col;
        while (diagRow < numRows && diagCol < numCols) {
            diagString += charArray[diagRow][diagCol];
            diagRow++;
            diagCol++;
        }
        allStrings.push_back(diagString);
        // Down to up also
        if (diagString.size() > 1) {
            reverse(diagString.begin(), diagString.end());
            allStrings.push_back(diagString);
        }
    }
    sectionOccurrences = countSubstringOccurrences(allStrings, substring);
    if (sectionOccurrences > 0) {
        // cout << "diags pointing down and to the right, top row" << endl;
        // cout << sectionOccurrences << endl << endl;
        allStrings.clear();
        occurrences += sectionOccurrences;
    }

    // Get all diagonals going down-left or up-right

    // Step 1: Traverse the right-most column from bottom to top
    for (int row = numRows - 1; row >= 0; --row) {
        string diagString;
        int diagRow = row;
        int diagCol = numCols - 1;
        while (diagRow < numRows && diagCol >= 0) {
            diagString += charArray[diagRow][diagCol];
            diagRow++;
            diagCol--;
        }
        allStrings.push_back(diagString);
        // Down to up also
        if (diagString.size() > 1) {
            reverse(diagString.begin(), diagString.end());
            allStrings.push_back(diagString);
        }
    }
    sectionOccurrences = countSubstringOccurrences(allStrings, substring);
    if (sectionOccurrences > 0) {
        // cout << "diags pointing down and to the left, right col" << endl;
        // cout << sectionOccurrences << endl << endl;
        allStrings.clear();
        occurrences += sectionOccurrences;
    }

    // Step 2: Traverse the top row (top-right to top-left)
    for (int col = numCols - 2; col >= 0; col--) {
        string diagString;
        int diagRow = 0;
        int diagCol = col;
        while (diagRow < numRows && diagCol >= 0) {
            diagString += charArray[diagRow][diagCol];
            diagRow++;
            diagCol--;
        }
        // cout << "diagStr " << diagString << endl;
        allStrings.push_back(diagString);
        // Down to up also
        if (diagString.size() > 1) {
            reverse(diagString.begin(), diagString.end());
            allStrings.push_back(diagString);
        }
    }
    sectionOccurrences = countSubstringOccurrences(allStrings, substring);
    if (sectionOccurrences > 0) {
        // cout << "diags pointing down and to the left, top row" << endl;
        // cout << sectionOccurrences << endl << endl;
        allStrings.clear();
        occurrences += sectionOccurrences;
    }

    // for (const auto& str : allStrings) {
    //     cout << str << endl;
    // }

    return occurrences;
}

int solution2() {
    return 0;
}

int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}

