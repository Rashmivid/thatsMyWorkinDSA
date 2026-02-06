#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

struct Cube {
    vector<vector<vector<char>>> faces;
    int n;
    
    Cube(int size) : n(size) {
        faces.resize(6, vector<vector<char>>(n, vector<char>(n)));
    }
    
    void rotateMatrixRight(vector<vector<char>>& mat) {
        vector<vector<char>> temp = mat;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[j][n-1-i] = temp[i][j];
    }
    
    void rotateMatrixLeft(vector<vector<char>>& mat) {
        vector<vector<char>> temp = mat;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[n-1-j][i] = temp[i][j];
    }
    
    void turnLeft() {
        vector<vector<char>> temp = faces[3];
        faces[3] = faces[5];
        faces[5] = faces[1];
        faces[1] = faces[4];
        faces[4] = temp;
        rotateMatrixRight(faces[2]);
        rotateMatrixLeft(faces[0]);
    }
    
    void turnRight() {
        vector<vector<char>> temp = faces[3];
        faces[3] = faces[4];
        faces[4] = faces[1];
        faces[1] = faces[5];
        faces[5] = temp;
        rotateMatrixLeft(faces[2]);
        rotateMatrixRight(faces[0]);
    }
    
    void rotateFront() {
        vector<vector<char>> temp = faces[3];
        faces[3] = faces[2];
        faces[2] = faces[1];
        faces[1] = faces[0];
        faces[0] = temp;
        rotateMatrixRight(faces[4]);
        rotateMatrixLeft(faces[5]);
    }
    
    void rotateBack() {
        vector<vector<char>> temp = faces[3];
        faces[3] = faces[0];
        faces[0] = faces[1];
        faces[1] = faces[2];
        faces[2] = temp;
        rotateMatrixLeft(faces[4]);
        rotateMatrixRight(faces[5]);
    }
    
    void rotateLeft() {
        vector<vector<char>> temp = faces[2];
        faces[2] = faces[5];
        faces[5] = faces[0];
        faces[0] = faces[4];
        faces[4] = temp;
        rotateMatrixLeft(faces[3]);
        rotateMatrixRight(faces[1]);
    }
    
    void rotateRight() {
        vector<vector<char>> temp = faces[2];
        faces[2] = faces[4];
        faces[4] = faces[0];
        faces[0] = faces[5];
        faces[5] = temp;
        rotateMatrixRight(faces[3]);
        rotateMatrixLeft(faces[1]);
    }
    
    void moveFaceRowCol(int faceIdx, int row, string dir) {
        row--;
        if (faceIdx == 3) { // front
            if (dir == "up") {
                vector<char> temp(n);
                for (int i = 0; i < n; i++) temp[i] = faces[3][row][i];
                for (int i = 0; i < n; i++) faces[3][row][i] = faces[0][row][i];
                for (int i = 0; i < n; i++) faces[0][row][i] = faces[1][n-1-row][n-1-i];
                for (int i = 0; i < n; i++) faces[1][n-1-row][n-1-i] = faces[2][row][i];
                for (int i = 0; i < n; i++) faces[2][row][i] = temp[i];
            } else if (dir == "down") {
                vector<char> temp(n);
                for (int i = 0; i < n; i++) temp[i] = faces[3][row][i];
                for (int i = 0; i < n; i++) faces[3][row][i] = faces[2][row][i];
                for (int i = 0; i < n; i++) faces[2][row][i] = faces[1][n-1-row][n-1-i];
                for (int i = 0; i < n; i++) faces[1][n-1-row][n-1-i] = faces[0][row][i];
                for (int i = 0; i < n; i++) faces[0][row][i] = temp[i];
            } else if (dir == "left") {
                vector<char> temp(n);
                for (int i = 0; i < n; i++) temp[i] = faces[3][i][row];
                for (int i = 0; i < n; i++) faces[3][i][row] = faces[5][i][row];
                for (int i = 0; i < n; i++) faces[5][i][row] = faces[1][n-1-i][n-1-row];
                for (int i = 0; i < n; i++) faces[1][n-1-i][n-1-row] = faces[4][i][row];
                for (int i = 0; i < n; i++) faces[4][i][row] = temp[i];
            } else if (dir == "right") {
                vector<char> temp(n);
                for (int i = 0; i < n; i++) temp[i] = faces[3][i][row];
                for (int i = 0; i < n; i++) faces[3][i][row] = faces[4][i][row];
                for (int i = 0; i < n; i++) faces[4][i][row] = faces[1][n-1-i][n-1-row];
                for (int i = 0; i < n; i++) faces[1][n-1-i][n-1-row] = faces[5][i][row];
                for (int i = 0; i < n; i++) faces[5][i][row] = temp[i];
            }
        }
        // Implement other faces similarly...
    }
    
    bool isSolved(int faceIdx) {
        char c = faces[faceIdx][0][0];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (faces[faceIdx][i][j] != c) return false;
        return true;
    }
    
    bool hasAnySolved() {
        for (int i = 0; i < 6; i++)
            if (isSolved(i)) return true;
        return false;
    }
};

void execute(Cube& cube, const string& inst) {
    if (inst == "turn left") cube.turnLeft();
    else if (inst == "turn right") cube.turnRight();
    else if (inst == "rotate front") cube.rotateFront();
    else if (inst == "rotate back") cube.rotateBack();
    else if (inst == "rotate left") cube.rotateLeft();
    else if (inst == "rotate right") cube.rotateRight();
    else {
        istringstream iss(inst);
        string side, dir;
        int idx;
        iss >> side >> idx >> dir;
        int faceIdx = (side == "base") ? 0 : (side == "back") ? 1 : 
                      (side == "top") ? 2 : (side == "front") ? 3 :
                      (side == "left") ? 4 : 5;
        cube.moveFaceRowCol(faceIdx, idx, dir);
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    
    Cube orig(n);
    for (int f = 0; f < 6; f++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> orig.faces[f][i][j];
    cin.ignore();
    
    vector<string> insts(k);
    for (int i = 0; i < k; i++)
        getline(cin, insts[i]);
    
    // Check without faulty - skip one instruction
    for (int skip = 0; skip < k; skip++) {
        Cube c = orig;
        for (int i = 0; i < k; i++)
            if (i != skip) execute(c, insts[i]);
        if (c.hasAnySolved()) {
            cout << insts[skip] << endl;
            return 0;
        }
    }
    
    // Check with one faulty cube - collect all colors
    set<char> allColors;
    for (int f = 0; f < 6; f++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                allColors.insert(orig.faces[f][i][j]);
    
    // Try fixing one position
    for (int f = 0; f < 6; f++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                char origColor = orig.faces[f][i][j];
                for (char newColor : allColors) {
                    if (newColor == origColor) continue;
                    
                    Cube fixed = orig;
                    fixed.faces[f][i][j] = newColor;
                    
                    for (int skip = 0; skip < k; skip++) {
                        Cube c = fixed;
                        for (int idx = 0; idx < k; idx++)
                            if (idx != skip) execute(c, insts[idx]);
                        if (c.hasAnySolved()) {
                            cout << "Faulty" << endl;
                            cout << insts[skip] << endl;
                            return 0;
                        }
                    }
                }
            }
        }
    }
    
    cout << "Not Possible" << endl;
    return 0;
}