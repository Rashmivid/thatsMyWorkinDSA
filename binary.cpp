#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <algorithm>
#include <functional>

using namespace std;

string extract7Segment(vector<string>& lines, int col) {
    string segment = "";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int pos = col * 3 + j;
            if (pos < lines[i].length()) {
                segment += (lines[i][pos] == ' ') ? '0' : '1';
            }
        }
    }
    return segment;
}

string binaryAND(string a, string b) {
    int maxLen = max(a.length(), b.length());
    while (a.length() < maxLen) a = "0" + a;
    while (b.length() < maxLen) b = "0" + b;
    
    string result = "";
    for (int i = 0; i < maxLen; i++) {
        result += ((a[i] == '1' && b[i] == '1') ? '1' : '0');
    }
    return result;
}

string binaryOR(string a, string b) {
    int maxLen = max(a.length(), b.length());
    while (a.length() < maxLen) a = "0" + a;
    while (b.length() < maxLen) b = "0" + b;
    
    string result = "";
    for (int i = 0; i < maxLen; i++) {
        result += ((a[i] == '1' || b[i] == '1') ? '1' : '0');
    }
    return result;
}

string binaryNOT(string a) {
    string result = "";
    for (char c : a) {
        result += (c == '1') ? '0' : '1';
    }
    return result;
}

long long binaryToDecimal(string binary) {
    long long result = 0;
    for (char c : binary) {
        result = result * 2 + (c - '0');
    }
    return result;
}

string evaluate(vector<string>& tokens, map<string, string>& patterns) {
    // Convert tokens to binary
    vector<string> binaryTokens;
    for (string& token : tokens) {
        if (token == "||" || token == "&&" || token == "!" || token == "(" || token == ")") {
            binaryTokens.push_back(token);
        } else {
            // It's a number - convert to binary
            string binary = "";
            for (char c : token) {
                binary += patterns[string(1, c)];
            }
            binaryTokens.push_back(binary);
        }
    }
    
    // Evaluate with precedence: () > ! > || > &&
    // First handle brackets and NOT
    stack<int> brackets;
    
    function<string(int, int)> evalRange = [&](int start, int end) -> string {
        vector<string> tokens;
        for (int i = start; i <= end; i++) {
            tokens.push_back(binaryTokens[i]);
        }
        
        // Handle brackets first
        while (true) {
            int openIdx = -1;
            for (int i = 0; i < tokens.size(); i++) {
                if (tokens[i] == "(") openIdx = i;
                if (tokens[i] == ")") {
                    string result = evalRange(openIdx + 1, i - 1);
                    tokens.erase(tokens.begin() + openIdx, tokens.begin() + i + 1);
                    tokens.insert(tokens.begin() + openIdx, result);
                    break;
                }
            }
            if (openIdx == -1) break;
        }
        
        // Handle NOT
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "!") {
                string result = binaryNOT(tokens[i + 1]);
                tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
                tokens.insert(tokens.begin() + i, result);
                i--;
            }
        }
        
        // Handle OR
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "||") {
                string result = binaryOR(tokens[i - 1], tokens[i + 1]);
                tokens.erase(tokens.begin() + i - 1, tokens.begin() + i + 2);
                tokens.insert(tokens.begin() + i - 1, result);
                i--;
            }
        }
        
        // Handle AND
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "&&") {
                string result = binaryAND(tokens[i - 1], tokens[i + 1]);
                tokens.erase(tokens.begin() + i - 1, tokens.begin() + i + 2);
                tokens.insert(tokens.begin() + i - 1, result);
                i--;
            }
        }
        
        return tokens[0];
    };
    
    return evalRange(0, binaryTokens.size() - 1);
}

int main() {
    vector<string> digitLines(3), opLines(3), exprLines(3);
    
    getline(cin, digitLines[0]);
    getline(cin, digitLines[1]);
    getline(cin, digitLines[2]);
    
    getline(cin, opLines[0]);
    getline(cin, opLines[1]);
    getline(cin, opLines[2]);
    
    getline(cin, exprLines[0]);
    getline(cin, exprLines[1]);
    getline(cin, exprLines[2]);
    
    // Extract digit patterns
    map<string, string> segmentToChar;
    map<string, string> charToBinary;
    
    for (int i = 0; i < 10; i++) {
        string seg = extract7Segment(digitLines, i);
        segmentToChar[seg] = to_string(i);
        charToBinary[to_string(i)] = seg;
    }
    
    // Extract operator patterns
    string orSeg = extract7Segment(opLines, 0);
    string andSeg = extract7Segment(opLines, 1);
    string notSeg = extract7Segment(opLines, 2);
    string openSeg = extract7Segment(opLines, 3);
    string closeSeg = extract7Segment(opLines, 4);
    
    segmentToChar[orSeg] = "||";
    segmentToChar[andSeg] = "&&";
    segmentToChar[notSeg] = "!";
    segmentToChar[openSeg] = "(";
    segmentToChar[closeSeg] = ")";
    
    // Parse expression
    vector<string> tokens;
    int cols = exprLines[0].length() / 3;
    
    for (int i = 0; i < cols; i++) {
        string seg = extract7Segment(exprLines, i);
        if (segmentToChar.count(seg)) {
            string ch = segmentToChar[seg];
            if (ch == "||" || ch == "&&" || ch == "!" || ch == "(" || ch == ")") {
                tokens.push_back(ch);
            } else {
                // It's a digit
                if (!tokens.empty() && tokens.back() != "||" && tokens.back() != "&&" && 
                    tokens.back() != "!" && tokens.back() != "(" && tokens.back() != ")") {
                    tokens.back() += ch;
                } else {
                    tokens.push_back(ch);
                }
            }
        }
    }
    
    string result = evaluate(tokens, charToBinary);
    cout << binaryToDecimal(result) << endl;
    
    return 0;
}